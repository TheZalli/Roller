# Namespace

The namespace of the Roller script is a map from identifiers strings into values.
The values can be of any valid datatype.

Allowed identifier names are UTF-8 strings that start with a Unicode letter character or an underscore, continued by any amount of Unicode letter characters, Unicode numeral characters and underscores.

The parser has a set of built-in values and functions, called constants, that can't be changed from inside Roller.
Constant values will include the Pi as `pi` and the Euler's number as `e`.

Examples:

Function argument shadowing a global name:
```
> a = 2
> foo = () -> a * 2
> foo()
4
> bar = (a) -> a * 2
> bar(3)
6
```
