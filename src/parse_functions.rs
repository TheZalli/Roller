use syntax_structures::*;
use lexer::*;

use nom::IResult;
use nom::Err;
use nom::ErrorKind;

use std::str::FromStr;
//use std::collections::VecDeque;

/*fn take1_from_vecdeque<T>(input: &VecDeque<T>) -> IResult<&VecDeque<T>, T> {
	let mut input_clone = input.clone(); // TODO: get rid of copying
	let opt = input_clone.pop_front();
	expr_opt!(input_clone, opt)
}*/

fn take1_from_lexlist(input: &LexList) -> IResult<&LexList, Lexeme> {
	let &LexList(ref val) = input;
	let ref opt = val.split_first();

	match opt {
		&Some( ( ref first, ref rest ) ) => {
				IResult::Done(
					&LexList(slice_from_vec_back_to_vec(rest, &val, 1)), // we took one off
					(*first).to_owned()
				)
			},
		&None => expr_opt!(&LexList(val.to_owned()), None) // TODO: remove cloning
	}// TODO make cleaner*/
}
/// Takes a slice and returns a vector from it that has smaller or equal capacity and length as original_vec.
/// Assumes that the slice is smaller by the amount size_smaller than than the original_vec.
fn slice_from_vec_back_to_vec<'a, T>(slice: &'a[T], original_vec: &'a Vec<T>, size_smaller: usize)
		-> Vec<T> {
	let len = original_vec.len();
	let capacity = original_vec.capacity();

	// oh goody unsafe code
	// if memory stuff starts to happen mysteriously, check this
	unsafe {
		Vec::from_raw_parts(slice.as_ptr() as *mut T, len - size_smaller, capacity - size_smaller)
	}
}

/*fn vd_parser_into_lexlist_parser<T>(input: IResult<&VecDeque<Lexeme>, T >)
		-> IResult<&LexList, T > {
	match input {
		IResult::Done(I, O) => IResult::Done(&LexList(*I), O),
		IResult::Error(Err::Code(x)) => IResult::Error(Err::Code(x)),
		IResult::Incomplete(needed) => IResult::Incomplete(needed),
		_ => IResult::Error(Err::Code(ErrorKind::Custom(3))) // TODO
	}
}*/

macro_rules! take_enum_from_lexlist {
	($input:expr, $en:ident :: $kind:ident) =>
	{
		match try_parse!($input, take1_from_lexlist) {
			( i2, $en :: $kind ) => IResult::Done(i2, () ),
			( i2, _ ) => IResult::Error(Err::Code(ErrorKind::Custom(1)) )
			// TODO error types
		}
	};
	($input:expr, $en:ident :: $kind:ident ( $stuff:ident )) =>
	{
		match try_parse!($input, take1_from_lexlist) {
			( i2, $en :: $kind ( $stuff ) ) => IResult::Done(i2, $stuff ),
			( i2, _ ) => IResult::Error(Err::Code(ErrorKind::Custom(2)) )
		}
	};
}

/*macro_rules! take_enum_from_lexlist {
	($input:expr, $en:ident :: $kind:ident) => (
		vd_parser_into_lexlist_parser(take_enum_from_vecdeque!($input, $en :: $kind));
	);
	($input:expr, $en:ident :: $kind:ident ( $stuff:ident )) => (
		vd_parser_into_lexlist_parser(take_enum_from_vecdeque!($input, $en :: $kind ( $stuff )) );
	);
}*/

/// Parses commands
//named!(pub parse_cmd(&LexList) -> Cmd,
pub fn parse_cmd(input: &LexList) -> IResult<&LexList, Cmd > {
	alt!(input,
		/*parse_stmt => {
			|_| Cmd::Empty
		}
		|*/ parse_expr => {
			|exp: Expr| Cmd::Expression(exp)
		}
	)
}
//);

// Parses statements
// named!(parse_stmt(&Vec<Lexeme>) -> &str,
// 	tag_s!("stmt")
// );

/// Parses expressions
//named!(parse_expr(&LexList) -> Expr,
pub fn parse_expr(input: &LexList) -> IResult<&LexList, Expr > {
	alt_complete!(input,
		/*get_literal => {
			|litexp: LiteralExpr| Expr::Literal(Box::new(litexp))
		}
		|*/ parse_function_call => {
			|fun_sign: (Box<Ident>, Vec<Expr >)| Expr::FunCall(fun_sign) // this is a very fun line
		}
		| take_enum_from_lexlist!(Lexeme::Id(id)) => {
			|id: Box<Ident>| Expr::Var(id)
		}
	)
}
//);


/*
named!(get_identifier(&Vec<Lexeme>) -> Ident,
	expr_opt!(
		match take_from_vec<Lexeme> {
			Lexeme::Id(ident) => Some(ident),
			_ => None
		}
	)
);
*/

//named!(parse_function_call(&LexList) -> (Ident, Vec<Expr>),
pub fn parse_function_call(input: &LexList) ->
		IResult<&LexList, (Box<Ident>, Vec<Expr>)> {
	tuple!(input,
		take_enum_from_lexlist!(Lexeme::Id(Ident)),
		chain!(
			take_enum_from_lexlist!(Lexeme::LeftParen) ~
			list: separated_list!(
				take_enum_from_lexlist!(Lexeme::Comma),
				parse_expr
			) ~
			take_enum_from_lexlist!(Lexeme::RightParen),
			|| {list}
		)
	)
}
// );
