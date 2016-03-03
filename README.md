# Roller
An interactive dice rolling command parser written with Rust. WIP

The aim is to create a simple (yeah, right) interactive command-line parser for virtual dice throwing, using the [dice notation] (https://en.wikipedia.org/wiki/Dice_notation).
In addition, there will be other features, such as list filtering, variables and functions.

## Documentation

The "Roller.cf" -file contains the parsing rules in Labeled BNF grammar, as used by the [BNFC program] (http://bnfc.digitalgrammars.com).
Though at the moment I will not use BNFC anymore and it is outdated, the file is still left as a reference for the current implementation.

The "language draft" files contain, slightly outdated, drafts and ideas for the finished Roller language.
The latest version of the language rules is currently only in my head, but there shouldn't be any great differences when compared to my drafts.
