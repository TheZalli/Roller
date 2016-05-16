use std::fmt;
use std::error;

use common_util::Side;
use syntax_tree::InfixOp;
use eval::types::{Value, NumType, RollerType, Ident};

#[derive(Debug)]
pub enum EvalErr {
	NoVarFound(Ident),
	NoFunFound(Ident),
	ExpectedVarFoundFun(Ident),
	ExpectedFunFoundVar(Ident),
	WrongNumParams {
		expected: usize,
		found: usize
	},
	MissingOpArg {
		op: InfixOp,
		side: Side,
	},
	NoOpArgs(InfixOp),
	UnsupportedOpTypes {
		op: InfixOp,
		left: RollerType,
		right: RollerType,
	},
	ExpectedType {
		expected: RollerType,
		found: RollerType
	},
	NegNotSupported(RollerType),
	ListsNotSameSize(Value, Value),
	ReachedMaxCallDepth,
	ExpectedPosNum(NumType),
	ExpectedNegNum(NumType),
	// TODO: remove when everything is implemented
	Unimplemented
}

impl fmt::Display for EvalErr {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&EvalErr::NoVarFound(ref id) =>
				write!(f, "No variable named \"{}\" found", id),

			&EvalErr::NoFunFound(ref id) =>
				write!(f, "No function named \"{}\" found", id),

			&EvalErr::ExpectedVarFoundFun(ref id) =>
				write!(f, "Expected a variable named \"{}\", but found a function", id),

			&EvalErr::ExpectedFunFoundVar(ref id) =>
				write!(f, "Expected a function named \"{}\", but found a variable", id),

			&EvalErr::WrongNumParams{expected, found} =>
				write!(f, "Expected {} parameters, but found {}", expected, found),

			&EvalErr::MissingOpArg{op, side} =>
				write!(f, "Operator '{}' has a missing argument on the {} side", op, side),

			&EvalErr::NoOpArgs(op) =>
				write!(f, "Operator '{}' has no arguments", op),

			&EvalErr::UnsupportedOpTypes{op, left, right} =>
				write!(f, "Operator '{}' is not defined between the types {} and {}",
					op, left, right),

			&EvalErr::ExpectedType{expected, found} =>
				write!(f, "Expected type {}, but found {}", expected, found),

			&EvalErr::NegNotSupported(arg) =>
				write!(f, "Negation is not defined for the type {}", arg),

			&EvalErr::ListsNotSameSize(ref a, ref b) =>
				write!(f, "Lists {} and {} were not of same size", a, b),

			&EvalErr::ReachedMaxCallDepth =>
				write!(f, "Reached maximum function call depth"),

			&EvalErr::ExpectedPosNum(x) =>
				write!(f, "Expected a positive numeral, found {}", x),

			&EvalErr::ExpectedNegNum(x) =>
				write!(f, "Expected a negative numeral, found {}", x),

			&EvalErr::Unimplemented =>
				write!(f, "Unimplemented feature"),
		}
	}
}

impl error::Error for EvalErr {
	fn description(&self) -> &str {
		match self {
			&EvalErr::NoVarFound(_)				=> "no variable found",
			&EvalErr::NoFunFound(_)				=> "no function found",
			&EvalErr::ExpectedVarFoundFun(_)	=> "expected a variable, found a function",
			&EvalErr::ExpectedFunFoundVar(_)	=> "expected a function, found a variable",
			&EvalErr::WrongNumParams{..}		=> "found wrong number of parameters",
			&EvalErr::MissingOpArg{..}			=> "missing operator argument",
			&EvalErr::NoOpArgs(_)				=> "operator has no arguments",
			&EvalErr::UnsupportedOpTypes{..}	=> "operator not defined between types",
			&EvalErr::ExpectedType{..}			=> "wrong type",
			&EvalErr::NegNotSupported(_)		=> "negation not defined for the type",
			&EvalErr::ListsNotSameSize(..)		=> "lists were not of the same size",
			&EvalErr::ReachedMaxCallDepth		=> "reached maximum function call depth",
			&EvalErr::ExpectedPosNum(_)			=> "expected a positive numeral",
			&EvalErr::ExpectedNegNum(_)			=> "expected a negative numeral",
			&EvalErr::Unimplemented				=> "unimplemented feature",
		}
	}
}
