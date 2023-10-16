#include <fstream>
#include <iostream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream *sourceCodeFile; //Pointer to an ifstream (input file stream) object that will be used to read from a file.
    LexicalAnalyzer *la; //Pointer to a LexicalAnalyzer object.
    Token *nextToken; //Pointer to a Token object.
    TokenCodes tc; //Variable of type TokenCodes
    sourceCodeFile = new ifstream();
    //tries to open file passed in as argument
    sourceCodeFile->open(argv[1], ifstream::in);
    if  (sourceCodeFile->is_open())
    {
        //create new LexicalAnalyzer object and pass in the opened file
        la = new LexicalAnalyzer(sourceCodeFile);
        //enter loop to retrieve the next token from lexical analyzer until token has EOI code
        //each token is printed, then deleted
        do
        {
            nextToken = la->getNextToken();
            cout << *nextToken << endl;
            tc = nextToken->getTokenCode();
            delete nextToken;
        } while (tc != EOI);
        //after processing, the lexical analyzer is deleted and the file is closed
        delete la;
        sourceCodeFile->close();
    }
    else
        cout << "ERROR - cannot open input file." << endl;

    return 0;
}
