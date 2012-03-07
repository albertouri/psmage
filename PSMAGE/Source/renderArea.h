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
	RenderArea(QWidget *parent = 0);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	int getMaxRegions() const;

public slots:
	void setNumRegions(int numRegions);

protected:
	void paintEvent(QPaintEvent *event);

private:
	// Voronoi objects
	vor::Voronoi * v;
	vor::Vertices * ver;
	vor::Edges * edg;

	int numRegions;
	static const int maxRegions = 30;
	int mapWidth;
	int mapHeight;
};

#endif
