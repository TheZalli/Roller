//#![allow(dead_code)]

//use std::str::pattern::Pattern;
use std::str::FromStr;

use regex::{Regex, Captures};

use parse_util::*;
use lexer::lexer_util::*;


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

/// Parses one token and consumes the input
/// IMPORTANT: If no input was consumed, an error should be returned, so that tokenize won't go into infinite loop.
fn parse_token(input: InType) -> ParseOutput<Lexeme> {
	let input = ignore_whitespace(input);

	Err(0)
	.or(parse_operator(input))
	.or(parse_pred(input))
	.or(parse_identifier(input))
	.or(parse_literal(input))
	.or(parse_misc_char_tokens(input))
	.or(parse_end(input))
}

/// Evaluates the input with the given regex and returns the captures and the right side of the input splitted from the right end of the whole capture (the rest is consumed).
/// Returns an error if nothing was captured.
//fn parse_pat_capture<'a, P: Sized + Pattern<'a>>(input: InType<'a>, pat: P) ->
fn parse_pat_capture<'a>(input: InType<'a>, pat: &Regex) -> ParseOutput<'a, Captures<'a>> {
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
fn expect_pattern<'a>(input: InType<'a>, pat: &Regex) -> ParseOutput<'a, ()> {
	match pat.find(input) {
		Some( ( _ , right) ) => {
			Ok( ( (), input.split_at(right).1) )
		},
		None => Err(2)
	}
}

/// Similar to expect_pattern, but with a character pattern, because std::pattern is unstable.
/// Expects that the first character is pat
fn expect_char<'a>(input: InType<'a>, pat: char) -> ParseOutput<'a, ()> {
	match input.starts_with(pat) {
		true => {
			Ok( ( (), input.split_at(1).1) )
		},
		false => Err(2)
	}
}

/// A macro that consumes and parses the first matching pattern from the input and returns it in an enum variant.
/// The type_name must implement std::str::FromStr.
/// The capturing variant must be supplied with the index of the capture, which has to be an usize, or the name of the capture group.
macro_rules! parse_first_capture {
	($input:expr, $regex:expr, $cap_index:expr,
		$enum_name:ident :: $enum_var:ident ( $type_name:ident ) ) =>
	{
		match parse_pat_capture($input, $regex) {
			Ok( (cap, i) ) => match $type_name::from_str(&cap[$cap_index]) {
				Ok(first_cap) => Ok( ($enum_name::$enum_var(first_cap), i) ),
				Err(e) => Err(3) // TODO: fix
			},
			Err(e) => Err(e)
		}
	};

	($input:expr, $regex:expr, $enum_name:ident :: $enum_var:ident ) => {
		match expect_pattern($input, $regex) {
			Ok( (_, i) ) => Ok( ($enum_name::$enum_var, i) ),
			Err(e) => Err(e)
		}
	};
}

macro_rules! parse_first_char_capture {
	($input:expr, $ch:expr, $enum_name:ident :: $enum_var:ident ) => {
		match expect_char($input, $ch) {
			Ok( (_, i) ) => Ok( ($enum_name::$enum_var, i) ),
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

/// Parses an integer literal.
/// Please parse floating point literals before parsing integers, because otherwise the start of a float can be mistaken as an integer.
fn parse_int(input: InType) -> ParseOutput<Lexeme> {
	parse_first_capture!(input, &INT_REGEX, 1, Lexeme::IntLit(i64))
}

/// Parses a floating point/real literal.
fn parse_float(input: InType) -> ParseOutput<Lexeme> {
	parse_first_capture!(input, &FLOAT_REGEX, 1, Lexeme::RealLit(f64))
}

/// Parses a double-quotation mark limited string literal.
/// No escaping supported yet.
// TODO: Add escape support.
fn parse_str_lit<'a>(input: InType<'a>) -> ParseOutput<'a, Lexeme> {
	parse_first_capture!(input, &STR_REGEX, 1, Lexeme::StrLit(String))
}

/// Parses a float, integer or string literal.
fn parse_literal<'a>(input: InType<'a>) -> ParseOutput<'a, Lexeme> {
	parse_str_lit(input)
	.or(parse_float(input))
	.or(parse_int(input))
}

/// Parses an identifier.
/// The first character must be an unicode letters or underscores, and the rest can be unicode letters, numbers and underscores.
/// Reserved keywords are not allowed as variable and function names, but this is checked after the lexer.
// TODO: Use Unicode identifier and pattern syntax http://www.unicode.org/reports/tr31/tr31-23.html
fn parse_identifier(input: InType) -> ParseOutput<Lexeme> {
	parse_first_capture!(input, &ID_REGEX, 1, Lexeme::Id(Ident))
}

/// Parses an operator.
/// Parses range ellipsis operator and the mathematical operations.
fn parse_operator(input: InType) -> ParseOutput<Lexeme> {
	let op_result = Err(0)
		.or(parse_first_capture!(input, &RANGE_ELLIPSIS_REGEX, OpToken::RangeEllipsis))
		.or(parse_first_char_capture!(input, DICE_THROW, OpToken::DiceThrow))
		.or(parse_first_char_capture!(input, NEG, OpToken::Neg))
		.or(parse_first_char_capture!(input, POW, OpToken::Pow))
		.or(parse_first_char_capture!(input, MUL, OpToken::Mul))
		.or(parse_first_char_capture!(input, DIV, OpToken::Div))
		.or(parse_first_char_capture!(input, ADD, OpToken::Add))
	;

	match op_result {
		Ok( (op_tk, i) ) => Ok( (Lexeme::Op(op_tk), i) ),
		Err(e) => Err(e),
	}
}

/// Parses a single predicate from a filter's pattern.
fn parse_pred(input:InType) -> ParseOutput<Lexeme> {
	let pred_result = Err(0)
		.or(parse_first_char_capture!(input, NOT, PredToken::Not))
		//.or(parse_first_char_capture!(input, EQ, PredToken::Eq))
		.or(parse_first_char_capture!(input, GT, PredToken::Gt))
		.or(parse_first_char_capture!(input, LT, PredToken::Lt))
		.or(parse_first_capture!(input, &AND_REGEX, PredToken::And))
		.or(parse_first_capture!(input, &OR_REGEX, PredToken::Or))
		.or(parse_first_capture!(input, &XOR_REGEX, PredToken::XOr))
	;

	match pred_result {
		Ok( (pr_tk, i) ) => Ok( (Lexeme::Pred(pr_tk), i) ),
		Err(e) => Err(e),
	}
}

/// Parses all of the misc one-character tokens
fn parse_misc_char_tokens(input: InType) -> ParseOutput<Lexeme> {
	Err(0)
	.or(parse_first_char_capture!(input, EQ, Lexeme::Eq))
	.or(parse_first_char_capture!(input, COMMA, Lexeme::Comma))

	.or(parse_first_char_capture!(input, LEFT_PAREN, Lexeme::LeftParen))
	.or(parse_first_char_capture!(input, RIGHT_PAREN, Lexeme::RightParen))

	.or(parse_first_char_capture!(input, LEFT_BRACKET, Lexeme::LeftBracket))
	.or(parse_first_char_capture!(input, RIGHT_BRACKET, Lexeme::RightBracket))

	.or(parse_first_char_capture!(input, LEFT_SQ_BRACKET, Lexeme::LeftSqBracket))
	.or(parse_first_char_capture!(input, RIGHT_SQ_BRACKET, Lexeme::RightSqBracket))
}
