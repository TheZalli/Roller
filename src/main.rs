#[macro_use] extern crate lazy_static;
extern crate regex;

mod parser;
mod eval;

use std::io::prelude::*;
use std::io;

use parser::*;

fn main() {
	let mut input;

	// The REP loop
	// Currently there is no way to exit other than the interrupt signal (ctrl + c)
	loop {
		print!(">> ");
		// flush so our prompt is visible
		io::stdout().flush().ok().expect("Couldn't flush stdout");

		let mut temp = String::new();
		match io::stdin().read_line(&mut temp) { // read input
			Err(error) => {
				println!("Input error: {}", error);
				continue; // go to loop start, do not pass parse and eval
			},
			_ => {
				if temp.trim().is_empty() { continue; } // ignore empty lines
				input = temp;
			}
		}
		let token_res = tokenize(&input as &str);
		println!("Tokens: {:?} ", token_res); // DEBUG

		if let Ok(tk_vec) = token_res {
			let synparsed = parse_cmd(&tk_vec);
			println!("AST: {:?} ", synparsed); // DEBUG
		}
	}
}
