#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>

#include "Voronoi.h"
#include "Region.h"
#include "VPoint.h"
#include <map>

typedef std::vector<Region*> RegionSet;
typedef std::map<VPoint *,Region *> PointToRegionMap;

typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

class RenderArea : public QWidget
{
	Q_OBJECT

public:
	static const int minRegions = 2;
	static const int maxRegions = 30;

	RenderArea(QWidget *parent = 0);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	int getNumRegions() const;
	int getMapSize() const;

public slots:
	void generateRegions(int size, int numRegions);
	void generateElevations();
	void mirroringMap();
	void generateTXT();

protected:
	void paintEvent(QPaintEvent *event);

private:
	// Voronoi objects
	vor::Voronoi * v;
	vor::Vertices * ver;
	vor::Edges * edg;
	RegionSet regions;
	PointToRegionMap pointsToRegion;

	vor::Vertices x0edges; // contains tuple of elements P1 and P2 of an edge (where P1 is on x0edge)
	vor::Vertices xMaxedges;
	vor::Vertices y0edges;
	vor::Vertices yMaxedges;

	int numRegions;
	int mapWidth;
	int mapHeight;
	bool elevations;
	bool mapMirrored;

	void generateVoroni();
	OutCode computeOutCode(VPoint *p1);
	void clipping(VPoint *p1, VPoint *p2);
};

#endif
