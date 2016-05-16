use std::path::PathBuf;

use syntax_tree::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_parser::expr_parse::*;
use parser::syntax_parser::synpar_util::*;
use error::{RollerErr, SynErr, ParseResult};

#[allow(unused_variables)]
pub fn parse_stmt(input: InType) -> ParseResult<Stmt> {
	Err(())
	.or(parse_assign(input))
	.or(parse_fundef(input))
	.or(parse_delete(input))
	.or(parse_clear(input))
	.or(parse_run(input))
	.or(parse_save(input))
	.or(Err(RollerErr::SyntaxError(SynErr::Unimplemented)))
}

fn parse_assign(input: InType) -> ParseResult<Stmt, ()> {
	// if we have an identifier, followed by =, followed by expression
	if let Some((&Lexeme::Id(ref id), input)) = input.split_first() {
		if let Some((&Lexeme::Eq, input)) = input.split_first() {
			if let Ok(exp) = parse_expr(input) {
				return Ok(Stmt::Assign(id.clone(), exp));
			}
		}
	}
	Err(())
}

fn parse_fundef(input: InType) -> ParseResult<Stmt, ()> {
	if let Some((&Lexeme::Id(ref id), input)) = input.split_first() {
		if let Some((&Lexeme::LeftParen, input)) = input.split_first() {
			// parse parameters
			let mut mut_input = input.clone();
			let mut param_ids = Vec::new();

			loop {
				match mut_input.split_first() {
					Some((&Lexeme::Id(ref id), input)) => {
						// parameter found
						param_ids.push(id.clone());
						mut_input = input;
					},
					Some((&Lexeme::Comma, input)) => {
						// ignore commas
						// commas are optional
						mut_input = input
					},
					Some((&Lexeme::RightParen, input)) => {
						// found the end of parameter definition
						mut_input = input;
						break;
					},
					_ => return Err(())
				}
			}

			// check if we have an equal sign and an expression
			if let Some((&Lexeme::Eq, input)) = mut_input.split_first() {
				if let Ok(exp) = parse_expr(input) {
					return Ok(Stmt::FnDef(id.clone(), RollerFun::new(param_ids, exp) ));
				}
			}

		}
	}
	Err(())
}

fn parse_delete(input: InType) -> ParseResult<Stmt, ()> {
	if let Some((&Lexeme::Kw(KwsToken::Delete), input)) = input.split_first() {
		if let Some((&Lexeme::Id(ref id), input)) = input.split_first() {
			if input.get(0) == Some(&Lexeme::End) {
				return Ok(Stmt::Delete(id.clone()) );
			}
		}
	}
	Err(())
}

fn parse_clear(input: InType) -> ParseResult<Stmt, ()> {
	if input.len() == 2 { // clear, end
		if let Lexeme::Kw(KwsToken::Clear) = input[0] {
			return Ok(Stmt::Clear);
		}
	}
	Err(())
}

fn parse_run(input: InType) -> ParseResult<Stmt, ()> {
	if let Some((&Lexeme::Kw(KwsToken::Run), input)) = input.split_first() {
		if let Some((&Lexeme::Id(ref s), input)) = input.split_first() {
			if input.get(0) == Some(&Lexeme::End) {
				return Ok(Stmt::Run(PathBuf::from(s) ));
			}
		}
	}
	Err(())
}

fn parse_save(input: InType) -> ParseResult<Stmt, ()> {
	if let Some((&Lexeme::Kw(KwsToken::Save), input)) = input.split_first() {
		if let Some((&Lexeme::Id(ref s), input)) = input.split_first() {
			if input.get(0) == Some(&Lexeme::End) {
				return Ok(Stmt::Save(PathBuf::from(s) ));
			}
		}
	}
	Err(())
}
