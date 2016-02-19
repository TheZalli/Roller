#![allow(dead_code)]
use std::boxed::Box;
use std::path::PathBuf;

/// An variable and function identifier
pub type Ident = String;

/// A keyword identifier
pub type KWIdent = String;

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
	Var(Ident),
	FunCall(Ident, Vec<Expr>),
	DiceThrow(Box<(Expr, Expr)>),
	Math(MathOp, Box<(Expr, Expr)>),
	Cmp(CmpOp, Box<(Expr, Expr)>),
	LogConn(LogConnOp, Box<(Expr, Expr)>),
	Unary(UnaryOp, Box<Expr>),
	ListVal(ListValExpr),
	Filter(Pred, Box<(Expr, Pred)>),
	KeyWord(KWIdent, Box<Expr>),
}

/// A single literal value
#[derive(Debug, PartialEq)]
pub enum LiteralExpr {
	Num(NumType),
	Str(String),
	Error,
}

/// A numeral, either an integer or real (floating point)
#[derive(Debug, PartialEq)]
pub enum NumType {
	Int(i32),
	Real(f32), // TODO: deal with floating point errors
	Invalid, // NaN, infinity, undefined
}

#[derive(Debug, PartialEq)]
pub enum ListValExpr {
	Vector(Vec<Expr>),
	Range(Box<(Expr, Expr, Expr)>), // (start, step, end)
}

#[derive(Debug, PartialEq)]
/// A predicate for the filtering expression.
pub enum Pred {
	Index(Box<Expr>),
	Cmp(CmpOp, Box<Expr>),
	LogConn(LogConnOp, Box<(Pred, Pred)>),
	Type(TypePred),
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
	List(Option<Box<Pred>>),
}
