/*
 * File: StockCutting.cpp
 * ----------------------
 * 
 * Computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces.
 *
 * Not sure if I ever got this working...
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "simpio.h"
#include "set.h"
using namespace std;

/* Function prototypes */

int cutStock(Vector<int> & requests, int stockLength);
void shuffleTheRequests (Vector<int> requests, Vector<int> results, int count);

/* Main program */

int main() {
    //Input storage variables:
    Vector<int> desiredLengths;
    int stockLength;
    //Accept input for stock length:
    stockLength = getInteger("Enter the desired stock length:");
    //Accept input for desired lengths:
    while (true) {
        cout << "Enter requested pipe lengths ('0' when finished): ";
        int input = getInteger();
        if (input == 0) break;
        desiredLengths.add(input);
    }

    Vector<Vector<int> > results;
    shuffleTheRequests (desiredLengths, results, desiredLengths.size());
    cout << "Permutated vector: " << results << endl;
    cout << "INPUTS:"  << desiredLengths << endl << "Stock:" << stockLength << endl;

    return 0;
}

/*
 * Function: cutStock
 * Usage: int units = cutStock(requests, stockLength);
 * ---------------------------------------------------
 * Computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces.
 */

//int cutStock(Vector<int> & requests, int stockLength) {
//    shuffleTheRequests (requests, requests.size());
//    //fillPossibleBuckets(requests, requests.size(), );
//    return 0;
//}

/*
 * Can't get this working...
 */
void shuffleTheRequests (Vector<int> requests, Vector<int> & results, int count) {
    if (count == 0) {
        results = results;
    }
    else {
        for (int i = count - 1; i >= 0; i--) {
            int x = requests[i];
            Vector<int> rest = requests;
            rest.remove(i);
            for (Vector<int> intVec : shuffleTheRequests (rest, results, i)) {
                intVec.insert(0,x);
                intVec += rest;
                results.add(intVec);
            }
        }
    }
}
/*

Set<string> generatePermutations (string str) {
    Set<string> result;
    if (str == "") {
        result += "";
    }
    else {
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            string rest = str.substr (0,i) + str.substr (i + 1);
            for (string s : generatePermutations (rest)) {
                result += ch + s;
            }
        }
    }
    return result;
}*/
