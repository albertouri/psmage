#include "mapGenerator.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

MapGenerator::MapGenerator(int mapWidthIn, int mapHeightIn)
{
	mapWidth = mapWidthIn;
	mapHeight = mapHeightIn;
	v = new vor::Voronoi();
	ver = new vor::Vertices();

	srand((unsigned int)time(0));
}


void MapGenerator::generateRandomPoints(int pointsToGenerate, double minDist)
{
	delete ver;
	ver = new vor::Vertices();
	regions.clear();
	downToHigh.clear();
	highToDown.clear();

	//PoissonDiskSampler(minDist, pointsToGenerate);

	// Random points
	//for(int i=0; i<pointsToGenerate; i++) {
	//	VPoint *seed = new VPoint( mapWidth * (double)rand()/(double)RAND_MAX , mapHeight * (double)rand()/(double)RAND_MAX );
	//	ver->push_back(seed);
	//	Region *newRegion = new Region(seed);
	//	regions.push_back(newRegion);
	//}

	// Random points with minimum distance
	bool tooClose;
	int steps = 0;
	while (ver->size() < (unsigned int)pointsToGenerate && steps < 1000 ) {
		steps++;
		tooClose = false;
		VPoint *seed = new VPoint( mapWidth * (double)rand()/(double)RAND_MAX , mapHeight * (double)rand()/(double)RAND_MAX );
		for(std::vector<VPoint*>::iterator k = ver->begin(); k!= ver->end(); ++k) {
			if (distance(*k, seed) < minDist) tooClose = true;
		}
		if (!tooClose) {
			ver->push_back(seed);
			Region *newRegion = new Region(seed);
			regions.push_back(newRegion);
		}
	}
}

void MapGenerator::PoissonDiskSampler(double minDist, int pointsToGenerate)
{
	double cellSize = minDist / sqrt((double)2);
	int gridWidth = (int) (mapWidth / cellSize) + 1;
	int gridHeight = (int) (mapHeight / cellSize) + 1;

	std::vector<VPoint*> activeList;
	std::vector<VPoint*> pointList;
	VPointMatrix grid;
	grid.resize( gridHeight , std::vector<std::vector<VPoint*>>( gridWidth , NULL ) );

	//generate the first point randomly
	VPoint *firstPoint = new VPoint( mapWidth * (double)rand()/(double)RAND_MAX , mapHeight * (double)rand()/(double)RAND_MAX );

	//update containers
	activeList.push_back(firstPoint);
	pointList.push_back(firstPoint);
	VPoint *gridPoint = imageToGrid(firstPoint, cellSize);
	std::vector<VPoint*> gridCell = grid[(int)gridPoint->x][(int)gridPoint->y];
	gridCell.push_back(firstPoint);


	while (!activeList.empty()) {
		int listIndex = rand() % activeList.size();

		VPoint* point = activeList[listIndex];
		bool found = false;

		for (int k = 0; k < pointsToGenerate; k++) {
			found |= addNextPoint(grid, activeList, pointList, point, minDist, cellSize);
			if (pointList.size() == pointsToGenerate) break;
		}
		if (pointList.size() == pointsToGenerate) break;

		if (!found) {
			activeList.erase (activeList.begin()+listIndex);
		}
	}

	// Final points
	for(std::vector<VPoint*>::iterator i = pointList.begin(); i!= pointList.end(); ++i) {
		ver->push_back(*i);
		Region *newRegion = new Region(*i);
		regions.push_back(newRegion);
	}

}

VPoint* MapGenerator::imageToGrid(VPoint *point, double cellSize)
{
	double gridX = (point->x / cellSize);
	double gridY = (point->y / cellSize);
	return new VPoint(gridX, gridY);
}

