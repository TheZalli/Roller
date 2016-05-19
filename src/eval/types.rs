#![allow(dead_code)] // TODO remove
use std::f32;
use std::fmt;
use std::ops;

use common_util::{IntType, FloatType, Pow};
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
	NumInt,
	NumReal,
	Str,
	List,
	//Func
}

/// A numeral, either an integer or real
#[derive(PartialEq, Clone, Copy)]
pub enum NumType {
	Int(IntType),
	Real(FloatType),
}

/// The error allowed for floating point equality comparison.
const EPSILON: FloatType = f32::EPSILON * 2.0; // multiply just to be safe about floating point errors

/// Floating point equality comparison.
fn float_eq(x: FloatType, y: FloatType) -> bool {
	let abs_diff = (x - y).abs();
	abs_diff <= EPSILON
}

impl Value {
	/// Converts self into a singular value if able.
	pub fn to_singular(&self) -> ParseResult<Value> {
		match self {
			&Value::Num(_) => Ok(self.clone()),
			&Value::Str(_) => Ok(self.clone()),

			&Value::List(ref x) => {
				let mut iter = x.into_iter();
				if let Some(x) = iter.next() {
					let mut sum = x.clone();

					for i in iter {
						if let Ok(val) = sum + i.clone() {
							sum = val;
						}
						else {
							return Err(RollerErr::EvalError(
								EvalErr::CantConvertToSingular(self.clone())
							));
						}
					}
					return Ok(sum);
				}
				Err(RollerErr::EvalError(
					EvalErr::CantConvertToSingular(self.clone())
				))
			},
		}

	}

}

impl NumType {
	/// Returns the numeral equality, which means that the integers can be compared with floats.
	fn num_eq(&self, other: &Self) -> bool {
		match ( self, other ) {
			( &NumType::Int(x), &NumType::Int(y) ) => x == y,
			( &NumType::Real(x), &NumType::Real(y) ) => float_eq(x, y),
			// if one of them is a real, convert both of them into reals and try again
			(x, y) => x.to_real().num_eq(&y.to_real()),
		}
	}

	/// Converts the numeral into a real value
	pub fn to_real(self) -> Self {
		match self {
			NumType::Real(_) => self,
			NumType::Int(x) => NumType::Real(x as FloatType)
		}
	}

	pub fn to_float(self) -> FloatType {
		match self {
			NumType::Real(x) => x,
			NumType::Int(x) => x as FloatType,
		}
	}

	/// Tells whether self is an integer or a real.
	/// If self is a real with a fractional part, this will return false.
	pub fn is_int(self) -> bool {
		match self {
			NumType::Int(_) => true,
			NumType::Real(x) if float_eq(x.fract(), 0 as FloatType) => true,
			_ => false,
		}
	}

	/// Converts self into integer.
	pub fn as_int(self) -> IntType {
		match self {
			NumType::Int(x) => x,
			NumType::Real(x) => x as IntType,
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
			&Value::Str(ref st) => write!(f, "\"{}\"", st),
			&Value::List(ref v) => {
				try!(write!(f, "{{"));

				let mut sum: Option<ParseResult<Value>> = None;
				let mut iter = v.iter();

				if let Some(x) = iter.next() {
					sum = Some(Ok(x.clone()) );
					try!(write!(f, "{}", x));

					for i in iter  {
						if let Some(Ok(val)) = sum {
							sum = Some(val + i.clone());
						}
						try!(write!(f, ", {}", i));
					}
				}

				// try to write the sum, don't write if encountered error
				if let Some(Ok(sum)) = sum {
					write!(f, "}}, sum = {}", sum)
				}
				else {
					write!(f, "}}")
				}
			},
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
			&RollerType::NumInt => write!(f, "integer numeral"),
			&RollerType::NumReal => write!(f, "real numeral"),
			&RollerType::Str => write!(f, "string"),
			&RollerType::List => write!(f, "list"),
			//&RollerType::Func => write!(f, "function"),
		}
	}
}

impl From<Value> for RollerType {
	fn from(val: Value) -> Self {
		match val {
			Value::Num(_) => RollerType::Num,
			Value::Str(_) => RollerType::Str,
			Value::List(_) => RollerType::List,
		}
	}
}

impl<'a> From<&'a Value> for RollerType {
	fn from(val: &'a Value) -> Self {
		match val {
			&Value::Num(_) => RollerType::Num,
			&Value::Str(_) => RollerType::Str,
			&Value::List(_) => RollerType::List,
		}
	}
}

impl From<NumType> for RollerType {
	fn from(num: NumType) -> Self {
		match num {
			NumType::Int(_) => RollerType::NumInt,
			NumType::Real(_) => RollerType::NumReal
		}
	}
}

// ---

