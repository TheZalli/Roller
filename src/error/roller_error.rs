use std::fmt;
use std::error;

use error::*;

#[allow(dead_code)] // TODO: remove when EvalErrors are used
#[derive(Debug)]
pub enum RollerErr<'a> {
	LexingError(LexErr<'a>),
	SyntaxError(SynErr),
	EvalError(EvalErr),
}

impl<'a> fmt::Display for RollerErr<'a> {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&RollerErr::LexingError(ref e) => write!(f, "Lexing error: {}", e),
			&RollerErr::SyntaxError(ref e) => write!(f, "Syntax error: {}", e),
			&RollerErr::EvalError(ref e)   => write!(f, "Evaluation error: {}", e)
		}
	}
}

impl<'a> error::Error for RollerErr<'a> {
	fn description(&self) -> &str {
		match self {
			&RollerErr::LexingError(ref e) => e.description(),
			&RollerErr::SyntaxError(ref e) => e.description(),
			&RollerErr::EvalError(ref e)   => e.description()
		}
	}
}
