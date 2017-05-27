/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: Ron Guglielmone
 *
 * This program creates a Sierpinski Triangle
 * using graphical recursion.
 *
 * Looks like this, but with actual pixels:
 *_______________________________1_______________________________
 *______________________________111______________________________
 *_____________________________1___1_____________________________
 *____________________________111_111____________________________
 *___________________________1_______1___________________________
 *__________________________111_____111__________________________
 *_________________________1___1___1___1_________________________
 *________________________111_111_111_111________________________
 *_______________________1_______________1_______________________
 *______________________111_____________111______________________
 *_____________________1___1___________1___1_____________________
 *____________________111_111_________111_111____________________
 *___________________1_______1_______1_______1___________________
 *__________________111_____111_____111_____111__________________
 *_________________1___1___1___1___1___1___1___1_________________
 *________________111_111_111_111_111_111_111_111________________
 *_______________1_______________________________1_______________
 *______________111_____________________________111______________
 *_____________1___1___________________________1___1_____________
 *____________111_111_________________________111_111____________
 *___________1_______1_______________________1_______1___________
 *__________111_____111_____________________111_____111__________
 *_________1___1___1___1___________________1___1___1___1_________
 *________111_111_111_111_________________111_111_111_111________
 *_______1_______________1_______________1_______________1_______
 *______111_____________111_____________111_____________111______
 *_____1___1___________1___1___________1___1___________1___1_____
 *____111_111_________111_111_________111_111_________111_111____
 *___1_______1_______1_______1_______1_______1_______1_______1___
 *__111_____111_____111_____111_____111_____111_____111_____111__
 *_1___1___1___1___1___1___1___1___1___1___1___1___1___1___1___1_
 *111_111_111_111_111_111_111_111_111_111_111_111_111_111_111_111
 *
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
