/*
 * File: Basic.cpp
 * ---------------
 * Name: Ron Guglielmone
 *
 * Accomplished tasks:
 *      -Implemented statement.cpp.
 *      -Wrote basic.cpp to accept inputs and store them.
 *      -Wrote basic.cpp to execute LIST and CLEAR.
 *      -Added get and set current line to EvalState.
 *      -Implemented the Statement class and sub-classes.
 *      -Added parseStatement to the parse.h class.
 *      -Wrote HELP, LET, PRINT, RUN in basic.cpp.
 *      -Lots of other things I'm forgetting.
 *
 * Still need to do:
 *      -Remove = in parser.
 *      -Remove = in expression.
 *      -DeBug...
 */

#include <cctype>
#include <iostream>
#include <string>
#include "console.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   cout << "C++ implementation of BASIC:" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}



/* Function: processLine
*
* Reads a line from the user and identifies what type of command it
* begins with.
*
*/
void processLine(string line, Program & program, EvalState & state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string token = scanner.nextToken();

    //Statement beggining w/ int:
    if (stringIsInteger(token)) {
        int lineNumber = stringToInteger(token);
        string sourceLine = "";
        while (scanner.hasMoreTokens()) {
            sourceLine += scanner.nextToken();
            sourceLine += " ";
        }
        program.addSourceLine(lineNumber, sourceLine);
    }

    //RUN command:
    if (token == "RUN") {
        int workingLine = program.getFirstLineNumber();
        while (workingLine != -1) {
            string sourceLine = program.getSourceLine(workingLine);
            scanner.setInput(sourceLine);
            parseStatement(scanner);
            workingLine = program.getNextLineNumber(workingLine);
        }
    }

    //PRINT command:
    if (token == "PRINT") {
        new PrintStmt(scanner);
    }

    //LET command:
    if (token == "LET") {
        new LetStmt(scanner);
    }

    //INPUT command:
    if (token == "INPUT") {
        new InputStmt(scanner);
    }

    //LIST command:
    int workingLineNumber = program.getFirstLineNumber();
    if (token == "LIST") {
        while (workingLineNumber != -1) {
            string line = program.getSourceLine(workingLineNumber);
            cout << workingLineNumber << " " << line << endl;
            workingLineNumber = program.getNextLineNumber(workingLineNumber);
        }
    }

    //CLEAR command:
    if (token == "CLEAR") {
        program.clear();
    }

    //HELP command:
    if (token == "HELP") {
        cout << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "----------------------HELP SCREEN--------------------" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "BASIC is written in terms of Statements and Commands." << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "Commands:" << endl;
        cout << endl;
        cout << "RUN:    begins program execution." << endl;
        cout << "LIST:   lists all of the lines in the current program." << endl;
        cout << "CLEAR:  deletes all lines from the current program." << endl;
        cout << "HELP:   you already know what this does..." << endl;
        cout << "QUIT:   exits from the BASIC interpreter." << endl;
        cout << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "Statements:" << endl;
        cout << endl;
        cout << "REM: used to make comments." << endl;
        cout << "LET: used to make variable assignments." << endl;
        cout << "PRINT: used to print an expression." << endl;
        cout << "INPUT: used to store a user-specified value." << endl;
        cout << "GOTO: moves program execution to the specified line." << endl;
        cout << "IF: created a conditional statement.  IF exp1 op exp 2 THEN n." << endl;
        cout << "END: terminated program execution." << endl;
        cout << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << endl;
    }


    //QUIT command:
    if (token == "QUIT") {
        exit(0);
    }
}
