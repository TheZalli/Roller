use std::fmt;
use std::collections::HashMap;
use std::hash::Hash;

#[derive(Debug, PartialEq, Clone, Copy)]
pub enum Side {
	Left,
	Right
}

impl fmt::Display for Side {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&Side::Left => write!(f, "left"),
			&Side::Right => write!(f, "right"),
		}
	}
}

/// Takes a vector and transforms it into a map.
/// Why is there nothing like this in std?
pub fn vec2map<K: PartialEq + Eq + Hash, T>(vec: Vec<(K, T)>) -> HashMap<K, T> {
	let mut map = HashMap::new();
	for (k, t) in vec {
		map.insert(k, t);
	}
	return map;
}
