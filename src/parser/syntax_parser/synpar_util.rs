use std::collections::HashMap;
use std::hash::Hash;

use parser::parse_util::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_types::*;

pub type InType<'a> = &'a [Lexeme];

#[derive(Debug, PartialEq, Clone, Copy)]
pub enum Side {
	Left,
	Right
}

#[derive(Debug, PartialEq, Clone, Copy)]
#[allow(dead_code)] // TODO: remove when all the variants are used somewhere
pub enum ArgInfo {
	/// Operators with a singular argument
	/// The argument tells at which side of the argument the operator must be in.
	Unary(Side),
	/// Operators with two arguments
	Binary,
	/// For binary operators that can be used as unary, like substraction/negation.
	/// The argument tells at which side of the argument the operator must be in.
	AllowUnary(Side),
	/// For special operators that can have 0-2 arguments.
	/// For the dice operator.
	AllowNullary,
	// / For function calls etc
	//Variable,
}

/// Information associated with an operation
#[derive(Debug, Clone, Copy)]
pub struct OpInfo {
	/// Precedence level
	pub level: i32,
	/// associativity
	pub assoc: Side,
	// Argument info
	pub arg_info: ArgInfo,
}

impl OpInfo {
	fn new(precedence_level: i32, associativity: Side, argument_info: ArgInfo) -> Self {
		OpInfo {
			level: precedence_level,
			assoc: associativity,
			arg_info: argument_info
		}
	}
}

lazy_static! {
	pub static ref OP_INFOS: HashMap<InfixOp, OpInfo> =
		vec2map(vec![
			(InfixOp::Plus,  OpInfo::new(1, Side::Left, ArgInfo::AllowUnary(Side::Left)) ),
			(InfixOp::Minus, OpInfo::new(1, Side::Left, ArgInfo::AllowUnary(Side::Left)) ),
			(InfixOp::Mul, OpInfo::new(3, Side::Left, ArgInfo::Binary)),
			(InfixOp::Div, OpInfo::new(3, Side::Left, ArgInfo::Binary)),
			(InfixOp::Pow, OpInfo::new(4, Side::Right, ArgInfo::Binary)),
			(InfixOp::Dice, OpInfo::new(5, Side::Left, ArgInfo::AllowNullary))
		]);
}

/// The smallest existing precedence level.
pub const PREC_MIN: i32 = 1;
/// The largest existing precedence level.
pub const PREC_MAX: i32 = 5;


#[derive(Debug, Clone)]
pub enum ParseTemp {
	Op(InfixOp),
	Exp(Expr)
}

#[derive(Debug, Clone)]
pub struct IncompAst {
	op: Option<InfixOp>,
	left: Vec<IncAstNode>,
	right: Vec<IncAstNode>,
}

#[derive(Debug, Clone)]
pub enum IncAstNode {
	ParTmp(ParseTemp),
	Node(Box<IncompAst>),
}

impl IncompAst {
	pub fn new() -> IncompAst {
		IncompAst {
			op: None,
			left: Vec::new(),
			right: Vec::new(),
		}
	}

	/*fn set_op(&mut self, new_op: InfixOp) {
		self.op = Some(new_op);
	}*/

	pub fn add_child_left(&mut self, child: Vec<IncAstNode>) {
		self.left = child;
	}

	/*fn add_child_right(&mut self, child: Vec<IncAstNode>) {
		self.right = Some(IncAstChild(child));
	}*/

	pub fn process_left_child(&mut self, prec_level: i32) {
		// do nothing if left is empty
		if self.left.is_empty() {
			return;
		}
		// TODO: fix this
		assert!(self.op.is_none());
		assert!(self.right.is_empty());

		// maybe there is a prettier solution than a flag variable?
		let mut op_found_at = false;

		let mut temp_left = Vec::new();
		let mut temp_right = Vec::new();

		// go through everything and move it to approriate container
		for n in self.left.iter() {
			// check the mode whether we are in the left side or the right side of the operator
			if !op_found_at {
				// we are at the left side of the operator
				match n {
					&IncAstNode::ParTmp(ParseTemp::Op(ref o)) => {
						// did we find our operator?
						if OP_INFOS[o].level == prec_level {
							self.op = Some(o.clone());
							op_found_at = true;
						}
						else {
							temp_left.push(IncAstNode::from(ParseTemp::Op(o.clone() )) );
						}
					},
					_ => temp_left.push(IncAstNode::from(n.clone() ))
				}
			}
			else {
				// we are the right side of the operator
				temp_right.push(IncAstNode::from(n.clone() ));
			}
		}

		self.left = temp_left;
		self.right = temp_right;
	}
}

