#[macro_use]
extern crate lazy_static;
extern crate regex;
//extern crate bincode;
//extern crate rustc_serialize;
//extern crate combine;

mod syntax_structures;
mod parse_util;
mod lexer;
mod eval;

use std::io::prelude::*;
use std::io;

//use combine::{parser, Parser, ParserExt};
//use combine::primitives::{State, Stream, ParseResult};

//use parse_functions::*;
use lexer::*;



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
				//if temp.trim().is_empty() { continue; } // ignore empty lines
				input = temp;
			}
		}
		let result = tokenize(&input as &str);
		println!("{:?} ", result);
		/*match lexed {
			IResult::Done( _ , lexlist) => {
				let parsed = parse_cmd(lexlist);
				println!("{:?}", parsed);
			},
			_ => { println!("Parsing failed"); }
		}*/
	}
}
