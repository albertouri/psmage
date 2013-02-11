#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <time.h>
#include <algorithm>

#include "utils.h"
#include "Voronoi.h"
#include "Region.h"

typedef std::vector<Region*> RegionSet;
typedef std::vector<std::vector<std::vector<VPoint*>>> VPointMatrix;

class MapGenerator
{
public:
	MapGenerator() {};
	MapGenerator(int mapWidthIn, int mapHeightIn);

	void generateRandomPoints(int pointsToGenerate, double minDist);
	void PoissonDiskSampler(double minDist, int pointsToGenerate);
	VPoint* imageToGrid(VPoint *point, double cellSize);
	bool addNextPoint(VPointMatrix &grid, std::vector<VPoint*> &activeList, std::vector<VPoint*> &pointList, VPoint* point, double minDist, double cellSize);
	VPoint* generateRandomAround(VPoint* centre, double minDist);
	double distance(VPoint* p1, VPoint* p2);

	void generateVoroni();
	RegionSet getRegions() { return regions; };

	void generateElevations();
	Edges getDownToHigh() { return downToHigh; };
	Edges getHighToDown() { return highToDown; };

	void mirroringMap();

	Vertices * ver;

private:
	int mapWidth;
	int mapHeight;

	Voronoi * v;
	Edges * edg;
	RegionSet regions;

	Vertices x0edges; // contains tuple of elements P1 and P2 of an edge (where P1 is on x0edge)
	Vertices xMaxedges;
	Vertices y0edges;
	Vertices yMaxedges;

	Edges downToHigh;
	Edges highToDown;

	Region* getRegion(VPoint *location);
	void generateHillEdges();
};

#endif // MAP_GENERATOR_H
