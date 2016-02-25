//#![allow(dead_code)]
//use std::str::pattern::Pattern;
use std::str::FromStr;

use regex::{Regex, Captures};

/// An variable and function identifier
pub type Ident = String;

#[derive(Debug, Clone, PartialEq)]
pub enum Lexeme {
	IntLit(i64), // integer literals
	RealLit(f64), // floating point literals
	StrLit(String), // string literals
	Id(Ident), // function and variable identifiers
	Operator(String), // mathematical and other operators
	TypeChar(char), // Type pattern characters: #, %, $
	Comma, // ,
	LeftParen, // (
	RightParen, // )
	LeftBracket, // {
	RightBracket, // }
	LeftSqBracket, // [
	RightSqBracket, // ]
	End, // newline, evaluates the command and prints the expression value
}

pub type ErrType = u32; // TODO: make a better errortype

/// The type of the input.
pub type InType<'a> = &'a str;

/// The final result of a parser.
pub type ParseResult<R> = Result<R, ErrType>;

/// The output of a parser and the consumed input.
pub type ParseState<'a, T> = (T, InType<'a>);

/// State or error of a parser
pub type ParseOutput<'a, T> = Result<ParseState<'a, T>, ErrType>;

/// A state of the lexer
struct LexState<'a> {
	tokens: Vec<Lexeme>,
	// the input left to parse
	input: InType<'a>,
	//is_done: bool,
}

impl<'a> LexState<'a> {
	fn new(input: InType<'a>) -> LexState<'a> {
		LexState{tokens: Vec::new(), input: input}
	}

	fn add_from_parse_state(&mut self, st: ParseState<'a, Lexeme>) {
		self.tokens.push(st.0);
		self.input = st.1;
	}

	/*fn add_token(&mut self, token: Lexeme) {
		self.tokens.push(token)
	}

	fn get_input(&self) -> &InType {
		&self.input
	}

	fn set_input(&mut self, i: InType<'a>) {
		self.input = i
	}

	fn map_input(&mut self, f: (fn (InType) -> InType)) {
		self.input = f(self.input)
	}*/

	fn is_done(&self) -> bool {
		self.input.is_empty()
	}
}

pub fn tokenize(input: InType) -> ParseResult<Vec<Lexeme>> {
	let mut state = LexState::new(input);

	// beware infinite loops!
	while !state.is_done() {
		match parse_token(state.input) {
			Ok(p_st) => {
				state.add_from_parse_state(p_st);
			},
			Err(e) => return Err(e),
		};
	}

	Ok(state.tokens)
}

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

/// Parses one token and consumes the input
/// IMPORTANT: If no input was consumed, an error should be returned, so that tokenize won't go into infinite loop.
fn parse_token(input: InType) -> ParseOutput<Lexeme> {
	let input = ignore_whitespace(input);

	parse_identifier(input)
	.or(parse_end(input))
}

/// Evaluates the input with the given regex and returns the captures and the right side of the input splitted from the right end of the whole capture (the rest is consumed).
/// Returns an error if nothing was captured.
//fn parse_pat_capture<'a, P: Sized + Pattern<'a>>(input: InType<'a>, pat: P) ->
fn parse_pat_capture<'a>(input: InType<'a>, pat: Regex) -> ParseOutput<'a, Captures<'a>> {
	match pat.captures(input) {
		Some(cap) => {
			// a safe unwrap, since we know that we captured something,
			// which means that the entire capture, which is at zero, exists.
			let split_point = cap.pos(0).unwrap().1;
			Ok( (cap, input.split_at(split_point).1) )
		},
		None => Err(1)
	}
}

/// Same as parse_pat_capture, expect doesn't capture.
/// This function just consumes the pattern if found and returns an error not found
fn expect_pattern<'a>(input: InType<'a>, pat: Regex) -> ParseOutput<'a, ()> {
	match pat.find(input) {
		Some( ( _ , right) ) => {
			Ok( ( (), input.split_at(right).1) )
		},
		None => Err(2)
	}
}

/// A macro that consumes and parses the first pattern that matches the regex from the input and returns it in an enum variant.
macro_rules! parse_first_capture {
	($input:expr, $regex:expr, $enum_name:ident :: $enum_var:ident ( $type_name:ident ) ) => {
		match parse_pat_capture($input, $regex) {
			Ok( (cap, i) ) => match $type_name::from_str(&cap[1]) {
				Ok(first_cap) => Ok( ($enum_name::$enum_var(first_cap), i) ),
				Err(e) => Err(3) // TODO: fix
			},
			Err(e) => Err(e)
		}
	};

	($input:expr, $regex:expr, $enum_name:ident :: $enum_var:ident ) => {
		match expect_pattern($input, $regex) {
			Ok(i) => Ok( ($enum_name::$enum_var, i) ),
			Err(e) => Err(e)
		}
	};
}

/// Consumes the whitespace from the start of the input
fn ignore_whitespace(input: InType) -> InType {
	input.trim_left()
}

/// Parses an end of line.
fn parse_end(input: InType) -> ParseOutput<Lexeme> {
	if input.trim().is_empty() {
		Ok( (Lexeme::End, "") )
	} else {
		Err(4)
	}
}

/// Parses an identifier.
/// The first character must be an unicode letters or underscores, and the rest can be unicode letters, numbers and underscores, but there must be at least one character that is not an underscore. (Similar to Rusts identifier syntax)
// TODO: Use Unicode identifier and pattern syntax http://www.unicode.org/reports/tr31/tr31-23.html
fn parse_identifier(input: InType) -> ParseOutput<Lexeme> {
	lazy_static! {
		static ref pat: Regex = Regex::new(r#"^(_*[\pL][\pL\pN_]*|_+[\pL\pN]+)"#).unwrap();
	}
	let re: Regex = pat.clone();
	parse_first_capture!(input, re, Lexeme::Id(Ident))
}
