#![allow(dead_code)] // TODO remove
use std::f64;
use std::fmt;
use std::ops;

use syntax_tree::InfixOp;
use error::{RollerErr, EvalErr, ParseResult};

///! These are runtime value types, but the syntax parser uses some of these also.

/// An variable and function identifier
pub type Ident = String;

/// A numeral, string, or list value.
/// The basic datatype.
#[derive(PartialEq, Clone)]
pub enum Value {
	Num(NumType),
	Str(String),
	List(Vec<Value>)
}

#[derive(Debug, PartialEq, Clone, Copy)]
pub enum RollerType {
	Num,
	//NumInt,
	//NumReal,
	Str,
	List,
	//Func
}

/// A numeral, either an integer or real
#[derive(PartialEq, Clone, Copy)]
pub enum NumType {
	Int(i64),
	Real(f64),
}

/// The error allowed for floating point equality comparison.
const EPSILON: f64 = f64::EPSILON * 2.0; // multiply just to be safe about floating point errors

/// Floating point equality comparison.
fn float_eq(x: f64, y: f64) -> bool {
	let abs_diff = (x - y).abs();
	abs_diff <= EPSILON
}

impl NumType {
	/// Returns the numeral equality, which means that the integers can be compared with floats.
	fn num_eq(&self, other: &Self) -> bool {
		match ( self, other ) {
			( &NumType::Int(x), &NumType::Int(y) ) =>
				x == y,

			  ( &NumType::Real(x), &NumType::Int(y)  )
			| ( &NumType::Int(y),  &NumType::Real(x) ) =>
				float_eq(x, y as f64),

			( &NumType::Real(x), &NumType::Real(y) ) =>
				float_eq(x, y),
		}
	}

	fn to_real(self) -> Self {
		match self {
			NumType::Real(_) => self,
			NumType::Int(i) => NumType::Real(i as f64)
		}
	}
}

//impl Eq for NumType {}

// to make reading debug prints easier
impl fmt::Debug for Value {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		fmt::Display::fmt(self, f)
	}
}

impl fmt::Debug for NumType {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		fmt::Display::fmt(self, f)
	}
}

impl fmt::Display for Value {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&Value::Num(ref nt) => write!(f, "{}", nt),
			&Value::Str(ref st) => write!(f, "{}", st),
			&Value::List(ref v) => write!(f, "{:?}", v) // TODO impl Display for Value::List
		}
	}
}

impl fmt::Display for NumType {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&NumType::Int(i)  => write!(f, "{}", i),
			&NumType::Real(r) => write!(f, "{}", r)
		}
	}
}

impl fmt::Display for RollerType {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&RollerType::Num => write!(f, "numeral"),
			&RollerType::Str => write!(f, "string"),
			&RollerType::List => write!(f, "list"),
			//&RollerType::Func => write!(f, "function"),
		}
	}
}

/*impl From<Value> for RollerType {
	fn from(val: Value) -> Self {
		match val {
			Value::Num(_) => RollerType::Num,
			Value::Str(_) => RollerType::Str,
			Value::List(_) => RollerType::List,
		}
	}
}*/

impl<'a> From<&'a Value> for RollerType {
	fn from(val: &'a Value) -> Self {
		match val {
			&Value::Num(_) => RollerType::Num,
			&Value::Str(_) => RollerType::Str,
			&Value::List(_) => RollerType::List,
		}
	}
}

// ---

impl ops::Add for Value {
	type Output = ParseResult<Self>;
	fn add(self, rhs: Self) -> Self::Output {
		match (self, rhs) {
			(Value::Num(a), Value::Num(b)) => Ok(Value::Num(a + b)),
			(Value::Str(a), Value::Str(b)) => Ok(Value::Str(a + &b)),
			(Value::List(a), Value::List(b)) => {
				if a.len() != b.len() {
					return Err(RollerErr::EvalError(
						EvalErr::ListsNotSameSize(Value::List(a), Value::List(b))
					));
				}
				Ok(
					Value::List(try!(
						a.into_iter() // [a,..]
						.zip(b.into_iter()) // [(a,b),..]
						.map(|(a,b)| a + b ) // [Ok(a+b),..]
						.collect()// [a+b,..]
					))
				)
			},

			(a, b) =>
				Err(RollerErr::EvalError(
					EvalErr::UnsupportedOpTypes{
						op: InfixOp::Plus,
						left: RollerType::from(&a),
						right: RollerType::from(&b)
					}
				)),
		}
	}
}

impl ops::Sub for Value {
	type Output = ParseResult<Self>;
	fn sub(self, rhs: Self) -> Self::Output {
		Err::<Self, RollerErr>(RollerErr::EvalError(EvalErr::Unimplemented))
	}
}

impl ops::Mul for Value  {
	type Output = ParseResult<Self>;
	fn mul(self, rhs: Self) -> Self::Output {
		Err::<Self, RollerErr>(RollerErr::EvalError(EvalErr::Unimplemented))
	}
}

impl ops::Div for Value  {
	type Output = ParseResult<Self>;
	fn div(self, rhs: Self) -> Self::Output {
		Err::<Self, RollerErr>(RollerErr::EvalError(EvalErr::Unimplemented))
	}
}

impl ops::Neg for Value  {
	type Output = ParseResult<Self>;
	fn neg(self) -> Self::Output {
		Err::<Self, RollerErr>(RollerErr::EvalError(EvalErr::Unimplemented))
	}
}

pub trait Pow<RHS = Self> {
	type Output;
	fn pow(self, rhs: RHS) -> Self::Output;
}

impl Pow for Value {
	type Output = ParseResult<Self>;
	fn pow(self, rhs: Self) -> Self::Output {
		Err::<Self, RollerErr>(RollerErr::EvalError(EvalErr::Unimplemented))
	}
}

// ---

impl ops::Add for NumType {
	type Output = Self;
	fn add(self, rhs: Self) -> Self::Output {
		match (self, rhs) {
			(NumType::Int(a), NumType::Int(b)) => NumType::Int(a + b),
			(NumType::Real(a), NumType::Real(b)) => NumType::Real(a + b),
			// convert both into real values and call this function again
			(a,b) => a.to_real() + b.to_real(),
		}
	}
}
