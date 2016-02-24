#[macro_use]
extern crate nom;
extern crate regex;
extern crate bincode;
extern crate rustc_serialize;

use std::io::prelude::*;
use std::io;

mod syntax_structures;
mod parse_functions;
mod lexer;
//mod eval;

use parse_functions::*;
use lexer::*;

use nom::IResult;

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
		let lexed = tokenize(&input);
		print!("{:?} -> ", lexed);
		match lexed {
			IResult::Done( _ , lexlist) => {
				let parsed = parse_cmd(lexlist);
				println!("{:?}", parsed);
			},
			_ => { println!("Parsing failed"); }
		}
	}
}
