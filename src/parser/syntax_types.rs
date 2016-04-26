#![allow(dead_code)]
use std::boxed::Box;
use std::path::PathBuf;

pub use eval::types::*;
use parser::parse_util::Ident;

#[derive(Debug, PartialEq, Clone)]
pub enum ExprList {
	Vector(Vec<Expr>),
	Range {
		start: Box<Expr>,
		step: Option<Box<Expr>>,
		end: Box<Expr>,
	},
}

// / A keyword identifier
//pub type KWIdent = String;

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
	/// A list or range of expressions
	List(ExprList),
	/// Variable
	Var(Ident),
	/// An operation, like a mathematical operation or function call.
	Op {
		op: AnyOp,
		args: Vec<Option<Expr>> // Option, because sometimes absence of an argument conveys info
	},
	/// A list filtering
	Filter {
		list: Box<Expr>,
		pred: Pred
	},

	/*KeyWord {
		keyword: KWIdent,
		params: Vec<Expr>
	},*/
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

#[derive(Debug, PartialEq, Clone)]
pub enum MathOp {
	Dice,
	Plus,
	Minus,
	Mul,
	Div,
	Pow,
}

#[derive(Debug, PartialEq, Clone)]
pub enum PredOp {
	Cmp(CmpOp),
	LogConn(LogConnOp),
}

#[derive(Debug, PartialEq, Clone)]
pub enum CmpOp {
	Eq,
	Ineq,
	Gt,
	Lt,
	Gteq,
	Lteq,
}

#[derive(Debug, PartialEq, Clone)]
pub enum LogConnOp {
	And,
	Or,
	Xor,

	Not,
}


#[derive(Debug, PartialEq, Clone)]
pub enum AnyOp {
	Math(MathOp),
	FunCall(Ident),
}


/*
#[derive(Debug, PartialEq)]
pub enum TypePred {
	Int,
	Real,
	String,
}*/
