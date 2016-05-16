use std::ops::{Add, Sub, Neg, Mul, Div};

use common_util::Side;
use syntax_tree::*;
use eval::types::*;
use eval::env::*;
use error::{RollerErr, EvalErr, ParseResult};

macro_rules! expect_binary_op {
	($op: expr, $lhs: expr, $rhs: expr, $fun: path) => {
		match ($lhs, $rhs) {
			(Some(l_val), Some(r_val)) => $fun(l_val, r_val),

			(None, Some(_)) =>
				Err(RollerErr::EvalError(
					EvalErr::MissingOpArg{op: $op, side: Side::Left}
				)),
			(Some(_), None) =>
				Err(RollerErr::EvalError(
					EvalErr::MissingOpArg{op: $op, side: Side::Right}
				)),
			(None, None) =>
				Err(RollerErr::EvalError(
					EvalErr::NoOpArgs($op)
				)),
			}
	};
}


/// Evaluates a command and returns the value, if it was an expression, or returns an error.
pub fn eval_cmd(input: Cmd, env: &mut RollerEnv) -> Option<ParseResult<Value>> {
	match input {
		Cmd::Statement(s) =>
			match eval_stmt(s, env) {
				Ok(()) => None,
				Err(e) => Some(Err(e))
			},
		Cmd::Expression(e) =>
			match eval_expr(e, env) {
				Ok(val) => Some(Ok(val)),
				Err(e) => Some(Err(e))
			}
	}
}

/// Evaluates a statement and returns an error if one was encountered.
pub fn eval_stmt(input: Stmt, env: &mut RollerEnv) -> ParseResult<()> {
	match input {
		Stmt::Assign(id, exp) => {
			let val = try!(eval_expr(exp, env));
			Ok(env.assign_var(id, val) )
		},
		Stmt::FnDef(id, fun) =>
			Ok(env.declare_function(id, fun)),
		Stmt::Delete(id) =>
			Ok(env.delete_id(&id)),
		Stmt::Clear =>
			Ok(env.clear()),
		/*Stmt::Run(path) =>
			,
		Stmt::Save(path) =>
			,*/
		_ => Err(RollerErr::EvalError(EvalErr::Unimplemented))
	}
}

/// Evaluates an expression and returns a value or error.
pub fn eval_expr(input: Expr, env: &RollerEnv) -> ParseResult<Value> {
	match input {
		Expr::Val(val) =>
			Ok(val),
		Expr::List(vec_exp) =>
			Ok(Value::List(try!(eval_expr_vec(vec_exp, env))) ),
		//Expr::Range{start, step, end} =>
		//	,
		Expr::Var(id) =>
			env.get_var(id),
		Expr::FunCall(id, args) =>
			env.call_fun(id, try!(eval_expr_vec(args, env))),
		Expr::Op{op, left, right} => {
			let eval_opt = |opt_exp: Option<Box<Expr>>|
				match opt_exp.map(|e| eval_expr(*e, env)) {
					Some(Ok(v)) => Ok(Some(v)),
					None => Ok(None),
					Some(Err(e)) => Err(e)
				};

			eval_op(op, try!(eval_opt(left)), try!(eval_opt(right)) )
		},
		_ => Err(RollerErr::EvalError(EvalErr::Unimplemented))
	}
}

/// Evaluates a vector of expressions and stops at the first error.
fn eval_expr_vec(expr_vec: Vec<Expr>, env: &RollerEnv) -> ParseResult<Vec<Value>> {
	let mut to_return = Vec::new();
	for i in expr_vec.into_iter() {
		match eval_expr(i, env) {
			Ok(v) => to_return.push(v),
			Err(e) => return Err(e)
		}
	}
	return Ok(to_return);
}

/// Evaluates an infix operation
fn eval_op(op: InfixOp, lhs: Option<Value>, rhs: Option<Value>) -> ParseResult<Value> {
	match op {
		InfixOp::Dice =>
			Err(RollerErr::EvalError(
				EvalErr::Unimplemented
			)),
		InfixOp::Plus =>
			match rhs {
				Some(r_val) =>
					match lhs {
						// case a + b
						Some(l_val) => l_val.add(r_val),
						// case + a
						None => Ok(r_val)
					},
				None =>
					Err(RollerErr::EvalError(
						EvalErr::MissingOpArg{op: op, side: Side::Right}
					))
			},
		InfixOp::Minus =>
			match rhs {
				Some(r_val) =>
					match lhs {
						// case a - b
						Some(l_val) => l_val.sub(r_val),
						// case - a
						None => r_val.neg()
					},
				None =>
					Err(RollerErr::EvalError(
						EvalErr::MissingOpArg{op: op, side: Side::Right}
					))
			},
		InfixOp::Mul => expect_binary_op!(op, lhs, rhs, Value::mul),
		InfixOp::Div => expect_binary_op!(op, lhs, rhs, Value::div),
		InfixOp::Pow => expect_binary_op!(op, lhs, rhs, Value::pow),
	}
}
