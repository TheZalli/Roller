# Statements

Statements are commands that change the value of the environment and don't return a value.

The statements of Roller script:
* Variable assignment
* Function definition
* Delete statement
* Try/Catch statement

## Variable assignment

Values are assigned to variables by writing their identifier followed by an equality sign and then the value as an expression.
Assigning to a previously undefined name or to a function's name defines them as a variable.

Syntax in EBNF:
```
assignment = identifier , "=" , expression ;
```
