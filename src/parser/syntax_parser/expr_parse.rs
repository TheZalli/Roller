use parser::parse_util::*;
use parser::syntax_types::*;
use parser::lexer::lexer_util::lexemes::*;
use parser::syntax_parser::synpar_util::*;

/// Information associated with an operation
#[derive(Clone, Copy)]
struct OpInfo {
	/// Precedence level
	level: u32,
	/// associativity
	assoc: Assoc,
	// Argument info
	arg_info: ArgInfo,
}

#[derive(PartialEq, Clone, Copy)]
enum Assoc {
	Left,
	Right
}

#[derive(PartialEq, Clone, Copy)]
#[allow(dead_code)] // TODO: remove when all the variants are used somewhere
enum ArgInfo {
	/// Operators with a singular argument
	/// The argument tells at which side of the argument the operator must be in.
	Unary(Assoc),
	/// Operators with two arguments
	Binary,
	/// For binary operators that can be used as unary, like substraction/negation.
	/// The argument tells at which side of the argument the operator must be in.
	AllowUnary(Assoc),
	/// For special operators that are allowed to stand alone in addition of having two arguments.
	/// For the dice operator.
	AllowNullary,
	/// For function calls etc
	Variable,
}

fn get_op_info(op: &AnyOp) -> OpInfo {
	let (lvl, assoc, arg_am) =
		match *op {
			AnyOp::Math(ref x) =>
				match *x {
					MathOp::Dice => (5, Assoc::Left, ArgInfo::AllowNullary),
					MathOp::Plus => (1, Assoc::Left, ArgInfo::AllowUnary(Assoc::Left)),
					MathOp::Minus => (1, Assoc::Left, ArgInfo::AllowUnary(Assoc::Left)),
					MathOp::Mul => (3, Assoc::Left, ArgInfo::Binary),
					MathOp::Div => (3, Assoc::Left, ArgInfo::Binary),
					MathOp::Pow => (4, Assoc::Right, ArgInfo::Binary),
				},
			AnyOp::FunCall(_) => (0, Assoc::Left, ArgInfo::Variable), // different than the others
		};
	OpInfo{ level: lvl, assoc: assoc, arg_info: arg_am}
}

/// Parses expressions using the Shunting-yard algorithm
pub fn parse_expr(input: InType) -> ParseResult<Expr> {
	let mut operator_stack	= Vec::<AnyOp>::new();
	let mut operand_stack	= Vec::<Expr>::new();

	let mut input_clone = input.clone();

	// read while there is unread input or still operators left
	while !input_clone.is_empty() {
		// read a token
		let pair = input_clone.split_first();
		// since we know our input isn't empty yet this should be a safe unwrap
		let pair = pair.unwrap();

		let tk = pair.0.clone();
		input_clone = pair.1;

		// check the token
		match tk {
			// push all of the operand lexemes into the operand stack
			Lexeme::IntLit(x) => {
				let exp = Expr::Val(Value::Num(NumType::Int(x)));
				// TODO: ^^^^^ make this look not horrible
				operand_stack.push(exp);
			},
			Lexeme::RealLit(x) => {
				let exp = Expr::Val(Value::Num(NumType::Real(x)));
				operand_stack.push(exp);
			},
			Lexeme::StrLit(x) => {
				let exp = Expr::Val(Value::Str(x));
				operand_stack.push(exp);
			},
			Lexeme::Id(x) => {
				// check if we have a function call
				if input_clone.get(0) == Some(&Lexeme::LeftParen) {
					unimplemented!();
				}
				else {
					operand_stack.push(Expr::Var(x));
				}
			},
			// if we find a normal operator push it to the operator stack
			Lexeme::Op(x) => {
				let op = AnyOp::Math(x);
				let op_info = get_op_info(&op);

				// the predicate for popping operators from the operator stack
				let pop_pred = |info1: OpInfo, info2: OpInfo| {
					((info1.assoc == Assoc::Left) && (info1.level <= info2.level)) ||
					((info1.assoc == Assoc::Right) && (info1.level < info2.level))
				};

				// pop and 'actualize' operators from the stack if they have smaller precedence.
				// this loop is important for the algorithm
				loop {
					// if the stack isn't empty
					if let Some(popped_op) = operator_stack.pop() {
						let popped_info = get_op_info(&popped_op);

						// if the predicate holds
						if pop_pred(op_info, popped_info) {
							try!(actualize_op(&mut operand_stack, popped_op));
						} else {
							break;
						}
					}
					else {
						break;
					}
				}

				operator_stack.push(op);
			},
			Lexeme::LeftParen => { // (
				// TODO
			},
			Lexeme::RightParen => { // )
				// TODO
			}
			Lexeme::End => {
				// we found our end token, assume it was the last
				return Err(1)
			},
			_ => unimplemented!(), // TODO: implement the rest
		}
	};

	// now we empty the operator stack as well
	// phase 2 of the algorithm
	loop {
		match operator_stack.pop() {
			Some(op) => try!(actualize_op(&mut operand_stack, op)),
			None => break,
		}
	}

	// if the input was well formed we should have only one expression as the final expression
	if operand_stack.len() != 1 {
		// TODO: Remove these prints or move them behind the debug feature gate
		println!("operands: {:?}", operand_stack);
		println!("operators: {:?}", operator_stack);
		println!("unconsumed input: {:?}", input_clone);
		Err(8)
	}
	else {
		Ok(operand_stack[0].clone())
	}
}

/// Actualizes the given operator into the operand stack given
fn actualize_op(operand_stack: &mut Vec<Expr>, operator: AnyOp) -> ParseResult<()> {
	//let lhs_arg_opt: Option<Expr>;
	//let rhs_arg: Expr;
	let ast_node: Expr;

	// actualize the operation from tokens into abstract syntax tree
	match get_op_info(&operator).arg_info {
		// if the operation has only one argument
		ArgInfo::Unary(_) => {
			match operand_stack.pop() {
				Some(x) => {
					ast_node = Expr::Op{op: operator, args: vec!(Some(x))};
				},
				None => return Err(3),
			}

		},
		// if the operation has one or two arguments
		ArgInfo::Binary | ArgInfo::AllowUnary(_) => {
			// check the right hand side
			match operand_stack.pop() {
				Some(rhs) => {
					ast_node =
						match operand_stack.pop() {
							Some(lhs) => Expr::Op{op: operator, args: vec!(Some(lhs), Some(rhs))},
							None => {
								// if unary application of the operation is allowed,
								// only one argument is ok
								match get_op_info(&operator).arg_info {
									ArgInfo::AllowUnary(_) =>
										Expr::Op{op: operator, args: vec!(Some(rhs))},
									_ => return Err(6),
								}
							},
						};
					},
				None => return Err(5),
			};
		},
		ArgInfo::AllowNullary => {
			// first argument?

			ast_node =
				match operand_stack.pop() {
					Some(rhs) =>
						match operand_stack.pop() {
								Some(lhs) => Expr::Op{op: operator,
													args: vec!(Some(lhs), Some(rhs))},
								None => {
									match get_op_info(&operator).arg_info {
										ArgInfo::AllowUnary(_) =>
											Expr::Op{op: operator, args: vec!(None, Some(rhs))},
										_ => return Err(6),
									}
								},
						},
					None =>
						Expr::Op{op: operator, args: Vec::new()},
				};
		}
		// if the operation has variable amount of arguments, TODO
		ArgInfo::Variable => return Err(7),
	}

	operand_stack.push(ast_node);

	Ok(())
}
