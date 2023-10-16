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

Token* LexicalAnalyzer::getNextToken()
{
    Token *t;



    return t;
}
