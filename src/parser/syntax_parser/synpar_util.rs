/*use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;


pub fn lex_output_to_val_output<I>(outp: ParseOutput<Lexeme, I>) -> ParseOutput<Value, I> {
	match outp {
		Ok( (token, i) ) => Ok(
			(
				match lexeme_literal_to_value(token) {
					Ok(val) => val,
					Err(e) => return Err(e)
				},
				i
			)
		),
		Err(e) => Err(e)
	}
}

/// Transforms all literal lexemes into Values
fn lexeme_literal_to_value(token: Lexeme) -> ParseResult<Value> {
	match token {
		Lexeme::IntLit(i) =>  Ok(Value::Num(NumType::Int(i))),
		Lexeme::RealLit(f) => Ok(Value::Num(NumType::Real(f))),
		Lexeme::StrLit(s) =>  Ok(Value::Str(s)),
		_ => Err(123) // TODO: fix
	}
}*/
