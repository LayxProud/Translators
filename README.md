# Translators
Translator design programs

The task is to create interpretators for a following "try-catch" grammar:

stmt ::= try { a' } cc
a' ::= a b
a ::= print expr; | throw expr; | stmt
b ::= a' | Epsilon
cc ::= catch ( expr ) { a' } [cc]
