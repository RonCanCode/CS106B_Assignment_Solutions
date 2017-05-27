/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * Name: Ron Guglilemone
 * Section: Marielos Sanson
 *
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
#include "string.h"
using namespace std;

PriorityQueue::PriorityQueue() {
    count = 0;
    capacity = INITIAL_CAPACITY;
    array = new ValuePriorityPair[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] array;
}

int PriorityQueue::size() {
    return count;
}

bool PriorityQueue::isEmpty() {
    return count == 0;
}

void PriorityQueue::clear() {
    count = 0;
}

void PriorityQueue::enqueue(string value, double priority) {

    //Expand array if needed:
    if (size() == capacity - 1) expandCapacity();

    //Added test:
    bool hasBeenAdded = false;

    //Create a new entry:
    ValuePriorityPair thisEntry;
    thisEntry.value = value;
    thisEntry.priority = priority;

    //First entry:
    if (count == 0) {
        array[0] = thisEntry;
        count++;
    }
    else {

        //Check priority against current entries:
        for (int i = 0; i < count; i++) {
            double previousPriority = array[i].priority;
            if (previousPriority > priority) {
                //Move previous entries back:
                for (int j = count; j > i; j--) {
                    array[j] = array[j-1];
                }
                //Add new entry in its place:
                array[i] = thisEntry;
                count++;
                hasBeenAdded = true;
                break;
            }
            //Else, add new entry to end:
        }
        if (!hasBeenAdded) {
            array[count] = thisEntry;
            count++;

        }
    }
}

string PriorityQueue::dequeue() {
    if (isEmpty()) error("Sorry, bro...  I ain't got no more.");
    //Return first element:
    ValuePriorityPair thisEntry = array[0];
    string entryString = thisEntry.value;
    //Shift everything else:
    for (int i = 0; i < count; i++) {
        array[i] = array[i + 1];
    }
    count--;
    return entryString;
}

string PriorityQueue::peek() {
    ValuePriorityPair thisEntry = array[0];
    return thisEntry.value;
}

double PriorityQueue::peekPriority() {
    ValuePriorityPair thisEntry = array[0];
    return thisEntry.priority;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow the standard
 * paradigm described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
    deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
    if (this != &src) {
        if (array != NULL) delete[] array;
        deepCopy(src);
    }
    return *this;
}
