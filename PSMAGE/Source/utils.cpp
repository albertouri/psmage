#include "utils.h"

double round(double d)
{
	return floor(d + 0.5);
}

OutCode computeOutCode(double x, double y, double xMax, double yMax)
{
	OutCode code;

	code = INSIDE;          // initialized as being inside of clip window

	if (x < 0.0)		code |= LEFT;	// to the left of clip window
	else if (x > xMax)	code |= RIGHT;	// to the right of clip window
	if (y < 0.0)		code |= BOTTOM;	// below the clip window
	else if (y > yMax)	code |= TOP;	// above the clip window

	return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
// diagonal from (xmin, ymin) to (xmax, ymax).
void clipping(VPoint *p0, VPoint *p1, double xMax, double yMax)
{
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = computeOutCode(p0->x, p0->y, xMax, yMax);
	OutCode outcode1 = computeOutCode(p1->x, p1->y, xMax, yMax);
	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
			accept = true;
			break;
		} else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			double x, y;

			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode0? outcode0 : outcode1;

			// Now find the intersection point;
			// use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
			if (outcodeOut & TOP) {           // point is above the clip rectangle
				x = p0->x + (p1->x - p0->x) * (yMax - p0->y) / (p1->y - p0->y);
				y = yMax;
			} else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
				x = p0->x + (p1->x - p0->x) * (0.0 - p0->y) / (p1->y - p0->y);
				y = 0.0;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
				y = p0->y + (p1->y - p0->y) * (xMax - p0->x) / (p1->x - p0->x);
				x = xMax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
				y = p0->y + (p1->y - p0->y) * (0.0 - p0->x) / (p1->x - p0->x);
				x = 0.0;
			}
			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				p0->x = x;
				p0->y = y;
				outcode0 = computeOutCode(p0->x, p0->y, xMax, yMax);
			} else {
				p1->x = x;
				p1->y = y;
				outcode1 = computeOutCode(p1->x, p1->y, xMax, yMax);
			}
		}
	}
	if (!accept) {
		p0->x = 0.0;
		p0->y = 0.0;
		p1->x = 0.0;
		p1->y = 0.0;
	}
}