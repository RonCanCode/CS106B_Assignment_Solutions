/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: Ron Guglilemone
 *
 * This program simulates flipping a coin and terminates
 * when either heads or tails has been the result three
 * times in a row.
 *
 * -Contains some kind of bug that causes four tails
 *  to slip through sometimes...  (?)
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
using namespace std;

/* Prototypes: */
string flipCoin();

/* Globals: */
int consecutiveCount = 0;
int totalFlipCount = 0;
string lastFlip;

int main() {
   cout << "-----------------------------------------" << endl;
   cout << "This program will simulate coin flips..." << endl;
   cout << "After three consecutive heads or tails," << endl;
   cout << "the total number of flips is printed:" << endl;
   cout << "-----------------------------------------" << endl;

   while (consecutiveCount < 3) {
      string lastFlip = flipCoin();
      cout << lastFlip << endl;
   }

   cout << "-----------------------------------------" << endl;
   cout << "The total number of flips was " << totalFlipCount << "." << endl;
   cout << "-----------------------------------------" << endl;
   return 0;
}

/* Funtion: flipCoin()
 * Returns: string lastFlip
 *
 * Simulates a coin flip by calling randomChance in #include random.h
 * Increments global counters for totalFlipCount and consectiveCount.
 */
string flipCoin() {
    totalFlipCount++;
    if (randomChance(0.50)) {
        string head = "heads";
            if (lastFlip == head) {
                consecutiveCount++;
            }
        lastFlip = head;
        return "heads";
    }
    else {
        string tail = "tails";
            if (lastFlip == tail) {
                consecutiveCount++;
            }
        lastFlip = tail;
        return "tails";
    }
}
