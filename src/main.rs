#[macro_use]
extern crate nom;
extern crate regex;

use std::io::prelude::*;
use std::io;

mod syntax_structures;
mod parse_functions;
//mod eval;

use parse_functions::*;

fn main() {
	let mut input;

	// our main loop
	// Currently there is no way to exit other than the interrupt signal (ctrl + c in Unix-like)
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

		println!("{:?}", parse_cmd(&input));
	}
}
