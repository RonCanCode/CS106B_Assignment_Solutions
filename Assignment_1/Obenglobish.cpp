/*
 * File: Obenglobish.java
 * ----------------------
 * Name: Ron Guglielmone
 *
 * This file solves the Oblenglobish problem outlines in CS106b
 * Assignment #1, Winter Quarter, 2015 at Stanford Univertsity.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Prototypes: */
string obenglobish (string word);
bool isAVowell (char ch);

/* Main program */

int main () {
    while (true) {
        string word = getLine("Enter a word: ");
        if (word == "") break;
        string trans = obenglobish (word);
        cout << word << " -> " << trans << endl;
    }
    return 0;
}

/* Function: string obenglobish (string word)
 *
 * Takes and returns a string, adding "ob" before any vowel
 * which does not follow another vowel, and which is not the
 * terminating character of a word.
 *
 */
string obenglobish (string word) {
    bool wasLastCharVowell;
    string newString;
    for (int i = 0; i < word.length(); i++) {
        if (isAVowell (word[i]) &&
            !wasLastCharVowell &&
            (i != word.length() - 1 &&
            (i != 'e' || 'E'))) {
               newString += "ob" + word.substr(i, 1);
               wasLastCharVowell = true;
        } else {
            newString += word.substr(i, 1);
            if (isAVowell(word[i])) {
                wasLastCharVowell = true;
            } else {
                wasLastCharVowell = false;
            }
        }
    }
    return newString;
}

/* Function: bool isAVowell (char ch)
 *
 * Checks to see is a character is a vowell.
 */
bool isAVowell (char ch) {
    switch (ch) {
    case 'a' : case 'e' : case 'i' : case 'o' : case 'u' :
    case 'A' : case 'E' : case 'I' : case 'O' : case 'U' :
        return true;
    default :
        return false;
    }
}
