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

	loop {
		print!(">> ");
		io::stdout().flush().ok().expect("Couldn't flush stdout");
		let mut temp = String::new();
		match io::stdin().read_line(&mut temp) {
			Err(error) => {
				println!("Error: {}", error);
				continue;
			},
			_ => input = temp
		}

		println!("\n{:?}", parse_cmd(&input));
	}
}
