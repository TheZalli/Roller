use std::fmt;
use std::error;

use error::*;

#[derive(Debug)]
pub enum RollerErr {
	LexingError(LexErr),
	SyntaxError(SynErr),
	EvalError(EvalErr),
}

impl fmt::Display for RollerErr {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&RollerErr::LexingError(ref e) => write!(f, "Lexing error: {}", e),
			&RollerErr::SyntaxError(ref e) => write!(f, "Syntax error: {}", e),
			&RollerErr::EvalError(ref e)   => write!(f, "Evaluation error: {}", e)
		}
	}
}

impl error::Error for RollerErr {
	fn description(&self) -> &str {
		match self {
			&RollerErr::LexingError(ref e) => e.description(),
			&RollerErr::SyntaxError(ref e) => e.description(),
			&RollerErr::EvalError(ref e)   => e.description()
		}
	}
}

pub type ErrType = RollerErr;

/// The final result of a parser.
pub type ParseResult<R, E = ErrType> = Result<R, E>;
