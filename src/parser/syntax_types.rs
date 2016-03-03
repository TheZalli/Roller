#![allow(dead_code)]
use std::boxed::Box;
use std::path::PathBuf;

pub use eval::types::*;
use parser::parse_util::Ident;

#[derive(Debug, PartialEq)]
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
#[derive(Debug, PartialEq)]
pub enum Cmd {
	Statement(Stmt),
	Expression(Expr),
	//Empty,
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
	/// A scalar value
	Val(Value),
	/// A list or range of expressions
	List(ExprList),
	/// Variable
	Var(Ident),
	/// A function call.
	FunCall {
		/// Name of the function.
		name: Ident,
		params: Vec<Expr >
	},
	/// A dice throw.
	DiceThrow(Box<(Expr, Expr)>),
	/// A math expression.
	Math {
		op: MathOp,
		sides: Box<(Expr, Expr)>
	},
	/// A comparison predicate.
	Cmp {
		op: CmpOp,
		sides: Box<(Expr, Expr)>
	},
	/// A logical connective.
	LogConn {
		op: LogConnOp,
		sides: Box<(Expr, Expr)>
	},
	/// An unary operation.
	Unary {
		op: UnaryOp,
		sides: Box<Expr>
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

#[derive(Debug, PartialEq)]
/// A predicate pattern for the filtering expression.
pub enum Pred {
	/// Indexing predicate, like in C-like languages.
	Index(Box<Expr>),
	/// A comparison predicate.
	Cmp {
		op: CmpOp,
		sides: Box<(Expr, Expr)>
	},
	/// A logical connective.
	LogConn {
		op: LogConnOp,
		sides: Box<(Expr, Expr)>
	},
	//Type(TypePred),
	/// A list pattern predicate {[Predicate]}. Matches lists
	List(Option<Box<Pred>>),
}

#[derive(Debug, PartialEq)]
pub enum MathOp {
	Add,
	Sub,
	Mul,
	Div,
	Pow,
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
/*
#[derive(Debug, PartialEq)]
pub enum TypePred {
	Int,
	Real,
	String,
}*/
