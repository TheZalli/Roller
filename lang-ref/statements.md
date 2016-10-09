# Statements

Statements are commands that change the value of the environment and don't return a value.

The statements of Roller script:
* Variable assignment
* Function definition
* Delete statement
* If statement.
* Try/Catch statement

## Variable assignment

Values are assigned to variables by writing their identifier followed by an equality sign and then the value as an expression.

Assigning to a previously undefined name or to a function's name defines them as a variable.

Syntax in EBNF:
```
assignment = identifier , "=" , expression ;
```

## Function definition

Functions are defined by writing their name, followed by a comma separated arguments, if any, in parentheses, followed by an equality sign and the body as an expression.

Defining a function overrides any other function or variable with the same name.

Syntax in EBNF:
```
function definition = identifier , "(" , [ identifier , { "," , identifier } ] , ")" , "=" , expression ;
```

## Delete statement

Delete statements remove a variable or a function from the namespace, freeing their memory.
Delete statements are written by writing `delete` followed by the name of the variable or function you want to delete.

Syntax in EBNF:
```
delete = "delete" , identifier ;
```

## If statement

If-statements are similar to the If-expressions, except that they accept any commands as the body.

## Try/Catch statement

Try/Catch statements are similar to the Try/Catch expressions, so that the both will catch errors created in the try-part and then move to executing the catch-part.

The statement version accepts any commands as

Syntax in EBNF:
```
try-catch stmt = "try" , stmt , "catch", stmt ;
```
