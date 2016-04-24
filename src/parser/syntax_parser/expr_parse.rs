use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_parser::synpar_util::*;

struct Precedence {
	level: u32,
	assoc: Assoc // associativity
}

#[derive(PartialEq)]
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
					MathOp::Dice => (5, Assoc::Non),
					MathOp::Plus => (1, Assoc::Left),
					MathOp::Minus => (1, Assoc::Left),
					MathOp::Mul => (3, Assoc::Left),
					MathOp::Div => (3, Assoc::Left),
					MathOp::Pow => (4, Assoc::Right),
				},
			AnyOp::Cmp(_) => (2, Assoc::Non), // NOTE: these are allowed only in the predicates (for now)
			AnyOp::LogConn(_) => (1, Assoc::Left),
			AnyOp::Unary(x) =>
				match x {
					UnaryOp::Neg => (2, Assoc::Right),
					UnaryOp::Not => (3, Assoc::Right),
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
		// since we know our input isn't empty yet this should be a safe unwrap
		let pair = pair.unwrap();

		let tk = pair.0.clone();
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
			Lexeme::Id(x) => {
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

				let f = |&o| {
					let prec2 = get_op_precedence(o);
					!(
						(prec.assoc == Assoc::Left && prec.level <= prec2.level) ||
						(prec.assoc == Assoc::Right && prec.level < prec2.level)
					)
				};

				// the index op has to be inserted
				let insert_index = operator_stack.iter().rev().rposition(f);
				let insert_index = insert_index.unwrap_or(0); // if none was found use 0

				operator_stack.insert(insert_index, op);
			},
			Lexeme::End => {
				// we found our end token, assume it was the last
				assert!(input_clone.is_empty());
			},
			_ => unimplemented!(), // TODO: implement the rest
		}
	};
	unimplemented!();
}
