use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;
//use parser::syntax_parser::expr_parse::*;
use parser::syntax_parser::synpar_util::*;

pub fn parse_stmt(input: InType) -> ParseResult<Stmt> {
	Err(0)
	// .or(parse_assign(input))
	// .or(parse_fundef(input))
	// .or(parse_delete(input))
	// .or(parse_clear(input))
	// .or(parse_run(input))
	// .or(parse_save(input))


	// match res {
	// 	Ok( (stmt, i) ) => Ok( (Cmd::Statement(stmt), i) ),
	// 	Err(e) => Err(e),
	// }
}
