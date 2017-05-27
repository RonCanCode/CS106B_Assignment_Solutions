/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: Ron Guglielmone
 * Section: Marielos Sanson
 *
 * This program creates a Sierpinski Triangle
 * using graphical recursion.
 */

#include <iostream>
#include "gwindow.h"
using namespace std;
#include <cmath>

/* Globals: */
//Adjusts the size of a side:
const double SIZE = 500;
//Adjusts the window dimensions:
const double WINDOW_WIDTH = 1200;
const double WINDOW_HEIGHT = 800;
//Adjusts the depth of recursion:
const int ORDER = 9;

/* Prototypes: */
GPoint drawATriangle (GWindow & gw, GPoint start,
                      double SIZE, double theta, int order);

/* Main program */

int main() {
    GWindow gw(WINDOW_WIDTH, WINDOW_HEIGHT);
    double cx = gw.getWidth () / 2;
    double cy = gw.getHeight () / 2;
    GPoint pt (cx - SIZE / 2, cy + sqrt (3.0) * SIZE / 4);
    pt = drawATriangle (gw, pt, SIZE, 0, ORDER);
    pt = drawATriangle (gw, pt, SIZE, +120, ORDER);
    pt = drawATriangle (gw, pt, SIZE, -120, ORDER);
    return 0;
}

/* Function: drawATriangle (GWindow, GPoint, double, double, int)
 *
 * Based on the drawFractalLine method in Chapter 9 of Eric Robert's
 * C++ Course Reader.
 */
GPoint drawATriangle (GWindow & gw, GPoint pt,
                      double SIZE, double theta, int order) {
    //Base case, which actually draws the lines:
    if (order == 0) {
        return gw.drawPolarLine (pt, SIZE, theta);
    }
    //Recursive loop:
    else {
        GPoint returnPt = pt;
        pt = drawATriangle (gw, pt, SIZE / 2, theta, order - 1);
        //Sets a new start-point for next triangle:
        double x2 = pt.getX() + SIZE / 2;
        double y2 = pt.getY();
        GPoint pt2(x2,y2);
        //Draws next triangle:
        pt = drawATriangle (gw, pt2, SIZE / 2, theta + 120, order -1);
        //Sets a new start-point for next triangle:
        double x3 = pt.getX() - SIZE / 4;
        double y3 = pt.getY() - ((sqrt (3.0) * SIZE) / 4);
        GPoint pt3(x3,y3);
        //Draws next triangle:
        pt = drawATriangle (gw, pt3, SIZE / 2, theta -120, order - 1);
        //Returns the point of containing triangle:
        return drawATriangle (gw, returnPt, SIZE / 2, theta, order - 1);
    }
}