/*
impl fmt::Display for ParseTemp {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&ParseTemp::Op(ref o) => write!(f, "{:?}", o),
			&ParseTemp::Exp(ref e) => write!(f, "{}", e)
		}
	}
}

impl fmt::Display for IncompAst {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		write!(f, "({:?} {}, {})",
			self.op,
			self.left.clone().unwrap_or(IncAstChild::new()), // TODO remove clones
			self.right.clone().unwrap_or(IncAstChild::new())
		)
	}
}

impl fmt::Display for IncAstChild {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		try!(write!(f, "["));

		for i in self.0.iter() {
			try!(write!(f, "{}, ", i));
		}

		write!(f, "]")
	}
}

impl fmt::Display for IncAstNode {
	fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
		match self {
			&IncAstNode::ParTmp(ref pt) => write!(f, "{}", pt),
			&IncAstNode::Node(ref b) => write!(f, "{}", **b)
		}
	}
}*/

impl From<ParseTemp> for IncAstNode {
	fn from(t: ParseTemp) -> Self {
		IncAstNode::ParTmp(t)
	}
}

impl From<Box<IncompAst>> for IncAstNode {
	fn from(n: Box<IncompAst>) -> Self {
		IncAstNode::Node(n)
	}
}

/// Takes a vector and transforms it into a map.
/// Why is there nothing like this in std?
fn vec2map<K: PartialEq + Eq + Hash, T>(vec: Vec<(K, T)>) -> HashMap<K, T> {
	let mut map = HashMap::new();
	for (k, t) in vec {
		map.insert(k, t);
	}
	return map;
}

/// Takes and returns the first token from the input.
pub fn consume_token(input: InType) -> ParseOutput<Lexeme, InType> {
	match input.first() {
		Some(tk) => Ok( (tk.clone(), &input[1..]) ),
		None => Err(1)
	}
}

/// Peeks and doesn't remove the first token from the input.
pub fn peek_token(input: InType) -> ParseResult<Lexeme> {
	match input.first() {
		Some(tk) => Ok(tk.clone()),
		None => Err(2)
	}
}

/// Consumes and ignores one token
/// Returns an error if the input is empty.
pub fn ignore_token(input: InType) -> ParseResult<InType> {
	if input.is_empty() {
		return Err(3)
	}
	Ok(&input[1..])
}

/// Takes a token and places it into an enum.
macro_rules! expect_token {
	($input:expr, $enum_name:ident :: $enum_var:ident ( $type_name:ident ) ) =>
	{
		match consume_token($input) {
			Ok( ($enum_name::$enum_var(val), i) ) => Ok( (val, i) ),
			Err(e) => Err(e),
			_ => Err(4)
		}
	};

	($input:expr, $enum_name:ident :: $enum_var:ident ) =>
	{
		match consume_token($input) {
			Ok( ($enum_name::$enum_var, i) ) => Ok( ( (), i) ),
			Err(e) => Err(e),
			_ => Err(4)
		}
	};
}

// / Parses and consumes an End token, or results an error.
// fn parse_end(input: InType) -> ParseOutput<(), InType> {
// 	match input.first() {
// 		Some(&Lexeme::End) => Ok( ( (), &input[1..]) ),
// 		_ => Err(5)
// 	}
// }

/// Finds the given enum variant and returns it in an Option or returns None.
macro_rules! find_token {
	($input:expr, $enum_name:ident :: $enum_var:ident ( $what:expr ))  =>
	({
		$input.into_iter().position(
			|lex| {
				match lex {
					&$enum_name::$enum_var($what) => true,
					_ => false,
				}
			}
		)
	});

	($input:expr, $enum_name:ident :: $enum_var:ident () )  =>
	({
		$input.into_iter().position(
			|lex| {
				match lex {
					&$enum_name::$enum_var( _ ) => true,
					_ => false,
				}
			}
		)
	});

	($input:expr, $enum_name:ident :: $enum_var:ident)  =>
	({
		$input.into_iter().position(
			|lex| {
				match lex {
					&$enum_name::$enum_var => true,
					_ => false,
				}
			}
		)
	});
}
