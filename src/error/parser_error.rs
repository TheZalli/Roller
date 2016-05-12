use std::fmt;
use std::error;

#[derive(Debug)]
pub enum LexErr<'a> {
	InvalidTokenAt(&'a str)
}

impl<'a> fmt::Display for LexErr<'a> {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&LexErr::InvalidTokenAt(s) =>
				write!(f, "Invalid token at: {:?}", s)
		}
	}

}

impl<'a> error::Error for LexErr<'a> {
	fn description(&self) -> &str {
		match self {
			&LexErr::InvalidTokenAt(_) => "invalid token found"
		}
	}

}
