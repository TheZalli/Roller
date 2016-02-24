#![allow(dead_code)]
use std::boxed::Box;
use std::path::PathBuf;
use std::f64;

use lexer::Ident;

/// The error allowed for floating point equality comparison.
const EPSILON: f64 = f64::EPSILON * 2.0; // multiply just to be safe about floating point errors

/// Floating point equality comparison.
fn float_eq(x: f64, y: f64) -> bool {
	let abs_diff = (x - y).abs();
	abs_diff <= EPSILON
}



/// A keyword identifier
pub type KWIdent = String;

/// A numeral, either an integer or real (floating point)
#[derive(Debug)]
pub enum NumType {
	Int(i64),
	Real(f64),
}

impl PartialEq for NumType {
	fn eq(&self, other: &Self) -> bool {
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

/// A command given to the interpreter
#[derive(Debug, PartialEq)]
pub enum Cmd {
	Statement(Stmt),
	Expression(Expr),
	Empty,
}

/// A statement, a command that changes the environment and doesn't return.
#[derive(Debug, PartialEq)]
pub enum Stmt {
	Assign(Ident, Expr),
	FnDef(Ident, Vec<Ident>, Expr),
	Delete(Ident),
	Clear,
	Run(PathBuf),
	Save(PathBuf),
}

/// An expression, a command that returns a value and doesn't change the environment.
#[derive(Debug, PartialEq)]
pub enum Expr {
	Literal(Box<LiteralExpr>),
	Var(Box<Ident>),
	FunCall( (Box<Ident>, Vec<Expr >) ),
	DiceThrow(Box<(Expr, Expr)>),
	Math(MathOp, Box<(Expr, Expr)>),
	Cmp(CmpOp, Box<(Expr, Expr)>),
	LogConn(LogConnOp, Box<(Expr, Expr)>),
	Unary(UnaryOp, Box<Expr>),
	ListVal(ListValExpr),
	Filter(Box<(Expr, Pred)>),
	KeyWord(KWIdent, Box<Expr >),
}

/// A single literal value
#[derive(Debug, PartialEq)]
pub enum LiteralExpr {
	Num(NumType),
	Str(Box<String>),
	Error,
}

#[derive(Debug, PartialEq)]
pub enum ListValExpr {
	Vector(Vec<Expr >),
	Range(Box<RollerRange >), // (start, step, end)
}

#[derive(Debug, PartialEq)]
struct RollerRange {
	start: Expr,
	step: Expr,
	end: Expr,
}

impl RollerRange {
	// TODO: error checking if step is of wrong sign
	fn new(start: Expr, step: Expr, end: Expr) -> RollerRange {
		RollerRange{start: start, step: step, end: end}
	}
}

#[derive(Debug, PartialEq)]
/// A predicate for the filtering expression.
pub enum Pred {
	Index(Box<Expr >),
	Cmp(CmpOp, Box<Expr >),
	LogConn(LogConnOp, Box<(Pred, Pred)>),
	Type(TypePred),
	List(Option<Box<Pred >>),
}

#[derive(Debug, PartialEq)]
pub enum MathOp {
	Add,
	Sub,
	Mul,
	Div,
	Exp,
}

#[derive(Debug, PartialEq)]
pub enum CmpOp {
	Eq,
	Ineq,
	Gt,
	Lt,
	Gteq,
	Lteq,
}

#[derive(Debug, PartialEq)]
pub enum LogConnOp {
	And,
	Or,
	Xor,
}

#[derive(Debug, PartialEq)]
pub enum UnaryOp {
	Neg,
	Not,
}

#[derive(Debug, PartialEq)]
pub enum TypePred {
	Int,
	Real,
	String,
}
