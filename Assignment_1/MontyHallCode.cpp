/*
 * File: MontyHallCode.cpp
 * --------------------------
 * Name: Ron Guglilemone
 *
 * Simulates Monty Hall, 3 Doors.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Prototypes: */
string flipCoin();

/* Globals: */
int switchStrategy = 0;
int stayStrategy = 0;

int main() {
   cout << "------------------------------------------------" << endl;
   cout << "This program will simulate the Mony Hall Problem" << endl;
   cout << "with three doors and one chance to switch.  The " << endl;
   cout << "simulation will run 'n' times, and print the    " << endl;
   cout << "number of wins with a 'sticking' strategy and a " << endl;
   cout << "'staying' straregy.                             " << endl;
   cout << "------------------------------------------------" << endl;

   int nIterations = getInteger('Enter the number of iterations to run: ');

   for (int i = 1; i < nIterations; i++) {
       int winningDoor = randomInteger(1,3);
       int pickAndStick = 1;
       int switchDoor = -1;
       int openDoor = -1;

       if (winningDoor = 1) {
           openDoor = 2;
           switchDoor = 3;
       }
       else if (winningDoor != 2) {
           openDoor = 2;
           switchDoor = 3;
       }
       else if (winningDoor != 3) {
           openDoor = 3;
           switchDoor = 2;
       }

       if (pickAndStick == winningDoor) {
           stayStrategy++;
       }

       if (switchDoor == winningDoor) {
           switchStrategy++;
       }
   }

   cout << "------------------------------------------------" << endl;
   cout << "Out of " << nIterations << " Stay Strategy has " << stayStrategy << " wins." << endl;
   cout << "Out of " << nIterations << " Switch Strategy has " << switchStrategy << " wins." << endl;
   cout << "------------------------------------------------" << endl;
   return 0;
}

