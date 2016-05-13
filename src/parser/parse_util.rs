use std::collections::HashMap;
use std::hash::Hash;

use error::RollerErr;

/// An variable and function identifier
pub type Ident = String;

pub type ErrType<'a> = RollerErr<'a>;

/// The final result of a parser.
pub type ParseResult<'a, R, E = ErrType<'a>> = Result<R, E>;

/// The output of a parser and the consumed input.
pub type ParseState<T, I> = (T, I);

/// State or error of a parser
pub type ParseOutput<'a, T, I, E = ErrType<'a>> = Result<ParseState<T, I>, E>;

pub fn map_output<T, I, U, E>(out: ParseOutput<T, I, E>, fun: &Fn(T) -> U) -> ParseOutput<U, I, E>
{
	match out {
		Ok( (t, i) ) => Ok( (fun(t), i) ),
		Err(e) => Err(e)
	}
}

/// Takes a vector and transforms it into a map.
/// Why is there nothing like this in std?
pub fn vec2map<K: PartialEq + Eq + Hash, T>(vec: Vec<(K, T)>) -> HashMap<K, T> {
	let mut map = HashMap::new();
	for (k, t) in vec {
		map.insert(k, t);
	}
	return map;
}

/*pub trait Complete {
	type Out;
	/// Converts a parse output into a result.
	/// Returns an error if the output has an error, or if the input has not been consumed.
	fn complete(&self) -> ParseResult<Self::Out>;
}

impl<'a, T, I> Complete for ParseOutput<T, &'a [I]> {
	type Out = T;
	fn complete(&self) -> ParseResult<Self::Out> {
		match self {
			&Ok( (x, i) ) => {
				if i.is_empty() {
					Ok(x)
				} else {
					Err(2)
				}
			},
			&Err(e) => Err(e)
		}
	}
}*/
