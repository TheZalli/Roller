# Namespace

The namespace of the Roller script is a map from identifiers strings into values.
The values can be of any valid datatype, which are numerals, booleans, strings and collections.

Allowed identifier names are UTF-8 strings that start with a Unicode letter character or an underscore, continued by any amount of Unicode letter characters, Unicode numeral characters and underscores.

Examples:

Reassigning a function as a variable:
```
> foo(x) = x + 1
> foo(1)
2
> foo = 3
> foo(1)
Evaluation error: No function named "foo" found
```

Function argument shadowing a global name:
```
> a = 2
> foo() = a * 2
> foo()
4
> bar(a) = a * 2
> bar(3)
6
```
