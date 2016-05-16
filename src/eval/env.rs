use std::ops::{Deref, DerefMut};
use std::collections::HashMap;
use std::iter::FromIterator;
use std::cell::RefCell;

use syntax_tree::*;
use eval::types::*;
use eval::eval_functions::eval_expr;
use error::*;

/// An runtime environment
pub struct RollerEnv {
	/// The global namespace for functions
	fun_ns: HashMap<Ident, RollerFun>,
	/// The global namespace for variables
	var_ns: HashMap<Ident, Value>,

	/// The callstack for the functions.
	/// Stores the temporary variables of the functions.
	call_stack: RefCell<Vec<HashMap<Ident, Value>>>,
	/// How many function calls can be in the callstack
	max_call_depth: usize
}

#[allow(dead_code)] // TODO: remove when used
pub enum NameInfo {
	Val,
	Fun,
	Empty,
}

impl RollerEnv {
	/// Creates a new empty runtime environment
	pub fn new(max_call_depth: usize) -> RollerEnv {
		RollerEnv {
			fun_ns: HashMap::new(),
			var_ns: HashMap::new(),
			call_stack: RefCell::new(Vec::new()),
			max_call_depth: max_call_depth,
		}
	}

	pub fn clear(&mut self) {
		*self = RollerEnv {
			fun_ns: HashMap::new(),
			var_ns: HashMap::new(),
			call_stack: RefCell::new(Vec::new()),
			max_call_depth: self.max_call_depth,
		}
	}

	#[allow(dead_code)] // TODO: remove when used
	pub fn set_max_call_depth(&mut self, new_depth: usize) {
		self.max_call_depth = new_depth;
	}

	/// Sets a variable with name id to value.
	/// If there were a variable or function with same name, it will be replaced.
	pub fn assign_var(&mut self, id: &Ident, value: Value) {
		self.fun_ns.remove(id);
		self.var_ns.insert(id.to_owned(), value);
	}

	/// Declares a function with the name id.
	/// If there were a variable or function with same name, it will be replaced.
	pub fn declare_function(&mut self, id: &Ident, body: &RollerFun) {
		self.var_ns.remove(id);
		self.fun_ns.insert(id.to_owned(), body.clone());
	}

	/// Deletes a function or variable with the given name.
	pub fn delete_id(&mut self, id: &Ident) {
		if let None = self.var_ns.remove(id) {
			self.fun_ns.remove(id);
		}
	}

	/// Tells if there is a variable, function or nothing with that name.
	#[allow(dead_code)] // TODO: remove when used
	pub fn get_name_info(&self, id: Ident) -> NameInfo {
		if let Some(_) = self.var_ns.get(&id) {
			NameInfo::Val
		}
		else if let Some(_) = self.fun_ns.get(&id) {
			NameInfo::Fun
		}
		else {
			NameInfo::Empty
		}
	}

	pub fn get_var(&self, id: &Ident) -> ParseResult<Value> {
		if self.call_stack.borrow().deref().is_empty() {
			match self.var_ns.get(id) {
				Some(ref x) => Ok((*x).clone()),
				None => Err(RollerErr::EvalError(EvalErr::NoVarFound(id.to_owned() ))),
			}
		}
		else {
			for i in self.call_stack.borrow().deref().iter().rev() {
				if let Some(ref x) = i.get(id) {
					return Ok((*x).clone());
				}
			}
			Err(RollerErr::EvalError(EvalErr::NoVarFound(id.clone() )))
		}
	}

	pub fn call_fun(&self, id: &Ident, args: Vec<Value>) -> ParseResult<Value> {
		match self.fun_ns.get(id) {
			Some(ref fun) => {
				if self.call_stack.borrow().deref().len() > self.max_call_depth {
					return Err(RollerErr::EvalError(EvalErr::ReachedMaxCallDepth));
				}

				let local_ns = try!(Self::ns_from_args(&fun.params, args));
				self.call_stack.borrow_mut().deref_mut().push(local_ns);

				let to_return = eval_expr(&fun.body, self);

				self.call_stack.borrow_mut().deref_mut().pop();
				to_return
			},
			None => Err(RollerErr::EvalError(EvalErr::NoFunFound(id.to_owned() ))),
		}
	}

	fn ns_from_args(names: &Vec<Ident>, args: Vec<Value>) -> ParseResult<HashMap<Ident, Value>>
	{
		// chech whether the lengths match
		if names.len() != args.len() {
			return Err(RollerErr::EvalError(
				EvalErr::WrongNumParams{expected: names.len(), found: args.len()}
			));
		}
		// ok they do, use iterator magic to add them
		Ok(
			HashMap::from_iter(
				names.iter()
				.cloned()
				.zip(args.into_iter())
			)
		)
	}
}
