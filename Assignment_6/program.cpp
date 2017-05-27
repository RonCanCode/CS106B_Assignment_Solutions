/*
 * File: program.cpp
 * -----------------
 *
 * Name:  Ron Guglielmone
 * Section:  Marielos Sanson
 *
 * This is an implementation of the program.h interface.
 * It uses a linked-list, a hashMap and some structures
 * to deliver the required methods at the specified Big-O.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;


// Constructor:
Program::Program() {
    statementMap = new HashMap<int, StatementContainer>;
    head = tail = NULL;
    count = 0;
}

// Destructor:
Program::~Program() {
    clear();
}

/* Function: clear()
 *
 * Clears the map and the linked list.
 */
void Program::clear() {

    //Clear the maps:
    statementMap->clear();

    //Clear the linked-list:
    Cell *list = head;
    while (list != NULL) {
        Cell *next = list->link;
        delete list;
        list = next;
    }
    head = tail = NULL;
    count = 0;
}

/* Function: addSourceLine(int lineNumber, string line)
 *
 * Adds a new line of code to the internal data structures.
 * This line is a string-- not a statement...
 */
void Program::addSourceLine(int lineNumber, string line) {

    //Added yet?
    bool hasBeenAdded = false;

    //Case to delete a line:
    if (line == "" && statementMap->containsKey(lineNumber)) {
        removeSourceLine(lineNumber);
        hasBeenAdded = true;
    }

    //If lineNumber already exists:
    if (statementMap->containsKey(lineNumber)) {
        removeSourceLine(lineNumber);
    }

    //Add to the linked-list:
    if (hasBeenAdded == false) {
        Cell *newCell = new Cell;
        newCell->lineNumber = lineNumber;
        enqueue(lineNumber, newCell);

        //Add to the statementMap:
        StatementContainer tempContainer;
        tempContainer.sourceLine = line;
        tempContainer.link = newCell;
        statementMap->add(lineNumber, tempContainer);
    }
}

/* Function: removeSourceLine(int lineNumber)
 *
 * Removes a source line...
 */
void Program::removeSourceLine(int lineNumber) {

    //Removed yet?
    bool hasBeenRemoved = false;

    //Remove from map:
    if (statementMap->containsKey(lineNumber)) {
        statementMap->remove(lineNumber);

        //Remove from linked-list:
        Cell *walker = head;
        //When lineNumber refrences head:
        if (walker->lineNumber == lineNumber) {
            head = walker->link;
            delete walker;
            count --;
            hasBeenRemoved = true;
        }

        //Finding midway lineNumber:
        while (walker->link->link != NULL && !hasBeenRemoved) {
            if (walker->link->lineNumber == lineNumber) {
                Cell *temp = walker->link->link;
                delete walker->link;
                walker->link = temp;
                count--;
                hasBeenRemoved = true;
                break;
            }
            walker = walker->link;
        }

        //Deleting the last line:
        if (walker->link->link == NULL && !hasBeenRemoved) {
            if (walker->link->lineNumber == lineNumber) {
                delete walker->link;
                walker->link = NULL;
                hasBeenRemoved = true;
                count--;
                tail = walker;
            }
        }
    }
}


/* Function: getSourceLine(int lineNumber)
 *
 * Returns a source line given its lineNumber.
 */
string Program::getSourceLine(int lineNumber) {
    if (statementMap->containsKey(lineNumber)) {
        string line = statementMap->get(lineNumber).sourceLine;
        return line;
    }
    else return "";
}

/* Function: setParcedStatement(int lineNumber, Statement *stmt)
 *
 * I don't know what a statement is, but this sets one...
 */
void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    StatementContainer stm;
    stm.stateMnt = stmt;
    statementMap->add(lineNumber, stm);
}


/* Function: getParsedStatement(int lineNumber)
 *
 * Again, not sure what one is, but this gets a statement.
 */
Statement* Program::getParsedStatement(int lineNumber) {
    if (statementMap->containsKey(lineNumber)) {
        Statement *stmt = statementMap->get(lineNumber).stateMnt;
        return stmt;
    }
    return NULL;
}


/* Function: getFirstLineNumber ()
 *
 * Does what it says...
 */
int Program::getFirstLineNumber() {
    if (head == NULL) {
        return -1;
    }
    else return head->lineNumber;
}

/* Function: getNextLineNumber(int lineNumber)
 *
 * Not sure if I really need to be commenting all of these,
 * but it makes it easier for me to see each function.
 */
int Program::getNextLineNumber(int lineNumber) {
    if (statementMap->containsKey(lineNumber)) {
        if (statementMap->get(lineNumber).link != NULL) {
            Cell *current = statementMap->get(lineNumber).link;
            if (current->link != NULL) {
                Cell *next = current->link;
                int number = next->lineNumber;
                return number;
            }
        }
    }
    return -1;
}

/* Function: enqueue
 *
 * Adds elements by priority to the linked-list.
 */
void Program::enqueue(int lineNumber, Cell *cell) {

    //Added marker:
    bool hasBeenAdded = false;

    //Build new cell:
    Cell *walker;
    cell->lineNumber = lineNumber;
    cell->link = NULL;

    //Case for first entry:
    if (head == NULL) {
        head = cell;
        tail = cell;
        hasBeenAdded = true;
    }

    //Case for low-# priority:
    if (lineNumber < head->lineNumber && !hasBeenAdded) {
        cell->link = head;
        head = cell;
        hasBeenAdded = true;
    }

    //Case for high-# priority, NULL head pointer:
    if (lineNumber > head->lineNumber && !hasBeenAdded
            && head->link == NULL) {
        head->link = cell;
        tail = cell;
        hasBeenAdded = true;
    }

    //Case for finding middle index:
    if (!hasBeenAdded) {
        walker = head;
        while (walker->link != NULL) {

            if (walker->link->lineNumber < lineNumber) {
                walker = walker->link;
            }
            else {
                cell->link = walker->link;
                walker->link = cell;
                hasBeenAdded = true;
                break;
            }
        }
    }

    //End has been reached, nothing added:
    if (!hasBeenAdded) {
        tail->link = cell;
        tail = cell;
    }
    count++;
}

/* Function:  dequeue
 *
 * Removes the first element (lowest priority #).
 */
int Program::dequeue() {
    if (count == 0) {
        error("Trying to dequeue empty list-- no program lines left.");
        return -1;
    }
    Cell *cp = head;
    int result = cp->lineNumber;
    head = cp->link;
    delete cp;
    count--;
    return result;
}

/* Function:  isEmpty
 *
 * Returns true is there's nothing in the linked list.
 */
bool Program::isEmpty() {
    return statementMap->isEmpty();
}
