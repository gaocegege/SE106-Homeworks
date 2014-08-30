/*
 * File: Sierpinski.cpp
 * ----------------------
 * Student ID: 5120379091
 * Name: Gao Ce
 * This file is the starter project for the Sierpinski Triangle problem.
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

const double SQRT3 = sqrt(3);

GWindow* win;

void drawTriangle(GPoint a, GPoint b, GPoint c) {
  win->drawLine(a, b);
  win->drawLine(b, c);
  win->drawLine(c, a);
}

void drawS(GPoint a, GPoint b, GPoint c, double length, int order)
{
	if (order == 0)
		return;
	else if (order >0)
	{
    length = length/2;
    order --;
    drawTriangle(a,GPoint((b.getX() + a.getX())/2,(b.getY() + a.getY())/2),\
      GPoint((a.getX() + c.getX())/2,(a.getY() + c.getY())/2));

    drawTriangle(b,GPoint((b.getX() + a.getX())/2,(b.getY() + a.getY())/2),\
      GPoint((b.getX() + c.getX())/2,(b.getY() + c.getY())/2));

    drawTriangle(c,GPoint((c.getX() + a.getX())/2,(c.getY() + a.getY())/2),\
      GPoint((b.getX() + c.getX())/2,(b.getY() + c.getY())/2));

    drawS(a,GPoint((b.getX() + a.getX())/2,(b.getY() + a.getY())/2),\
      GPoint((a.getX() + c.getX())/2,(a.getY() + c.getY())/2), length, order);
    drawS(b,GPoint((b.getX() + a.getX())/2,(b.getY() + a.getY())/2),\
      GPoint((b.getX() + c.getX())/2,(b.getY() + c.getY())/2), length, order);
    drawS(c,GPoint((c.getX() + a.getX())/2,(c.getY() + a.getY())/2),\
      GPoint((b.getX() + c.getX())/2,(b.getY() + c.getY())/2), length, order);
	}
}

int main() {
  win = new GWindow(640, 480);
  double len = getReal("Please input the length of edge: ");
  int order = getInteger("Please input the order of the Sierpinski Triangle: ");
  // [TODO: fill in the code]
  drawTriangle(GPoint(320, 240 - (len)*1.747/4),\
  	GPoint(320 - len/2, 240 + (len)*1.747/4),\
  	GPoint(320 + len/2, 240 + (len)*1.747/4));
  drawS(GPoint(320, 240 - (len)*1.747/4),\
    GPoint(320 - len/2, 240 + (len)*1.747/4),\
    GPoint(320 + len/2, 240 + (len)*1.747/4),len,order);
  return 0;
}
