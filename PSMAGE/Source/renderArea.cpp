#include <QtGui>
#include <time.h>
#include "renderArea.h"
//#include "Voronoi.h"


#include <fstream>
std::ofstream fileLog("log.txt");
#define LOG(Message) fileLog << Message << std::endl

RenderArea::RenderArea(QWidget *parent)
:	QWidget(parent)
{
	mapWidth = 200;
	mapHeight = 200;
	numRegions = 10;
	elevations = FALSE;

	v = new vor::Voronoi();
	ver = new vor::Vertices();
	srand ( time(NULL) );
	generateVoroni();

	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);
}

void RenderArea::generateVoroni()
{
	regions.clear();

	// Generate random points
	for(int i=0; i<numRegions; i++) {
		VPoint *seed = new VPoint( mapWidth * (double)rand()/(double)RAND_MAX , mapHeight * (double)rand()/(double)RAND_MAX );
		ver->push_back(seed);
		Region *newRegion = new Region(seed);
		regions.push_back(newRegion);
		pointsToRegion.insert(PointToRegionMap::value_type(seed, newRegion));
	}
	// Generate Voronoi edges
	edg = v->GetEdges(ver, mapWidth, mapHeight);

	// Generate Regions Graph (and clipping edges)
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i) {
		clipping((*i)->start, (*i)->end);
		if ( !((int)(*i)->start->x == (int)(*i)->end->x && (int)(*i)->start->y == (int)(*i)->end->y) ) { // ignoring edge of length=0
			// ignoring bad borders
			if (!(((int)(*i)->start->x == 0 && (int)(*i)->end->x == 0) ||
				((int)(*i)->start->x == mapWidth && (int)(*i)->end->x == mapWidth) ||
				((int)(*i)->start->y == 0 && (int)(*i)->end->y == 0) ||
				((int)(*i)->start->y == mapHeight && (int)(*i)->end->y == mapHeight)) ) {
					PointToRegionMap::iterator found = pointsToRegion.find((*i)->left);
					Region *region1 = found->second;
					PointToRegionMap::iterator found2 = pointsToRegion.find((*i)->right);
					Region *region2 = found2->second;
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
			bool goTopY = TRUE;
			double newY = (((*i)->seed->y-x0edges[0]->y)*(x0edges[1]->x-x0edges[0]->x)-((*i)->seed->x-x0edges[0]->x)*(x0edges[1]->y-x0edges[0]->y));
			if ( newY < 0 ) goTopY = FALSE;
			(*i)->minXborderMap = TRUE;
			if (goTopY) { // we are at 0,mapHeight; check yMaxedges
				(*i)->borders.push_back(new VEdge(x0edges[0], new VPoint(0, mapHeight)));
				(*i)->maxYborderMap = TRUE;
				if (yMaxedges.size() == 2) {
					(*i)->borders.push_back(new VEdge(yMaxedges[0], new VPoint(0, mapHeight)));
				} else {
					(*i)->borders.push_back(new VEdge(new VPoint(0, mapHeight), new VPoint(mapWidth, mapHeight)));
					(*i)->maxXborderMap = TRUE;
					if (xMaxedges.size() == 2) {
						(*i)->borders.push_back(new VEdge(xMaxedges[0], new VPoint(mapWidth, mapHeight)));
					} else {
						(*i)->borders.push_back(new VEdge(new VPoint(mapWidth, 0), new VPoint(mapWidth, mapHeight)));
						(*i)->minYborderMap = TRUE;
						if (y0edges.size() == 2) { 
							(*i)->borders.push_front(new VEdge(new VPoint(mapWidth, 0), y0edges[0]));
						} else { /* UNEXPECTED END, MISSING EDGES? */ }
					}	
				}
			} else { // we are at 0,0; check y0edges
				(*i)->borders.push_back(new VEdge(x0edges[0], new VPoint(0, 0)));
				(*i)->minYborderMap = TRUE;
				if (y0edges.size() == 2) {
					(*i)->borders.push_back(new VEdge(y0edges[0], new VPoint(0, 0)));
				} else {
					(*i)->borders.push_back(new VEdge(new VPoint(0, 0), new VPoint(mapWidth, 0)));
					(*i)->maxXborderMap = TRUE;
					if (xMaxedges.size() == 2) {
						(*i)->borders.push_back(new VEdge(xMaxedges[0], new VPoint(mapWidth, 0)));
					} else {
						(*i)->borders.push_back(new VEdge(new VPoint(mapWidth, 0), new VPoint(mapWidth, mapHeight)));
						(*i)->maxYborderMap = TRUE;
						if (yMaxedges.size() == 2) { 
							(*i)->borders.push_back(new VEdge(new VPoint(mapWidth, mapHeight), yMaxedges[0]));
						} else { /* UNEXPECTED END, MISSING EDGES? */ }
					}	
				}
			}
		} else if (x0edges.size() == 4 && (int)x0edges[0]->y != (int)x0edges[2]->y) {
			(*i)->minXborderMap = TRUE;
			(*i)->borders.push_back(new VEdge(x0edges[0], x0edges[2]));
		}
		// starting on x=max edges
		else if (xMaxedges.size() == 2) {
			bool goTopY = TRUE;
			//double m = (double)(xMaxedges[1]->y - xMaxedges[0]->y) / (xMaxedges[1]->x - xMaxedges[0]->x);
			//double b = (double)xMaxedges[0]->y - (m * xMaxedges[0]->x);

			////double newX = (m * (*i)->seed->y + (*i)->seed->x - m * b) / (m * m + 1);
			//double newY = (m * m * (*i)->seed->y + m * (*i)->seed->x + b) / (m * m + 1);

			double newY = (((*i)->seed->y-xMaxedges[0]->y)*(xMaxedges[1]->x-xMaxedges[0]->x)-((*i)->seed->x-xMaxedges[0]->x)*(xMaxedges[1]->y-xMaxedges[0]->y));
			if ( newY > 0 ) goTopY = FALSE;
			//if ( newY > (*i)->seed->y ) goTopY = FALSE;
			(*i)->maxXborderMap = TRUE;
			if (goTopY) {
				(*i)->borders.push_back(new VEdge(xMaxedges[0], new VPoint(mapWidth, mapHeight)));
				(*i)->maxYborderMap = TRUE;
				if (yMaxedges.size() == 2) {
					(*i)->borders.push_back(new VEdge(yMaxedges[0], new VPoint(mapWidth, mapHeight)));
				} else {
					(*i)->borders.push_back(new VEdge(new VPoint(0, mapHeight), new VPoint(mapWidth, mapHeight)));
					(*i)->minXborderMap = TRUE;
					if (x0edges.size() == 2) {
						(*i)->borders.push_back(new VEdge(x0edges[0], new VPoint(0, mapHeight)));
					} else {
						(*i)->borders.push_back(new VEdge(new VPoint(0, 0), new VPoint(0, mapHeight)));
						(*i)->minYborderMap = TRUE;
						if (y0edges.size() == 2) { 
							(*i)->borders.push_front(new VEdge(new VPoint(0, 0), y0edges[0]));
						} else { /* UNEXPECTED END, MISSING EDGES? */ }
					}
				}
			} else {
				(*i)->borders.push_back(new VEdge(xMaxedges[0], new VPoint(mapWidth, 0)));
				(*i)->minYborderMap = TRUE;
				if (y0edges.size() == 2) {
					(*i)->borders.push_back(new VEdge(y0edges[0], new VPoint(mapWidth, 0)));
				} else {
					(*i)->borders.push_back(new VEdge(new VPoint(0, 0), new VPoint(mapWidth, 0)));
					(*i)->minXborderMap = TRUE;
					if (x0edges.size() == 2) {
						(*i)->borders.push_back(new VEdge(x0edges[0], new VPoint(0, 0)));
					} else {
						(*i)->borders.push_back(new VEdge(new VPoint(0, mapHeight), new VPoint(0, 0)));
						(*i)->maxYborderMap = TRUE;
						if (yMaxedges.size() == 2) { 
							(*i)->borders.push_front(new VEdge(new VPoint(0, mapHeight), yMaxedges[0]));
						} else { /* UNEXPECTED END, MISSING EDGES? */ }
					}
				}
			}
		} else if (xMaxedges.size() == 4 && (int)xMaxedges[0]->y != (int)xMaxedges[2]->y) {
			(*i)->maxXborderMap = TRUE;
			(*i)->borders.push_back(new VEdge(xMaxedges[0], xMaxedges[2]));
		} else if (y0edges.size() == 4 && (int)y0edges[0]->x != (int)y0edges[2]->x) {
			(*i)->minYborderMap = TRUE;
			(*i)->borders.push_back(new VEdge(y0edges[0], y0edges[2]));
		} else if (yMaxedges.size() == 4 && (int)yMaxedges[0]->x != (int)yMaxedges[2]->x) {
			(*i)->maxYborderMap = TRUE;
			(*i)->borders.push_back(new VEdge(yMaxedges[0], yMaxedges[2]));
		}

		x0edges.clear();
		xMaxedges.clear();
		y0edges.clear();
		yMaxedges.clear();
	}
}

