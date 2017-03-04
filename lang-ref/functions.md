# Functions

Functions are first-class citizens in Roller script.
This means that functions are a datatype just as any other.
The arguments are given by-name reference.

The function body is a single expression where the parameter variables are replaced with the corresponding argument values.

Examples:

A simple addition function:
```
> foo = (x, y) -> x + y
```

The recursive factorial function:
```
> factorial = (x) -> if x <= 0 then 1 else x * factorial(x-1)
```

Function value syntax in EBNF:
```
function = "(" , [ { identifier "," } , identifier ] , ")" , "->" , expression ;
```
