use std::collections::HashMap;
use std::iter::FromIterator;

use syntax_tree::*;
use eval::types::*;
use eval::eval_functions::eval_expr;
use error::*;

/// An runtime environment
pub struct RollerEnv<'a> {
	/// The global namespace for variables and functions.
	ns: RollerNamespace<'a>,
}

/// A namespace for variables and functions
struct RollerNamespace<'a> {
	/// The variable data
	vars: HashMap<Ident, Value>,
	funs: HashMap<Ident, RollerFun>,
	/// A reference to the previous namespace
	parent_ns: Option<&'a RollerNamespace<'a>>,
}

#[allow(dead_code)] // TODO: remove when used
pub enum NameInfo {
	Val,
	Fun,
	Empty,
}

impl<'a> RollerEnv<'a> {
	/// Creates a new empty runtime environment.
	pub fn new() -> RollerEnv<'a> {
		RollerEnv{ns: RollerNamespace::new()}
	}

	/// Creates a new local environment to be used when calling functions.
	pub fn local_from_args(&'a self, names: &Vec<Ident>, args: Vec<Value>)
		-> ParseResult<RollerEnv<'a>>
	{
		Ok(RollerEnv{ns: try!( RollerNamespace::from_args(names, args, Some(&self.ns)) ) })
	}

	pub fn clear(&mut self) {
		*self = RollerEnv::new()
	}

	/// Sets a variable with name id to value.
	/// If there were a variable or function with same name, it will be replaced.
	pub fn assign_var(&mut self, id: Ident, value: Value) {
		self.ns.remove_fun(&id);
		self.ns.insert_var(id, value);
	}

	/// Declares a function with the name id.
	/// If there were a variable or function with same name, it will be replaced.
	pub fn declare_function(&mut self, id: Ident, body: RollerFun) {
		self.ns.remove_var(&id);
		self.ns.insert_fun(id, body);
	}

	/// Deletes a function or variable with the given name.
	pub fn delete_id(&mut self, id: &Ident) {
		if let None = self.ns.remove_var(id) {
			self.ns.remove_fun(id);
		}
	}

	/// Tells if there is a variable, function or nothing with that name.
	#[allow(dead_code)] // TODO: remove when used
	pub fn get_name_info(&self, id: Ident) -> NameInfo {
		if let Some(_) = self.ns.get_var(&id) {
			NameInfo::Val
		}
		else if let Some(_) = self.ns.get_fun(&id) {
			NameInfo::Fun
		}
		else {
			NameInfo::Empty
		}
	}

	pub fn get_var(&self, id: Ident) -> ParseResult<Value> {
		match self.ns.get_var(&id) {
			Some(ref v) => Ok((*v).clone()),
			None => Err(RollerErr::EvalError(EvalErr::NoVarFound(id))),
		}
	}

	pub fn call_fun(&self, id: Ident, args: Vec<Value>) -> ParseResult<Value> {
		match self.ns.get_fun(&id) {
			Some(ref fun) => {
				let local_env = try!(self.local_from_args(&fun.params, args));
				eval_expr(fun.body.clone(), &local_env)
			},
			None => Err(RollerErr::EvalError(EvalErr::NoFunFound(id))),
		}
	}
}

impl<'a> RollerNamespace<'a> {
	pub fn new() -> RollerNamespace<'a> {
		RollerNamespace{vars: HashMap::new(), funs: HashMap::new(), parent_ns: None}
	}

	pub fn from_args(names: &Vec<Ident>, args: Vec<Value>,
		parent_namespace: Option<&'a RollerNamespace>) -> ParseResult<RollerNamespace<'a>>
	{
		// chech whether the lengths match
		if names.len() != args.len() {
			return Err(RollerErr::EvalError(
				EvalErr::WrongNumParams{expected: names.len(), found: args.len()}
			));
		}
		// ok they do, use iterator magic to add them
		Ok(
			RollerNamespace{
				vars:
					HashMap::from_iter(
						names.iter()
						.cloned()
						.zip(args.into_iter())
					),
				funs: HashMap::new(),
				parent_ns: parent_namespace,
			}
		)
	}

	/// Tries to find a variable with given name from the namespace if possible.
	/// If no variable was found, checks the parent namespace
	pub fn get_var(&self, id: &Ident) -> Option<&Value> {
		match self.vars.get(id) {
			Some(val) => Some(val),
			None =>
				match self.parent_ns {
					Some(ns) => ns.get_var(id),
					None => None,
				},
		}
	}

	/// Tries to find the given function from the parent namespace or from itself.
	pub fn get_fun(&self, id: &Ident) -> Option<&RollerFun> {
		match self.parent_ns {
			Some(ns) => ns.get_fun(id),
			None => self.funs.get(id),
		}
	}

	/// Adds or replaces a variable into namespace
	pub fn insert_var(&mut self, id: Ident, val: Value) -> Option<Value> {
		self.vars.insert(id, val)
	}

	/// Adds or replaces a function into namespace
	pub fn insert_fun(&mut self, id: Ident, body: RollerFun) -> Option<RollerFun> {
		self.funs.insert(id, body)
	}

	/// Removes a variable with given name.
	pub fn remove_var(&mut self, id: &Ident) -> Option<Value> {
		self.vars.remove(id)
	}

	/// Removes a function with given name.
	pub fn remove_fun(&mut self, id: &Ident) -> Option<RollerFun> {
		self.funs.remove(id)
	}
}
