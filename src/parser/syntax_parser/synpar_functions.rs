use syntax_tree::*;
use parser::syntax_parser::synpar_util::*;
use parser::syntax_parser::expr_parse::*;
use parser::syntax_parser::stmt_parse::*;
use error::ParseResult;

/// Parses a single command.
pub fn parse_cmd<'a>(tokens: InType<'a>) -> ParseResult<Cmd> {
	parse_stmt(tokens).map(&Cmd::Statement)
	.or(parse_expr(tokens).map(&Cmd::Expression))
}