bool MapGenerator::addNextPoint(VPointMatrix &grid, std::vector<VPoint*> &activeList, std::vector<VPoint*> &pointList, VPoint* point, double minDist, double cellSize)
{
	int gridWidth = (int) (mapWidth / cellSize) + 1;
	int gridHeight = (int) (mapHeight / cellSize) + 1;


	bool found = false;
	//double fraction = distribution.getDouble((int) point.x, (int) point.y);
	//VPoint* q = generateRandomAround(point, fraction * minDist);
	VPoint* q = generateRandomAround(point, minDist);

	if ((q->x >= 0) && (q->x < mapWidth) && (q->y > 0) && (q->y < mapHeight)) {
		VPoint* qIndex = imageToGrid(q, cellSize);

		bool tooClose = false;

		for (int i = std::max(0, int(qIndex->x - 2)); (i < std::min(gridWidth, int(qIndex->x + 3))) && !tooClose; i++) {
			for (int j = std::max(0, int(qIndex->y - 2)); (j < std::min(gridHeight, int(qIndex->y + 3))) && !tooClose; j++) {
				std::vector<VPoint*> gridCell = grid[i][j];
				for(std::vector<VPoint*>::iterator k = gridCell.begin(); k!= gridCell.end(); ++k) {
					// compute distance
					//if (distance(*k, q) < minDist * fraction) {
					if (distance(*k, q) < minDist) {
						tooClose = true;
					}
				}
			}
		}

		if (!tooClose) {
			found = true;
			activeList.push_back(q);
			pointList.push_back(q);
			std::vector<VPoint*> gridCell = grid[(int)qIndex->x][(int)qIndex->y];
			gridCell.push_back(q);
		}
	}

	return found;
}

/**
 * Generates a random point in the analus around the given point. The analus has inner radius minimum distance and
 * outer radius twice that.
 * 
 * @param centre
 *            The point around which the random point should be.
 * @return A new point, randomly selected.
 */
VPoint* MapGenerator::generateRandomAround(VPoint* centre, double minDist)
{
	double radius = (minDist + minDist * (double)rand()/(double)RAND_MAX);
	double angle = 2 * M_PI * (double)rand()/(double)RAND_MAX;

	double newX = radius * sin(angle);
	double newY = radius * cos(angle);

	return new VPoint(centre->x + newX, centre->y + newY);
}

// TODO add in vector 2D class
double MapGenerator::distance(VPoint* p1, VPoint* p2)
{
	double x = p2->x - p1->x;
	double y = p2->y - p1->y;
	return sqrt(x * x + y * y);
}


