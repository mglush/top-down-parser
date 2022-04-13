// calculator.hpp
// Michael Glushchenko, 9403890.

#pragma once

#include "helpers.hpp"
#include <climits>
#include <stack>

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
    Token recordNum();
    void eatToken(Token);
    
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
    std::stack<std::string> my_stack;
    std::string final_result;

    void start();
    void expressionList();
    void expressionA();
    void expressionB();
    void termA();
    void termB();
    void factor();
    
public:
    void parse();
    
    Parser(bool);
};
