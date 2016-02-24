#![allow(dead_code)]
use nom::IResult;
use nom::Err;
use nom::ErrorKind;
use nom::InputLength;

use std::str::FromStr;
use std::iter::{FromIterator, IntoIterator};
use std::ops::Deref;

/// An variable and function identifier
pub type Ident = String;

named!(pub ignore_ws(&str) -> &str,
	take_while_s!(char::is_whitespace)
);

#[derive(Debug, Clone)]
pub enum Lexeme {
	IntLit(i64), // integer literals
	RealLit(f64), // floating point literals
	StrLit(Box<String>), // string literals
	Id(Box<Ident>), // function and variable identifiers
	Operator(Box<String>), // mathematical and other operators
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

/// This exists solely because of the Rusts orphan rules.
//pub enum LexList { List(Vec<Lexeme>) }
#[derive(Debug, Clone)]
pub struct LexList(pub Vec<Lexeme>);

impl Deref for LexList {
	type Target = Vec<Lexeme>;

	fn deref(&self) -> &Vec<Lexeme > {
        let &LexList(ref val) = self;
		&val
    }
}

impl InputLength for LexList {
	#[inline]
	fn input_len(&self) -> usize {
		let LexList(ref val) = *self;
		val.len()
	}
}

/// Takes the command string as input and returns it split into lexeme tokens.
pub fn tokenize(input: &str) -> IResult<&str, LexList > {
	let res1 = try_parse!(input, many1!(parse_token));
	match res1 {
		(i2 , v) => {
			IResult::Done(i2, LexList(Vec::from_iter(v.into_iter())) )
		},
		//_ => IResult::Error(Err::Code(ErrorKind::Custom(4)) )
	}
}

pub fn parse_token(input: &str) -> IResult<&str, Lexeme> {
	chain!(input,
		ignore_ws ~
		lex: alt_complete!(
			parse_literal => {
				|lex: Lexeme| lex
			}
			| parse_identifier => {
				|lex: Lexeme| lex
			}
		),
		|| { lex }
	)

}

/// Parses literal values.
//named!(parse_literal(&str) -> Lexeme,
pub fn parse_literal(input: &str) -> IResult<&str, Lexeme> {
	alt_complete!(input,
		parse_float_literal => {
			|lex: Lexeme| lex
		}
		| parse_int_literal => {
			|lex: Lexeme| lex
		}
		| parse_str_literal => {
			|lex: Lexeme| lex
		}
	)
}
//);

/// Parses integer literals.
named!(parse_int_literal(&str) -> Lexeme,
	chain!(
		ignore_ws ~
		cap_vec: re_capture!(r"^(-?\d*)") ~ // capture an integer numeral with a regex pattern
		str_slice: expr_opt!(cap_vec.get(1)) ~ // get the captured str
		int: expr_res!(i64::from_str(str_slice)), // type conversion
		|| { Lexeme::IntLit(int) }
	)
);

/// Parses float literals.
/// The number before the decimal point is optional and it is assumed to be 0 if missing.
named!(parse_float_literal(&str) -> Lexeme,
	chain!(
		ignore_ws ~
		cap_vec: re_capture!(r"^(-?\d*\.\d+)") ~ // capture a real numeral with a regex pattern
		str_slice: expr_opt!(cap_vec.get(1)) ~ // get the captured str
		float: expr_res!(f64::from_str(str_slice)), // type conversion
		|| { Lexeme::RealLit(float) }
	)
);

/// Parses double quote limited string literals.
/// The strings may not contain double quote characters.
/// There are no escape characters in the strings (yet).
fn parse_str_literal(i: &str) -> IResult<&str, Lexeme> {
	chain!(i,
		ignore_ws ~
		cap_vec: re_capture!("^\"([^\"]*)\"") ~ // capture the string literal with a regex pattern
		str_slice: expr_opt!(cap_vec.get(1)) ~ // get the captured str
		string: expr_res!(String::from_str(str_slice)), // type conversion
		|| { Lexeme::StrLit(Box::new(string)) }
	)
}

/// Parses an identifier.
/// The first character must be an unicode letters or underscores, and the rest can be unicode letters, numbers and underscores, but there must be at least one character that is not an underscore. (Similar to Rusts identifier syntax)
// TODO: Use Unicode identifier and pattern syntax http://www.unicode.org/reports/tr31/tr31-23.html
named!(parse_identifier(&str) -> Lexeme,
	chain!(
		ignore_ws ~
		// capture an identifier string with a regex pattern
		cap_vec: re_capture!(r#"(_*[\pL][\pL\pN_]*|_+[\pL\pN]+)"#) ~
		str_slice: expr_opt!(cap_vec.get(1)) ~ // get the captured str
		id: expr_res!(Ident::from_str(str_slice)), // type conversion
		|| { Lexeme::Id(Box::new(id)) }
	)
);
