/*
 * File: parser.cpp
 * ----------------
 *
 * Name: Ron Guglielmone
 * Section: Marielos Sanson
 *
 * Implements the parser.h interface.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "exp.h"
#include "parser.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner & scanner) {
    Expression *exp = readE(scanner);
    if (scanner.hasMoreTokens()) {
        error("parseExp: Found extra token: " + scanner.nextToken());
    }
    return exp;
}

/*
 * Implementation notes: parseStatement
 * ------------------------------
 * Reads a statement of type:
 *
 * -RemStmt    REM
 * -LetStmt    LET
 * -PrintStmt  PRINT
 * -InputStmt  INPUT
 * -GotoStmt   GOTO
 * -IfStmt     IF
 * -EndStmt    END
 */

void parseStatement(TokenScanner & sourceLine) {
    //Initialize:
    string statement = sourceLine.nextToken();

    //Different cases:
    if (statement == "REM") {
        new RemStmt(sourceLine);
    }
    if (statement == "LET") {
        new LetStmt(sourceLine);
    }
    if (statement == "PRINT") {
        new PrintStmt(sourceLine);
    }
    if (statement == "INPUT") {
        new InputStmt(sourceLine);
    }
    if (statement == "GOTO") {
        new GotoStmt(sourceLine);
    }
    if (statement == "IF") {
        new IfStmt(sourceLine);
    }
    if (statement == "END") {
        new EndStmt(sourceLine);
    }
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner & scanner, int prec) {
    Expression *exp = readT(scanner);
    string token;
    while (true) {
        token = scanner.nextToken();
        int newPrec = precedence(token);
        if (newPrec <= prec) break;
        Expression *rhs = readE(scanner, newPrec);
        exp = new CompoundExp(token, exp, rhs);
    }
    scanner.saveToken(token);
    return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner) {
    string token = scanner.nextToken();
    TokenType type = scanner.getTokenType(token);
    if (type == WORD) return new IdentifierExp(token);
    if (type == NUMBER) return new ConstantExp(stringToInteger(token));
    if (token != "(") error("Illegal term in expression");
    Expression *exp = readE(scanner);
    if (scanner.nextToken() != ")") {
        error("Unbalanced parentheses in expression");
    }
    return exp;
}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */

int precedence(string token) {
    if (token == "=") return 1;
    if (token == "+" || token == "-") return 2;
    if (token == "*" || token == "/") return 3;
    return 0;
}
