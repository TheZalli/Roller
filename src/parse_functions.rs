use syntax_structures::*;

use nom::{IResult,digit};
//use nom::IResult::*;

use std::str::FromStr;

named!(pub parse_cmd(&str) -> Cmd,
	alt!(
		/*parse_stmt => {
			|_| Cmd::Empty
		}
		|*/ parse_expr => {
			|exp: Expr| Cmd::Expression(exp)
		}
	)
);
/*
named!(parse_stmt(&str) -> &str,
	map_res!(
		map_res!(
			tag!("s"),
			str::as_bytes
		),
		str::from_utf8
	)
);*/


named!(parse_expr(&str) -> Expr,
	alt!(
		parse_literal => {
			|litexp: LiteralExpr| Expr::Literal(Box::new(litexp))
		}
	)
);

named!(parse_literal(&str) -> LiteralExpr,
	alt!(
		parse_float_literal => {
			|i: f64| LiteralExpr::Num(NumType::Real(i))
		}
		| parse_int_literal => {
			|i: i64| LiteralExpr::Num(NumType::Int(i))
		}
		| parse_str_literal => {
			|string: String| LiteralExpr::Str(string)
		}
	)
);

named!(parse_int_literal(&str) -> i64,
	map_res!(
		digit,
		FromStr::from_str
	)
);

named!(parse_float_literal(&str) -> f64,
	chain!(
		cap_vec: re_capture!(r"(\d*\.\d+)") ~
		str_slice: expr_opt!(cap_vec.get(1)) ~
		float: expr_res!(f64::from_str(str_slice)),
		|| { float }
	)
);

fn parse_str_literal(i: &str) -> IResult<&str, String> {
	chain!(i,
		cap_vec: re_capture!("\"([^\"]*)\"") ~
		str_slice: expr_opt!(cap_vec.get(1)) ~
		string: expr_res!(String::from_str(str_slice)),
		|| { string }
	)
}
