/*
 * File: Combinations.cpp
 * ----------------------
 * Name: Ron Guglielmone
 * Section: Marielos Sanson
 * This program reads in two values from the user for use
 * in a Pascal's Trangle Combinations Function.  The value
 * at position C(n,k) is calculated recursively.
 *
 * -Sometimes this is "unexpectedly crashing"?
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Prototypes: */
int pascalFunction (int row, int col);

int main() {
    cout << "----------------------------------------------------------------" << endl;
    cout << "This program calculates the combinations function," << endl;
    cout << "returning a value in Pascal's Trangle as defined by c (row,col)." << endl;
    cout << "----------------------------------------------------------------" << endl;

    while (true) {
        int row = getInteger ("Enter row:");
        int col = getInteger ("Enter col:");
        cout << "The value is: " << pascalFunction(row,col) << endl;
    }

    return 0;
}

/* Function: pascalFunction (int row, int col)
 *
 * This is a recursive loop for calculating the value.
 */
int pascalFunction (int row, int col) {
    if (col == 0) return 1;
    if (row == col) return 1;
    else return (pascalFunction(row - 1, col - 1)) + (pascalFunction(row - 1, col));
}