QSize RenderArea::minimumSizeHint() const
{
	return QSize(601, 601);
	//return QSize(mapWidth, mapHeight);
}

QSize RenderArea::sizeHint() const
{
	return QSize(601, 601);
	//return QSize(mapWidth, mapHeight);
}

int RenderArea::getMapSize() const
{
	return mapHeight;
}

int RenderArea::getNumRegions() const
{
	return numRegions;
}

void RenderArea::generateRegions(int size, int numRegions)
{
	this->numRegions = numRegions;
	this->mapWidth = size;
	this->mapHeight = size;
	delete ver;
	elevations = FALSE;
	ver = new vor::Vertices();
	generateVoroni();
	update();
}

void RenderArea::generateElevations()
{
	elevations = TRUE;
	// reset all elevations info
	for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
		(*i)->elevation = 1;
	}

	// % of hills
	int percentHills = 50;
	int totalHills = (percentHills*numRegions)/100;
	int hillRegions = 0;
	while(hillRegions <= totalHills) {
		int regionID = int(regions.size() * (double)rand()/(double)RAND_MAX);
		//if ( !(regions[regionID]->minXborderMap && regions[regionID]->minYborderMap) ||
		//	!(regions[regionID]->maxXborderMap && regions[regionID]->maxYborderMap) ) {
			regions[regionID]->elevation = 2;
			hillRegions++;
		//}
	}

	update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
	QPoint points[maxRegions];
	int j = 0;
	for(vor::Vertices::iterator i = ver->begin(); i!= ver->end(); ++i) {
		points[j] = QPoint((*i)->x*(600/mapWidth), (*i)->y*(600/mapWidth));
		j++;
	}

	QPainter painter(this);

	// Draw mark
	//painter.setPen(palette().dark().color());
	//painter.drawRect(QRect(0, 0, width()-1, height()-1));

	painter.scale(600/mapWidth, 600/mapHeight);

	// Draw Regions
	if (elevations) {
		for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
			painter.setPen(QPen(Qt::green, 0));
			painter.setBrush(Qt::green);
			if ((*i)->elevation == 2) {
				painter.setBrush(Qt::yellow);
				painter.setPen(QPen(Qt::yellow, 0));
			}
			
			// Sorting vertexes of polygon
			std::vector<VEdge *> edgesVector;
			std::vector<QPoint> polyVvector;
			for(vor::Edges::iterator j = (*i)->borders.begin(); j!= (*i)->borders.end(); ++j) {
				edgesVector.push_back(*j);
			}
			polyVvector.push_back(QPoint((int)edgesVector[0]->start->x, (int)edgesVector[0]->start->y));
			polyVvector.push_back(QPoint((int)edgesVector[0]->end->x, (int)edgesVector[0]->end->y));
			edgesVector.erase(edgesVector.begin());
			while (edgesVector.size() > 0) {
				for(std::vector<VEdge *>::iterator m = edgesVector.begin(); m!= edgesVector.end(); ++m) {
					if (polyVvector.back().x() == (int)(*m)->start->x && polyVvector.back().y() == (int)(*m)->start->y) {
						polyVvector.push_back(QPoint((int)(*m)->end->x, (*m)->end->y));
						edgesVector.erase(m);
						break;
					}
					if (polyVvector.back().x() == (int)(*m)->end->x && polyVvector.back().y() == (int)(*m)->end->y) {
						polyVvector.push_back(QPoint((int)(*m)->start->x, (*m)->start->y));
						edgesVector.erase(m);
						break;
					}
				}
			}

			QPoint polyPoints[99];  // TODO better use of memory
			int k = 0;
			for(std::vector<QPoint>::iterator m = polyVvector.begin(); m!= polyVvector.end(); ++m) {
				polyPoints[k] = *m; ++k;
			}
			painter.drawPolygon(polyPoints, k);
		}
	}


	// Draw Voronoi Edges
	//painter.setPen(QPen(Qt::red, 0));
	//for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i) {
	//	painter.drawLine((*i)->start->x, (*i)->start->y, (*i)->end->x, (*i)->end->y);
	//}
	painter.setPen(palette().dark().color());
	for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
		for(vor::Edges::iterator j = (*i)->borders.begin(); j!= (*i)->borders.end(); ++j) {
			//clipping((*j)->start, (*j)->end);
			painter.drawLine((*j)->start->x, (*j)->start->y, (*j)->end->x, (*j)->end->y);
		}
	}

	painter.resetTransform();
	// Draw Random Points
	painter.setPen(QPen(Qt::blue, 3));
	painter.drawPoints(points, numRegions);

}

