#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QtGui>
#include <QBrush>
#include <QPen>
#include <QWidget>

#include "mapGenerator.h"
#include "MapFormat.h"

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
	void generateRegions(int numRegions);
	void generateElevations();
	void mirroringMap();
	void generateTXT(int size);

protected:
	void paintEvent(QPaintEvent *event);

private:
	int numRegions;
	int renderMapWidth;
	int renderMapHeight;
	MapGenerator* generator;
	bool elevations;
	bool mapMirrored;
	short** mapInfo;
};

#endif
