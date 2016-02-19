use syntax_structures::*;


named!(pub parse_cmd<Cmd>, alt!(
		parse_stmt => {
			|_| Cmd::Empty
		}
		| parse_expr => {
			|_| Cmd::Empty
		}
	)
);

named!(parse_stmt, tag!("s"));
named!(parse_expr, tag!("e"));
