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

	void generateRandomPoints(int pointsToGenerate);
	void PoissonDiskSampler(double minDist, int pointsToGenerate);
	VPoint* imageToGrid(VPoint *point, double cellSize);
	bool addNextPoint(VPointMatrix &grid, std::vector<VPoint*> &activeList, std::vector<VPoint*> &pointList, VPoint* point, double minDist, double cellSize);
	VPoint* generateRandomAround(VPoint* centre, double minDist);
	double distance(VPoint* p1, VPoint* p2);

	void generateVoroni();
	RegionSet getRegions() { return regions; };

	void generateElevations();
	vor::Edges getDownToHigh() { return downToHigh; };
	vor::Edges getHighToDown() { return highToDown; };

	void mirroringMap();

private:
	int mapWidth;
	int mapHeight;

	vor::Voronoi * v;
	vor::Vertices * ver;
	vor::Edges * edg;
	RegionSet regions;

	vor::Vertices x0edges; // contains tuple of elements P1 and P2 of an edge (where P1 is on x0edge)
	vor::Vertices xMaxedges;
	vor::Vertices y0edges;
	vor::Vertices yMaxedges;

	vor::Edges downToHigh;
	vor::Edges highToDown;

	Region* getRegion(VPoint *location);
	void generateHillEdges();
};

#endif // MAP_GENERATOR_H
