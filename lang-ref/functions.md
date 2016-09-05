# Functions

Roller script has functions that can take any values as arguments and returns a value as a result.
The arguments are given by-name reference.

The function body is a single expression where the parameter variables are replaced with the corresponding argument values.

Because of this functions behave like ordinary expressions, they can't change their environment but they are not 'pure' deterministic functions because they can reference to their environment and they can generate random numbers.

References to variables are stored by names, so that if `foo() = a`, then `foo()` is equivalent to `a`.

Examples:

A simple addition function:
```
> foo(x, y) = x + y
```

The recursive factorial function:
```
> factorial(x) = if x <= 0 then 1 else x * factorial(x-1)
```

Function definition syntax in EBNF:
```
function = identifier , "(" , [ identifier , { "," , identifier } ] , ")" , "=" , expression ;
```
