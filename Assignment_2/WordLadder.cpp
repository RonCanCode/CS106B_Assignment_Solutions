/*
 * File: WordLadder.cpp
 * --------------------
 * Name: Ron Guglielmone
 *
 * This program creates word ladders from a start and end
 * word entered by the user.  If no word ladder exists,
 * the user is told so.
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include "filelib.h"
#include "strlib.h"

using namespace std;

/* Prototypes: */
void generateWordLadder(Lexicon & wordDictionary, string firstWord, string lastWord);
void makeNextWord (string oldWord, Lexicon & wordDictionary, Lexicon & usedWords, Vector<string> & workingLadder, Queue<Vector <string> > &ladderStorage);
void printTheResult (Vector<string>  printThisLadder);
void populateTheADTs (Queue<Vector<string> > &ladderStorage, Lexicon &usedWords, Vector<string> &workingLadder, string &firstWord);

/* Globals: */
bool resultWasPrinted = false;

int main() {

    Lexicon wordDictionary("EnglishWords.txt");

    while (true) {
        string firstWord = toLowerCase(getLine("Enter a starting word:"));
        string lastWord = toLowerCase(getLine("Enter an ending word:"));
        generateWordLadder(wordDictionary, firstWord, lastWord);
        resultWasPrinted = false;
    }
    return 0;
}

/* Function: generateWordLadder
 *
 * This is the main wrapper for creating a word ladder.
 * A Queue of string Vectors holds each ladder as
 * it progresses in length.  New words are added to the
 * end by a call to the makeNextWord function.  When
 * the last word in a ladder is the same as the targeted
 * finish word, the vector is printed.
 */
void generateWordLadder(Lexicon & wordDictionary, string firstWord, string lastWord) {
    //Build the initial data structures:
    Queue<Vector <string> > ladderStorage;
    Lexicon usedWords;
    Vector<string> workingLadder;
    //Populate the initial data structures:
    populateTheADTs (ladderStorage, usedWords, workingLadder, firstWord);
    //MAIN LOOP:
    while (!ladderStorage.isEmpty()) {
        //Remove the last word from the last ladder in the quque.
        Vector<string> testLadder = ladderStorage.dequeue();
        string testWord = testLadder[testLadder.size() - 1];
        //If found, print a successful ladder.
        if (testWord == lastWord) {
            printTheResult (testLadder);
            resultWasPrinted = true;
            break;
        } else {
            makeNextWord (testWord, wordDictionary, usedWords, testLadder, ladderStorage);
        }
    }
    //Inform the user if there are no ladders.
    if (!resultWasPrinted) {
        cout << "------------------------------------" << endl;
        cout << "There is no ladder." << endl;
        cout << "------------------------------------" << endl;
    }
}


/* Function: makeNextWord
 *
 * Takes in a word, checks for new words with one altered character, and adds them to the ladder.
 */
void makeNextWord (string oldWord, Lexicon & wordDictionary, Lexicon & usedWords, Vector<string> & workingLadder, Queue<Vector <string> > &ladderStorage) {
    string possibleWord;
    for (int i = 0; i < oldWord.length(); i++) {
        for (char ch = 'a'; ch <= 'z'; ch++) {
            string testWord = oldWord;
            testWord[i] = ch;
            if (wordDictionary.contains(testWord) && !usedWords.contains(testWord)) {
                possibleWord = testWord;
                usedWords.add(possibleWord);
                Vector<string> copyOfWorkingLadder = workingLadder;
                copyOfWorkingLadder.add(possibleWord);
                ladderStorage.add(copyOfWorkingLadder);
            }
        }
    }
}


/* Function: populateTheADTs
 *
 * Fills the data structures with initial starting values.
 */
void populateTheADTs (Queue<Vector <string> > &ladderStorage, Lexicon &usedWords, Vector<string> &workingLadder, string &firstWord) {
    ladderStorage.clear();
    usedWords.clear();
    workingLadder.clear();
    workingLadder.add(firstWord);
    usedWords.add(firstWord);
    ladderStorage.enqueue(workingLadder);
}

/* Function: printTheResult
 *
 * Prints a word ladder to the console.
 */
void printTheResult (Vector<string> ladderToPrint) {
    cout << "------------------------------------" << endl;
    cout << "A possible word ladder is:" << endl;
    for (int i = 0; i < ladderToPrint.size(); i++) {
        string individualWord = ladderToPrint[i];
        cout << individualWord << " ";
    }
    cout << endl << "------------------------------------" << endl;
}
