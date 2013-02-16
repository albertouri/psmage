#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QtGui>
#include <QBrush>
#include <QPen>
#include <QWidget>

#include "mapGenerator.h"
#include "MapFile.h"

class RenderArea : public QWidget
{
	Q_OBJECT

public:
	static const int minRegions = 2;
	static const int maxRegions = 30;
	static const int minMinDistance = 10;
	static const int maxMinDistance = 500;

	RenderArea(QWidget *parent = 0);

	QSize minimumSizeHint() const { return QSize(601, 601); };
	QSize sizeHint() const { return QSize(601, 601); };
	int getNumRegions() const { return numRegions; };
	int getMinDistance() const { return minDistance; };
	int getMapSize() const { return renderMapHeight; };

public slots:
	void generateRegions(int numRegions, int minDistance);
	void generateElevations();
	void mirroringMap();
	void generateTXT(int size);

protected:
	void paintEvent(QPaintEvent *event);

private:
	int numRegions;
	int minDistance;
	int renderMapWidth;
	int renderMapHeight;
	MapGenerator* generator;
	bool elevations;
	bool mapMirrored;
	short** mapInfo;
};

#endif
