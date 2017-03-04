# Control structures

## If expression

If expressions perform conditional execution based on a condition expression.
Has else if branches that start with the keyword `elsif`.

Syntax in EBNF:
```
if = "if" , expression , "then" , expression , { "elsif" , expression }, [ "else" , expression ] ;
```

## Try/Catch expression

Try/Catch expressions will catch errors created in the try-part and then move to executing the catch-part.

Syntax in EBNF:
```
try-catch = "try" , expression , "catch" , expression ;
```

## While-loop

Loops the given expression as long as the given condition expression holds true.

Syntax in EBNF:
```
while-loop = [ label , ":" ] , "while" , expression , "loop" , expression ;
```

## For-loop

Loops the given expression with one or more loop variables.

Syntax in EBNF:
```
for-loop = [ label , ":" ] , "for" , identifier , { "," , identifier } , "in" , expression , "loop" , expression ;
```

## Break statement

The `break` keyword breaks from the current loop, or from the loop with the given label.

If a label is given and the execution is not inside any loops with the given name, an error is raised.

Syntax in EBNF:
```
break = "break" , [ label ] ;
```

## Continue statement

Restarts the current loop, or a parent loop with the given label, from the start of the next loop execution.

Syntax in EBNF:
```
continue = "continue" , [ label ] ;
```
