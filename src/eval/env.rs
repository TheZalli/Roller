use std::ops::{Deref, DerefMut};
use std::collections::HashMap;
use std::iter::FromIterator;
use std::cell::RefCell;

use rand::IsaacRng;
use rand::distributions::{Range, Sample};

use common_util::IntType;
use syntax_tree::*;
use eval::types::*;
use eval::eval_functions::eval_expr;
use error::*;

/// The Roller runtime environment. Stores the variable and function namespaces, the function call_stack, and the random number generator.
pub struct RollerEnv {
	/// The global namespace for functions
	fun_ns: HashMap<Ident, RollerFun>,
	/// The global namespace for variables
	var_ns: HashMap<Ident, Value>,

	/// The callstack for the functions.
	/// Stores the temporary variables of the functions.
	call_stack: RefCell<Vec<HashMap<Ident, Value>>>,
	/// How many function calls can be in the callstack
	max_call_depth: usize,

	/// The random number generator
	rng: RefCell<IsaacRng>,
}

pub enum NameInfo {
	Var,
	Fun,
	Empty,
}

impl RollerEnv {
	/// Creates a new empty runtime environment
	pub fn new(max_call_depth: usize) -> RollerEnv {
		RollerEnv {
			fun_ns:			HashMap::new(),
			var_ns:			HashMap::new(),
			call_stack:		RefCell::new(Vec::new()),
			rng:			RefCell::new(IsaacRng::new_unseeded()),
			max_call_depth:	max_call_depth,
		}
	}

	/// Clears the function and variable namespaces.
	pub fn clear(&mut self) {
		*self = RollerEnv {
			fun_ns: HashMap::new(),
			var_ns: HashMap::new(),
			call_stack: RefCell::new(Vec::new()),
			rng: RefCell::new(IsaacRng::new_unseeded()),
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
	/// Returns the type of the deleted identifier
	pub fn delete_id(&mut self, id: &Ident) -> ParseResult<NameInfo> {
		match self.var_ns.remove(id) {
			Some(_) => Ok(NameInfo::Var),
			// no variable found, try to delete a function
			None => match self.fun_ns.remove(id) {
				Some(_) => Ok(NameInfo::Fun),
				None => Err(RollerErr::EvalError(EvalErr::NoIdFound(id.to_owned() ))),
			},
		}
	}

	/// Tells if there is a variable, function or nothing with that name.
	#[allow(dead_code)] // TODO: remove when used
	pub fn get_name_info(&self, id: Ident) -> NameInfo {
		if let Some(_) = self.var_ns.get(&id) {
			NameInfo::Var
		}
		else if let Some(_) = self.fun_ns.get(&id) {
			NameInfo::Fun
		}
		else {
			NameInfo::Empty
		}
	}

	/// Returns the value of the variable with the given identifier.
	pub fn get_var<'a>(&'a self, id: &Ident) -> ParseResult<Value> {
		// check the last element of the call stack
		if let Some(ref hm) = self.call_stack.borrow().deref().last() {
			if let Some(ref val) = hm.get(id) {
				// check if we found the variable in the stack as a function argument
				return Ok((*val).clone());
			}
		}
		// if we didn't find the variable from the stack, check the global space
		if let Some(ref val) = self.var_ns.get(id) {
			return Ok((*val).clone());
		}
		// didn't find the variable from either of the namespaces
		Err(RollerErr::EvalError(EvalErr::NoVarFound(id.clone() )))
	}

	/// Calls the function with the given identifier with the given arguments.
	/// Returns an error if no such function was found, if the number of parameters was wrong, if the maximum function call depth was reached or if the evaluation of the function's body failed.
	/// Calls the eval_expr function to evaluate the function.
	pub fn call_fun(&self, id: &Ident, args: Vec<Value>) -> ParseResult<Value> {
		match self.fun_ns.get(id) {
			Some(ref fun) => {
				if self.call_stack.borrow().deref().len() > self.max_call_depth {
					return Err(RollerErr::EvalError(EvalErr::ReachedMaxCallDepth));
				}
				// the fumction's local namespace
				let local_ns = try!(Self::ns_from_args(&fun.params, args));

				// add the function's local namespace
				self.call_stack.borrow_mut().deref_mut().push(local_ns);
				// evaluate the function body
				let to_return = eval_expr(&fun.body, self);
				// remove the call stack namespace. IMPORTANT
				self.call_stack.borrow_mut().deref_mut().pop();

				// return the output value
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

	pub fn get_roll(&self, amount: IntType, sides: IntType) -> Vec<IntType> {
		let mut distr = Range::new(1, sides+1);
		let mut to_return = Vec::with_capacity(amount as usize);

		for _ in 1..amount+1 {
			to_return.push(distr.sample(&mut *self.rng.borrow_mut()) )
		}

		to_return
	}
}
