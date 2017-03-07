# Expressions

Expressions are the commands given to the Roller parser and they always return a value or throw an error.

The expressions of Roller script:
* Value literal
* Variable assignment
* Variable reference
* Call expressions
* Dice expression
* Mathematical operators
* Comparison operators
* Logical connectives
* Delete expression
* Built-in functions

## Value literal
A literal of any of the Roller script's [data types](types).

## Assignment

Values are assigned to mapping fields by writing their [name](field_names) followed by an equality sign and then the value as an expression.

Assigning `none` to a field means deleting it.

Syntax in EBNF:
```
assignment = field-name , "=" , expression ;
```

## Field access

Mapping fields are accessed by writing their name, which returns their value.

When referencing an unassigned variable, a `none` value is returned.

Examples:
```
> foo
none
> foo = 3
> foo
3
```

Syntax in EBNF:
```
reference = field-name ;
```

## Call expressions

Call expressions produce a value from a mapping, which can be functions, vectors or maps.

To call a mapping, write the parenthesized (`()`) arguments/keys after it.

Using a call expression on vectors and maps is the same as indexing them with a period.

Syntax in EBNF:
```
call = field-name , "(" , [ expression , { "," , expression } ] , ")" ;
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

## Built-in functions

Special functions are more complex functions defined by the interpreter.
They might be able to do things that normal functions can't but they are defined in compile-time.

Some built-in functions:
* `len(a)`, returns the length of `a`.
* `sum(a)`, returns the sum of `a`.
* `sqrt(a)`, returns the square root of `a`.
* `root(n, a)`, returns `n`:th root of `a`.
* `flatten(a)`, flattens all of the sub-collections of `a`.
* `map(f, a)`, maps the function `f` over the collection `a`.
* `acc(f, s, a)`, accumulates function `f` over the collection `a` using `s` as the starting value.
* `to_string(a)`, returns the string representation of `a`.
* `parse(a)`, parses the given string `a` into a Roller type.
* `to_list(a)`, changes the string `a` into a vector of characters.
* `eval(a)`, evaluates the `a` string as a Roller command and returns the value.
