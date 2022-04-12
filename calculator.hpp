// calculator.hpp
// Michael Glushchenko, 9403890.

#pragma once

#include "helpers.hpp"
#include <climits>
#include <vector>

//------------------------------------------------------------------------------------------
// SCANNER DEFINITION
//------------------------------------------------------------------------------------------

class Scanner {
    int line;
    int value;
    int charPos; // keeps track of the position processed at the time.
    std::string currStr; // the string that must be processed.

public:
    Token nextToken();
    void eatToken(Token);

    // helper function for when a number is encountered.
    Token recordNum();

    int lineNumber();
    int getNumberValue();
    
    Scanner();
};

//------------------------------------------------------------------------------------------
// PARSER DEFINITION
//------------------------------------------------------------------------------------------

class Parser {
    Scanner scanner;

    bool evaluate;
    std::vector<std::string> polishPostfixNotation;

    void start();
    void expressionList();
    void expressionA();
    void expressionB();
    void termA();
    void termB();
    void factor();

    // prints the result of the evaluated expression.
    // throws indexOutOfBoundsError to std::cerr if result > INT_MAX.
    // throws a divideByZeroError if division by zero occurs anywhere in the expression.
    void polishPostfixEvaluation(std::vector<std::string> polishPostfixNotation);
    
public:
    void parse();
    
    Parser(bool);
};
