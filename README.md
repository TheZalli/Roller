# Roller
An interactive dice rolling command parser with Rust and Nom parsing library. WIP

The aim is to create a simple interactive command-line parser for virtual dice throwing, using [dice notation] (https://en.wikipedia.org/wiki/Dice_notation).
In addition, there will be other features, such as list filtering, and variable and function definition.

The "Roller.cf" -file contains the parsing rules in Labeled BNF grammar, as used by the [BNFC program] (http://bnfc.digitalgrammars.com).
Though at the moment I will not use BNFC anymore, the file is still left as a reference for the current implementation.