void MapGenerator::generateVoroni()
{
	// Generate Voronoi edges
	edg = v->GetEdges(ver, mapWidth, mapHeight);

	// Generate Regions Graph (and clipping edges)
	//LOG("Start clipping");
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i) {
		//LOG("[ IN] " << (*i)->start->x << "," << (*i)->start->y << " " << (*i)->end->x << "," << (*i)->end->y);
		clipping((*i)->start, (*i)->end, mapWidth, mapHeight);
		//LOG("[OUT] " << (*i)->start->x << "," << (*i)->start->y << " " << (*i)->end->x << "," << (*i)->end->y);
		if ( !((int)(*i)->start->x == (int)(*i)->end->x && (int)(*i)->start->y == (int)(*i)->end->y) ) { // ignoring edge of length=0
			// ignoring bad borders
			if (!(((int)(*i)->start->x == 0 && (int)(*i)->end->x == 0) ||
				((int)(*i)->start->x == mapWidth && (int)(*i)->end->x == mapWidth) ||
				((int)(*i)->start->y == 0 && (int)(*i)->end->y == 0) ||
				((int)(*i)->start->y == mapHeight && (int)(*i)->end->y == mapHeight)) ) {
					Region *region1 = getRegion((*i)->left);
					Region *region2 = getRegion((*i)->right);
					region1->neighbors.push_back(region2);
					region1->borders.push_back(*i);
					region2->neighbors.push_back(region1);
					region2->borders.push_back(*i);
			}
		}
	}

	// Generate border map edges
	for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
		// Iterate over edges of a region
		for(vor::Edges::iterator j = (*i)->borders.begin(); j!= (*i)->borders.end(); ++j) {
			// Store x=0 edges
			if ((*j)->start->x <= 0) {
				x0edges.push_back((*j)->start);
				x0edges.push_back((*j)->end);
			} else if ((*j)->end->x <= 0) {
				x0edges.push_back((*j)->end);
				x0edges.push_back((*j)->start);
			}

			// Store x=max edges
			if ((*j)->start->x >= mapWidth) {
				xMaxedges.push_back((*j)->start);
				xMaxedges.push_back((*j)->end);
			} else if ((*j)->end->x >= mapWidth) {
				xMaxedges.push_back((*j)->end);
				xMaxedges.push_back((*j)->start);
			}

			// Store y=0 edges
			if ((*j)->start->y <= 0) {
				y0edges.push_back((*j)->start);
				y0edges.push_back((*j)->end);
			} else if ((*j)->end->y <= 0) {
				y0edges.push_back((*j)->end);
				y0edges.push_back((*j)->start);
			}

			// Store y=max edges
			if ((*j)->start->y >= mapHeight) {
				yMaxedges.push_back((*j)->start);
				yMaxedges.push_back((*j)->end);
			} else if ((*j)->end->y >= mapHeight) {
				yMaxedges.push_back((*j)->end);
				yMaxedges.push_back((*j)->start);
			}	
		}

		// starting on x=0 edges
		if (x0edges.size() == 2) {
			bool goTopY = true;
			double newY = (((*i)->seed->y-x0edges[0]->y)*(x0edges[1]->x-x0edges[0]->x)-((*i)->seed->x-x0edges[0]->x)*(x0edges[1]->y-x0edges[0]->y));
			if ( newY < 0 ) goTopY = false;
			(*i)->minXborderMap = true;
			if (goTopY) { // we are at 0,mapHeight; check yMaxedges
				(*i)->borders.push_back(new VEdge(x0edges[0], new VPoint(0, mapHeight)));
				(*i)->maxYborderMap = true;
				if (yMaxedges.size() == 2) {
					(*i)->borders.push_back(new VEdge(yMaxedges[0], new VPoint(0, mapHeight)));
				} else {
					(*i)->borders.push_back(new VEdge(new VPoint(0, mapHeight), new VPoint(mapWidth, mapHeight)));
					(*i)->maxXborderMap = true;
					if (xMaxedges.size() == 2) {
						(*i)->borders.push_back(new VEdge(xMaxedges[0], new VPoint(mapWidth, mapHeight)));
					} else {
						(*i)->borders.push_back(new VEdge(new VPoint(mapWidth, 0), new VPoint(mapWidth, mapHeight)));
						(*i)->minYborderMap = true;
						if (y0edges.size() == 2) { 
							(*i)->borders.push_front(new VEdge(new VPoint(mapWidth, 0), y0edges[0]));
						} else { /* UNEXPECTED END, MISSING EDGES? */ }
					}	
				}
			} else { // we are at 0,0; check y0edges
				(*i)->borders.push_back(new VEdge(x0edges[0], new VPoint(0, 0)));
				(*i)->minYborderMap = true;
				if (y0edges.size() == 2) {
					(*i)->borders.push_back(new VEdge(y0edges[0], new VPoint(0, 0)));
				} else {
					(*i)->borders.push_back(new VEdge(new VPoint(0, 0), new VPoint(mapWidth, 0)));
					(*i)->maxXborderMap = true;
					if (xMaxedges.size() == 2) {
						(*i)->borders.push_back(new VEdge(xMaxedges[0], new VPoint(mapWidth, 0)));
					} else {
						(*i)->borders.push_back(new VEdge(new VPoint(mapWidth, 0), new VPoint(mapWidth, mapHeight)));
						(*i)->maxYborderMap = true;
						if (yMaxedges.size() == 2) { 
							(*i)->borders.push_back(new VEdge(new VPoint(mapWidth, mapHeight), yMaxedges[0]));
						} else { /* UNEXPECTED END, MISSING EDGES? */ }
					}	
				}
			}
		} else if (x0edges.size() == 4 && (int)x0edges[0]->y != (int)x0edges[2]->y) {
			(*i)->minXborderMap = true;
			(*i)->borders.push_back(new VEdge(x0edges[0], x0edges[2]));
		}
		// starting on x=max edges
		else if (xMaxedges.size() == 2) {
			bool goTopY = true;
			//double m = (double)(xMaxedges[1]->y - xMaxedges[0]->y) / (xMaxedges[1]->x - xMaxedges[0]->x);
			//double b = (double)xMaxedges[0]->y - (m * xMaxedges[0]->x);

			////double newX = (m * (*i)->seed->y + (*i)->seed->x - m * b) / (m * m + 1);
			//double newY = (m * m * (*i)->seed->y + m * (*i)->seed->x + b) / (m * m + 1);

			double newY = (((*i)->seed->y-xMaxedges[0]->y)*(xMaxedges[1]->x-xMaxedges[0]->x)-((*i)->seed->x-xMaxedges[0]->x)*(xMaxedges[1]->y-xMaxedges[0]->y));
			if ( newY > 0 ) goTopY = false;
			//if ( newY > (*i)->seed->y ) goTopY = false;
			(*i)->maxXborderMap = true;
			if (goTopY) {
				(*i)->borders.push_back(new VEdge(xMaxedges[0], new VPoint(mapWidth, mapHeight)));
				(*i)->maxYborderMap = true;
				if (yMaxedges.size() == 2) {
					(*i)->borders.push_back(new VEdge(yMaxedges[0], new VPoint(mapWidth, mapHeight)));
				} else {
					(*i)->borders.push_back(new VEdge(new VPoint(0, mapHeight), new VPoint(mapWidth, mapHeight)));
					(*i)->minXborderMap = true;
					if (x0edges.size() == 2) {
						(*i)->borders.push_back(new VEdge(x0edges[0], new VPoint(0, mapHeight)));
					} else {
						(*i)->borders.push_back(new VEdge(new VPoint(0, 0), new VPoint(0, mapHeight)));
						(*i)->minYborderMap = true;
						if (y0edges.size() == 2) { 
							(*i)->borders.push_front(new VEdge(new VPoint(0, 0), y0edges[0]));
						} else { /* UNEXPECTED END, MISSING EDGES? */ }
					}
				}
			} else {
				(*i)->borders.push_back(new VEdge(xMaxedges[0], new VPoint(mapWidth, 0)));
				(*i)->minYborderMap = true;
				if (y0edges.size() == 2) {
					(*i)->borders.push_back(new VEdge(y0edges[0], new VPoint(mapWidth, 0)));
				} else {
					(*i)->borders.push_back(new VEdge(new VPoint(0, 0), new VPoint(mapWidth, 0)));
					(*i)->minXborderMap = true;
					if (x0edges.size() == 2) {
						(*i)->borders.push_back(new VEdge(x0edges[0], new VPoint(0, 0)));
					} else {
						(*i)->borders.push_back(new VEdge(new VPoint(0, mapHeight), new VPoint(0, 0)));
						(*i)->maxYborderMap = true;
						if (yMaxedges.size() == 2) { 
							(*i)->borders.push_front(new VEdge(new VPoint(0, mapHeight), yMaxedges[0]));
						} else { /* UNEXPECTED END, MISSING EDGES? */ }
					}
				}
			}
		} else if (xMaxedges.size() == 4 && (int)xMaxedges[0]->y != (int)xMaxedges[2]->y) {
			(*i)->maxXborderMap = true;
			(*i)->borders.push_back(new VEdge(xMaxedges[0], xMaxedges[2]));
		} else if (y0edges.size() == 4 && (int)y0edges[0]->x != (int)y0edges[2]->x) {
			(*i)->minYborderMap = true;
			(*i)->borders.push_back(new VEdge(y0edges[0], y0edges[2]));
		} else if (yMaxedges.size() == 4 && (int)yMaxedges[0]->x != (int)yMaxedges[2]->x) {
			(*i)->maxYborderMap = true;
			(*i)->borders.push_back(new VEdge(yMaxedges[0], yMaxedges[2]));
		}

		x0edges.clear();
		xMaxedges.clear();
		y0edges.clear();
		yMaxedges.clear();
	}
}

