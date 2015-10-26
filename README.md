# Roller
An interactive dice rolling command parser. WIP

The aim is to create a simple interactive command-line parser for virtual dice throwing, using [dice notation] (https://en.wikipedia.org/wiki/Dice_notation).
In addition, there will be other features, such as list filtering, and variable and function definition.

The "Roller.cf" -file contains the parsing rules in Labeled BNF grammar, as used by the [BNFC program] (http://bnfc.digitalgrammars.com).

Currently I am using a custom fork of the original BNFC program (https://github.com/mrZalli/bnfc).
The only difference at the moment is that my fork names C++ source files with '.CPP' extension instead of '.C'.
Install it like you would install the original program from the source.
