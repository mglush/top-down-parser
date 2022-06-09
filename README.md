# C++ Implementation of a Top-Down Parser.
#### By Michael Glushchenko for UCSB CS160 Spring 2022 (Translation of Programming Languages).

## Idea
Hand-code a parser to learn how parsing works firsr-hand.

## How to Run
~~~
git clone https://github.com/mglush/top-down-parser     # clone the repository.
cd top-down-parser                                      # enter repository folder.
make clean && make                                      # make the executable.
echo -n 'expression_goes_here' | ./calculator -s        # expressions are piped into the executable
~~~
where 'expression_goes_here' is a substituted by a regular arithmetic expression you would like to evaluate.

## Some Notes
  - In the last line, the expression may involve addition, substraction, multiplication, division, mod, paranthesis. Each expression is separated by a semicolon.
  - The -s flag will output a stream of tokens based on the input expression.
  - The -e flag will evaluate the input expression.
  - No flag provided will result in default parsing functionality, where scan/parse errors are checked but no output is provided.
