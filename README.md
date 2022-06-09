# C++ Implementation of a Top-Down Parser.
#### By Michael Glushchenko for UCSB CS160 Spring 2022 (Translation of Programming Languages).

## Table of Contents
* [Purpose](https://github.com/mglush/three-class-classifier/blob/main/README.md#purpose)
* [How To Run](https://github.com/mglush/three-class-classifier/blob/main/README.md#how-to-run)
* [Project Notes](https://github.com/mglush/three-class-classifier/blob/main/README.md#project-notes)

## Purpose
Implement a top-down recursive descent parser by hand to learn understand parsing works.

## How to Run
~~~
git clone git@github.com:mglush/top-down-parser.git     # clone the repository.
cd top-down-parser                                      # enter repository folder.
make clean && make                                      # make the executable.
echo -n 'expression_goes_here' | ./calculator -s        # expressions are piped into the executable
~~~
where 'expression_goes_here' is a substituted by a regular arithmetic expression you would like to evaluate.

## Project Notes
  - In the last line, the expression may involve addition, substraction, multiplication, division, mod, paranthesis. Each expression is separated by a semicolon.
  - The -s flag will output a stream of tokens based on the input expression.
  - The -e flag will evaluate the input expression.
  - No flag provided will result in default parsing functionality, where scan/parse errors are checked but no output is provided.
