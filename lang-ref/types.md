# Types

Roller script's accepted data types for variables are divided into two categories: singular values and collections.
These are all 'primitive' types and Roller script has no way of creating your own types.

Roller also has errors, but these are not a separate script data type, since the interpreter takes care of their manipulation.

## Singular values

Singular types are:
* None type, `none`
	* A special type with only one value
	* `none` value is treated as an empty value
	* Can be also treated as a function that always returns `none` for all parameters
		* `none(...)` evaluates to `none`
	* Assigning a none as a value of a field deletes it
		* `{a: 1, b: 2}.a = none` evaluates to `{b: 2}`
* Numerals, `num`
	* Numerals are split into integer, `int`, and real, `real`, numerals
* Booleans, `bool`
	* A type with two possible values, `true` and `false`
	* Other types can be treated as boolean `false`, called as *falsey* values
		* NOTE, unlike some other languages, zero (0 and 0.0) are **not** treated as `false`
		* Empty string (`""` or `''`) is treated as `false`
		* Empty collections are treated as `false`
		* `none` value is treated as `false`
	* No value can be treated as a boolean `true` implicitly
		* One way to convert into boolean `true` is to use the negation of to boolean `false` conversion, eg. `a != false`
* Strings, `str`
	* The strings are a stream of UTF-8 encoded characters surrounded by double-quotation marks (`"`) or single-quotation marks (`'`).

## Collections

Some operations that expect a singular value can also take collections as arguments, but they try to convert it into a singular value by taking it's sum if possible.

Lists, maps and dice throws, are indexable and therefore considered to be 'mappings', which means they can be called just as functions using indexing values as arguments.

Collection types are:
* List, `(,)`
	* A comma-separated (`,`), parenthesis-limited (`(...)`) collection that contains items and behaves similarly to the vector or tuple data type in many other languages
	* Each item can be in the list many times and the ordering does matter
	* The items can be of singular or collection types
	* Can be interpreted as a function/mapping from indexes to values
	* A single item list can be interpreted as a singular value
* Set, `{}`/`{,}`
	* A bracket limited (`{...}`) collection that contains items and behaves similarly to the mathematical set
	* Each item can be in the set only once and the order of items is irrelevant
		* Can't be indexed, but can be iterated over
	* The items can be of singular or collection types
	* The items of the set can be a comma-separated list of zero or more items and it can end to a predicate describing what items belong to the set
* Dictionary, `{:}`
	* A bracket limited (`{...}`) collection that contains keys and their associated items and behaves similarly to the mathematical mapping.
	* Each key can be in the set only once
	* The items can be of singular or collection types
	* The items of the set can be a comma-separated list of zero or more key/item pairs
	* The key/item pairs are separated by colons (`:`)
	* Can be interpreted as a function from keys to items
* [Function](functions), `() -> ()`
	* A special map that maps input arguments into return values
	* Functions with one or more arguments and maps can be equivalent to each other
	* Functions with 0 arguments are interpreted as singular values
* Dice throw, `d`
	* A special collection that is returned by the dice throwing expression
	* It is functionally similar to the vector and dictionary (distribution map and result to amount occurred)
		* When treated as a dictionary, the result is a map from values to weights
		* When treated as a vector, the die are thrown and the data is forever transformed into a vector

The syntax of the collection type literals written in EBNF:
```
list     = "(" , "," | ( item , { "," , item } , [ "," ] ) , ")" ;
set      = "{" , [ item , { "," , item } ] , predicate , "}" ;
map      = "{" , ":" | ( map pair , { "," , map pair } ) , "}" ;
map pair = key , ":" , item ;
function = "(" , [ { identifier "," } , identifier ] , ")" , "->" , expression ;
```

## Type checking
