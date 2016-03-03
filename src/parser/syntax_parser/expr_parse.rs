use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_parser::synpar_util::*;

pub fn parse_expr(input: InType) -> ParseOutput<Expr, InType> {
	Err(0)
	 .or(parse_paren_expr(input))
	// .or(parse_kwexpr(input))
	// .or(parse_op(input))
	// .or(parse_funcall(input))
	.or(parse_var(input))
	.or(parse_literal(input))
	.or(parse_list(input))
	// .or(parse_filter(input))
}

fn parse_paren_expr(input: InType) -> ParseOutput<Expr, InType> {
	let ( (), input) = try!(expect_token!(input, Lexeme::LeftParen));
	let (to_ret, input) = try!(parse_expr(input));
	let ( (), input) = try!(expect_token!(input, Lexeme::RightParen));
	Ok( (to_ret, input) )
}

fn parse_var(input: InType) -> ParseOutput<Expr, InType> {
	map_output(expect_token!(input, Lexeme::Id(Ident)), &Expr::Var)
}

/// Parses a numerical literal or a string literal
fn parse_literal(input: InType) -> ParseOutput<Expr, InType> {
	map_output(
		match consume_token(input) {
			Ok( (Lexeme::IntLit(n), i) ) =>  Ok( (Value::Num(NumType::Int(n)), i) ),
			Ok( (Lexeme::RealLit(f), i) ) => Ok( (Value::Num(NumType::Real(f)), i) ),
			Ok( (Lexeme::StrLit(s), i) ) =>  Ok( (Value::Str(s), i) ),
			_ => Err(6) // TODO: fix
		},
		&Expr::Val
	)
}

/// Parses a list, which is a comma separated list or a Range
/// Calls parse_expr several times.
fn parse_list(input: InType) -> ParseOutput<Expr, InType> {
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
fn parse_cs_list(input: InType) -> ParseOutput<ExprList, InType> {
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
fn parse_range(input: InType) -> ParseOutput<ExprList, InType> {
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
