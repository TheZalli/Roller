use syntax_tree::*;
use parser::parse_util::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_parser::synpar_util::*;
use parser::syntax_parser::expr_functions;
use eval::types::*;
use error::{RollerErr, SynErr, ParseResult};

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
pub fn parse_expr_to_end(input: InType, end_token: Lexeme) -> ParseOutput<Expr, InType> {
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
		// does recursive calls to parse other expressions
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
				match input_queue.split_first() {
					// if we're dealing with a function call
					Some((&Lexeme::LeftParen, new_input)) => {
						match parse_expr_list(new_input, Lexeme::RightParen) {
							Ok((exp_vec, new_input)) => {
								input_queue = new_input;
								ParseTemp::Exp(Expr::FunCall(id, exp_vec))
							},
							// if the call was badly formed, return error
							Err(_) =>
								return Err(RollerErr::SyntaxError(SynErr::InvalidFunctionCall))
						}
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
			// handle bracketed lists
			Lexeme::LeftBracket => {
				match parse_expr_list(input_queue, Lexeme::RightBracket) {
					Ok((exp_vec, new_input)) => {
						input_queue = new_input;
						ParseTemp::Exp(Expr::List(exp_vec))
					},
					Err(e) => return Err(e)
				}
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
			_ => return Err(RollerErr::SyntaxError(SynErr::UnexpectedToken(tk)))
		};
		work_output.push(work_var);
	}

	// Phase 2 of the algorithm: Apply ops
	// go through the precedence levels and create the abstract syntax tree
	// this phase is in two functions

	// the root of the unfinished abstract syntax tree
	let root = expr_functions::pt_vec_to_incomp_ast(&work_output);

	// DEBUG
	//println!("Incomplete AST: {:?}", &root);

	// Return the values and the unconsumed input
	match expr_functions::complete_iast(root) {
		Ok(exp) => Ok((exp, input_queue)),
		Err(e) => Err(e)
	}
}

/// Parses and returns a comma separated list of expressions.
fn parse_expr_list(input: InType, end_token: Lexeme) -> ParseOutput<Vec<Expr>, InType> {
	match input.first() {
		// if the list was empty return an empty vector
		Some(&ref tk) if *tk == end_token => return Ok((Vec::new(), &input[1..])),
		// if the input was empty already
		None => return Err(RollerErr::SyntaxError(SynErr::UnexpectedEnd)),
		_ => {}
	};

	let mut exp_vec = Vec::new();
	let mut mut_input = input.clone();

	loop {
		// read to next comma
		match parse_expr_to_end(mut_input, Lexeme::Comma) {
			Ok((exp, new_input)) => {
				exp_vec.push(exp);
				mut_input = new_input;
			},
			Err(RollerErr::SyntaxError(SynErr::UnexpectedToken(ref tk))) if *tk == end_token => {
				// read to the end token if reading to next comma was unsuccesful
				match parse_expr_to_end(mut_input, end_token) {
					Ok((exp, new_input)) => {
						exp_vec.push(exp);
						return Ok((exp_vec, new_input))
					},
					Err(e) => return Err(e)
				}
			},
			Err(e) => return Err(e)
		};
	}

}
