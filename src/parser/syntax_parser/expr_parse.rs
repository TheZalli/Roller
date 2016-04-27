use std::collections::HashMap;
use std::collections::VecDeque;
use std::hash::Hash;
use std::iter::FromIterator;

use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_parser::synpar_util::*;

/// Information associated with an operation
#[derive(Clone, Copy)]
struct OpInfo {
	/// Precedence level
	level: u32,
	/// associativity
	assoc: Assoc,
	// Argument info
	arg_info: ArgInfo,
}

impl OpInfo {
	fn new(precedence_level: u32, associativity: Assoc, argument_info: ArgInfo) -> Self {
		OpInfo {
			level: precedence_level,
			assoc: associativity,
			arg_info: argument_info
		}
	}
}

#[derive(PartialEq, Clone, Copy)]
enum Assoc {
	Left,
	Right
}

#[derive(PartialEq, Clone, Copy)]
#[allow(dead_code)] // TODO: remove when all the variants are used somewhere
enum ArgInfo {
	/// Operators with a singular argument
	/// The argument tells at which side of the argument the operator must be in.
	Unary(Assoc),
	/// Operators with two arguments
	Binary,
	/// For binary operators that can be used as unary, like substraction/negation.
	/// The argument tells at which side of the argument the operator must be in.
	AllowUnary(Assoc),
	/// For special operators that can have 0-2 arguments.
	/// For the dice operator.
	AllowNullary,
	// / For function calls etc
	//Variable,
}

lazy_static! {
	static ref OP_INFOS: HashMap<InfixOp, OpInfo> =
		vec2map(vec![
			(InfixOp::Plus,  OpInfo::new(1, Assoc::Left, ArgInfo::AllowUnary(Assoc::Left)) ),
			(InfixOp::Minus, OpInfo::new(1, Assoc::Left, ArgInfo::AllowUnary(Assoc::Left)) ),
			(InfixOp::Mul, OpInfo::new(3, Assoc::Left, ArgInfo::Binary)),
			(InfixOp::Div, OpInfo::new(3, Assoc::Left, ArgInfo::Binary)),
			(InfixOp::Pow, OpInfo::new(4, Assoc::Right, ArgInfo::Binary)),
			(InfixOp::Dice, OpInfo::new(5, Assoc::Left, ArgInfo::AllowNullary))
		]);
}

const PREC_MIN: u32 = 1;
const PREC_MAX: u32 = 5;

fn vec2map<K: PartialEq + Eq + Hash, T>(vec: Vec<(K, T)>) -> HashMap<K, T> {
	let mut map = HashMap::new();
	for (k, t) in vec {
		map.insert(k, t);
	}
	return map;
}

/// Parses expressions
pub fn parse_expr(input: InType) -> ParseResult<Expr> {
	match parse_expr_to_end(input, Lexeme::End) {
		Ok((exp, i)) =>
			if i.is_empty() {
				Ok(exp)
			}
			else {
				Err(1)
			},
		Err(e) => Err(e),
	}
}

#[derive(Debug, Clone)]
enum ParseTemp {
	Op(InfixOp),
	Exp(Expr),
}

/// Parses expression until the given end_token is found
/// Returns the unconsumed input
pub fn parse_expr_to_end(input: InType, end_token: Lexeme) -> ParseResult<(Expr, InType)> {
	// our temporary vector that ideally gets worked into a singular expression
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
			None => return Err(2)
		};

		let tk = pair.0.clone();
		input_queue = pair.1;

		// if we encountered the end
		// NOTE: the ending token is consumed away, this is important with parentheses
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
						return Err(3); // TODO: implement
					},
					// if we have a variable
					Some(_) => {
						ParseTemp::Exp(Expr::Var(id))
					},
					// if the input ran out prematurely before the end_token
					None => return Err(4)
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
			_ => return Err(5)
		};
		work_output.push(work_var);
	}

	/*/ Phase 2 of the algorithm: Apply ops
	// go through the precedence levels
	for level in PREC_MIN..(PREC_MAX+1) {
		let arg = get_arg_under_prec_lvl(&mut work_output, level);
		// TODO
	}*/

	// DEBUG
	//println!("left input: {:?}", input_queue);
	//println!("work_output: {:?}", work_output);

	// Return the values
	if work_output.len() == 1 {
		match work_output[0] {
			// we got a expression as a result, we're ok
			ParseTemp::Exp(ref e) => Ok((e.clone(), input_queue)),
			// we got only a lonely operation
			// if this was nullary op it would have been catched in phase 2
			ParseTemp::Op(_) => Err(6)
		}
	}
	else {
		Err(7)
	}
}

fn get_arg_under_prec_lvl(inp: &mut Vec<ParseTemp>, level: u32) -> Vec<ParseTemp> {
	let mut arg = Vec::new();

	// TODO: make this better
	let mut inp_queue = VecDeque::from_iter(inp.iter().cloned());

	// loop through the input until you find an operator with the given precedence level
	loop {
		match inp_queue.pop_front() {
			// it's an operator
			Some(ParseTemp::Op(o)) => {
				// all of the lower level operations should be already handled
				assert!(OP_INFOS[&o].level >= level);

				// this op is of our level
				if OP_INFOS[&o].level == level {
					// put it back
					inp_queue.push_front(ParseTemp::Op(o));
					break;
				}
				else {
					arg.push(ParseTemp::Op(o));
				}
			},
			// it's an expression
			Some(e) => {
				arg.push(e);
			},
			// ran out of input
			None => break,
		}
	}
	*inp = Vec::from_iter(inp_queue.iter().cloned());
	return arg;
}
