#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include "TokenCodes.h"

using namespace std;

class Token
{
private:
    string lexemeString; //to store actual string representation of token
    TokenCodes tokenCode; //to store the type of token

public:
    Token();
    Token(TokenCodes, string);
    string getLexemeString();
    void setLexemeString(string);
    TokenCodes getTokenCode();
    void setTokenCode(TokenCodes);
    friend ostream& operator<<(ostream& os, const Token& t);
};

#endif