Region* MapGenerator::getRegion(VPoint *location)
{
	if (location == 0) return 0;
	for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
		if ((*i)->seed->x == location->x && (*i)->seed->y == location->y)
			return (*i);
	}
	return 0;
}

void MapGenerator::generateElevations()
{
	//mapMirrored = false;
	//elevations = true;
	// reset all elevations info
	for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
		(*i)->elevation = 1;
	}

	// % of hills
	int percentHills = 50;
	int totalHills = (percentHills*regions.size())/100;
	int hillRegions = 0;
	while(hillRegions <= totalHills) {
		int regionID = int(regions.size() * (double)rand()/(double)RAND_MAX);
		regions[regionID]->elevation = 2;
		hillRegions++;
	}

	generateHillEdges();
}

void MapGenerator::generateHillEdges()
{
	downToHigh.clear();
	highToDown.clear();

	for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
		if ((*i)->elevation == 2) { // Iterate over edges of high regions
			for(vor::Edges::iterator j = (*i)->borders.begin(); j!= (*i)->borders.end(); ++j) {
				Region *leftRegion = getRegion((*j)->left);
				Region *rightRegion = getRegion((*j)->right);
				if (leftRegion != 0 && rightRegion != 0 && leftRegion->elevation !=  rightRegion->elevation ) {
					Region *downRegion = leftRegion;
					if (leftRegion->elevation == 2) downRegion = rightRegion;
					// calculate slope
					VPoint *start = (*j)->start;
					VPoint *end = (*j)->end;
					if (start->x > end->x) {
						std::swap(start, end);
					}
					double dx = end->x - start->x;
					double dy = end->y - start->y;
					double slope = 0;
					if (dx!=0) slope = dy / dx;

					double distanceToHigh = sqrt(pow((*i)->seed->x - start->x, 2) + pow((*i)->seed->y - end->y, 2));
					double distanceToDown = sqrt(pow(downRegion->seed->x - start->x, 2) + pow(downRegion->seed->y - end->y, 2));

					// check direction of the hill
					if (slope > 0) {
						if (distanceToHigh < distanceToDown) {
							highToDown.push_back(*j);
						} else {
							downToHigh.push_back(*j);
						}
					} else {
						if (round(dx) == 0 && start->y < end->y && downRegion == rightRegion) {
							std::swap((*j)->start,(*j)->end);
						}
						if (distanceToHigh < distanceToDown) {
							downToHigh.push_front(*j);
						} else {
							highToDown.push_front(*j);
						}
					}
				}

			}
		}
	}
}

