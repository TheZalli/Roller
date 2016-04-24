use parser::parse_util::*;
use parser::lexer::lexer_util::lexemes::*;

pub type InType<'a> = &'a [Lexeme];

/// Takes and returns the first token from the input.
pub fn consume_token(input: InType) -> ParseOutput<Lexeme, InType> {
	match input.first() {
		Some(tk) => Ok( (tk.clone(), &input[1..]) ),
		None => Err(1)
	}
}

/// Peeks and doesn't remove the first token from the input.
pub fn peek_token(input: InType) -> ParseResult<Lexeme> {
	match input.first() {
		Some(tk) => Ok(tk.clone()),
		None => Err(2)
	}
}

/// Consumes and ignores one token
/// Returns an error if the input is empty.
pub fn ignore_token(input: InType) -> ParseResult<InType> {
	if input.is_empty() {
		return Err(3)
	}
	Ok(&input[1..])
}

/// Takes a token and places it into an enum.
macro_rules! expect_token {
	($input:expr, $enum_name:ident :: $enum_var:ident ( $type_name:ident ) ) =>
	{
		match consume_token($input) {
			Ok( ($enum_name::$enum_var(val), i) ) => Ok( (val, i) ),
			Err(e) => Err(e),
			_ => Err(4)
		}
	};

	($input:expr, $enum_name:ident :: $enum_var:ident ) =>
	{
		match consume_token($input) {
			Ok( ($enum_name::$enum_var, i) ) => Ok( ( (), i) ),
			Err(e) => Err(e),
			_ => Err(4)
		}
	};
}

// / Parses and consumes an End token, or results an error.
// fn parse_end(input: InType) -> ParseOutput<(), InType> {
// 	match input.first() {
// 		Some(&Lexeme::End) => Ok( ( (), &input[1..]) ),
// 		_ => Err(5)
// 	}
// }

/// Finds the given enum variant and returns it in an Option or returns None.
macro_rules! find_token {
	($input:expr, $enum_name:ident :: $enum_var:ident ( $what:expr ))  =>
	({
		$input.into_iter().position(
			|lex| {
				match lex {
					&$enum_name::$enum_var($what) => true,
					_ => false,
				}
			}
		)
	});

	($input:expr, $enum_name:ident :: $enum_var:ident () )  =>
	({
		$input.into_iter().position(
			|lex| {
				match lex {
					&$enum_name::$enum_var( _ ) => true,
					_ => false,
				}
			}
		)
	});

	($input:expr, $enum_name:ident :: $enum_var:ident)  =>
	({
		$input.into_iter().position(
			|lex| {
				match lex {
					&$enum_name::$enum_var => true,
					_ => false,
				}
			}
		)
	});
}
