use std::collections::HashMap;
use std::hash::Hash;

//use parser::parse_util::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_types::*;

pub type InType<'a> = &'a [Lexeme];

#[derive(Debug, PartialEq, Clone, Copy)]
pub enum Side {
	Left,
	Right
}

#[derive(Debug, PartialEq, Clone, Copy)]
#[allow(dead_code)] // TODO: remove when all the variants are used somewhere
pub enum ArgInfo {
	/// Operators with a singular argument
	/// The argument tells at which side of the argument the operator must be in.
	Unary(Side),
	/// Operators with two arguments
	Binary,
	/// For binary operators that can be used as unary, like substraction/negation.
	/// The argument tells at which side of the argument the operator must be in.
	AllowUnary(Side),
	/// For special operators that can have 0-2 arguments.
	/// For the dice operator.
	AllowNullary,
	// / For function calls etc
	//Variable,
}

/// Information associated with an operation
#[derive(Debug, Clone, Copy)]
pub struct OpInfo {
	/// Precedence level
	pub level: i32,
	/// associativity
	pub assoc: Side,
	// Argument info
	pub arg_info: ArgInfo,
}

impl OpInfo {
	fn new(precedence_level: i32, associativity: Side, argument_info: ArgInfo) -> Self {
		OpInfo {
			level: precedence_level,
			assoc: associativity,
			arg_info: argument_info
		}
	}
}

lazy_static! {
	pub static ref OP_INFOS: HashMap<InfixOp, OpInfo> =
		vec2map(vec![
			(InfixOp::Plus,  OpInfo::new(1, Side::Left, ArgInfo::AllowUnary(Side::Left)) ),
			(InfixOp::Minus, OpInfo::new(1, Side::Left, ArgInfo::AllowUnary(Side::Left)) ),
			(InfixOp::Mul, OpInfo::new(3, Side::Left, ArgInfo::Binary)),
			(InfixOp::Div, OpInfo::new(3, Side::Left, ArgInfo::Binary)),
			(InfixOp::Pow, OpInfo::new(4, Side::Right, ArgInfo::Binary)),
			(InfixOp::Dice, OpInfo::new(5, Side::Left, ArgInfo::AllowNullary))
		]);
}

/// The smallest existing precedence level.
pub const PREC_MIN: i32 = 1;
/// The largest existing precedence level.
pub const PREC_MAX: i32 = 5;


#[derive(Debug, Clone, PartialEq)]
pub enum ParseTemp {
	Op(InfixOp),
	Exp(Expr)
}

/// Takes a vector and transforms it into a map.
/// Why is there nothing like this in std?
fn vec2map<K: PartialEq + Eq + Hash, T>(vec: Vec<(K, T)>) -> HashMap<K, T> {
	let mut map = HashMap::new();
	for (k, t) in vec {
		map.insert(k, t);
	}
	return map;
}

/*// Takes and returns the first token from the input.
pub fn consume_token(input: InType) -> ParseOutput<Lexeme, InType> {
	match input.first() {
		Some(tk) => Ok( (tk.clone(), &input[1..]) ),
		None => Err(1)
	}
}

/ // Peeks and doesn't remove the first token from the input.
pub fn peek_token(input: InType) -> ParseResult<Lexeme> {
	match input.first() {
		Some(tk) => Ok(tk.clone()),
		None => Err(2)
	}
}

/ // Consumes and ignores one token
/ // Returns an error if the input is empty.
pub fn ignore_token(input: InType) -> ParseResult<InType> {
	if input.is_empty() {
		return Err(3)
	}
	Ok(&input[1..])
}
*/

/// Takes a token and places it into an enum.
macro_rules! expect_token {
	($input:expr, $enum_name:ident :: $enum_var:ident ( $type_name:ident ) ) =>
	{
		match consume_token($input) {
			Ok( ($enum_name::$enum_var(val), i) ) => Ok( (val, i) ),
			Err(e) => Err(e),
			_ => Err(4)
		}
	};

	($input:expr, $enum_name:ident :: $enum_var:ident ) =>
	{
		match consume_token($input) {
			Ok( ($enum_name::$enum_var, i) ) => Ok( ( (), i) ),
			Err(e) => Err(e),
			_ => Err(4)
		}
	};
}

// / Parses and consumes an End token, or results an error.
// fn parse_end(input: InType) -> ParseOutput<(), InType> {
// 	match input.first() {
// 		Some(&Lexeme::End) => Ok( ( (), &input[1..]) ),
// 		_ => Err(5)
// 	}
// }

/// Finds the given enum variant and returns it in an Option or returns None.
macro_rules! find_token {
	($input:expr, $enum_name:ident :: $enum_var:ident ( $what:expr ))  =>
	({
		$input.into_iter().position(
			|lex| {
				match lex {
					&$enum_name::$enum_var($what) => true,
					_ => false,
				}
			}
		)
	});

	($input:expr, $enum_name:ident :: $enum_var:ident () )  =>
	({
		$input.into_iter().position(
			|lex| {
				match lex {
					&$enum_name::$enum_var( _ ) => true,
					_ => false,
				}
			}
		)
	});

	($input:expr, $enum_name:ident :: $enum_var:ident)  =>
	({
		$input.into_iter().position(
			|lex| {
				match lex {
					&$enum_name::$enum_var => true,
					_ => false,
				}
			}
		)
	});
}