void RenderArea::generateTXT()
{
	// Paint ******
	// Color brushes
	QColor *Qblack = new QColor(Qt::black);
	QImage myQImage(mapWidth, mapHeight, QImage::Format_RGB32);
	QPainter painter(&myQImage);
	// Set background
	painter.fillRect(0, 0, mapWidth, mapHeight, Qt::white);
	// Draw Voronoi Edges
	painter.setBrush(Qt::black);
 	//for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i) {
 	//	painter.drawLine((*i)->start->x, (*i)->start->y, (*i)->end->x, (*i)->end->y);
 	//}
	for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
		for(vor::Edges::iterator j = (*i)->borders.begin(); j!= (*i)->borders.end(); ++j) {
			painter.drawLine((*j)->start->x, (*j)->start->y, (*j)->end->x, (*j)->end->y);
		}
	}
	painter.end();


	// Print TXT ************
	QColor *color = new QColor;
	std::ofstream fileTxt("map.txt");
	for (int i=0; i<mapWidth; i++) {
		for (int j=0; j<mapHeight; j++) {
			color->setRgb(myQImage.pixel(j,i));
			if (color->name() == Qblack->name())
				fileTxt << 1;
			else
				fileTxt << 0;
		}
		fileTxt << std::endl;
	}
	fileTxt.close();
}






