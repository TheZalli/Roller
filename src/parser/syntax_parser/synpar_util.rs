use std::collections::HashMap;

use syntax_tree::{InfixOp, Expr};
use common_util::{Side, vec2map};
use parser::lexer::lexer_util::lexemes::Lexeme;

pub type InType<'a> = &'a [Lexeme];

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


#[derive(Debug, Clone, PartialEq)]
pub enum ParseTemp {
	Op(InfixOp),
	Exp(Expr)
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
