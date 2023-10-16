#include <iostream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

//constructor
LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
    currentChar = '\n';
    currentCharIndex = 0;
    sourceCodeFile = scf;
    line = "\n";
}

//checks if reached the end of the source code file
bool LexicalAnalyzer::isEOI()
{
    return (sourceCodeFile->eof() && (currentCharIndex == (line.length() - 1)));
}

void LexicalAnalyzer::readNextLine()
{
    getline(*sourceCodeFile, line);
    line = line + "\n";
}

void LexicalAnalyzer::getNextChar()
{
    if (currentCharIndex == (line.length() - 1))
    {
        readNextLine();
        currentCharIndex = -1;
    }

    currentCharIndex++;
    currentChar = line.at(currentCharIndex);
}

bool LexicalAnalyzer::isWhiteSpace() {
    return (currentChar == ' ' || currentChar == '\t' || currentChar == '\n');
}

void LexicalAnalyzer::skipWhiteSpace() {
    while(!isEOI() && isWhiteSpace()){
        getNextChar();
    }
}

Token* LexicalAnalyzer::getArithmeticOrParenToken() {
    switch (currentChar) {
        case '+':
            getNextChar();
            return new Token(PLUS, "+");
        case '-':
            getNextChar();
            return new Token(MINUS, "-");
        case '*':
            getNextChar();
            return new Token(TIMES, "*");
        case '/':
            getNextChar();
            return new Token(SLASH, "/");
        case '%':
            getNextChar();
            return new Token(MOD, "%");
        case '(':
            getNextChar();
            return new Token(LPAREN, "(");
        case ')':
            getNextChar();
            return new Token(RPAREN, ")");
        default:
            return nullptr;
    }
}

Token* LexicalAnalyzer::getNextToken()
{
    Token *t;

    skipWhiteSpace();

    if(isEOI()) {
        t = new Token(EOI, "EOI");
        return t;
    }

    t = getArithmeticOrParenToken();
    if(t != nullptr){
        return t;
    }

    return t;
}
