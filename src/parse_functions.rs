use syntax_structures::*;

use nom::IResult;

use std::str::FromStr;

/// Parses commands
named!(pub parse_cmd(&str) -> Cmd,
	alt!(
		parse_stmt => {
			|_| Cmd::Empty
		}
		| parse_expr => {
			|exp: Expr| Cmd::Expression(exp)
		}
	)
);

// Parses statements
named!(parse_stmt(&str) -> &str,
	tag_s!("s")
);

/// Parses expressions
named!(parse_expr(&str) -> Expr,
	alt!(
		parse_literal => {
			|litexp: LiteralExpr| Expr::Literal(Box::new(litexp))
		}
		| parse_function_call => {
			|fun_sign: (Ident, Vec<Expr>)| Expr::FunCall(fun_sign)
		}
		| parse_variable_call => {
			|id: Ident| Expr::Var(id)
		}
	)
);

/// Parses literal values.
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

named!(parse_function_call(&str) -> (Ident, Vec<Expr>),
	tuple!(
		parse_identifier,
		delimited!(
			tag_s!("("),
			separated_list!(
				//take_while1_s!(call!(|c: char| c == ',' || c.is_whitespace()) ),
				tag_s!(","),
				parse_expr
			),
			tag_s!(")")
		)
	)
);

named!(parse_variable_call(&str) -> Ident,
	alt!(parse_identifier)
);

/// Parses integer literals.
named!(parse_int_literal(&str) -> i64,
	chain!(
		cap_vec: re_capture!(r"^(-?\d*)") ~ // capture an integer numeral with a regex pattern
		str_slice: expr_opt!(cap_vec.get(1)) ~ // get the captured str
		float: expr_res!(i64::from_str(str_slice)), // type conversion
		|| { float }
	)
);

/// Parses float literals.
/// The number before the decimal point is optional and it is assumed to be 0 if missing.
named!(parse_float_literal(&str) -> f64,
	chain!(
		cap_vec: re_capture!(r"^(-?\d*\.\d+)") ~ // capture a real numeral with a regex pattern
		str_slice: expr_opt!(cap_vec.get(1)) ~ // get the captured str
		float: expr_res!(f64::from_str(str_slice)), // type conversion
		|| { float }
	)
);

/// Parses double quote limited string literals.
/// The strings may not contain double quote characters.
/// There are no escape characters in the strings (yet).
fn parse_str_literal(i: &str) -> IResult<&str, String> {
	chain!(i,
		cap_vec: re_capture!("^\"([^\"]*)\"") ~ // capture the string literal with a regex pattern
		str_slice: expr_opt!(cap_vec.get(1)) ~ // get the captured str
		string: expr_res!(String::from_str(str_slice)), // type conversion
		|| { string }
	)
}

/// Parses an identifier.
/// The first character must be an unicode letters or underscores, and the rest can be unicode letters, numbers and underscores, but there must be at least one character that is not an underscore. (Similar to Rusts identifier syntax)
// TODO: Use Unicode identifier and pattern syntax http://www.unicode.org/reports/tr31/tr31-23.html
named!(parse_identifier(&str) -> Ident,
	chain!(
		// capture an identifier string with a regex pattern
		cap_vec: re_capture!(r#"^(_*[\pL][\pL\pN_]*|_+[\pL\pN]+)"#) ~
		str_slice: expr_opt!(cap_vec.get(1)) ~ // get the captured str
		id: expr_res!(Ident::from_str(str_slice)), // type conversion
		|| { id }
	)
);
