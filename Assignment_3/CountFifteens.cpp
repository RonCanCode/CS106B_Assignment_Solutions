/*
 * File: CountFifteens.cpp
 * -----------------------
 * Name: Ron Guglielmone
 * Section: Marielos Sanson
 *
 * This program takes in a set of five cards
 * (as defined by the Cards class), and prints
 * out a count of all the possible ways such
 * cards can be combined to reach the TARGET_VALUE.
 */

#include <exception>
#include <iostream>
#include <string>
#include "card.h"
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "vector.h"
using namespace std;

/* Globals: */

int TARGET_VALUE = 15;

/* Function prototypes */

int countFifteens(Vector<Card> & cards);
Vector<int> buildCardVector (Vector<Card> & cards);
bool subsetSumExists (Vector<int> &cards, int target);
int countPossibilities (Vector<int> & cards, int target, int counter);

/*
 * Main program
 * ------------
 * This test program does no error-checking on the input.  One of the
 * extensions you might consider is adding code to this program (and
 * possibly to the Card class) to allow the program to report errors.
 */

int main() {
    while (true) {
        string line = getLine("Enter a hand of cards: ");
        if (line == "") break;
        TokenScanner scanner(line);
        scanner.ignoreWhitespace();
        Vector<Card> hand;
        while (scanner.hasMoreTokens()) {
            hand.add(Card(scanner.nextToken()));
        }
        int nWays = countFifteens(hand);
        if (nWays > 0) {
            string plural = (nWays == 1) ? "" : "s";
            cout << nWays << " way" << plural << endl;
        }
        else {
            cout << "There are no possible ways." << endl;
        }
    }
    return 0;
}

/*
 * Counts the number of ways of making a total of 15 from the vector of
 * cards.
 */
int countFifteens(Vector<Card> & cards) {
    Vector<int> cardIntegerValues = buildCardVector (cards);
    if (subsetSumExists(cardIntegerValues, TARGET_VALUE)) {
        int possibilities = countPossibilities(cardIntegerValues, TARGET_VALUE, 0);
        return possibilities;
    }
    else {
        return -1;
    }
}

/* Function: buildCardVector
 *
 * Creates a vector of ints corresponding to the values of
 * the input cards.
 */
Vector<int> buildCardVector (Vector<Card> &cards) {
    Vector<int> cardIntegerValues;
    for ( int i = 0; i < cards.size(); i++) {
        Card workingCard = cards[i];
        int workingInt = workingCard.getRank();
        cardIntegerValues.add(workingInt);
    }
    return cardIntegerValues;
}

/* bool subsetSumExists (Vector<int> cards, int target)
 *
 * Adapted from ch 8 of Eric Robert's C++ Course Reader.
 */
bool subsetSumExists (Vector<int> & cards, int target) {
    if (cards.isEmpty()) {
        return target == 0;
    }
    else {
        int element = cards[0];
        Vector<int> rest = cards;
        rest.remove(0);
        return subsetSumExists (rest, target)
                || subsetSumExists (rest, target - element);
    }
}

/* int countPossibilities (Vector<int> cards, int target, int counter)
 *
 * Adapted from Handout #33, May 4, 2009,
 * written by Eric Roberts at Stanford University.
 */
int countPossibilities (Vector<int> & cards, int target, int counter) {
    if (counter == cards.size()) {
        return (target == 0) ? 1 : 0;
    }
    if (target < 0) return 0;
    int currentRank = cards[counter];
    if (currentRank > 10) currentRank = 10;
    return countPossibilities (cards, target, counter + 1)
           + countPossibilities (cards, target - currentRank, counter + 1);
}
