use std::fmt;
use std::error;

#[derive(Debug)]
pub enum LexErr {
	InvalidTokenAt(String)
}

impl fmt::Display for LexErr {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&LexErr::InvalidTokenAt(ref s) =>
				write!(f, "Invalid token at: {}", s)
		}
	}

}

impl error::Error for LexErr {
	fn description(&self) -> &str {
		match self {
			&LexErr::InvalidTokenAt(_) => "invalid token found"
		}
	}

}
