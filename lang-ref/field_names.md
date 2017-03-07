# Field names

Field names are basically variable identifiers, meaning they map to values.

A field name consists of keys of mapping fields separated by periods and it starts with a period, but it can be omitted.
The first period means indexing the current namespace dictionary from variable identifiers into their values.

Using only a period means (eg. `if foo in . then ...`) that you are using the current namespace dictionary.
You cannot change the current namespace into any other type than dictionary (eg. `. = 4` is an error).

The name of a field can be any string value or an expression returning a string if the mapping is a dictionary or an integer if the mapping is a list.

Examples:
```
// this is always true since the first dot can be omitted
> foo == .foo
true
```
```
> a = {:} // a is now an empty map
> a.b = 5.6
> a.c = (5, 6, 7)
> a
{b: 5.6, c: (5, 6, 7)}
> a.c.0 = 3
> a
{b: 5.6, c: (3, 6, 7)}
```
```
// check if variable exists
> foo in .
false
> .foo = 413
> foo in .
true
```
```
// deleting all of the namespaces fields
> . = {:}
```

Syntax in EBNF:
```
field-name = "." , expression , { "." , expression }
```
