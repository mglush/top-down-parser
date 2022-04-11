// calculator.cpp
// Michael Glushchenko, 9403890.

#include "calculator.hpp"
#include <iostream>

//---------------------------------------------
// Scanner implementation
//---------------------------------------------

Scanner::Scanner() : line(1), value(0), charPos(0) {
    std::getline(std::cin, this->currStr);
    this->currStr = this->currStr.substr(3);
}

Token Scanner::nextToken() {
    if (std::isspace(this->currStr[this->charPos])) { this->charPos++; return this->nextToken(); }
    else if (std::isdigit(this->currStr[this->charPos])) { return this->recordNum(); }
    else if (this->currStr[this->charPos] == '+') { return T_PLUS; }
    else if (this->currStr[this->charPos] == '-') { return T_MINUS; }
    else if (this->currStr[this->charPos] == '*') { return T_MULTIPLY; }
    else if (this->currStr[this->charPos] == '/') { return T_DIVIDE; }
    else if (this->currStr[this->charPos] == '(') { return T_OPENPAREN; }
    else if (this->currStr[this->charPos] == ')') { return T_CLOSEPAREN; }
    else if (this->currStr[this->charPos] == ';') { return T_SEMICOLON; }
    else if (this->currStr[this->charPos] == 'm') {
        if (this->charPos + 1 > this->currStr.length() - 1) { scanError(this->line, this->currStr[this->charPos]); }
        if (this->currStr[this->charPos + 1] == 'o') {
            if (this->charPos + 2 > this->currStr.length() - 1) { scanError(this->line, this->currStr[this->charPos]); }
            if (this->currStr[this->charPos + 2] == 'd') { return T_MODULO; }
            else { scanError(this->line, this->currStr[this->charPos + 2]); }
        } else { scanError(this->line, this->currStr[this->charPos + 1]); }
    }
    else if (this->charPos >= this->currStr.length()) {
        std::getline(std::cin, this->currStr);
        this->charPos = 0;
        if (this->currStr.length() > 0) { return this->nextToken(); }
        else { return T_EOF; }
    }
    else { scanError(this->line, this->currStr[this->charPos]); }
}

void Scanner::eatToken(Token toConsume) {
    Token next = this->nextToken();

    if (tokenToString(next) != tokenToString(toConsume)) { mismatchError(this->line, toConsume, next); }
    else {
        if (next == T_PLUS || next == T_MINUS || next == T_MULTIPLY || next == T_DIVIDE ||
            next == T_OPENPAREN || next == T_CLOSEPAREN) { this->charPos++; }
        else if (next == T_MODULO) { this->charPos += 3; }
        else if (next == T_NUMBER) { this->charPos += std::to_string(this->value).length(); }
        else if (next == T_SEMICOLON) { this->line++; this->charPos++; }
        else if (next == T_EOF) { /* do nothing. */ }
    }
}

Token Scanner::recordNum() {
    std::string result;
    int temp = this->charPos;
    result += this->currStr[temp];
    
    while (this->currStr.length() - 1 >= temp + 1
        && std::isdigit(this->currStr[temp + 1])
        && !std::isspace(this->currStr[temp + 1])) { 
        result += this->currStr[temp + 1]; temp++;
    }
    
    this->value = std::stoi(result);
    return T_NUMBER;
}

int Scanner::lineNumber() { return this->line; }

int Scanner::getNumberValue() { return this->value; }

//---------------------------------------------
// Parser implementation
//---------------------------------------------

Parser::Parser(bool eval) : evaluate(eval), result(0) { }

void Parser::parse() { start(); }

void Parser::start() { expressionA(); expressionList(); }

void Parser::expressionList() {
    switch (scanner.nextToken()) {
        case T_SEMICOLON: scanner.eatToken(T_SEMICOLON); expressionA(); break;
        default: break; // epsilon transition, do nothing.
    }
}

void Parser::expressionA() { termA(); expressionB(); }

void Parser::expressionB() {
    switch (scanner.nextToken()) { 
        case T_PLUS: scanner.eatToken(T_PLUS); termA(); expressionB(); break;
        case T_MINUS: scanner.eatToken(T_MINUS); termA(); expressionB(); break;
        default: break; // epsilon transition, do nothing.
    }
}

void Parser::termA() { factor(); termB(); }

void Parser::termB() {
    switch (scanner.nextToken()) {
        case T_MULTIPLY: scanner.eatToken(T_MULTIPLY); factor(); termB(); break;
        case T_DIVIDE: scanner.eatToken(T_DIVIDE); factor(); termB(); break;
        case T_MODULO: scanner.eatToken(T_MODULO); factor(); termB(); break;
        default: break; // epsilon transition, do nothing.
    }
}

void Parser::factor() {
    switch (scanner.nextToken()) {
        case T_NUMBER: scanner.eatToken(T_NUMBER); break;
        case T_OPENPAREN: scanner.eatToken(T_OPENPAREN); expressionA(); scanner.eatToken(T_CLOSEPAREN); break;
        default: parseError(scanner.lineNumber(), scanner.nextToken());
    }
}