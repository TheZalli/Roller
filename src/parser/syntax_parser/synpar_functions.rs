use parser::parse_util::*;
use parser::syntax_types::*;
//use parser::lexer::lexer_util::lexemes::*;

use parser::syntax_parser::synpar_util::*;
use parser::syntax_parser::expr_parse::*;
use parser::syntax_parser::stmt_parse::*;

/// Parses a single command.
pub fn parse_cmd<'a>(tokens: InType<'a>) -> ParseResult<Cmd> {
	Err(0)
	.or(parse_stmt(tokens).map(&Cmd::Statement))
	.or(parse_expr(tokens).map(&Cmd::Expression))
}
