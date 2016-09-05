# Roller script language reference

This is a WIP reference/specification for the script language used in the Roller command line interpreter, known as the Roller script.

To get a better sense what has been already implemented, go to the old-lang-ref folder.

You can find short snippets written in [EBNF](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_Form) (Extended Backus-Nauer Form) that explain the syntax of some of the language features.

## Short description

The Roller script is a simple dynamically typed, interpreted language with by-name reference semantics.

It's original purpose is to allow users to easily generate, manipulate and show dice throws from an interactive REPL command line application, but it can also be used as a simple command-line calculator.
