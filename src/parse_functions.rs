use syntax_structures::*;

use nom::{IResult,digit};
use nom::IResult::*;

use std::str;
use std::str::FromStr;

named!(pub parse_cmd<Cmd>,
	alt!(
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

named!(parse_literal<LiteralExpr>,
	alt!(
		parse_int_literal => {
			|i: i64| LiteralExpr::Num(NumType::Int(i))
		}
		| parse_float_literal => {
			|i: f64| LiteralExpr::Num(NumType::Real(i))
		}
		| parse_str_literal => {
			|string: String| LiteralExpr::Str(string)
		}
	)
);

named!(parse_int_literal<i64>,
	map_res!(
		map_res!(
			digit,
			str::from_utf8
		),
		FromStr::from_str
	)
);

named!(parse_float_literal<f64>,
	map_res!(
	 	map_res!(
			digit,
			str::from_utf8
		),
	FromStr::from_str
	)
);

fn parse_str_literal(i: &[u8]) -> IResult<&[u8], String> {
	chain!(i,
		expr_res!(str::from_utf8(i)) ~
		// captures strings that start and end with a double quotation mark.
		cap_vec: re_capture!("\"([^\"]*)\"") ~
		str_slice: expr_opt!(cap_vec.get(1))  ~
		string: expr_res!(String::from_str(str_slice)) ,
		|| { string }
	)
}

/*fn parse_str_literal(i: &[u8]) -> IResult<&[u8], String> {
	one_of!(i, ['"' as u8]);

	one_of!(i, ['"' as u8]);
}*/
