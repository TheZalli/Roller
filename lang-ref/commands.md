# Commands

The Roller parser reads the input one command a time, then parses and evaluates it immediately.

The commands belong to one of the two categories, expressions or statements.
Expressions are commands that return a value and don't change the environment.
Statements change their environment and don't return a value.

When parsing, statements have a higher priority than expressions, so if a given command input string could be interpreted either as an expression or as a statement, the statement one is chosen.

Command syntax in EBNF:
```
command = statement | expression ;
```
