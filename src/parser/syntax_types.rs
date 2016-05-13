#![allow(dead_code)]
use std::boxed::Box;
use std::path::PathBuf;

pub use eval::types::*;
use parser::parse_util::Ident;

/// A command given to the interpreter
#[derive(Debug, PartialEq, Clone)]
pub enum Cmd {
	Statement(Stmt),
	Expression(Expr),
	//Empty,
}

/// A statement, a command that changes the environment and doesn't return.
#[derive(Debug, PartialEq, Clone)]
pub enum Stmt {
	Assign(Ident, Expr),
	FnDef(Ident, Vec<Ident>, Expr),
	Delete(Ident),
	Clear,
	Run(PathBuf),
	Save(PathBuf),
}

/// An expression, a command that returns a value and doesn't change the environment.
#[derive(Debug, PartialEq, Clone)]
pub enum Expr {
	/// A scalar value
	Val(Value),
	/// A list of expressions
	List(Vec<Expr>),
	/// A numerical range
	Range {
		start: Box<Expr>,
		step: Option<Box<Expr>>,
		end: Box<Expr>,
	},
	/// Variable
	Var(Ident),
	/// A function call
	FunCall(Ident, Vec<Expr>),
	/// An operation, like a mathematical operation.
	Op {
		op: InfixOp,
		left:  Option<Box<Expr>>, // Option, because sometimes absence of an argument is allowed
		right: Option<Box<Expr>>,
	},
	/// A list filtering
	Filter {
		list: Box<Expr>,
		pred: Pred
	},
}

#[derive(Debug, PartialEq, Clone)]
/// A predicate pattern for the filtering expression.
pub enum Pred {
	/// Indexing predicate, like in C-like languages.
	Index(Box<Expr>),
	/// A comparison predicate.
	Cmp {
		op: CmpOp,
		right: Box<Expr>,
	},
	/// A logical connective with two arguments.
	LogConn {
		op: LogConnOp,
		left: Option<Box<Expr>>,
		right: Box<Expr>,
	},
	//Type(TypePred),
	/// A list pattern predicate {[Predicate]}. Matches lists
	List(Option<Box<Pred>>),
}

#[derive(Debug, PartialEq, Eq, Clone, Copy, Hash)]
pub enum InfixOp {
	Dice,
	Plus,
	Minus,
	Mul,
	Div,
	Pow,
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum PredOp {
	Cmp(CmpOp),
	LogConn(LogConnOp),
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum CmpOp {
	Eq,
	Ineq,
	Gt,
	Lt,
	Gteq,
	Lteq,
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum LogConnOp {
	And,
	Or,
	Xor,

	Not,
}

/*
#[derive(Debug, PartialEq)]
pub enum TypePred {
	Int,
	Real,
	String,
}*/
