use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_parser::synpar_util::*;

struct Precedence {
	level: u32,
	assoc: Assoc // associativity
}

#[derive(Eq)]
enum Assoc {
	Non, //non-associative, remove?
	Left,
	Right
}

fn get_op_precedence(op: AnyOp) -> Precedence {
	let (lvl, assoc) =
		match op {
			AnyOp::Math(x) =>
				match x {
					Dice => (5, Assoc::Non),
					Plus => (1, Assoc::Left),
					Minus => (1, Assoc::Left),
					Mul => (3, Assoc::Left),
					Div => (3, Assoc::Left),
					Pow => (4, Assoc::Right),
				},
			AnyOp::Cmp(_) => (2, Assoc::Non), // NOTE: these are allowed only in the predicates (for now)
			AnyOp::LogConn(_) => (1, Assoc::Left),
			AnyOp::Unary(x) =>
				match x {
					Neg => (2, Assoc::Right),
					Not => (3, Assoc::Right),
				}, // this might need to be tweaked
			AnyOp::FunCall(_) => (0, Assoc::Non), // irrelevant
		};
	Precedence{ level: lvl, assoc: assoc}
}

/// Parses expressions using the Shunting-yard algorithm
pub fn parse_expr(input: InType) -> ParseResult<Expr> {
	let mut operator_stack	= Vec::new();
	let mut operand_stack	= Vec::new();

	let mut input_clone = input.clone();

	// read while there is unread input
	while !input_clone.is_empty() {
		// read a token
		let pair = input_clone.split_first_mut();
		let tk = pair.0;
		input_clone = pair.1;

		// check the token
		match tk {
			Lexeme::IntLit(x) => {
				let to_push = Expr::Val(Value::Num(NumType::Int(x)));
				// TODO: ^^^^^ make this look not horrible
				operand_stack.push(to_push);
			},
			Lexeme::RealLit(x) => {
				let to_push = Expr::Val(Value::Num(NumType::Real(x)));
				operand_stack.push(to_push);
			},
			Lexeme::StrLit(x) => {
				let to_push = Expr::Val(Value::Str(x));
				operand_stack.push(to_push);
			},
			Lexeme::Ident(x) => {
				// check if we have a function call
				if input_clone[0] == Lexeme::LeftParen {
					unimplemented!();
				}
				else {
					operand_stack.push(Expr::Var(x));
				}
			},
			Lexeme::Op(x) => {
				let op = AnyOp::Math(x);
				let prec = get_op_precedence(op);

				let f = |o| {
					let prec2 = get_op_precedence(o);
					!(
						(prec.assoc == Assoc::Left && prec.level <= prec2.level) ||
						(prec.assoc == Assoc::Right && prec.level < prec2.level)
					)
				};

				// the index op has to be inserted
				let insert_index = operator_stack.iter().rev().rposition(f);
				let insert_index = insert_index.or(0); // if none was found use 0

				operator_stack.insert(op, insert_index);
			},
		}
	}
}



/// Parses a parenthesized expression
fn parse_paren_expr(input: InType) -> ParseResult<Expr> {
	let ( (), input) = try!(expect_token!(input, Lexeme::LeftParen));

	let mut partial_i = Vec::new();

	// finds the end of the parenthesis expression by counting left parentheses - right parentheses
	let paren_count = 1;
	for t in input {
		if *t == Lexeme::LeftParen {
			paren_count += 1;
		}
		else if *t == Lexeme::RightParen {
			paren_count -= 1;
			assert!(paren_count > 0);
			if paren_count == 0 {
				break;
			}
		}
		// note: the ending right paren is not pushed
		partial_i.push(*t);
	}
	if paren_count != 0 {
		return Err(0); // TODO
	}

	parse_expr(partial_i.as_slice())
}

/// Parses value negation.
fn parse_negation(input: InType) -> ParseResult<Expr> {
	match consume_token(input) {
		Ok( (Lexeme::Op(MathOp::Minus), input) ) => {
			let exp = try!(parse_expr(input));
			Ok(Expr::Unary{ op: UnaryOp::Neg, right: Box::new(exp)})
		},
		Ok(_) => Err(1),
		Err(e) => Err(e),
	}
}

/// Parses infix mathematical operations.
fn parse_infix_op(input: InType, precedence: u8) -> ParseResult<Expr> {
	// find the operator
	//let (partial_input, input) = input.split(find_token!(input, Lexeme::Op()) );
	let left_input = Vec::new();
	let op_lex: Lexeme;
	let right_input = Vec::new();

	// I think we can assume the

	// parse the left operand
	let left = try!(parse_expr_prec(left_input.as_slice(), precedence));

	// parse the operator
	let op = match op_lex {
		Lexeme::Op(ref tk @ MathOp::Plus) |
		Lexeme::Op(ref tk @ MathOp::Minus)
			if precedence <= 1 =>
		{
			tk.clone()
		},

		_ => return Err(54)
	};

	// parse the right operand
	let right = try!(parse_expr_prec(right_input.as_slice(), precedence));

	Ok( Expr::Math{op: op, left: Box::new(left), right: Box::new(right)} )
}

