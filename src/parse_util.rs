

/// An variable and function identifier
pub type Ident = String;

pub type ErrType = u32; // TODO: make a better errortype

/// The type of the input.
pub type InType<'a> = &'a str;

/// The final result of a parser.
pub type ParseResult<R> = Result<R, ErrType>;

/// The output of a parser and the consumed input.
pub type ParseState<'a, T> = (T, InType<'a>);

/// State or error of a parser
pub type ParseOutput<'a, T> = Result<ParseState<'a, T>, ErrType>;

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
