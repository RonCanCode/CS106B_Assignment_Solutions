/*
 * File: PQTest.cpp
 * ----------------
 * Name: Ron Guglielmone
 *
 * This test program is used to verify the
 * correctness of various implementations
 * of the PriorityQueue class.
 */

#include <iostream>
#include <string>
#include "console.h"
#include "pqueue.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "tokenscanner.h"
using namespace std;

/* Function prototypes */

void helpCommand();
void enqueueCommand(PriorityQueue & pq, string cmd);
void dequeueCommand(PriorityQueue & pq);
void peekCommand(PriorityQueue & pq);
void peekPriorityCommand(PriorityQueue & pq);
void clearCommand(PriorityQueue & pq);
void sizeCommand(PriorityQueue & pq);
void isEmptyCommand(PriorityQueue & pq);
void listCommand(PriorityQueue & pq);

/* Main program */

int main() {
   PriorityQueue pq;
   while (true) {
      //Input data:
      string cmd = getLine("> ");
      bool commandWasValid = false;

      //Tests:
      if (!commandWasValid) {
          if (cmd == "test") {
              cout << "yeaaah" << endl;
          }
          if (cmd == "help") {
             helpCommand();
             commandWasValid = true;
          }
          if (startsWith(cmd, "enq")) {
              enqueueCommand(pq, cmd);
              commandWasValid = true;
          }
          if (startsWith(cmd, "deq")) {
              dequeueCommand(pq);
              commandWasValid = true;
          }
          if (cmd == "peek") {
              peekCommand(pq);
              commandWasValid = true;
          }
          if (cmd == "peekPriority") {
              peekPriorityCommand(pq);
              commandWasValid = true;
          }
          if (cmd == "clear") {
              clearCommand(pq);
              commandWasValid = true;
          }
          if (cmd == "size") {
              sizeCommand(pq);
              commandWasValid = true;
          }
          if (cmd == "isEmpty") {
              isEmptyCommand(pq);
              commandWasValid = true;
          }
          if (cmd == "list") {
              listCommand(pq);
              commandWasValid = true;
          }
          if (cmd == "Marielos Rocks!") {
              cout << "Hell yeah she does." << endl;
              commandWasValid = true;
          }
      }
      if (!commandWasValid){
         cout << "Undefined command: " << cmd << endl;
      }
      commandWasValid = false;
   }
   return 0;
}

/*
 * Function: helpCommand
 * ---------------------
 * Displays a list of the required commands.  If you extend this program,
 * you should add new entries to this function.
 */
void helpCommand() {
   cout << "enqueue value priority -- Enqueues value at priority" << endl;
   cout << "dequeue -- Dequeues the most urgent item" << endl;
   cout << "peek -- Peeks at the first item without removing it" << endl;
   cout << "peekPriority -- Reports the priority of the first item" << endl;
   cout << "clear -- Clears the queue" << endl;
   cout << "size -- Reports the size of the queue" << endl;
   cout << "isEmpty -- Reports whether the queue is empty" << endl;
   cout << "list -- Lists the elements of the queue" << endl;
   cout << "help -- Prints this message" << endl;
}

/*
 * Function: enqueueCommand
 * ---------------------
 * Reads a string in the format "enqueue str dbl"
 * where str is the data, dbl is the priority,
 * and the delimiters are empty spaces (" ").
 *
 * Then, adds that input to the queue.
 */
void enqueueCommand(PriorityQueue & pq, string cmd) {
    vector<string> rawData = stringSplit(cmd, " ");
    if (rawData.size() != 3) {
        cout << "Invalid input.  Format: enqueue str dbl." << endl;
    }
    if (rawData.size() == 3) {
        string inputString = rawData[1];
        string inputDouble = rawData[2];
        double inputPriority = stringToDouble(inputDouble);
        pq.enqueue(inputString, inputPriority);
    }
}

/*
 * Function: dequeueCommand
 * ---------------------
 * Dequeues the head element, testing first if the
 * queue isEmpty().  If so, an error is reported.
 */
void dequeueCommand(PriorityQueue & pq) {
    if (!pq.isEmpty()) {
        string output = pq.dequeue();
        cout << output << endl;
    }
    else {
        cout << "The queue is empty." << endl;
    }
}

/*
 * Function: peekCommand
 * ---------------------
 * Peeks at the top element in the queue.
 * If it's not there, an error is reported.
 */
void peekCommand(PriorityQueue & pq) {
    if (!pq.isEmpty()) {
        string output = pq.peek();
        cout << output << endl;
    }
    else {
        cout << "The queue is empty." << endl;
    }
}

/*
 * Function: peekPriorityCommand
 * ---------------------
 * Returns the double for the next priority in the queue,
 * reporting an error is the queue isEmpty().
 */
void peekPriorityCommand(PriorityQueue & pq) {
    if (!pq.isEmpty()) {
        double output = pq.peekPriority();
        cout << output << endl;
    }
    else {
        cout << "The queue is empty." << endl;
    }

}

/*
 * Function: clearCommand
 * ---------------------
 * Pretty straight forward...
 */
void clearCommand(PriorityQueue & pq) {
    pq.clear();
}

/*
 * Function: sizeCommand
 * ---------------------
 * Prints the size of the queue.
 */
void sizeCommand(PriorityQueue & pq) {
    int output = pq.size();
    cout << output << endl;
}

/*
 * Function: isEmptyCommand
 * ---------------------
 * Tests if the queue is empty.
 */
void isEmptyCommand(PriorityQueue & pq) {
    if (pq.isEmpty()) cout << "true" << endl;
    else cout << "false" << endl;
}

/*
 * Function: listCommand
 * ---------------------
 * Copies the queue, then lists all of the elements
 * currently stored (in order).
 */
void listCommand(PriorityQueue & pq) {
    PriorityQueue copyQueue = pq;
    while (!copyQueue.isEmpty()) {
        string output = copyQueue.dequeue();
        cout << output << " ";
    }   cout << endl;
}