// move this functions to a utils class
OutCode RenderArea::computeOutCode(VPoint *p1)
{
	OutCode code;

	code = INSIDE;          // initialised as being inside of clip window

	if (p1->x < 0)           // to the left of clip window
		code |= LEFT;
	else if (p1->x > mapWidth)      // to the right of clip window
		code |= RIGHT;
	if (p1->y < 0)           // below the clip window
		code |= BOTTOM;
	else if (p1->y > mapHeight)      // above the clip window
		code |= TOP;

	return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
// diagonal from (xmin, ymin) to (xmax, ymax).
void RenderArea::clipping(VPoint *p1, VPoint *p2)
{
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = computeOutCode(p1);
	OutCode outcode1 = computeOutCode(p2);
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
				x = p1->x + (p2->x - p1->x) * ((double)mapHeight - p1->y) / (p2->y - p1->y);
				y = (double)mapHeight;
			} else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
				x = p1->x + (p2->x - p1->x) * ((double)0 - p1->y) / (p2->y - p1->y);
				y = (double)0;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
				y = p1->y + (p2->y - p1->y) * ((double)mapWidth - p1->x) / (p2->x - p1->x);
				x = (double)mapWidth;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
				y = p1->y + (p2->y - p1->y) * ((double)0 - p1->x) / (p2->x - p1->x);
				x = (double)0;
			}
			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				p1->x = x;
				p1->y = y;
				outcode0 = computeOutCode(p1);
			} else {
				p2->x = x;
				p2->y = y;
				outcode1 = computeOutCode(p2);
			}
		}
	}
	if (!accept) {
		p1->x = 0.0;
		p1->y = 0.0;
		p2->x = 0.0;
		p2->y = 0.0;
	}

}