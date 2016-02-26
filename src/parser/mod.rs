mod parse_util;

pub mod syntax_types;
pub mod lexer;
pub mod syntax_parser;

pub use parser::lexer::lexer_functions::*; // imports the function tokenize
