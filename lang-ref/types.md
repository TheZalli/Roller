# Types

Roller script's accepted data types for variables are divided into two categories: singular values and collections.
These are all 'primitive' types as Roller script has no way of creating your own types.

Roller also has errors, but these are not a separate script data type, since the interpreter takes care of their manipulation.

## Singular values

Singular types are:
* Numerals
	* Numerals are further split into integers and reals (floating point).
	* No support for different base numbers yet, like hexadecimals.
* Booleans
	* A type with two possible values, `true` and `false`.
	* Can be converted from other types
		* 0 and 0.0 converts to `false`, and everything else converts to `true`.
		* Empty string (`""` or `''`) converts to `false` and everything else converts to `true`.
		* Empty collections ()
* Strings
	* The strings are UTF-8 encoded and surrounded by double-quotation marks (`"`) or single-quotation marks (`'`).
	* Escape characters are not allowed for now, but it is a TODO feature.

The syntax of all singular value literals written in regular expressions:

```
integer: [0-9]+
real: [0-9]*\.[0-9]+
string: \"(.*?)\"
```

## Collections

Some operations that expect a singular value can also take collections as arguments, but they try to convert it into a singular value by taking it's sum if possible.

Vector and map, are indexable and therefore considered as 'mappings', which means they can be called just as functions using indexing values as arguments.

Collection types are:
* Vector
	* A square bracket limited (`[]`) collection that contains items and behaves similarly to the vector data type in many other languages.
	* Each item can be in the vector many times and the ordering does matter.
	* The items can be of singular or collection types.
	* The items can be a comma-separated list of zero or more items.
	* Can be interpreted as a function/mapping from indexes to values.
* Set
	* A bracket limited (`{}`) collection that contains items and behaves similarly to the mathematical set.
	* Each item can be in the set only once and the order of items is irrelevant.
		* Can't be indexed, but can be iterated.
	* The items can be of singular or collection types.
	* The items of the set can be a comma-separated list of zero or more items and it can end to a predicate describing what items belong to the set.
* Map
	* A bracket limited (`{}`) collection that contains keys and their associated items and behaves similarly to the mathematical mapping.
	* Each key can be in the set only once.
	* The items can be of singular or collection types.
	* The items of the set can be a comma-separated list of zero or more key/item pairs.
	* The key/item pairs are separated by colons (`:`).
	* Can be interpreted as a function from keys to items.
* Dice throw
	* A special collection that is returned by a dice throwing expression.
	* A dice throw can't be represented by literals.
	* It is functionally similar to the vector and map (distribution map, result to amount occurred) and can be implicitly converted into both.

The syntax of the collection type literals written in EBNF:

```
vector ::= "[" , [ item , { "," , item } ] , "]" ;
set    ::= "{" , [ item , { "," , item } ] , predicate , "}" ;
map    ::= "{" , [ map pair , { "," , map pair } ] , "}" ;
map pair ::= key , ":" , item ;
```
