# Predicates

Predicates are functions and operators that take values and predicates and return a boolean or a predicate and they can be used in filtering and giving variables limitations.

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
Two operands are equal if and only if they are of the same type and same value, or one of the operands can be implicitly converted into to the same type as the other and they are of same value.

If the left operand is left empty, then the expression is treated as an anonymous function, for example `(< b)(a)` is equivalent to `a < b`.

## Logical connectives

Logical connectives connect predicates or boolean values.

Logical connectives:
* Not, `not a`
	* Returns the logical inversion of the boolean value or predicate
* And, `a and b`
	* Returns logical and
		* True if both are one
	* Short-circuiting
* Or, `a or b`
	* Returns logical or
		* True if either is one
	* Short-circuiting

## In operator, `in`

The in operator tells if the variable is in the given collection.

Examples:
```
> 3 in 1..10
true
> "foo" in {"bar", "baz"}
false
> 3 in (-2, 0, 1, -2, 3, -2)
true
```
