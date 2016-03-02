pub use self::lexemes::*;
pub use self::patterns::*;

/// Lexical token enums
pub mod lexemes {
	use parser::parse_util::*;
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
		/// .. or ...
		RangeEllipsis,
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

	/// Operator tokens.
	/// (From highest to lowest precedence)
	#[derive(Debug, Clone, PartialEq)]
	pub enum OpToken {
		Minus,
		Pow,

		Mul,
		Div,
		DiceThrow,

		Add,
		//Sub,
	}

	/// Predicate operation tokens.
	/// (From highest to lowest precedence)
	#[derive(Debug, Clone, PartialEq)]
	pub enum PredToken {
		Not,

		Gt,
		Lt,

		And,
		Or,
		XOr,
	}
}

/// Lexeme patterns
pub mod patterns {
	use regex::Regex;

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
	/// Negation and substraction.
	pub const MINUS: char = '-';
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
}
