use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_parser::synpar_util::*;
use parser::syntax_parser::expr_functions;
use error::{RollerErr, SynErr};

/// Parses expressions
pub fn parse_expr(input: InType) -> ParseResult<Expr> {
	match parse_expr_to_end(input, Lexeme::End) {
		Ok((exp, i)) =>
			// if the input is empty after parsing
			if i.is_empty() {
				Ok(exp)
			}
			else {
				Err(RollerErr::SyntaxError(
					SynErr::UnexpectedToken(i[0].clone())
				))
			},
		Err(e) => Err(e),
	}
}

/// Parses expression until the given end_token is found
/// Returns the unconsumed input
pub fn parse_expr_to_end(input: InType, end_token: Lexeme) -> ParseResult<(Expr, InType)> {
	// our temporary vector that ideally gets worked into the abstract syntax tree (AST) form
	let mut work_output: Vec<ParseTemp> = Vec::new();

	// a mutable clone of the input
	// we don't use VecDeque because then we would need to change it back into Vec or InType
	let mut input_queue = input.clone();

	// Phase 1 of the algorithm: Pass the input to work_output
	loop {
		// pop the first token
		let pair = match input_queue.split_first()
		{
			Some(p) => p,
			// the input ran out before encountering the end_token
			None => return Err(RollerErr::SyntaxError(SynErr::UnexpectedEnd))
		};

		let tk = pair.0.clone();
		input_queue = pair.1;

		// if we encountered the end
		// NOTE: the ending token IS consumed away. this is important with parentheses
		if tk == end_token {
			break;
		}

		// check the token and put corresponding ParseTemp variant into work_output
		let work_var = match tk
		{
			// handle number literals
			Lexeme::NumLit(x) => {
				ParseTemp::Exp(Expr::Val(Value::Num(x)) )
			},
			// handle string literals
			Lexeme::StrLit(s) => {
				ParseTemp::Exp(Expr::Val(Value::Str(s)) )
			},
			// handle identifiers
			Lexeme::Id(id) => {
				// peek the next token
				match input_queue.first() {
					// if we're dealing with a function call
					Some(&Lexeme::LeftParen) => {
						return Err(RollerErr::SyntaxError(SynErr::Unimplemented));
					},
					// if we have a variable
					_ => {
						ParseTemp::Exp(Expr::Var(id))
					},
				}
			},
			// handle infix operations from binary to nullary (dice)
			// the real work on operations is done later in the phase 2
			Lexeme::Op(op) => {
				ParseTemp::Op(op)
			},
			// handle parenthesized expressions recursively
			Lexeme::LeftParen => {
				// read until you find right parenthesis
				// Works on parenthesized sub-expressions because each recursive call removes the
				// matching right parenthesis.
				let (exp, inp) = try!(parse_expr_to_end(input_queue, Lexeme::RightParen));

				input_queue = inp;
				ParseTemp::Exp(exp)
			},
			// rest of the features are unimplemented, TODO
			_ => return Err(RollerErr::SyntaxError(SynErr::Unimplemented))
		};
		work_output.push(work_var);
	}

	// Phase 2 of the algorithm: Apply ops
	// go through the precedence levels and create the abstract syntax tree

	// the root of the unfinished abstract syntax tree
	let root = expr_functions::pt_vec_to_incomp_ast(&work_output);

	// DEBUG
	println!("Incomplete AST: {:?}", &root);

	// Return the values
	// TODO
	Err(RollerErr::SyntaxError(SynErr::Unimplemented))
}
