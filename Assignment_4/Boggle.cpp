/*
 * File: Boggle.cpp
 * ----------------
 * Name: Ron Guglielmone
 *
 * This is a solution to Assignment #4, CS106B,
 * Stanford, Winter Qt, 2015.  Relying on gboggle.h,
 * this solution fills in the required details...
 *
 * I plan to add to this solution.  Specifically, I'd
 * like to write another recursive loop to handle the
 * user-input case (so that I can highlight input words).
 *
 * I also need to add a check to see if the square has
 * already been used.  In its current form, this solution
 * prints out too many words, because it allows already
 * used letters to be used again.
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "point.h"
#include "gobjects.h"
#include "grid.h"
#include "direction.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
//Each cube's letter set:
const string CUBE01 = "AAEEGN";
const string CUBE02 = "ABBJOO";
const string CUBE03 = "ACHOPS";
const string CUBE04 = "AFFKPS";
const string CUBE05 = "AOOTTW";
const string CUBE06 = "CIMOTU";
const string CUBE07 = "DEILRX";
const string CUBE08 = "DELRVY";
const string CUBE09 = "DISTTY";
const string CUBE10 = "EEGHNW";
const string CUBE11 = "EEINSU";
const string CUBE12 = "EHRTVW";
const string CUBE13 = "EIOSST";
const string CUBE14 = "ELRTTY";
const string CUBE15 = "HIMNQU";
const string CUBE16 = "HLNNRZ";
//All the letters combined:
const string STANDARD_LETTERS  =
        CUBE01 + CUBE02 + CUBE03 + CUBE04
        +CUBE05 + CUBE06 + CUBE07 + CUBE08
        +CUBE09 + CUBE10 + CUBE11 + CUBE12
        +CUBE13 + CUBE14 + CUBE15 + CUBE16;
//Total number of letters:
const int FULL_LETTER_COUNT = 96;
//Number of letters per cube (0 -> n-1):
const int BLOCK_LETTER_COUNT = 6 - 1;

/* Function prototypes */

//Input functions:
void acceptControlStatement(Grid<char> & currentCube);
void acceptWordsFromUser(Lexicon & english, Lexicon & allPossibleWords);
//Game processing functions:
void findAllPossibleWords(Lexicon & allPossibleWords, Lexicon & english,
                          Grid<char> & currentCube, Grid<int> & usedLetters);
void findAllPossibleWordsRec (Lexicon & allPossibleWords, Lexicon & english,
                              Grid<char> & currentCube, Grid<int> & usedLetters, string prefix, int x, int y);
//Data-structure functions:
void fillTheBoard(Grid<char> & currentCube, int width, int height);
void fillTheBoardCustom(Grid<char> & currentCube,int width, int height, string customInput);
Vector<string> buildLettersVec ();
void shuffleLetterCubes (Vector<string> & inputVector);
char getRandomLetter (Vector<string> cubes, int w, int h);
void clearTheBools (Grid<int> & usedLetters);
//Type conversion functions:
int getIndexOf (int h, int w);
Point convertToPoints (int n);
//Print functions:
void printSpacer (string input);
void printInputPrompt();
void giveInstructions();
void printComputerNotice();
void printComputerWords (Lexicon & allPossibleWords);

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    Lexicon english ("EnglishWords.dat");
    Lexicon allPossibleWords;
    Grid<char> currentCube(4,4);
    Grid<int> usedLetters(4,4);
    while (true) {
        initGBoggle(gw);
        //printSpacer(" WELCOME ");
        //giveInstructions();
        acceptControlStatement(currentCube);
        findAllPossibleWords (allPossibleWords, english, currentCube, usedLetters);
        acceptWordsFromUser(english, allPossibleWords);
        printComputerNotice();
        printComputerWords(allPossibleWords);
    }

    return 0;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/* Function: acceptControlStatement()
 *
 * Accepts commands from the end user.
 */
void acceptControlStatement(Grid<char> & currentCube) {
    while (true) {
        printSpacer(" CONTROLS ");
        cout << "----------------------------------------" << endl;
        cout << "CI = Custom Input." << endl <<
                "JP = Just Play." << endl;
        cout << "----------------------------------------" << endl;

        string controlStatement = getLine("Enter control statement:");
        cout << "----------------------------------------" << endl;
        if (controlStatement == "CI") {
            drawBoard(4,4);
            string customInput;
            while (customInput.length() < 16){
                customInput = getLine("Enter custom characters (16 of them):");
                if (customInput.length() < 15) {
                    customInput = getLine("Enter custom characters (16 of them):");
                }
            }
            customInput = toUpperCase(customInput);
            fillTheBoardCustom(currentCube,4,4,customInput);
            controlStatement = "blank";
            break;
        }
        if (controlStatement == "JP") {
            drawBoard(4,4);
            fillTheBoard(currentCube,4,4);
            controlStatement = "blank";
            break;
        }
        else cout << "That's not a valid control statement..." << endl;
    }
}

