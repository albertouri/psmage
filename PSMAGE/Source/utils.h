#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include "VPoint.h"

typedef int OutCode;

const int INSIDE	= 0; // 0000
const int LEFT		= 1; // 0001
const int RIGHT		= 2; // 0010
const int BOTTOM	= 4; // 0100
const int TOP		= 8; // 1000

double round(double d);
OutCode computeOutCode(double x, double y, double xMax, double yMax);
void clipping(VPoint *p1, VPoint *p2, double xMax, double yMax);

#endif // UTILS_H