/// A macro that applies an operator function $func between operands $a and $b.
/// $op_name is for the error message so that it can show the appropriate operator if the operation is not defined between these particular types.
/// The last parameter tells if the $func is also defined between String and &str.
macro_rules! apply_value_bin_op {
	($a: expr, $b: expr, $func: expr, $op_name: path, true) => {
		match ($a, $b) {
			(Value::Str(a), Value::Str(b)) => Ok(Value::Str($func(a, &b))),
			(a, b) => apply_value_bin_op!(a, b, $func, $op_name, false)
		}
	};

	($a: expr, $b: expr, $func: expr, $op_name: path, false) => {
		match ($a, $b) {
			(Value::Num(a), Value::Num(b)) => Ok(Value::Num($func(a, b))),

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
						.map(|(a,b)| $func(a, b) ) // [Ok(a+b),..]
						.collect()// [a+b,..]
					))
				)
			},

			(a, Value::List(b)) => $func(a, try!(Value::List(b).to_singular())),

			(Value::List(a), b) => $func(try!(Value::List(a).to_singular()), b),

			(a, b) =>
				Err(RollerErr::EvalError(
					EvalErr::UnsupportedOpTypes{
						op: $op_name,
						left: RollerType::from(&a),
						right: RollerType::from(&b)
					}
				)),
		}
	};
}

impl ops::Add for Value {
	type Output = ParseResult<Self>;
	fn add(self, rhs: Self) -> Self::Output {
		apply_value_bin_op!(self, rhs, ops::Add::add, InfixOp::Plus, true)
	}
}

impl ops::Sub for Value {
	type Output = ParseResult<Self>;
	fn sub(self, rhs: Self) -> Self::Output {
		apply_value_bin_op!(self, rhs, ops::Sub::sub, InfixOp::Minus, false)
	}
}

impl ops::Mul for Value  {
	type Output = ParseResult<Self>;
	fn mul(self, rhs: Self) -> Self::Output {
		apply_value_bin_op!(self, rhs, ops::Mul::mul, InfixOp::Mul, false)
	}
}

impl ops::Div for Value  {
	type Output = ParseResult<Self>;
	fn div(self, rhs: Self) -> Self::Output {
		apply_value_bin_op!(self, rhs, ops::Div::div, InfixOp::Div, false)
	}
}

impl ops::Neg for Value  {
	type Output = ParseResult<Self>;
	fn neg(self) -> Self::Output {
		match self {
			Value::Num(a) => Ok(Value::Num(-a)),
			Value::List(a) => Ok(Value::List(try!(
				a.into_iter()
				.map(|x| -x)
				.collect()
			))),
			_ => Err(RollerErr::EvalError(EvalErr::NegNotSupported(RollerType::from(&self)) ))
		}
	}
}

impl Pow for Value {
	type Output = ParseResult<Self>;
	fn pow(self, rhs: Self) -> Self::Output {
		apply_value_bin_op!(self, rhs, Pow::pow, InfixOp::Pow, false)
	}
}

// ---

macro_rules! apply_numtype_bin_op {
	($a: expr, $b: expr, $func: expr) => {
		match ($a, $b) {
			(NumType::Int(a), NumType::Int(b)) => NumType::Int($func(a, b)),
			(NumType::Real(a), NumType::Real(b)) => NumType::Real($func(a, b)),
			// if one of the values is a real convert both into real values and call recursively
			(a,b) => $func(a.to_real(), b.to_real()),
		}
	};
}

macro_rules! impl_numtype_op {
	($trait_name: path, $func_name: ident, $applied_func: expr) => {
		impl $trait_name for NumType {
			type Output = Self;
			fn $func_name(self, rhs: Self) -> Self::Output {
				apply_numtype_bin_op!(self, rhs, $applied_func)
			}
		}
	};
}

impl_numtype_op!(ops::Add, add, ops::Add::add);
impl_numtype_op!(ops::Sub, sub, ops::Sub::sub);
impl_numtype_op!(ops::Mul, mul, ops::Mul::mul);

impl ops::Div for NumType {
	type Output = Self;
	fn div(self, rhs: Self) -> Self::Output {
		match (self, rhs) {
			(NumType::Real(a), NumType::Real(b)) => NumType::Real(a / b),
			// if one of the values is not a real change both into real values and call recursively
			(a,b) => a.to_real() / b.to_real(),
		}
	}
}

impl Pow for NumType {
	type Output = Self;
	fn pow(self, rhs: Self) -> Self::Output {
		// if you're wondering about the weird guards, they're to avoid truncation when typecasting
		match (self, rhs) {
			(NumType::Real(a), NumType::Real(b)) =>
				NumType::Real(a.powf(b)),

			(NumType::Int(a), NumType::Real(b)) =>
				NumType::Real((a as FloatType).powf(b)),

			(NumType::Real(a), NumType::Int(b)) =>
				NumType::Real(a.powi(b)),

			(NumType::Int(a), NumType::Int(b))
			if b >= 0 && b <= u32::max_value() as IntType =>
				NumType::Int(a.pow(b as u32)),

			(NumType::Int(a), NumType::Int(b)) if b < 0 =>
				NumType::Real((a as FloatType).powi(b)),

			(NumType::Int(a), NumType::Int(b)) =>
				NumType::Real((a as FloatType).powf(b as FloatType)),
		}
	}
}

impl ops::Neg for NumType {
	type Output = Self;
	fn neg(self) -> Self::Output {
		match self {
			NumType::Int(x) => NumType::Int(-x),
			NumType::Real(x) => NumType::Real(-x),
		}
	}
}