/* Function: fillTheBoard (int width, int height)
 *
 * Generates the random letters for a board-- i.e.
 * "shakes" the boggle cube.  Also labels each of
 * the squares with their letter.
 */
void fillTheBoard(Grid<char> & currentCube, int width, int height) {
    Vector<string> letterCubes = buildLettersVec();
    shuffleLetterCubes (letterCubes);
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            char ch = getRandomLetter (letterCubes, w, h);
            labelCube(w,h,ch);
            //int index = getIndexOf(w,h);
            currentCube.set(w,h,ch);
        }
    }
}

/* Function: fillTheBoardCustom
 *
 * Populates a user-specified board configuration.
 */
void fillTheBoardCustom(Grid<char> & currentCube, int width, int height, string customInput) {
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            char ch = customInput[getIndexOf(w,h)];
            labelCube(w,h,ch);
            //int index = getIndexOf(w,h);
            currentCube.set(w,h,ch);
        }
    }
}

/* Function: buildLettersVec ()
 *
 * Populates and returns a Vector<string> from
 * the initial input string of boggle letters.
 * Assumes the input string is properly ordered,
 * 96 characters long, and grouped by sets of 6
 * corresponding to each block, 1-16.
 */
Vector<string> buildLettersVec () {
    Vector<string> result;
    int i = 0;
    while (i <= FULL_LETTER_COUNT) {
        string tempString = STANDARD_LETTERS.substr(i,BLOCK_LETTER_COUNT);
        result.add(tempString);
        i += BLOCK_LETTER_COUNT;
    }
    return result;
}

/* Function: shuffleLetterCubes (Vector<string> & inputVector)
 *
 * Randomly shuffles a vector according to the algorithm
 * presented in the assignment handout.  LH iterates
 * through the index, swapping with a random RH.
 */
void shuffleLetterCubes (Vector<string> & inputVector) {
    int vectorSize = inputVector.size();
    for (int i = 0; i < vectorSize; i++) {
        int r = randomInteger(0, vectorSize - 1);
        string tempLH = inputVector.get(i);
        string tempRH = inputVector.get(r);
        inputVector[i] = tempLH;
        inputVector[r] = tempRH;
    }
}

/* Function: getRandomLetter (Vector<string>, int, int)
 *
 * Returns a random char when given a vector of strings,
 * assuming the string vector is indexed according to
 * appropriate boggle blocks of letters.
 */
char getRandomLetter (Vector<string> cubes, int w, int h) {
    int index = getIndexOf(w,h);
    string letters = cubes.get(index);
    int size = letters.length();
    int depth = randomInteger(0, size - 1);
    char result = letters[depth];
    return result;
}

/* Function: findAllPossibleWords
 *
 * This is a wrapper function for findAllPossibleWordsRec.
 * It just calls the recursive version for each position
 * in the main grid of the currentCube.
 */
void findAllPossibleWords (Lexicon & allPossibleWords, Lexicon & english,
                           Grid<char> & currentCube, Grid<int> & usedLetters) {
    //Call the recursive search function for each cube:
    for (int x=0; x < 4; x++) {
        for (int y=0; y < 4; y++) {
            clearTheBools (usedLetters);
            findAllPossibleWordsRec (allPossibleWords, english, currentCube, usedLetters, "", x, y);
        }
    }
}

/* Function: findAllPossibleWordsRec
 *
 * This is the main recursive backtracking algorithm.
 * I should have done two separate versions, so that
 * I could support highlighting of the user words...
 *
 * But...  Working on a time crunch, I thought this
 * solution was more elegant, and it provides 99%
 * of the same functionality.
 *
 * 2/19/15 -- bug fix: added check for already usedLetters.
 */
