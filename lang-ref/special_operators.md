# Special operators

## Error handling operators

### Question mark operator, `?`

The question mark operator is a right side unary operator that converts error values into `none` values.

Examples:
```
a = foo()?
// is equivalent to
a = try foo() catch none
```

## Expression chaining

### Pipe chaining, `|`

Works similarly to shell script pipes.
Takes an expression from left and uses it as the operand of the right hand side operand.

Examples:
```
a | foo
// is equivalent to
foo(a)
```
```
a | foo | bar | baz
// is equivalent to
baz(bar(foo(a)))
```
```
a, b, c | foo
// is equivalent to
foo(a, b, c)
```

### Sequential chaining, `;`

Evaluates the first operand and then the second and returns that.

Examples:
```
a = 1; b = a + 1; a + b
```

## Function combinators

### Combination, `~`

Takes to functions and combines them by piping the output of the first one to the second one.

Examples:
```
(foo ~ bar)(a)
// is equivalent to all of:
bar(foo(a))
foo(a) | bar
((x) -> x | foo | bar)(a)

// note that (foo | bar)(a) would be equivalent to bar(foo)(a)
```

### Disjunction, `\`

An infix operator that takes two functions and combines them with a short-circuiting disjunction between them.

The first operand is evaluated and if it is a falsey value then the second operand is evaluated and returned.

Examples:
```
(foo \ bar)(a)
// is equivalent to
foo(a) or bar(a)
```
```
(()->true \ ()->true)()     // => true
(()->true \ ()->false)()    // => true
(()->false \ ()->true)()    // => true
(()->false \ ()->false)()   // => false
```
```
if a < 2 \ > 4 then
    // if a is outside the range 2...4
    ...
```

### Junction, `&`

Similar to alternation, except the second operand will be evaluated and returned only if the first one is not a falsey value.

Examples:
```
(foo & bar)(a)
// is equivalent to
(foo(a) != false) and bar(b)
```
```
if a >= 2 & <= 4 // if a is inside the range 2...4
    ...
```
