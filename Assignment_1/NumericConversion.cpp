/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: Ron Guglielmone
 * Section: Marielos Sanson
 *
 * This program implements a conversion from type string to int
 * and from type int to string without using library calls or loops.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);
bool isADigitString (string str);

/* Main program */

int main() {
    cout << "------------------------------------------" << endl;
    cout << "This program converts a string to and int," << endl;
    cout << "and an int to a string..." << endl;
    cout << "------------------------------------------" << endl;

    /* Test Cases: */

    int a = 0;
    int b = 1;
    int c = 1234;
    int d = -1234;
    string e;
    string f = "0";
    string g = "1";
    string h = "1234";
    string k = "-1234";

    cout << intToString(a) << endl;
    cout << intToString(b) << endl;
    cout << intToString(c) << endl;
    cout << intToString(d) << endl;

    cout << stringToInt(e) << endl;
    cout << stringToInt(f) << endl;
    cout << stringToInt(g) << endl;
    cout << stringToInt(h) << endl;
    cout << stringToInt(k) << endl;

    return 0;
}

/* Function: intToString(int n)
 *
 * This functions converts an int to a string using recursion to
 * handle strings longer than one (or zero) character(s).
 */
string intToString(int n) {

    string str;

    if (n < 10 && n > 0) {
        char ch = n + '0';
        str = ch;
    }
    if (n == 0) {
        char ch = n + '0';
        str = ch;
    }
    if (n < 0) {
        str += "-" + intToString (n * -1);
    }
    if (n > 10) {
        char ch = n % 10 + '0';
        str = intToString (n / 10) + ch;
    }
    return str;
}

/* Function: stringToInt(string str)
 *
 * This function converts a string to an int, considering the
 * special cases of an empty string, a negative number, and using
 * recursion to handle multiple digit inputs.
 */
int stringToInt(string str) {

    int i = 0;

    if (str.empty()) {
        return i = 0;
    }

    if (str.length() == 1 && str[0] != '-') {
        i += (str[0] - '0');
        return i;
    }
    if (str.length() == 1 && str[0] == '-') {
        i += 0;
        return i;
    }
    if (str.length() > 1) {
        int j = str[str.length() - 1] - '0';
        i = (stringToInt(str.substr(0, str.length() - 1)) * 10) + j;
    }
    if (str.length() > 1 && str[0] == '-') {
        int j = str[str.length() - 1] - '0';
        i = (stringToInt(str.substr(0, str.length() - 1)) * 10) + j * -1;
    }
    return i;
}
