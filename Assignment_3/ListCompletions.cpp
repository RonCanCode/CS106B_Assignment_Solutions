/*
 * File: ListCompletions.cpp
 * -------------------------
 * Name: Ron Guglielmone
 *
 * Lists all the words in the lexicon that begin with the letters
 * corresponding to the specified digits on a telephone keypad.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "vector.h"
using namespace std;

/* Globals: */
string ENGLISH_LETTERS = "abcdefghijklmnopqrstuvwxyz";

/* Function prototypes */
void listCompletions (string digits, Lexicon & lexicon);
Set<string> generatePermutations (string str);
string lettersFromDigits (char ch);
Set<string> completeTheWords (string workingWord, Lexicon & englishWords);
void printFinalList (Set<string> & allPossibleWords);

/* Main program */

int main() {
    Lexicon english ("EnglishWords.dat");
    cout << "Cell phone mind-reading problem" << endl;
    while (true) {
        cout << "Enter a set of digits: ";
        string digits = getLine();
        if (digits == "" || digits == "quit") break;
        cout << "The words beginning with those digits are:" << endl;
        listCompletions(digits, english);
    }
    return 0;
}

/*
 * Function: listCompletions
 * Usage: listCompletions(digits, lexicon);
 * ----------------------------------------
 * Lists all the words in the lexicon that begin with the letters
 * corresponding to the specified digits on a telephone keypad.
 */

void listCompletions(string digits, Lexicon & lexicon) {
    //Contains strings of all the letters associated with each digit:
    Set<string> convertedDigits;
    for (int i = 0; i < digits.length(); i++) {
        convertedDigits.add(lettersFromDigits(digits[i]));
    }
    //Contains all the permutations of each convertedDigit string:
    Set<string> allPermutations;
    for (string str : convertedDigits) {
        allPermutations += generatePermutations(str);
    }
    //Contains all the possible words:
    Set<string> allPossibleWords;
    for (string str : allPermutations) {
        allPossibleWords += completeTheWords (str, lexicon);
    }
    printFinalList (allPossibleWords);
}

/* Function: generatePermutations (string str)
 *
 * From Eric Robert's C++ Course Reader, Chapter 8.
 */
Set<string> generatePermutations (string str) {
    Set<string> result;
    if (str == "") {
        result += "";
    }
    else {
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            string rest = str.substr (0,i) + str.substr (i + 1);
            for (string s : generatePermutations (rest)) {
                result += ch + s;
            }
        }
    }
    return result;
}

/* Function: lettersFromDigits (char ch)
 *
 * Converts a digit char into a string of associated letters.
 */
string lettersFromDigits (char x) {
    switch (x) {
    case '0': return ("0");
    case '1': return ("1");
    case '2': return ("abc");
    case '3': return ("def");
    case '4': return ("ghi");
    case '5': return ("jkl");
    case '6': return ("mno");
    case '7': return ("qprs");
    case '8': return ("tuv");
    case '9': return ("wxyz");
    default: error ("That's not a digit, bro...");
    }
    return "";
}

/* Function: completeTheWords (Set<string> & wordSet, string workingWord, Lexicon & englishWords)
 *
 * Itteratively adds letters to the end of a string, checking to see
 * if that word exists in the lexicon (base case).  If not, a recursive
 * call is made to explore the next possible letter addition.
 */
Set<string> completeTheWords (string workingWord, Lexicon & englishWords) {
    Set<string> result;
    //Base case:
    if (englishWords.contains(workingWord)) {
        result.add(workingWord);
    }
    //Recursive call if the prefix exists:
    for (int i = 0; i < ENGLISH_LETTERS.size(); i++) {
        string possibleWord = workingWord + ENGLISH_LETTERS[i];
        if (englishWords.containsPrefix(possibleWord)) {
            result += completeTheWords(possibleWord, englishWords);
        }
    }
    return result;
}

/* Function: printFinalList (Set<String> allPossibleWords
 *
 * Just prints the final word set.
 */
void printFinalList (Set<string> & allPossibleWords) {
    for (string str : allPossibleWords) {
        cout << str << endl;
    }
}
