/*
 * File: pqueue.cpp (heap version)
 * -------------------------------
 * Name: Ron Guglielmone
 *
 * 3/5/15:  Still haven't managed to fix this...
 * Definitely tried...  :/
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
#include "vector.h"
using namespace std;

/* Constructor:  PriorityQueue
 *
 */
PriorityQueue::PriorityQueue() {
    new Vector<Entry>;
}

/* Destructor:  ~PriorityQueue
 *
 */
PriorityQueue::~PriorityQueue() {
    bindingVector.clear();
}

/* size()
 *
 * Number of elements in the queue.
 */
int PriorityQueue::size() {
    return bindingVector.size();
}

/* isEmpty()
 *
 * Returns true when nothing is left in the queue.
 */
bool PriorityQueue::isEmpty() {
    return bindingVector.isEmpty();
}

/* clear()
 *
 * Deletes the entries in pQueue.
 */
void PriorityQueue::clear() {
    bindingVector.clear();
}

/* enqueue
 *
 * Adds elements to the queue
 */
void PriorityQueue::enqueue(string value, double priority) {

    //Create a new entry:
    Entry thisEntry;
    thisEntry.value = value;
    thisEntry.priority = priority;

    //First entry:
    if (bindingVector.isEmpty()) {
        bindingVector.add(thisEntry);
    }
    //Other entries:
    else {
        int end = bindingVector.size() - 1;
        int parentIndex = (end - 1) / 2;
        bindingVector[end] = thisEntry;
        while (bindingVector[parentIndex].priority >
               bindingVector[end].priority && parentIndex > 0) {
            Entry temp = bindingVector[parentIndex];
            bindingVector[parentIndex] = bindingVector[end];
            bindingVector[end] = temp;
            parentIndex = (parentIndex - 1) /2;
            end = parentIndex;
        }
    }
}

/* dequeue()
 *
 * Removes an element from pQueue.
 */
string PriorityQueue::dequeue() {
    if (isEmpty()) return "";

    //Return first element:
    Entry thisEntry = bindingVector[0];
    string entryString = thisEntry.value;
    bindingVector.remove(0);

    //Swap last element up to root:
    int end = bindingVector.size() - 1;
    if (end > 0) {
        Entry newRoot = bindingVector[end];
        bindingVector.insert(0,newRoot);
        bindingVector.remove(end);

        //Cascade it down if needed:
        int root = 0;
        int leftChild = 2 * 0 + 1;
        int rightChild = 2 * 0 + 2;
        while (bindingVector[root].priority >
               bindingVector[leftChild].priority |
               bindingVector[root].priority >
               bindingVector[rightChild].priority) {

            //When left is smaller, swap:
            if (bindingVector[leftChild].priority <
                    bindingVector[rightChild].priority) {
                Entry temp = bindingVector[leftChild];
                bindingVector[leftChild] = bindingVector [root];
                bindingVector[root] = temp;
            }
            //When right is smaller, swap:
            else if (bindingVector[rightChild].priority <
                    bindingVector[leftChild].priority) {
                Entry temp = bindingVector[rightChild];
                bindingVector[rightChild] = bindingVector [root];
                bindingVector[root] = temp;
            }
        }
    }
    //Finally, return the value that was removed:
    return entryString;
}

/* peek()
 *
 * Check out the next value without messing it up.
 */
string PriorityQueue::peek() {
    Entry thisEntry = bindingVector[0];
    return thisEntry.value;
}

/* peekPriority()
 *
 * Check out the next value's priority.
 */
double PriorityQueue::peekPriority() {
    Entry thisEntry = bindingVector[0];
    return thisEntry.priority;
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
