use std::ops::{Add, Sub, Neg, Mul, Div};

use common_util::{IntType, Side, Pow};
use syntax_tree::*;
use eval::types::*;
use eval::env::*;
use error::{RollerErr, EvalErr, ParseResult};

macro_rules! expect_binary_op {
	($op: expr, $lhs: expr, $rhs: expr, $fun: path) => {
		match ($lhs, $rhs) {
			(Some(l_val), Some(r_val)) => $fun(l_val, r_val),

			// the rest of these patterns are just for the sake of informative error messages
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
pub fn eval_cmd(input: &Cmd, env: &mut RollerEnv) -> Option<ParseResult<Value>> {
	match input {
		&Cmd::Statement(ref s) =>
			match eval_stmt(s, env) {
				Ok(()) => None,
				Err(e) => Some(Err(e))
			},
		&Cmd::Expression(ref e) =>
			match eval_expr(e, env) {
				Ok(val) => Some(Ok(val)),
				Err(e) => Some(Err(e))
			}
	}
}

/// Evaluates a statement and returns an error if one was encountered.
pub fn eval_stmt(input: &Stmt, env: &mut RollerEnv) -> ParseResult<()> {
	match input {
		&Stmt::Assign(ref id, ref exp) => {
			let val = try!(eval_expr(exp, env));
			Ok(env.assign_var(id, val) )
		},
		&Stmt::FnDef(ref id, ref fun) =>
			Ok(env.declare_function(id, fun)),
		&Stmt::Delete(ref id) =>
			env.delete_id(id).map(|_| ()), // TODO print the result instead of ignoring
		&Stmt::Clear =>
			Ok(env.clear()),
		/*Stmt::Run(path) =>
			,
		Stmt::Save(path) =>
			,*/
		_ => Err(RollerErr::EvalError(EvalErr::Unimplemented))
	}
}

/// Evaluates an expression and returns a value or error.
pub fn eval_expr(input: &Expr, env: &RollerEnv) -> ParseResult<Value> {
	match input {
		&Expr::Val(ref val) =>
			Ok(val.clone()),
		&Expr::List(ref vec_exp) =>
			Ok(Value::List(try!(eval_expr_vec(&vec_exp, env))) ),
		//Expr::Range{start, step, end} =>
		//	,
		&Expr::Var(ref id) =>
			env.get_var(id),
		&Expr::FunCall(ref id, ref args) =>
			env.call_fun(id, try!(eval_expr_vec(args, env))),

		// evaluate a dice throw
		&Expr::Op{op, ref left, ref right} if op == InfixOp::Dice => {
			let n = match left.clone().map(|exp| eval_expr(&*exp, env)) {
				None => 1,
				Some(Ok(Value::Num(x))) if x.is_int() => x.as_int(),
				Some(Ok(x)) =>
					return Err(RollerErr::EvalError(
							EvalErr::ExpectedType{
								expected: RollerType::NumInt,
								found: RollerType::from(x),
							}
					)),
				Some(Err(e)) => return Err(e),
			};

			let mut sides_list = None;

			let sides = match right.clone().map(|exp| eval_expr(&*exp, env)) {
				None => 6,
				Some(Ok(Value::Num(x))) if x.is_int() => x.as_int(),
				Some(Ok(Value::List(x))) => {
					sides_list = Some(x.clone());
					x.len() as IntType
				},
				Some(Ok(x)) =>
					return Err(RollerErr::EvalError(
							EvalErr::ExpectedType{
								expected: RollerType::NumInt,
								found: RollerType::from(x),
							}
					)),
				Some(Err(e)) => return Err(e),
			};

			if n < 0 {
				Err(RollerErr::EvalError(EvalErr::ExpectedPosNum(NumType::Int(n)) ))
			}
			else if sides <= 0 {
				Err(RollerErr::EvalError(EvalErr::ExpectedPosNum(NumType::Int(sides)) ))
			}
			else {
				let throws = env.get_roll(n, sides);
				if throws.len() != 1 {
					match sides_list {
						None => Ok(Value::List(
							throws.into_iter()
							.map(&NumType::Int) // package the integer into enums
							.map(&Value::Num)
							.collect()
						)),
						// if we had a list return it's values indexed by the rolls
						Some(list) => Ok(Value::List(
							throws.into_iter()
							.map(|x: i32| list[x as u32 as usize - 1].clone())
							.collect()
						))
					}
				}
				// in case we have a singular result, return it as a singular value
				else {
					match sides_list {
						None => Ok(Value::Num(NumType::Int(throws[0]))),
						Some(list) => Ok(list[throws[0] as u32 as usize - 1].clone())
					}
				}
			}
		},

		&Expr::Op{op, ref left, ref right} => {
			let eval_opt = |opt_exp: Option<Box<Expr>>|
				match opt_exp.map(|e| eval_expr(&*e, env)) {
					Some(Ok(v)) => Ok(Some(v)),
					None => Ok(None),
					Some(Err(e)) => Err(e)
				};
			eval_op(op, try!(eval_opt(left.clone() )), try!(eval_opt(right.clone() )) )
		},

		_ => Err(RollerErr::EvalError(EvalErr::Unimplemented))
	}
}

/// Evaluates a vector of expressions and stops at the first error.
fn eval_expr_vec(expr_vec: &Vec<Expr>, env: &RollerEnv) -> ParseResult<Vec<Value>> {
	let mut to_return = Vec::new();
	for i in expr_vec.into_iter() {
		match eval_expr(&i, env) {
			Ok(v) => to_return.push(v),
			Err(e) => return Err(e)
		}
	}
	return Ok(to_return);
}

/// Evaluates an infix operation
fn eval_op(op: InfixOp, lhs: Option<Value>, rhs: Option<Value>) -> ParseResult<Value> {
	match op {
		InfixOp::Dice => unreachable!(),
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
