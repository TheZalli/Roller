use regex::Regex;

use parse_util::*;

/// A lexical token.
#[derive(Debug, Clone, PartialEq)]
pub enum Lexeme {
	/// Integer literals
	IntLit(i64),
	/// Floating point literals
	RealLit(f64),
	/// String literals
	StrLit(String),
	/// Function and variable identifiers
	Id(Ident),
	/// Mathematical and other operators
	Op(OpToken),
	/// Predicate operations
	Pred(PredToken),
	/// =
	/// This is not a variant of the PredToken, since also statements use it
	Eq,
	/// ,
	Comma,
	/// (
	LeftParen,
	// )
	RightParen,
	/// {
	LeftBracket,
	/// }
	RightBracket,
	/// [
	LeftSqBracket,
	/// ]
	RightSqBracket,
	/// Newline, evaluates the command and prints the expression value
	End,
}

/// Operators from the highest to lowest precedence
#[derive(Debug, Clone, PartialEq)]
pub enum OpToken {
	RangeEllipsis, // ... or ..

	Neg,
	Pow,

	Mul,
	Div,
	DiceThrow,

	Add,
	//Sub,
}

// Predicate operations from highest to lowest precedence
#[derive(Debug, Clone, PartialEq)]
pub enum PredToken {
	Not,

	//Eq,
	// Inequality consists of lexemes Not and Eq
	Gt,
	Lt,
	//Gteq, //::= Gt, Eq
	//Lteq, //::= Lt, Eq

	And,
	Or,
	XOr,
}

// Lexeme patterns
lazy_static! {
	pub static ref ID_REGEX: Regex =
		Regex::new(r#"^([\pL_][\pL\pN_]*)"#).unwrap();

	pub static ref INT_REGEX: Regex = Regex::new(r#"^(\d+)"#).unwrap();
	pub static ref STR_REGEX: Regex = Regex::new("^\"(.*?)\"").unwrap();
	pub static ref FLOAT_REGEX: Regex = Regex::new(r#"^(\d*\.\d+)"#).unwrap();

	pub static ref RANGE_ELLIPSIS_REGEX: Regex = Regex::new(r#"^\.{2,3}"#).unwrap();

	pub static ref AND_REGEX: Regex = Regex::new(r#"^And|&"#).unwrap();
	pub static ref OR_REGEX: Regex = Regex::new(r#"^Or|\|"#).unwrap();
	pub static ref XOR_REGEX: Regex = Regex::new(r#"^XOr"#).unwrap();
}

// operator token characters
pub const NEG: char = '-';
pub const POW: char = '^';
pub const MUL: char = '*';
pub const DIV: char = '/';
pub const DICE_THROW: char = 'd';
pub const ADD: char = '+';
//pub const SUB: char = '-';

// predicate token characters
pub const NOT: char = '!';

pub const GT: char = '<';
pub const LT: char = '>';

// misc token characters
pub const EQ: char = '=';
pub const COMMA: char = ',';

pub const LEFT_PAREN: char = '(';
pub const RIGHT_PAREN: char = ')';

pub const LEFT_BRACKET: char = '{';
pub const RIGHT_BRACKET: char = '}';

pub const LEFT_SQ_BRACKET: char = '[';
pub const RIGHT_SQ_BRACKET: char = ']';
