#ifndef Region_h
#define Region_h

#include "Vpoint.h"
#include "VEdge.h"
#include "Voronoi.h"

class Region
{
public:

	VPoint * seed; // seed point of the region
	// enum type of region
	std::list<Region *> neighbors; // region neighbors
	vor::Edges borders; // edges of the region
	bool minXborderMap;
	bool maxXborderMap;
	bool minYborderMap;
	bool maxYborderMap;
	short int elevation; // 0=water, 1=normal, 2=hill

	Region(VPoint * s)
	{
		seed = s;
		minXborderMap = FALSE;
		maxXborderMap = FALSE;
		minYborderMap = FALSE;
		maxYborderMap = FALSE;
		elevation = 1;
	}

	~Region()
	{
		delete seed ;
	}
	
};

#endif