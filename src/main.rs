#[macro_use] extern crate lazy_static;
extern crate regex;
extern crate rand;

mod parser;
mod eval;
mod error;
mod common_util;
mod syntax_tree;

use std::io::prelude::*;
use std::io;

use parser::*;
use eval::*;

/// Works like the println macro, but prints to the stderr instead of stdout.
macro_rules! println_to_stderr(
	($($arg:tt)*) => { {
		let r = writeln!(&mut ::std::io::stderr(), $($arg)*);
		r.expect("failed printing to stderr");
	} }
);

fn main() {
	let mut input;

	let max_call_depth = 100;
	let mut env = RollerEnv::new(max_call_depth);

	// The REP loop
	// Currently there is no way to exit other than the interrupt signal (ctrl + c)
	loop {
		print!("> ");
		// flush so our prompt is visible
		io::stdout().flush().ok().expect("Couldn't flush stdout");

		let mut temp = String::new();

		// read input
		match io::stdin().read_line(&mut temp) {
			Err(error) => {
				println!("Input error: {}", error);
				break;
			},
			// EOF encountered
			Ok(0) => break,
			// Read some bytes
			Ok(_) => {
				if temp.trim().is_empty() {
					// ignore empty lines
					continue;
				}
				else {
					input = temp;
				}
			}
		}

		let token_res = tokenize(&input as &str);
		//println!("Tokens: {:?} ", token_res); // DEBUG

		match token_res {
			Ok(tk_vec) => {
				let ast_res = parse_cmd(&tk_vec);

				match ast_res {
					Ok(cmd) => {
						//println!("AST: {:?} ", exp); // TODO
						let val_res = eval_cmd(&cmd, &mut env);

						match val_res {
							Some(Ok(val)) => println!("{}", val),
							Some(Err(e)) => println_to_stderr!("{}", e),
							None => {},
						}
					},
					Err(e) => println_to_stderr!("{}", e)
				}
			},
			Err(e) => println_to_stderr!("{}", e)
		}
	}
}