void findAllPossibleWordsRec (Lexicon & allPossibleWords,Lexicon & english,
                              Grid<char> & currentCube, Grid<int> & usedLetters, string prefix, int x, int y) {

    //BASE CASE: is a word
        //*Add word to allPossibleWords*
    //BASE CASE: is out of bounds
        //*Prune shitty result*
    //if english.containsPrefix(currentCube[x][x])
        //Prefix += currentCube[x][x]
        //For (all directions)
            //Recursive call (all params, +prefix, +nextPoint)

    if (!currentCube.inBounds(x,y)) {
        return;
    }
    if (usedLetters[x][y] == 1) {
        return;
    }
    if (english.contains(prefix)
        && prefix.length() > 3) {
        allPossibleWords.add(prefix);
    }
    string newPrefix = prefix + currentCube[x][y];
    if (!english.containsPrefix(newPrefix)){
        return;
    }
    if (english.contains(newPrefix)
        && prefix.length() > 3) {
        allPossibleWords.add(newPrefix);
        usedLetters.set(x,y,1);
    }
    if (english.containsPrefix(newPrefix)) {
        //NORTH:
        findAllPossibleWordsRec(allPossibleWords, english, currentCube, usedLetters, newPrefix, x+0, y-1);
        //NORTHEAST:
        findAllPossibleWordsRec(allPossibleWords, english, currentCube, usedLetters, newPrefix, x+1, y-1);
        //EAST:
        findAllPossibleWordsRec(allPossibleWords, english, currentCube, usedLetters, newPrefix, x+1, y-0);
        //SOUTHEAST:
        findAllPossibleWordsRec(allPossibleWords, english, currentCube, usedLetters, newPrefix, x+1, y+1);
        //SOUTH:
        findAllPossibleWordsRec(allPossibleWords, english, currentCube, usedLetters, newPrefix, x-0, y+1);
        //SOUTHWEST:
        findAllPossibleWordsRec(allPossibleWords, english, currentCube, usedLetters, newPrefix, x-1, y+1);
        //WEST:
        findAllPossibleWordsRec(allPossibleWords, english, currentCube, usedLetters, newPrefix, x-1, y-0);
        //NORTHWEST:
        findAllPossibleWordsRec(allPossibleWords, english, currentCube, usedLetters, newPrefix, x-1, y-1);
    }
}

/* Function: acceptWordsFromUser(Lexicon & english, Lexicon & allPossibleWords)
 *
 * Reads words from the user-- checks that they're
 * in english, that they're > 4 letters, that they
 * haven't already been used, that they're on the board.
 */
void acceptWordsFromUser(Lexicon & english, Lexicon & allPossibleWords) {
    printInputPrompt();
    Lexicon alreadyUsed;
    string userInput = "qwerty";
    while (userInput != "") {
        userInput = getLine("Enter a word:");
        if (userInput == "") {
            break;
        }
        if (english.contains(userInput)
                && userInput.length() > 3
                && !alreadyUsed.contains(userInput)
                && allPossibleWords.contains(userInput)) {
            alreadyUsed.add(userInput);
            recordWordForPlayer(userInput, HUMAN);
            cout << "Good job.  \"" << userInput << "\" is a valid entry." << endl;
            userInput = "qwerty";
        }
        else {
            cout << "Sorry.  That's not a valid entry." << endl;
        }
    }
    cout << "----------------------------------------" << endl;
}

/* Function int getIndexOf (int h, int w)
 *
 * Calculates the index position of a string in the
 * main Vector<string> block letters collection
 * according to its height and width cordinates.
 * Possible return values span 0 - 15.
 *
 * Also used to find index positions for user
 * input strings when custom letters are provided.
 */
int getIndexOf (int h, int w) {
    if (h == 0) {
        return w;
    }
    if (h == 1) {
        return 4 + w;
    }
    if (h == 2) {
        return 8 + w;
    }
    if (h == 3) {
        return 12 + w;
    }
    else return -1;
}

/* Function: clearTheBools
 *
 * Clears the bool grid...
 * That's all...  o_O
 */
void clearTheBools (Grid<int> & usedLetters) {
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            usedLetters.set(x,y,0);
        }
    }
}

/* Function: printInputPrompt()
 *
 * Informs the user of the input specifications.
 */
void printInputPrompt() {
    printSpacer(" INSTRUCTIONS ");
    cout << "----------------------------------------" << endl;
    cout << "Input the words you'd like to play." << endl;
    cout << "Words must be at least four letters." << endl;
    cout << "Each word can only be played once." << endl;
    cout << "Hit \"return\" to submit your words." << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
}

/* Function: printSpacer (string input)
 *
 * Just prints a title, providing space
 * between user instructions on the console.
 * Input must be less than 20char.
 */
void printSpacer (string input) {
    int size = input.length();
    int xNumber;
    string Xs;
    xNumber = (20 - size);
    for (int i = 0; i < xNumber; i++) {
        Xs += "X";
    }
    cout << "" << endl;
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
    cout << Xs << input << "XXXXXXXXXXXXXXXXXXXX" << endl;
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
    cout << "" << endl;
}

/* Function: printComputerNotice
 *
 * Let's the user know on the console that
 * the computer's having its turn...
 */
void printComputerNotice() {
    printSpacer( " COMPUTER's TURN ");
    cout << "----------------------------------------" << endl;
    cout << "Processing computer's words..." <<endl;
    cout << "Don't feel bad if you lost..." << endl;
    cout << "Computers are really smart..." << endl;
    cout << "----------------------------------------" << endl;
}

/* Function: printComputerWords (Lexicon & allPossibleWords)
 *
 * Prints all the computer's words to the gameboard.
 */
void printComputerWords (Lexicon & allPossibleWords) {
    for (string str : allPossibleWords) {
        recordWordForPlayer(str, COMPUTER);
    }
}
