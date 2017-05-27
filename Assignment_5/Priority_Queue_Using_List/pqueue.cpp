/*
 * File: pqueue.cpp (linked-list version)
 * --------------------------------------
 * Name: Ron Guglielmone
 * Section: Marielos Sanson
 *
 * 3/5/15: Fixed bugs.  Seems to be working well, now.
 *
 * This is an implementation of priorityQueue using
 * a linked-list model.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

/* Constructor:  PriorityQueue
 *
 * Builds a new pQueue object.
 */
PriorityQueue::PriorityQueue() {
    head = NULL;
    tail = NULL;
    count = 0;
}

/* Destructor:  ~PriorityQueue
 *
 * Destroys a pQueue object.
 */
PriorityQueue::~PriorityQueue() {
    clear();
}

/* Function:  size
 *
 * Returns the number of elements in the pQueue.
 */
int PriorityQueue::size() {
    return count;
}

/* Function:  isEmpty
 *
 * Returns true is there's nothing in pQueue.
 */
bool PriorityQueue::isEmpty() {
    return count == 0;
}

/* Function clear
 *
 * Deletes everything from the pQueue.
 */
void PriorityQueue::clear() {
    while (count > 0) {
        dequeue();
    }
}

/* Function: enqueue
 *
 * Adds elements by priority to the queue.
 */
void PriorityQueue::enqueue(string value, double priority) {

    //Added marker:
    bool hasBeenAdded = false;

    //Build new cell:
    Cell *temp, *walker;
    temp = new Cell;
    temp->value = value;
    temp->priority = priority;
    temp->link = NULL;

    //Case for first entry:
    if (head == NULL) {
        head = temp;
        tail = temp;
        hasBeenAdded = true;
    }

    //Case for low-# priority:
    if (priority < head->priority && !hasBeenAdded) {
        temp->link = head;
        tail = head;
        head = temp;
        hasBeenAdded = true;
    }

    //Case for high-# priority, NULL head pointer:
    if (priority > head->priority && !hasBeenAdded
            && head->link == NULL) {
        head->link = temp;
        tail = temp;
        hasBeenAdded = true;
    }

    //Case for finding middle index:
    if (!hasBeenAdded) {
        walker = head;
        while (walker->link != NULL) {

            if (walker->link->priority < priority) {
                walker = walker->link;
            }
            else {
                temp->link = walker->link;
                walker->link = temp;
                hasBeenAdded = true;
                break;
            }
        }
    }

    //End has been reached, nothing added:
    if (!hasBeenAdded) {
        tail->link = temp;
        tail = temp;
    }
    count++;
}

/* Function:  dequeue
 *
 * Removes the first element (lowest priority #).
 */
string PriorityQueue::dequeue() {
    if (isEmpty()) {
        error("Sorry.  All out");
        return "";
    }
    Cell *cp = head;
    string result = cp->value;
    head = cp->link;
    delete cp;
    count--;
    return result;
}

/* Function:  peek
 *
 * Returns the first value without removing it.
 */
string PriorityQueue::peek() {
    if (isEmpty()) error("Sorry, bro...  Not happening.");
    return head->value;
}

/* Function: peekPriority
 *
 * Returns the first priority value without removing it.
 */
double PriorityQueue::peekPriority() {
    if (isEmpty()) error("Nothing there.");
    return head->priority;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
    deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }
    return *this;
}
