#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>

#include "Voronoi.h"

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
	void setMapSize(int size);
	void setNumRegions(int numRegions);
	void generateTXT();

protected:
	void paintEvent(QPaintEvent *event);

private:
	// Voronoi objects
	vor::Voronoi * v;
	vor::Vertices * ver;
	vor::Edges * edg;

	int numRegions;
	int mapWidth;
	int mapHeight;
};

#endif
