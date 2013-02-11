#ifndef VPoint_h
#define VPoint_h

/*
	A structure that stores 2D point
*/

struct VPoint {
public:
	double x, y;

    VPoint(double nx, double ny) {
		x = nx; 
		y = ny;
	}

	bool operator<( const VPoint& n) const {
		if (x != n.x)
			return (x < n.x);
		return (y < n.y);
	}
};

#endif