#[macro_use] extern crate lazy_static;
extern crate regex;

mod parser;
mod eval;
mod error;

use std::io::prelude::*;
use std::io;

use parser::*;

/// Works like the println macro, but prints to the stderr instead of stdout.
macro_rules! println_to_stderr(
	($($arg:tt)*) => { {
		let r = writeln!(&mut ::std::io::stderr(), $($arg)*);
		r.expect("failed printing to stderr");
	} }
);

fn main() {
	let mut input;

	// The REP loop
	// Currently there is no way to exit other than the interrupt signal (ctrl + c)
	loop {
		print!(">> ");
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
					Ok(exp) => println!("AST: {:?} ", exp), // TODO
					Err(e) => println_to_stderr!("{}", e)
				}
			},
			Err(e) => println_to_stderr!("{}", e)
		}
	}
}
