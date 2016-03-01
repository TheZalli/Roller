
/// An variable and function identifier
pub type Ident = String;

pub type ErrType = u32; // TODO: make a better errortype

/// The final result of a parser.
pub type ParseResult<R> = Result<R, ErrType>;

/// The output of a parser and the consumed input.
pub type ParseState<T, I> = (T, I);

/// State or error of a parser
pub type ParseOutput<T, I> = Result<ParseState<T, I>, ErrType>;

/* // Converts a parse output into a result.
/ // Returns an error if the output has an error, or if the input has not been consumed.
fn expect_results<T>(st: ParseOutput<T>) -> ParseResult<T> {
	match st {
		Ok( (x, i) ) => {
			if i.is_empty() {
				Ok(x)
			} else {
				Err(2)
			}
		},
		Err(e) => Err(e)
	}
}*/
