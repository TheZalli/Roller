use error::ErrType;

/// The output of a parser and the consumed input.
pub type ParseState<T, I> = (T, I);

/// State or error of a parser
pub type ParseOutput<T, I, E = ErrType> = Result<ParseState<T, I>, E>;

pub fn map_output<T, I, U, E>(out: ParseOutput<T, I, E>, fun: &Fn(T) -> U) -> ParseOutput<U, I, E>
{
	match out {
		Ok( (t, i) ) => Ok( (fun(t), i) ),
		Err(e) => Err(e)
	}
}
