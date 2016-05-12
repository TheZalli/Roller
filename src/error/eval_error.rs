use std::fmt;
use std::error;

// TODO: make this as an enum
#[derive(Debug)]
pub struct EvalErr {
	msg: String
}

impl fmt::Display for EvalErr {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "{}", self.msg)
	}
}

impl error::Error for EvalErr {
	fn description(&self) -> &str {
		&self.msg
	}
}
