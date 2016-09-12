# Namespace

The namespace of the Roller script is a space for variables and functions.

Having a variable and function with a same name is not possible because they are both in the same namespace.

All variables belong to the global namespace except the function arguments that exist only during the function execution and shadow the global name space.
Functions are always in the global namespace.

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
