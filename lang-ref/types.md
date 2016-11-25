# Types

Roller script's accepted data types for variables are divided into two categories: singular values and collections.
These are all 'primitive' types and Roller script has no way of creating your own types.

Roller also has errors, but these are not a separate script data type, since the interpreter takes care of their manipulation.

## Singular values

Singular types are:
* Numerals
	* Numerals are further split into integers and reals (floating point).
	* No support for different base numbers yet, like hexadecimals.
* Booleans
	* A type with two possible values, `true` and `false`.
	* Other types can be treated as singular values
		* 0 and 0.0 are treated as `false`, and everything else is treated as `true`.
		* Empty string (`""` or `''`) is treated as `false` and everything else is treated as `true`.
		* Empty collections are treated as `false` and everything else is treated as `true`.
			*
* Strings
	* The strings are UTF-8 encoded and surrounded by double-quotation marks (`"`) or single-quotation marks (`'`).

The syntax of all singular value literals written as [regular expressions](https://en.wikipedia.org/wiki/Regular_expression):

```
integer: [0-9]+
real: [0-9]*\.[0-9]+
bool: true|false
string: TODO
```

## Collections

Some operations that expect a singular value can also take collections as arguments, but they try to convert it into a singular value by taking it's sum if possible.

Vectors, maps and dice throws, are indexable and therefore considered to be 'mappings', which means they can be called just as functions using indexing values as arguments.

Collection types are:
* Vector
	* A square bracket limited (`[...]`) collection that contains items and behaves similarly to the vector data type in many other languages.
	* Each item can be in the vector many times and the ordering does matter.
	* The items can be of singular or collection types.
	* The items can be a comma-separated list of zero or more items.
	* Can be interpreted as a function/mapping from indexes to values.
* Set
	* A bracket limited (`{...}`) collection that contains items and behaves similarly to the mathematical set.
	* Each item can be in the set only once and the order of items is irrelevant.
		* Can't be indexed, but can be iterated over.
	* The items can be of singular or collection types.
	* The items of the set can be a comma-separated list of zero or more items and it can end to a predicate describing what items belong to the set.
* Map
	* A bracket limited (`{...}`) collection that contains keys and their associated items and behaves similarly to the mathematical mapping.
	* Each key can be in the set only once.
	* The items can be of singular or collection types.
	* The items of the set can be a comma-separated list of zero or more key/item pairs.
	* The key/item pairs are separated by colons (`:`).
	* Can be interpreted as a function from keys to items.
* [Function](functions)
	* A special map that maps input arguments into return values.
	* Functions with one or more arguments and maps can be equivalent to each other.
	* Functions with 0 arguments are interpreted as singular values.
* Dice throw
	* A special collection that is returned by a dice throwing expression.
	* It is functionally similar to the vector and map (distribution map and result to amount occurred).
		* When treated as a map, the result is a map from values to weights.
		* When treated as a vector, the die are thrown and the data is forever transformed into a vector.

The syntax of the collection type literals written in EBNF:
```
vector = "[" , [ item , { "," , item } ] , "]" ;
set    = "{" , [ item , { "," , item } ] , predicate , "}" ;
map    = "{" , [ map pair , { "," , map pair } ] , "}" ;
map pair = key , ":" , item ;
function =
```
