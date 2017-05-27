/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: Ron Guglielmone
 *
 * This program takes in an initial source text
 * and statistically analises it.  The text is
 * divided into "x" pieces of size "n", and the likelihood
 * of any particular letter following piece "x" is stored
 * implicity in a vector of such characters.  Then, a string
 * of random writing is generated from this data set.
 */

#include "simpio.h"
#include "random.h"
#include "vector.h"
#include <string>
#include "string.h"
#include "map.h"
#include "filelib.h"
#include <iostream>
#include <fstream>
#include "console.h"
using namespace std;

/* Prototypes: */
string readFileFromUser ();
int requestN ();
void fillTheDatabase (string & fileInput, int nLevel, Map<string, Vector<char> > & mainDatabase);
void readTheDatabase (int nLevel, Map<string, Vector<char> > & mainDatabase);
string findTheSeed (Map<string, Vector<char> > & mainDatabase);
void testPrint (Map<string, Vector<char> > & mainDatabase);

/* Constants: */
int LENGTH_OF_OUTPUT = 2000;

int main() {

    while (true) {
        cout << "|'''''''''''''''''''''''''''''''''''''|" << endl;
        cout << "|::::::::::::PROGRAM START::::::::::::|" << endl;
        cout << "|_____________________________________|" << endl;
        cout << " " << endl;

        //Accept input from the user:
        string fileInput = readFileFromUser ();
        int nLevel = requestN ();
        Map<string, Vector<char> > mainDatabase;
        cout << " " << endl;

        cout << "|'''''''''''''''''''''''''''''''''''''|" << endl;
        cout << "|:::::::::::::RANDOM TEXT:::::::::::::|" << endl;
        cout << "|_____________________________________|" << endl;
        cout << " " << endl;

        //Store the textfile in a Map:
        fillTheDatabase (fileInput, nLevel, mainDatabase);
        //Generate and print random text:
        readTheDatabase (nLevel, mainDatabase);

        cout << " " << endl;

    }
    return 0;
}

/* readFileFromUser
 * Usage: returns a string
 *
 * Reads a file character by character and stores it
 * into a string.
 */
string readFileFromUser () {
    ifstream infile;
    promptUserForFile (infile, "Input text file: ");
    int ch;
    string fileString;
    while ((ch = infile.get()) != EOF) {
        fileString += ch;
    }
    infile.close();
    return fileString;
}

/* requestN
 * Usage: returns an int
 *
 * Prompts the user for an integer.
 */
int requestN () {
    while (true) {
        int n = getInteger("Perform analysis to what degree (n): ");
        if (n > 0 && n < 11) {
            return n;
        }
        else cout << "Value (n) must be between 1 and 10." << endl;
    }
}

/* fillTheDatabade
 * Usage: populates mainDatabase
 *
 * Takes the file contents by refrence, adds substrings of nLevel
 * length to the mainDatabase, populates each substring key with
 * a vector of possible characters that can follow it.
 */
void fillTheDatabase (string & fileInput, int nLevel, Map<string, Vector<char> > & mainDatabase) {
    for (int i = 0; i < fileInput.length() - nLevel - 1; i++) {
        string str = fileInput.substr(i, nLevel);
        char nextLetter = fileInput[i + nLevel];
        Vector<char> workingVector;
        if (mainDatabase.containsKey(str)) {
            workingVector = mainDatabase.get(str);
        }
        workingVector.add(nextLetter);
        mainDatabase.put(str, workingVector);
    }
}

/* readTheDatabase
 * Usage: iterates through the mainDatabase
 *
 * Iterates through the mainDatabase and prints out
 * the random text, picking each next character by
 * random chance from the vector of possibilities.
 */
void readTheDatabase (int nLevel, Map<string, Vector<char> > & mainDatabase) {
    string theSeed = findTheSeed(mainDatabase);
    string finalRandomText = theSeed;
    Vector<char> temporaryVector = mainDatabase.get(theSeed);

    while (finalRandomText.length() < LENGTH_OF_OUTPUT && !temporaryVector.isEmpty()) {
        int vectorSize = temporaryVector.size();
        int i = randomInteger(0, vectorSize - 1);
        char nextCharacter = temporaryVector[i];
        finalRandomText += nextCharacter;
        theSeed = theSeed.substr(1);
        theSeed += nextCharacter;
        temporaryVector = mainDatabase.get(theSeed);
    }
    cout << finalRandomText << endl;
}

/* findTheSeed
 *
 * Returns the string name of the most used seed.
 */
string findTheSeed (Map<string, Vector<char> > & mainDatabase) {

    int longestVectorSize = 0;
    string longestVectorName = "RandomGenerationHasFailed";

    for (string key : mainDatabase) {
        Vector<char> workingVector = mainDatabase.get(key);
        int counter = workingVector.size();
        if (counter > longestVectorSize) {
            longestVectorSize = counter;
            longestVectorName = key;
        }
    }
    return longestVectorName;
}

/* Function: testPrint
 *
 * Apparently, one can just print ADTs, but I didn't know
 * this, so I wrote a function for debugging...  This is
 * not used in the actual run of the program.
 */
void testPrint (Map<string, Vector<char> > & mainDatabase) {
    cout << ":::::::::All Keys in Data Set:::::::::" << endl;
    for (string key : mainDatabase) {
        cout << key << endl;
    }

    string seedKey = findTheSeed (mainDatabase);
    cout << ":::::::::Seed:::::::::" << endl;
    cout << seedKey << endl;

    cout << ":::::::::All Entries in seedKey:::::::::" << endl;
    Vector<char> testVector = mainDatabase.get(seedKey);
    for (char entry : testVector) {
        cout << entry << endl;
    }

}
