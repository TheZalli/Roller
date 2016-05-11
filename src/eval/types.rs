#![allow(dead_code)] // TODO remove
use std::f64;
use std::fmt;

///! These are runtime value types, but the syntax parser uses some of these also.

#[derive(PartialEq, Clone)]
pub enum Value {
	Num(NumType),
	Str(String),
	List(Vec<Value>)
}

/// A numeral, either an integer or real
#[derive(PartialEq, Clone)]
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
}

//impl Eq for NumType {}

// to make reading debug prints easier
impl fmt::Debug for Value {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&Value::Num(ref nt) => write!(f, "{:?}", nt),
			&Value::Str(ref st) => write!(f, "{:?}", st),
			&Value::List(ref v) => write!(f, "{:?}", v)
		}
	}
}

impl fmt::Debug for NumType {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&NumType::Int(i)  => write!(f, "{}", i),
			&NumType::Real(r) => write!(f, "{}", r)
		}
	}
}
