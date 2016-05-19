pub use self::lexemes::*;
pub use self::patterns::*;

/// The type of the input.
pub type InType<'a> = &'a str;

/// Lexical token enums
pub mod lexemes {
	use std::collections::HashMap;

	use common_util::vec2map;
	use syntax_tree::*;
	use eval::types::*;

	/// A lexical token.
	#[derive(Debug, Clone, PartialEq)]
	pub enum Lexeme {
		/// Integer and floating point literals
		NumLit(NumType),
		/// String literals
		StrLit(String),
		/// Function and variable identifiers
		Id(Ident),
		/// Mathematical and other operators
		Op(InfixOp),
		/// Predicate operations
		Pred(PredToken),
		// A keyword
		Kw(KwToken),
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
		/// End of a command
		End,
	}

	/// Predicate operation tokens.
	/// (From highest to lowest precedence)
	#[derive(Debug, Clone, Copy, PartialEq)]
	pub enum PredToken {
		Not,

		Gt,
		Lt,

		And,
		Or,
		XOr,
	}

	// Keyword statement token
	#[derive(Debug, Clone, Copy, PartialEq)]
	pub enum KwToken {
		// statement only keywords
		Delete,
		Clear,
		Run,
		Save,
		// expression only keywords
		Length,
		Sum,
		Mean,
		Sqrt,
		Root,
		Repeat,
		Acc,
		Flatten,
		ToFlat,
		ToStr,
		ToNum,
		ToList,
		Raise,
		// both expression and statement keywords
		Try,
		Catch,
	}

	lazy_static! {
		/// A map from all of the keys into their tokens.
		pub static ref KW_STRINGS: HashMap<&'static str, KwToken> =
			vec2map(vec![
				("delete",	KwToken::Delete),
				("clear",	KwToken::Clear),
				("run",		KwToken::Run),
				("save",	KwToken::Save),

				("length", KwToken::Length),
				("sum", KwToken::Sum),
				("mean", KwToken::Mean),
				("sqrt", KwToken::Sqrt),
				("root", KwToken::Root),
				("repeat", KwToken::Repeat),
				("acc", KwToken::Acc),
				("flatten", KwToken::Flatten),
				("to_flat", KwToken::ToFlat),
				("to_string", KwToken::ToStr),
				("to_numeral", KwToken::ToNum),
				("to_list", KwToken::ToList),
				("raise", KwToken::Raise),

				("try", KwToken::Try),
				("catch", KwToken::Catch),
			]);
	}
}

/// Lexeme patterns
// NOTE: revise if the std Patterns become stable
pub mod patterns {
	use regex::Regex;

	// Our regex patterns for the more complicated lexemes.
	// Note that they need to be anchored to the start of the string (with the '^' character)
	// because of how the lexing algorithm works (characters are consumed from the beginning).
	lazy_static! {
		pub static ref ID_REGEX: Regex =
			Regex::new(r#"^([\pL_][\pL\pN_]*)"#).unwrap();

		/// Matches all keywords plus more.
		pub static ref KW_REGEX: Regex = Regex::new("^([_a-z]{3,10})").unwrap();

		pub static ref INT_REGEX: Regex = Regex::new(r#"^(\d+)"#).unwrap();
		pub static ref STR_REGEX: Regex = Regex::new("^\"(.*?)\"").unwrap();
		pub static ref FLOAT_REGEX: Regex = Regex::new(r#"^(\d*\.\d+)"#).unwrap();

		pub static ref RANGE_ELLIPSIS_REGEX: Regex = Regex::new(r#"^\.{2,3}"#).unwrap();

		pub static ref AND_REGEX: Regex = Regex::new(r#"^and|&"#).unwrap();
		pub static ref OR_REGEX: Regex = Regex::new(r#"^or|\|"#).unwrap();
		pub static ref XOR_REGEX: Regex = Regex::new(r#"^xor"#).unwrap();
	}

	// operator token characters
	/// Negation and substraction.
	pub const POW: char = '^';
	pub const MUL: char = '*';
	pub const DIV: char = '/';
	pub const DICE_THROW: char = 'd';
	pub const PLUS: char = '+';
	pub const MINUS: char = '-';

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
