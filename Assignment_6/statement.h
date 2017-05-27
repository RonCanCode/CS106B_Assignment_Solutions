/*
 * File: statement.h
 * -----------------
 *
 * Name:  Ron Guglielmone
 * Section:  Marielos Sanson
 *
 * This file defines the Statement abstract type.  
 * There are subclasses for each of the seven types.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "tokenscanner.h"
#include "strlib.h"
#include "parser.h"
#include "string.h"
#include "exp.h"
#include "functional"


/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

    /*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();

    /*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

    /*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvalState & state) = 0;

};



/*
 * Sub-Class: RemStmt
 * ------------------
 * Use:  REM string
 *
 * This subclass represents a remark statement.
 * Remarks are used for comments.  Any text on
 * the line after keyword REM is ignored.
 */

class RemStmt: public Statement {

public:

    RemStmt(TokenScanner & scanner);
    virtual ~RemStmt();
    virtual void execute(EvalState & state);

private:

    std::string remark;

};



/*
 * Sub-Class: LetStmt
 * ------------------
 * Use: LET var = value
 *
 * This subclass represents a let statement.
 * The LET keyword is followed by a variable
 * name, an equal sign, and an expression.  The
 * effect is to assign the value of the expression
 * to the variable in the symbol table.
 */

class LetStmt: public Statement {

public:

    LetStmt(TokenScanner & scanner);
    virtual ~LetStmt();
    virtual void execute(EvalState & state);

private:

    std::string identifierName;
    Expression *exp;
    int value;

};



/*
 * Sub-Class: PrintStmt
 * ------------------
 * Use:  PRINT exp
 *
 * This subclass represents a print statement.
 * The effect is to print an expression on its
 * own line, then start a new line.
 */

class PrintStmt: public Statement {

public:

    PrintStmt(TokenScanner & scanner);
    virtual ~PrintStmt();
    virtual void execute(EvalState & state);

private:

    Expression *exp;

};



/*
 * Sub-Class: InputStmt
 * ------------------
 * Use: INPUT var
 *
 * This subclass represents an input statement.
 * The effect is to print a prompt "?" and then
 * read in a value to be stored as a variable.
 */

class InputStmt: public Statement {

public:

    InputStmt(TokenScanner & scanner);
    virtual ~InputStmt();
    virtual void execute(EvalState & state);

private:

    std::string identifierName;
    int value;

};



/*
 * Sub-Class: GotoStmt
 * ------------------
 * Use: GOTO n
 *
 * This subclass represents a goto statement.
 * Goto forces unconditional change in the flow
 * of the program.  Reports an error is line n
 * doesn't exist.
 */

class GotoStmt: public Statement {

public:

    GotoStmt(TokenScanner & scanner);
    virtual ~GotoStmt();
    virtual void execute(EvalState & state);

private:

    int lineNumber;

};



/*
 * Sub-Class: IfStmt
 * ------------------
 * Use: IF exp1 op exp2 THEN n
 *
 * This subclass represents an if statement.
 * If the condition holds, the program should
 * continue from line n just as in GOTO.  If not,
 * the program advances to the next line.
 */

class IfStmt: public Statement {

public:

    IfStmt(TokenScanner & scanner);
    virtual ~IfStmt();
    virtual void execute(EvalState & state);

private:

    //Inputs:
    std::string leftToken;
    std::string op;
    std::string rightToken;

    //Terms:
    int num1;
    int num2;

    //GoTo number:
    int lineNumber;

    //Markers:
    bool leftTermIsNumber;
    bool rightTermIsNumber;

};


/*
 * Sub-Class: EndStmt
 * ------------------
 * This subclass represents an end statement.
 * END marks the end of the program, halting
 * execution.
 */

class EndStmt: public Statement {

public:

    EndStmt(TokenScanner & scanner);
    virtual ~EndStmt();
    virtual void execute(EvalState & state);

private:

    //Not sure what to do for this...

};



#endif
