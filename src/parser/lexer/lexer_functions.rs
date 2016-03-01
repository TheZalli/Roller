//#![allow(dead_code)]

//use std::str::pattern::Pattern;
use std::str::FromStr;

use regex::{Regex, Captures};

use parser::parse_util::*;
use parser::lexer::lexer_util::*;

/// The type of the input.
pub type InType<'a> = &'a str;

pub fn tokenize(input: InType) -> ParseResult<Vec<Lexeme>> {
	let mut input = input.clone();
	let mut tokens = Vec::new();

	while !input.is_empty() {
		match get_token(input) {
			Ok( (token, i) ) => {
				//state_add(p_st);
				tokens.push(token);
				input = i;
			},
			Err(e) => return Err(e),
		};
	}

	Ok(tokens)
}

/// Tokenizes one token and consumes the input
/// IMPORTANT: If no input was consumed, an error should be returned, so that tokenize won't go into infinite loop.
fn get_token(input: InType) -> ParseOutput<Lexeme, InType> {
	let input = ignore_whitespace(input);

	Err(0)
	.or(lex_operator(input))
	.or(lex_pred(input))
	.or(lex_identifier(input))
	.or(lex_literal(input))
	.or(lex_misc_char_tokens(input))
	.or(lex_end(input))
}

/// Evaluates the input with the given regex and returns the captures and the right side of the input splitted from the right end of the whole capture (the rest is consumed).
/// Returns an error if nothing was captured.
//fn lex_pat_capture<'a, P: Sized + Pattern<'a>>(input: InType<'a>, pat: P) ->
fn lex_pat_capture<'a>(input: InType<'a>, pat: &Regex) -> ParseOutput<Captures<'a>, InType<'a> > {
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

/// Same as lex_pat_capture, expect doesn't capture.
/// This function just consumes the pattern if found and returns an error not found
fn expect_pattern<'a>(input: InType<'a>, pat: &Regex) -> ParseOutput<(), InType<'a> > {
	match pat.find(input) {
		Some( ( _ , right) ) => {
			Ok( ( (), input.split_at(right).1) )
		},
		None => Err(2)
	}
}

/// Similar to expect_pattern, but with a character pattern, because std::pattern is unstable.
/// Expects that the first character is pat
fn expect_char<'a>(input: InType<'a>, pat: char) -> ParseOutput<(), InType> {
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
macro_rules! lex_first_capture {
	($input:expr, $regex:expr, $cap_index:expr,
		$enum_name:ident :: $enum_var:ident ( $type_name:ident ) ) =>
	{
		match lex_pat_capture($input, $regex) {
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

macro_rules! lex_first_char_capture {
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

/// Tokenizes an end of line.
fn lex_end(input: InType) -> ParseOutput<Lexeme, InType> {
	if input.trim().is_empty() {
		Ok( (Lexeme::End, "") )
	} else {
		Err(4)
	}
}

/// Tokenizes an integer literal.
/// Please parse floating point literals before parsing integers, because otherwise the start of a float can be mistaken as an integer.
fn lex_int(input: InType) -> ParseOutput<Lexeme, InType> {
	lex_first_capture!(input, &INT_REGEX, 1, Lexeme::IntLit(i64))
}

/// Tokenizes a floating point/real literal.
fn lex_float(input: InType) -> ParseOutput<Lexeme, InType> {
	lex_first_capture!(input, &FLOAT_REGEX, 1, Lexeme::RealLit(f64))
}

/// Tokenizes a double-quotation mark limited string literal.
/// No escaping supported yet.
// TODO: Add escape support.
fn lex_str_lit<'a>(input: InType<'a>) -> ParseOutput<Lexeme, InType> {
	lex_first_capture!(input, &STR_REGEX, 1, Lexeme::StrLit(String))
}

/// Tokenizes a float, integer or string literal.
fn lex_literal<'a>(input: InType<'a>) -> ParseOutput<Lexeme, InType<'a>> {
	lex_str_lit(input)
	.or(lex_float(input))
	.or(lex_int(input))
}

/// Tokenizes an identifier.
/// The first character must be an unicode letters or underscores, and the rest can be unicode letters, numbers and underscores.
/// Reserved keywords are not allowed as variable and function names, but this is checked after the lexer.
// TODO: Use Unicode identifier and pattern syntax http://www.unicode.org/reports/tr31/tr31-23.html
fn lex_identifier(input: InType) -> ParseOutput<Lexeme, InType> {
	lex_first_capture!(input, &ID_REGEX, 1, Lexeme::Id(Ident))
}

/// Tokenizes an operator.
/// Parses range ellipsis operator and the mathematical operations.
fn lex_operator(input: InType) -> ParseOutput<Lexeme, InType> {
	let op_result = Err(0)
		.or(lex_first_capture!(input, &RANGE_ELLIPSIS_REGEX, OpToken::RangeEllipsis))
		.or(lex_first_char_capture!(input, DICE_THROW, OpToken::DiceThrow))
		.or(lex_first_char_capture!(input, MINUS, OpToken::Minus))
		.or(lex_first_char_capture!(input, POW, OpToken::Pow))
		.or(lex_first_char_capture!(input, MUL, OpToken::Mul))
		.or(lex_first_char_capture!(input, DIV, OpToken::Div))
		.or(lex_first_char_capture!(input, ADD, OpToken::Add))
	;

	match op_result {
		Ok( (op_tk, i) ) => Ok( (Lexeme::Op(op_tk), i) ),
		Err(e) => Err(e),
	}
}

/// Tokenizes a single predicate from a filter's pattern.
fn lex_pred(input:InType) -> ParseOutput<Lexeme, InType> {
	let pred_result = Err(0)
		.or(lex_first_char_capture!(input, NOT, PredToken::Not))
		//.or(lex_first_char_capture!(input, EQ, PredToken::Eq))
		.or(lex_first_char_capture!(input, GT, PredToken::Gt))
		.or(lex_first_char_capture!(input, LT, PredToken::Lt))
		.or(lex_first_capture!(input, &AND_REGEX, PredToken::And))
		.or(lex_first_capture!(input, &OR_REGEX, PredToken::Or))
		.or(lex_first_capture!(input, &XOR_REGEX, PredToken::XOr))
	;

	match pred_result {
		Ok( (pr_tk, i) ) => Ok( (Lexeme::Pred(pr_tk), i) ),
		Err(e) => Err(e),
	}
}

/// Tokenizes all of the misc one-character tokens
fn lex_misc_char_tokens(input: InType) -> ParseOutput<Lexeme, InType> {
	Err(0)
	.or(lex_first_char_capture!(input, EQ, Lexeme::Eq))
	.or(lex_first_char_capture!(input, COMMA, Lexeme::Comma))

	.or(lex_first_char_capture!(input, LEFT_PAREN, Lexeme::LeftParen))
	.or(lex_first_char_capture!(input, RIGHT_PAREN, Lexeme::RightParen))

	.or(lex_first_char_capture!(input, LEFT_BRACKET, Lexeme::LeftBracket))
	.or(lex_first_char_capture!(input, RIGHT_BRACKET, Lexeme::RightBracket))

	.or(lex_first_char_capture!(input, LEFT_SQ_BRACKET, Lexeme::LeftSqBracket))
	.or(lex_first_char_capture!(input, RIGHT_SQ_BRACKET, Lexeme::RightSqBracket))
}
