#![allow(dead_code)]
use std::f64;

///! These are runtime value types, but the syntax parser uses some of these also.

#[derive(Debug, PartialEq)]
pub enum Value {
	Num(NumType),
	Str(String),
	List(Vec<Value>)
}

/// A numeral, either an integer or real
#[derive(Debug, PartialEq)]
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
