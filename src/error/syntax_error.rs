use std::fmt;
use std::error;

use parser::lexer::lexer_util::lexemes::*;

#[derive(Debug)]
pub enum SynErr {
	UnexpectedToken(Lexeme),
	UnexpectedEnd,
	// TODO: remove when everything is implementend
	Unimplemented
}

impl fmt::Display for SynErr {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&SynErr::UnexpectedToken(ref tk) =>
				// TODO: implement fmt::Display for tokens
				write!(f, "Unexpected token: {:?}", tk),
			&SynErr::UnexpectedEnd =>
				write!(f, "Unexpected end of input"),
			&SynErr::Unimplemented =>
				write!(f, "Unimplemented feature"),
		}
	}
}

impl error::Error for SynErr {
	fn description(&self) -> &str {
		match self {
			&SynErr::UnexpectedToken(_) => "unexpected token",
			&SynErr::UnexpectedEnd => "unexpected end of input",
			&SynErr::Unimplemented => "unimplemented feature",
		}
	}
}
