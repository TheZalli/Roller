use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;

pub type InType<'a> = &'a [Lexeme];

pub fn parse_cmd<'a>(tokens: InType<'a>) -> ParseOutput<Cmd, InType<'a>> {
	Err(0)
	.or(parse_stmt(tokens))
	.or(parse_expr(tokens))
}

fn parse_stmt(input: InType) -> ParseOutput<Cmd, InType> {
	let res = Err(0)
	// .or(parse_assign(tokens))
	// .or(parse_fundef(tokens))
	// .or(parse_delete(tokens))
	// .or(parse_clear(tokens))
	// .or(parse_run(tokens))
	// .or(parse_save(tokens))
	;

	match res {
		Ok( (stmt, i) ) => Ok( (Cmd::Statement(stmt), i) ),
		Err(e) => Err(e),
	}
}

fn parse_expr(input: InType) -> ParseOutput<Cmd, InType> {
	let res = Err(0)
	// .or(parse_kwexpr(tokens))
	// .or(parse_filter(tokens))
	// .or(parse_op(tokens))
	// .or(parse_value(tokens))
	// .or(parse_funcall(tokens))
	 .or(parse_var(input))
	 ;

	match res {
		Ok( (exp, i) ) => Ok( (Cmd::Expression(exp), i) ),
		Err(e) => Err(e),
	}
}

fn consume_token(input: InType) -> ParseOutput<Lexeme, InType> {
	match input.first() {
		Some(tk) => Ok( (tk.clone(), &input[1..]) ),
		None => Err(1)
	}
}

macro_rules! expect_token {
	($input:expr,
		$enum_name:ident :: $enum_var:ident ( $type_name:ident ) ) =>
	{
		match consume_token($input) {
			Ok( ($enum_name::$enum_var(val), i) ) => Ok( (val, i) ),
			Err(e) => Err(e),
			_ => Err(2)
		}
	};
}

/// Parses and consumes an End token, or results an error.
fn parse_end(input: InType) -> ParseOutput<(), InType> {
	match input.first() {
		Some(&Lexeme::End) => Ok( ( (), &input[1..]) ),
		_ => Err(3)
	}
}

fn parse_var(input: InType) -> ParseOutput<Expr, InType> {
	expect_token!(input, Lexeme::Id(Ident))
		.map(|(x,i)| (Expr::Var(x), i) )
}
