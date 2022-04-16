// calculator.hpp
// Michael Glushchenko

#pragma once

#include "helpers.hpp"
#include <climits>
#include <stack>

//--------------------
// SCANNER DEFINITION
//--------------------

class Scanner {
    int line;
    int value;
    unsigned int charPos;
    std::string currStr;

public:
    Token nextToken();
    // helper function for when a number
    // is encountered; functino records that
    // number into value member variable.
    Token recordNum();
    void eatToken(Token);
    
    int lineNumber();
    int getNumberValue();
    
    Scanner();
};

//-------------------
// PARSER DEFINITION
//-------------------

class Parser {
    Scanner scanner;

    bool evaluate;
    std::stack<std::string> my_stack;
    std::string final_result;

    //-----------------------------------------------------------------
    // the implementation uses the following LL(1) CFG:
    //-----------------------------------------------------------------
    // start -> expressionA expressionList
    // expressionList -> ; expressionA expressionList | ε
    // expressionA -> termA expressionB
    // expressionB -> + termA expressionB | - termA expressionB | ε
    // termA -> factor termB
    // termB -> * factor termB | / factor termB | mod factor termB | ε
    // factor -> (expressionA) | num
    //-----------------------------------------------------------------

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
