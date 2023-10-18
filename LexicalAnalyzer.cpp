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
    reservedWords["bool"] = BOOLSYM;
    reservedWords["do"] = DOSYM;
    reservedWords["else"] = ELSESYM;
    reservedWords["false"] = FALSESYM;
    reservedWords["float"] = FLOATSYM;
    reservedWords["for"] = FORSYM;
    reservedWords["if"] = IFSYM;
    reservedWords["int"] = INTSYM;
    reservedWords["printf"] = PRINTFSYM;
    reservedWords["return"] = RETURNSYM;
    reservedWords["scanf"] = SCANFSYM;
    reservedWords["true"] = TRUESYM;
    reservedWords["void"] = VOIDSYM;
    reservedWords["while"] = WHILESYM;
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
//    cout << "Current char: " << currentChar << endl;

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
        case '{':
            getNextChar();
            return new Token(LBRACE, "{");
        case '}':
            getNextChar();
            return new Token(RBRACE, "}");
        case ',':
            getNextChar();
            return new Token(COMMA, ",");
        case ';':
            getNextChar();
            return new Token(SEMICOLON, ";");
        case '=':
            getNextChar();
            return new Token(ASSIGN, "=");
        case '!':
            getNextChar();
            return new Token(NOT, "!");
        case '<':
            getNextChar();
            return new Token(LSS, "<");
        case '>':
            getNextChar();
            return new Token(GTR, ">");
        default:
            return nullptr;
    }
}

bool LexicalAnalyzer::isLetter() {
    return ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'));
}

bool LexicalAnalyzer::isDigit() {
    return (currentChar >= '0' && currentChar <= '9');
}

Token* LexicalAnalyzer::getMultiCharSymbol() {
    char initialChar = currentChar;
    getNextChar();
    switch (initialChar) {
        case '|':
            if(currentChar == '|'){
                getNextChar();
                return new Token(OR, "||");
            }
            return nullptr;
        case '&':
            if(currentChar == '&'){
                getNextChar();
                return new Token(AND, "&&");
            }
            return nullptr;
        case '=':
            if(currentChar == '='){
                getNextChar();
                return new Token(EQL, "==");
            }
            return nullptr;
        case '!':
            if(currentChar == '='){
                getNextChar();
                return new Token(NEQ, "!=");
            }
            return nullptr;
        case '<':
            if(currentChar == '='){
                getNextChar();
                return new Token(LEQ, "<=");
            }
            return nullptr;
        case '>':
            if(currentChar == '='){
                getNextChar();
                return new Token(GEQ, ">=");
            }
            return nullptr;
    }

    currentChar = initialChar;
    currentCharIndex--;
    return nullptr;
}

Token* LexicalAnalyzer::getReservedWord() {
    string lexeme = "";

    while(!isEOI() && isLetter()){
        lexeme += currentChar;
        getNextChar();
    }

    if(reservedWords.find(lexeme) != reservedWords.end()) {
        return new Token(reservedWords[lexeme], lexeme);
    }

    return nullptr;
}

Token* LexicalAnalyzer::getIdentifier() {
    string lexeme = "";

    while(isLetter() || isDigit()) {
        lexeme += currentChar;
        getNextChar();
    }

    if(!lexeme.empty()){
        for(auto & c: lexeme) c = tolower(c);
        return new Token(IDENT, lexeme);
    }

    return nullptr;
}

Token* LexicalAnalyzer::getNumericLiteral() {
    string lexeme = "";
    bool sawPeriod = false;

    while(isDigit() || (currentChar == '.' && !sawPeriod)) {
        if(currentChar == '.'){
            sawPeriod = true;
        }
        lexeme += currentChar;
        getNextChar();
    }

    if(!lexeme.empty()){
        return new Token(NUMLIT, lexeme);
    }

    return nullptr;
}

Token* LexicalAnalyzer::getNextToken()
{
    Token *t;

    skipWhiteSpace();

    if(isEOI()) {
        t = new Token(EOI, "EOI");
        return t;
    }

    t = getNumericLiteral();
    if(t != nullptr){
        return t;
    }

    t = getIdentifier();
    if(t != nullptr) {
        return t;
    }

    t = getMultiCharSymbol();
    if(t != nullptr){
        return t;
    }

    t = getArithmeticOrParenToken();
    if(t != nullptr){
        return t;
    }

    t = getReservedWord();
    if(t != nullptr) {
        return t;
    }


    string lexeme(1, currentChar);
    getNextChar();
    return new Token(NAL, lexeme);

}