void MapGenerator::mirroringMap()
{
	// --- Mirroring Y axis -----------------------
	RegionSet yRegions;
	// hard copy 
	for (RegionSet::iterator i=regions.begin();i!=regions.end();++i)  {
		Region *newRegion = new Region(**i);
		newRegion->seed = new VPoint(*(*i)->seed);
		newRegion->seed->y = (mapHeight*2)-newRegion->seed->y;
		vor::Edges::iterator o = (*i)->borders.begin();
		for(vor::Edges::iterator j = newRegion->borders.begin(); j!= newRegion->borders.end(); ++j,++o) {
			(*j) = new VEdge(**o);
			(*j)->start = new VPoint(*(*o)->start);
			(*j)->end = new VPoint(*(*o)->end);
			(*j)->start->y = (mapHeight*2)-(*j)->start->y;
			(*j)->end->y = (mapHeight*2)-(*j)->end->y;
			if ((*j)->left != 0 ) {
				(*j)->left = new VPoint(*(*o)->left);
				(*j)->left->y = (mapHeight*2)-(*j)->left->y;
			}
			if ((*j)->right != 0 ) {
				(*j)->right = new VPoint(*(*o)->right);
				(*j)->right->y = (mapHeight*2)-(*j)->right->y;
			}
		}
		yRegions.push_back(newRegion);
	}
	// concatenate vectors
	regions.insert( regions.end(), yRegions.begin(), yRegions.end() );

	// --- Mirroring X axis -----------------------
	RegionSet xRegions;
	// hard copy 
	for (RegionSet::iterator i=regions.begin();i!=regions.end();++i)  {
		Region *newRegion = new Region(**i);
		newRegion->seed = new VPoint(*(*i)->seed);
		newRegion->seed->x = (mapWidth*2)-newRegion->seed->x;
		vor::Edges::iterator o = (*i)->borders.begin();
		for(vor::Edges::iterator j = newRegion->borders.begin(); j!= newRegion->borders.end(); ++j,++o) {
			(*j) = new VEdge(**o);
			(*j)->start = new VPoint(*(*o)->start);
			(*j)->end = new VPoint(*(*o)->end);
			(*j)->start->x = (mapWidth*2)-(*j)->start->x;
			(*j)->end->x = (mapWidth*2)-(*j)->end->x;
			if ((*j)->left != 0 ) {
				(*j)->left = new VPoint(*(*o)->left);
				(*j)->left->x = (mapWidth*2)-(*j)->left->x;
			}
			if ((*j)->right != 0 ) {
				(*j)->right = new VPoint(*(*o)->right);
				(*j)->right->x = (mapWidth*2)-(*j)->right->x;
			}
		}
		xRegions.push_back(newRegion);
	}
	// concatenate vectors
	regions.insert( regions.end(), xRegions.begin(), xRegions.end() );

	// Generate hill edges
	generateHillEdges();
}