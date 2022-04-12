// calculator.cpp
// Michael Glushchenko, 9403890.

#include "calculator.hpp"
#include <iostream>
#include <stack>

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

// helper function for when a number is encountered.
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

int Scanner::lineNumber() { return this->line; }

int Scanner::getNumberValue() { return this->value; }

//---------------------------------------------
// Parser implementation
//---------------------------------------------

Parser::Parser(bool eval) : evaluate(eval) { }

void Parser::parse() {
    start(); 
    if (this->evaluate) { this->polishPostfixEvaluation(this->polishPostfixNotation); }
}

void Parser::start() { expressionA(); expressionList(); }

void Parser::expressionList() {
    switch (scanner.nextToken()) {
        case T_SEMICOLON: scanner.eatToken(T_SEMICOLON);
                        if (this->evaluate) { this->polishPostfixNotation.push_back(";"); }
                        expressionA();
                        expressionList();
                        break;
        default: break; // epsilon transition, do nothing.
    }
}

void Parser::expressionA() { termA(); expressionB(); }

void Parser::expressionB() {
    switch (scanner.nextToken()) { 
        case T_PLUS: scanner.eatToken(T_PLUS); termA();
                    if (this->evaluate) { this->polishPostfixNotation.push_back("+"); }
                    expressionB();
                    break;
        case T_MINUS: scanner.eatToken(T_MINUS); termA();
                    if (this->evaluate) { this->polishPostfixNotation.push_back("-"); }
                    expressionB();
                    break;
        default: break; // epsilon transition, do nothing.
    }
}

void Parser::termA() { factor(); termB(); }

void Parser::termB() {
    switch (scanner.nextToken()) {
        case T_MULTIPLY: scanner.eatToken(T_MULTIPLY); factor();
                        if (this->evaluate) { this->polishPostfixNotation.push_back("*"); }
                        termB();
                        break;
        case T_DIVIDE: scanner.eatToken(T_DIVIDE); factor();
                        if (this->evaluate) { this->polishPostfixNotation.push_back("/"); }
                        termB();
                        break;
        case T_MODULO: scanner.eatToken(T_MODULO); factor();
                        if (this->evaluate) { this->polishPostfixNotation.push_back("mod"); }
                        termB();
                        break;
        default: break; // epsilon transition, do nothing.
    }
}

void Parser::factor() {
    switch (scanner.nextToken()) {
        case T_NUMBER: scanner.eatToken(T_NUMBER);
                        if (this->evaluate) { this->polishPostfixNotation.push_back(std::to_string(scanner.getNumberValue())); }
                        break;
        case T_OPENPAREN: scanner.eatToken(T_OPENPAREN); expressionA(); scanner.eatToken(T_CLOSEPAREN); break;
        default: parseError(scanner.lineNumber(), scanner.nextToken());
    }
}

void Parser::polishPostfixEvaluation(std::vector<std::string> toBeEvaluated) {
    std::stack<std::string> my_stack;
    std::string res;
    std::string temp_str;
    long result;
    int temp_line_num = 1; // so that errors throw the correct line number in this function.

    for (int i = 0; i < toBeEvaluated.size(); i++) {
        temp_str = toBeEvaluated[i];

        if (temp_str == ";") {
            res += my_stack.top() + "\n";
            my_stack.pop();
            temp_line_num++;
        }
        else if (temp_str == "+" || temp_str == "-" || temp_str == "*" || temp_str == "/" ||  temp_str == "mod") {
            long temp2 = std::stoi(my_stack.top());
            my_stack.pop();
            long temp1 = std::stoi(my_stack.top());
            my_stack.pop();
            if (temp_str == "+") {
                if (INT_MAX - temp2 <= temp1) { outOfBoundsError(temp_line_num, temp1 + temp2); }
                else { result = temp1 + temp2; }
            }
            else if (temp_str == "*") {
                if (INT_MAX < temp1 * temp2) { outOfBoundsError(temp_line_num, temp1 * temp2); }
                else { result = temp1 * temp2; }
            }
            else if (temp_str == "/") {
                if (temp2 == 0) { divideByZeroError(temp_line_num, temp1); }
                else { result = temp1 / temp2; }
            }
            else if (temp_str == "-") { result = temp1 - temp2; }
            else if (temp_str == "mod") { result = temp1 % temp2; }
            my_stack.push(std::to_string(result));
        }
        else { my_stack.push(temp_str); }
    }
    if (!my_stack.empty()) { res += my_stack.top(); my_stack.pop(); }
    std::cout << res << "\n";
}