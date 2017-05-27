/*
 * File: statement.cpp
 * -------------------
 *
 * Name:  Ron Guglielmone
 *
 * This file implements the constructor and destructor for
 * the Statement class itself.
 *
 * Probably some bugs in here...
 */

#include <string>
#include "statement.h"
#include "exp.h"
#include "parser.h"
#include "evalstate.h"
#include "simpio.h"
#include "strlib.h"
#include "evalstate.h"
#include "program.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}



/*
 * RemStmt
 */

RemStmt::RemStmt(TokenScanner & scanner) {
    while (scanner.hasMoreTokens()) {
        remark = " " + scanner.nextToken();
    }
}

RemStmt::~RemStmt() {
   remark = "";
}

void RemStmt::execute(EvalState & state) {
    cout << remark << endl;
}



/*
 * LetStmt
 */

LetStmt::LetStmt(TokenScanner & scanner) {
    identifierName = scanner.nextToken();
    if (scanner.nextToken() == "=") {
        exp = readE(scanner, 0);
    }
    else {
        error ("LET statement syntax violated.");
    }
}

LetStmt::~LetStmt() {
   delete exp;
   identifierName = "";
   value = -1;
}

void LetStmt::execute(EvalState & state) {
    value = exp->eval(state);
    state.setValue(identifierName, value);
}



/*
 * PrintStmt
 */

PrintStmt::PrintStmt(TokenScanner & scanner) {
   exp = readE(scanner, 0);
   if (scanner.hasMoreTokens()) {
       error("Extraneous token " + scanner.nextToken());
   }
}

PrintStmt::~PrintStmt() {
   delete exp;
}

void PrintStmt::execute(EvalState & state) {
    cout << exp->eval(state) << endl;
}



/*
 * InputStmt
 */

InputStmt::InputStmt(TokenScanner & scanner) {
  identifierName = scanner.nextToken();
}

InputStmt::~InputStmt() {
   identifierName = "";
}

void InputStmt::execute(EvalState & state) {
    value = getInteger("?");
    state.setValue(identifierName, value);
}



/*
 * GotoStmt
 */

GotoStmt::GotoStmt(TokenScanner & scanner) {
  lineNumber = stringToInteger(scanner.nextToken());
  if (scanner.hasMoreTokens()) {
      error ("Too many line numbers.  Only one, please.");
  }
}

GotoStmt::~GotoStmt() {
   lineNumber = -1;
}

void GotoStmt::execute(EvalState & state) {
    state.setCurrentLine(lineNumber);
}



/*
 * IfStmt
 */

IfStmt::IfStmt(TokenScanner & scanner) {
    //Initialize markers:
    leftTermIsNumber = false;
    rightTermIsNumber = false;

  //Read first term:
  leftToken = scanner.nextToken();
  if (stringIsInteger(leftToken)) {
      num1 = stringToInteger(leftToken);
      leftTermIsNumber = true;
  }

  //Read operator term:
  op = scanner.nextToken();

  //Read third term:
  rightToken = scanner.nextToken();
  if (stringIsInteger(rightToken)) {
      num2 = stringToInteger(rightToken);
      rightTermIsNumber = true;
  }

  //Grab "THEN"
  string then = scanner.nextToken();
  if (then != "THEN") {
      error ("Syntax error: expected THEN.");
  }

  //Read GOTO line number
  lineNumber = stringToInteger(scanner.nextToken());
}

IfStmt::~IfStmt() {
}

void IfStmt::execute(EvalState & state) {
    //Get left term's int value:
    if (!leftTermIsNumber) {
        if (state.isDefined(leftToken)) {
            num1 = state.getValue(leftToken);
        }
        else error ("Symbol not defined.  Left term.");
    }

    //Get right term's int value:
    if (!rightTermIsNumber) {
        if (state.isDefined(rightToken)) {
            num2 = state.getValue(rightToken);
        }
        else error ("Symbol not defined.  Right term.");
    }

    //Evaluate:
    if (op == "=") {
        if (num1 == num2) {
            state.setCurrentLine(lineNumber);
        }
    }
    if (op == "<") {
        if (num1 < num2) {
            state.setCurrentLine(lineNumber);
        }
    }
    if (op == ">") {
        if (num1 > num2) {
            state.setCurrentLine(lineNumber);
        }
    }
    if (op == "!=") {
        if (num1 != num2) {
            state.setCurrentLine(lineNumber);
        }
    }

}


/*
 * EndStmt
 */

EndStmt::EndStmt(TokenScanner & scanner) {
  //Fill in:  Nothing to do?
}

EndStmt::~EndStmt() {
   //Fill in:  Nothing to do?
}

void EndStmt::execute(EvalState & state) {
    state.setCurrentLine(-1);
}


