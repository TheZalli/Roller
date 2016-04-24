
/// An variable and function identifier
pub type Ident = String;

pub type ErrType = u32; // TODO: make a better errortype

/// The final result of a parser.
pub type ParseResult<R> = Result<R, ErrType>;

/// The output of a parser and the consumed input.
pub type ParseState<T, I> = (T, I);

/// State or error of a parser
pub type ParseOutput<T, I> = Result<ParseState<T, I>, ErrType>;

pub fn map_output<T, I, U>(out: ParseOutput<T, I>, fun: &Fn(T) -> U) -> ParseOutput<U, I> {
	match out {
		Ok( (t, i) ) => Ok( (fun(t), i) ),
		Err(e) => Err(e)
	}
}

pub trait Complete {
	type Out;
	/// Converts a parse output into a result.
	/// Returns an error if the output has an error, or if the input has not been consumed.
	fn complete(&self) -> ParseResult<Self::Out>;
}

impl<'a, T, I> Complete for ParseOutput<T, &'a [I]> {
	type Out = T;
	pub fn complete(&self) -> ParseResult<Self::Out> {
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
}
