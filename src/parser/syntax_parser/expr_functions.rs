use syntax_tree::*;
use parser::syntax_parser::synpar_util::*;
use error::{RollerErr, SynErr, ParseResult};

#[derive(Debug, Clone, PartialEq)]
pub struct IncompAst {
	op: Option<InfixOp>,
	left: IncAstNode,
	right: IncAstNode,
}

#[derive(Debug, Clone, PartialEq)]
pub enum IncAstNode {
	ParTmp(Vec<ParseTemp>),
	Node(Box<IncompAst>),
	Singular(Expr),
	Empty
}

/// Transforms a ParseTemp vector into incomplete AST form.
pub fn pt_vec_to_incomp_ast(input: &Vec<ParseTemp>) -> IncompAst {
	process_pt_vec(input, PREC_MIN)
}

/// prec_level is the precedence_level of the operator to be applied as the AST nodes op.
fn process_pt_vec(input: &Vec<ParseTemp>, prec_level: i32) -> IncompAst {
	// the operator of our precedence_level level
	let mut op_found = None;

	let mut temp_left = Vec::new();
	let mut temp_right = Vec::new();

	// go through everything and move it to temp_left or temp_right
	for n in input.iter() {
		// check the mode whether we are in the left side or the right side of the operator
		if op_found == None {
			// we are at the left side of the operator
			match n {
				&ParseTemp::Op(ref o) => {
					// did we find our operator?
					if OP_INFOS[o].level == prec_level {
						op_found = Some(*o);
					}
					else {
						temp_left.push(ParseTemp::Op(*o) );
					}
				},
				_ => temp_left.push(n.clone() )
			}
		}
		else {
			// we are the right side of the operator
			temp_right.push(n.clone() );
		}
	}

	// if no operation of this level is found, try again with a larger precedence level
	if op_found == None && prec_level < PREC_MAX {
		return process_pt_vec(input, prec_level + 1)
	}

	// if a parse temp has 0-1 arguments, this lambda function handles them
	let handle_singular_arg = |pt_vec: Vec<ParseTemp>| -> IncAstNode {
		match pt_vec.first() {
			// if the last remaining token is an operator, make it a node
			Some(&ParseTemp::Op(ref o)) => {
				IncAstNode::Node(Box::new(
					IncompAst {
						op: Some(*o),
						left:	IncAstNode::Empty,
						right:	IncAstNode::Empty,
					}
				))
			},
			// if it's an expression we're okay
			Some(&ParseTemp::Exp(ref e)) => IncAstNode::Singular(e.clone()),
			// it was an empty vector so let's return an empty node
			None => IncAstNode::Empty,
		}
	};

	// ---
	// check and process left
	let new_left: IncAstNode;

	// if the left is just a singular or nullary parameter we're okay
	if temp_left.len() <= 1 {
		// exit condition from recursion of the left children
		new_left = handle_singular_arg(temp_left);
	}
	else if prec_level < PREC_MAX {
		// recursively go through the higher precedence levels on temp_left
		new_left = IncAstNode::Node(Box::new(
			process_pt_vec(&temp_left, prec_level + 1)
		));
	}
	else {
		new_left = IncAstNode::ParTmp(temp_left);
	}

	// ---
	// check and process right
	let new_right: IncAstNode;

	if temp_right.len() <= 1 {
		// exit condition from recursion of the righ children
		new_right = handle_singular_arg(temp_right);
	}
	else {
		// recursively do the rest
		new_right = IncAstNode::Node(Box::new(process_pt_vec(&temp_right, prec_level)) )
	}

	IncompAst {
		op:		op_found,
		left:	new_left,
		right:	new_right
	}
}

pub fn complete_iast(input: IncompAst) -> ParseResult<Expr> {
	match input.op {
		None => {
			// if the op is none then the right should be left empty by the algorithm of process_pt_vec
			assert!(input.right == IncAstNode::Empty);

			// check the left children which should be singular expression since op is none
			match input.left {
				IncAstNode::Singular(e) => Ok(e),
				// these two shouldn't be reached unless the previous algorithm has bugs
				IncAstNode::Empty => Err(RollerErr::SyntaxError(SynErr::EmptyCommand)),
				_ => Err(RollerErr::SyntaxError(SynErr::MalformedAST)),
			}
		},
		Some(o) => {
			let lhs =
				match input.left {
					IncAstNode::Singular(e) => Some(Box::new(e)),
					IncAstNode::Node(n) => Some(Box::new(try!(complete_iast(*n))) ),
					IncAstNode::Empty => None,
					IncAstNode::ParTmp(_) =>
						return Err(RollerErr::SyntaxError(SynErr::TooManyParameters)),
				};

			let rhs =
				match input.right {
					IncAstNode::Singular(e) => Some(Box::new(e)),
					IncAstNode::Node(n) => Some(Box::new(try!(complete_iast(*n))) ),
					IncAstNode::Empty => None,
					IncAstNode::ParTmp(_) =>
						return Err(RollerErr::SyntaxError(SynErr::TooManyParameters)),
				};

			Ok(Expr::Op{
				op: o,
				left: lhs,
				right: rhs
			})
		}
	}
}
