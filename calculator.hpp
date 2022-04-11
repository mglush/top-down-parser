// calculator.hpp
// Michael Glushchenko, 9403890.

#pragma once

#include "helpers.hpp"
#include <climits>

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
    int result;

    void start();
    void expressionListA();
    void expressionListB();
    void expressionA();
    void expressionB();
    void termA();
    void termB();
    void factor();
    
public:
    void parse();
    
    Parser(bool);
};
