use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_parser::synpar_util::*;

pub type InType<'a> = &'a [Lexeme];

pub fn parse_cmd<'a>(tokens: InType<'a>) -> ParseOutput<Cmd, InType<'a>> {
	Err(0)
	.or(parse_stmt(tokens))
	.or(parse_expr(tokens))
}

fn parse_stmt(input: InType) -> ParseOutput<Cmd, InType> {
	let res = Err(0)
		// .or(parse_assign(input))
		// .or(parse_fundef(input))
		// .or(parse_delete(input))
		// .or(parse_clear(input))
		// .or(parse_run(input))
		// .or(parse_save(input))
	;

	match res {
		Ok( (stmt, i) ) => Ok( (Cmd::Statement(stmt), i) ),
		Err(e) => Err(e),
	}
}

fn parse_expr(input: InType) -> ParseOutput<Cmd, InType> {
	let res = Err(0)
		// .or(parse_kwexpr(input))
		// .or(parse_filter(input))
		// .or(parse_op(input))
		.or(parse_value(input))
		// .or(parse_funcall(input))
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
	map_output(expect_token!(input, Lexeme::Id(Ident)), &Expr::Var)
}

fn parse_value(input: InType) -> ParseOutput<Expr, InType> {
	map_output(
		lex_output_to_val_output(consume_token(input)),
	&Expr::Val)
}
