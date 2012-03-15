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

	Region(VPoint * s)
	{
		seed = s;
		minXborderMap = FALSE;
		maxXborderMap = FALSE;
		minYborderMap = FALSE;
		maxYborderMap = FALSE;
	}

	~Region()
	{
		delete seed ;
	}
	
};

#endif