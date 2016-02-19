use syntax_structures::*;


named!(pub parse_cmd<CmdType>, alt!(
		parse_stmt => {
			|_| CmdType::Statement
		}
		| parse_expr => {
			|_| CmdType::Expression
		}
	)
);

named!(parse_stmt, tag!("s"));
named!(parse_expr, tag!("e"));
