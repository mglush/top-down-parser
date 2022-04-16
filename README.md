# C++ Implementation of a LL(1) Top-Down Parser.
# By Michael Glushchenko for UCSB CS160 Spring 2022.

The parser successfully scans (with the -s flag), parses (with no flag), and evaluates (with the -e flag) arithmetic expressions for the following context-free grammar:

Start	    →	ExprList
ExprList	→	ExprList ; Expression
            |	Expression
Expression	→	Expression + Expression
            |	Expression - Expression
            |	Expression * Expression
            |	Expression / Expression
            |	Expression mod Expression
            |	( Expression )
            |	num

That is, the parser works for lists of arithmetic expressions involving addition, subtraction, division, multiplication, modulus, parentheses, and semicolons.