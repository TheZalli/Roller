# Expressions

Expressions are commands that don't change the value of the environment and return a value.

The expressions of Roller script:
* Value literal
* Variable reference
* Call expressions
* Dice expression
* Mathematical operators
* Comparison operators
* Logical connectives
* Keyword expressions

## Value literal
A literal of any of the Roller script's data types. Check the Types for more info.

## Variable reference

Variables are referenced by writing their identifier, which returns their value.
When referencing an unassigned variable or trying to reference a function as a variable, an error is thrown.

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
	* An identity function, does nothing and is defined for every expression.
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