fn parse_var(input: InType) -> ParseResult<Expr> {
	map_output(expect_token!(input, Lexeme::Id(Ident)), &Expr::Var)
}

/// Parses a numerical literal or a string literal
fn parse_literal(input: InType) -> ParseResult<Expr> {
	map_output(
		match consume_token(input) {
			Ok( (Lexeme::IntLit(n), i) ) =>  Ok( Value::Num(NumType::Int(n)) ),
			Ok( (Lexeme::RealLit(f), i) ) => Ok( Value::Num(NumType::Real(f)) ),
			Ok( (Lexeme::StrLit(s), i) ) =>  Ok( Value::Str(s) ),
			_ => Err(6) // TODO: fix
		},
		&Expr::Val
	)
}

/// Parses a list, which is a comma separated list or a Range
/// Calls parse_expr several times.
fn parse_list(input: InType) -> ParseResult<Expr> {
	// parse either a list or range
	let (to_ret, input) =
		match expect_token!(input, Lexeme::LeftBracket) {
			Ok( ( (), input) ) => {
				try!(parse_cs_list(input).or(parse_range(input)))
			},
			Err(e) => return Err(e)
		}
	;
	// now let's see if we can find the closing bracket
	// note: this can fail only if we parsed a range, since comma separated list fails if it
	// doesn't end on a right bracket.
	match expect_token!(input, Lexeme::RightBracket) {
		Ok( ( (), input)) => Ok( (Expr::List(to_ret), input) ),
		Err(e) => Err(e)
	}
}

/// Parses a comma separated, bracket delimited list.
/// Does NOT consume the delimiting bracket.
/// The function assumes that the first square bracket has been consumed.
fn parse_cs_list(input: InType) -> ParseResult<ExprList> {
	// if we have an empty list
	if let Ok(Lexeme::RightBracket) = peek_token(input) {
		return Ok( (ExprList::Vector(Vec::new()), input) );
	}

	let mut expr_vec = Vec::new();
	let mut input = input;

	// check the first item
	// this is done so that we can match the rest with a comma following an expression (, exp)
	match parse_expr(input) {
		Ok( (exp, i) ) => {
			// ok add a new item
			expr_vec.push(exp);
			// and update input
			input = i;
		},
		// it shouldn't be an empty list since that case has been handled above
		Err(e) => return Err(e)
	}

	// loop through the rest of the lexemes until you find the right bracket
	loop {
		match peek_token(input) {
			Ok(Lexeme::RightBracket) => break, // We got all
			Ok( Lexeme::Comma ) => { // comma found
				// ignore comma
				// this should be a safe unwrap, since we peeked that there was a comma already
				match parse_expr(ignore_token(input).unwrap() ) {
					Ok( (exp, i) ) => { // expression found
						// add a new item
						expr_vec.push(exp);
						// and update input
						input = i;
					},
					Err(e) => return Err(e) // no expression found
				}
			},
			Ok( _ ) => return Err(7), // weird token
			Err(e) => return Err(e) // no lexeme found, the input is empty
		}
	}
	return Ok( (ExprList::Vector(expr_vec), input) );
}

// / Parses a range of the form a..c, or a,b..c.
// / Does NOT expect any delimiting characters.
fn parse_range(input: InType) -> ParseResult<ExprList> {
	// this function does a lot of moving/shadowing of the variable input

	// parse the start
	let (exp_start, input) = try!(parse_expr(input));

	// make a mutable input
	let mut input = input;
	// parse the step
	let step_exp_opt =
		match peek_token(input) {
			// a step expression found
			Ok(Lexeme::Comma) => {
				Some(
					// ignore comma
					match parse_expr(ignore_token(input).unwrap() ) {
						Ok( (exp, i) ) => { // expression found
							// update input
							input = i;
							// return expression
							exp
						},
						Err(e) => return Err(e) // no expression found
					}
				)
			},
			// use the default step value.
			Ok( _ ) => None, //Expr::Val(Value::Num(NumType::Int(1))),
			Err(e) => return Err(e) // peek failed, input is empty probably
		}
	;
	// ignore the ellipsis token ('..')
	let ((), input) = try!(expect_token!(input, Lexeme::RangeEllipsis));

	// parse the end
	let (exp_end, input) = try!(parse_expr(input));

	// return our range
	Ok::<(ExprList, InType), ErrType>(
		(
			ExprList::Range {
				start: Box::new(exp_start),
				step: step_exp_opt.map(Box::new),
				end: Box::new(exp_end)
			},
			input
		)
	)
}
