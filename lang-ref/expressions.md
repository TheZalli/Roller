# Expressions

Expressions are the commands given to the Roller parser and they always return a value or throw an error.

The expressions of Roller script:
* Value literal
* Variable assignment
* Variable reference
* Function definition
* Call expressions
* Dice expression
* Mathematical operators
* Comparison operators
* Logical connectives
* Delete expression
* If expression
* Try/Catch expression
* Keyword functions

## Value literal
A literal of any of the Roller script's [data types](types).

## Variable assignment

Values are assigned to variables by writing their identifier followed by an equality sign and then the value as an expression.

Assigning a variable overrides any other function or variable with the same name.

Syntax in EBNF:
```
assignment = identifier , "=" , expression ;
```

## Variable reference

Variables are referenced by writing their identifier, which returns their value.
When referencing an unassigned variable or trying to reference a function as a variable, an error is thrown.

## Function definition

Named functions are defined by writing their name, followed by a comma separated arguments, if any, in parentheses, followed by an equality sign and the body as an expression.

Syntax in EBNF:
```
function definition = identifier , "(" , [ identifier , { "," , identifier } ] , ")" , "=" , expression ;
```

## Call expressions

Call expressions produce a value from a mapping, which can be functions, vectors or maps.

To call a mapping, write the parenthesized (`()`) arguments/keys after it.

Using a call expression on vectors and maps means indexing them.

Call expression syntax in EBNF:
```
call = ( identifier | expression ) , "(" , [ expression , { "," , expression } ] , ")" ;
```

## Dice expression

An expression representing a dice throw in dice notation (`NdM`).

The first parameter tells the amount of dice thrown, and it's default value is 1.
The second parameter tells the amount of sides in the dices, and it's default value is 6.

If the second parameter is a collection, it uses that as the "sides" of the dices using the following rules:

* If it is a vector or set, it returns a vector or set respectively, containing random items from the argument.

* If it is a map, it expects the mapped values to be numerals, so that it is like a weighed distribution, and then uses those values as weights to create a set containing randomly picked keys from the argument.

If instead the first argument is a collection, the dice throw is done for each item (for map the keys are left untouched) and the resulting collection is returned.

## Mathematical operators

The mathematical operators are defined only for numerals and collections of numerals, except addition which also works as string concatenation.

The piecewise operators allow only collections of same size as their arguments and they are presented similarly to the "normal" singular ones but with a dot before them.

Singular addition, subtraction, modulo and exponentiation are defined only for the singular operands.

Singular multiplication and division allow either one of the operands to be a collection, but not both.

Negation is always a piecewise operation for collections.

Singular mathematical operators:
* Addition, `a + b`
* Identity, `+a`
	* Does nothing but returns the operand as-is and is defined for every expression.
* Subtraction, `a - b`
* Negation, `-a`
* Multiplication, `a * b`
* Division, `a / b`
* Modulo, `a % b`
* Exponentiation, `a ^ b`

The piecewise mathematical operators:
* Addition, `a .+ b`
* Subtraction, `a .- b`
* Multiplication, `a .* b`
* Division, `a ./ b`
* Modulo, `a .% b`
* Exponentiation, `a .^ b`

## Comparison operators

The comparison operators take values as operands and return boolean values.

Comparison operators:
* Equality, `a == b`
* Inequality, `a != b`
* Greater than, `a > b`
* Less than, `a < b`
* Greater or equal, `a >= b`
* Less or equal, `a <= b`

Equality and inequality are defined for almost all types.
Two operands are equal if and only if they are of the same type and same value, or one of the operands can be implicitly converted into to the same type as the other and they are of same value (like integers and reals).

If the left operand is left empty, then the expression is treated as an anonymous function, for example `(< b)(a)` is equivalent to `a < b`.

## Logical connectives

Logical connectives take boolean values as operands and return boolean values.

Logical connectives:
* And, `a and b`, `a && b`
	* Returns logical and
* Or, `a or b`, `a || b`
	* Returns logical or
* Xor, `a xor b`
	* Returns logical xor

## Delete expression

Delete expressions remove a variable from the namespace, freeing their memory.
Delete expressions are written by writing `delete` followed by the identifier you want to delete.

The delete expression returns the removed value.

Syntax in EBNF:
```
delete = "delete" , identifier ;
```

## If expression

If expressions perform conditional execution based on a condition expression.

Syntax in EBNF:
```
if = "if" , expr , "then" , expr , { "elsif" , expr }, [ "else" , expr ] ;
```

## Try/Catch expression

Try/Catch expressions will catch errors created in the try-part and then move to executing the catch-part.

Syntax in EBNF:
```
try-catch = "try" , expr , "catch" , expr ;
```

## Special functions

Special functions are more complex functions defined by the interpreter.
They can do things that normal functions can't but they could be defined compile-time.

Some keyword functions:
* `len(a)`, returns the length of `a`.
* `sum(a)`, returns the sum of `a`.
* `sqrt(a)`, returns the square root of `a`.
* `root(n, a)`, returns `n`:th root of `a`.
* `flatten(a)`, flattens all of the sub-collections of `a`.
* `acc(f, s, a)`, accumulates function `f` over the collection `a` using `s` as the starting value.
* `to_string(a)`, returns the string representation of `a`.
* `parse(a)`, parses the given string `a` into a Roller type.
* `to_list(a)`, changes the string `a` into a vector of characters.
