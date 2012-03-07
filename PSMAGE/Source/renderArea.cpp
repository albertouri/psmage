#include <QtGui>
#include <time.h>
#include "renderArea.h"
#include "Voronoi.h"
#include "VPoint.h"

RenderArea::RenderArea(QWidget *parent)
:	QWidget(parent)
{
	mapWidth = 600;
	mapHeight = 600;
	numRegions = 10;

	v = new vor::Voronoi();
	ver = new vor::Vertices();

	srand ( time(NULL) );
	for(int i=0; i<numRegions; i++) {
		ver->push_back(new VPoint( mapWidth * (double)rand()/(double)RAND_MAX , mapHeight * (double)rand()/(double)RAND_MAX ));
	}
	edg = v->GetEdges(ver, mapWidth, mapHeight);

	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const
{
	return QSize(mapWidth, mapHeight);
}

QSize RenderArea::sizeHint() const
{
	return QSize(mapWidth, mapHeight);
}

int RenderArea::getMaxRegions() const
{
	return maxRegions;
}

void RenderArea::setNumRegions(int numRegions)
{
	this->numRegions = numRegions;
	delete ver;
	ver = new vor::Vertices();
	srand ( time(NULL) );
	for(int i=0; i<numRegions; i++) {
		ver->push_back(new VPoint( mapWidth * (double)rand()/(double)RAND_MAX , mapHeight * (double)rand()/(double)RAND_MAX ));
	}
	edg = v->GetEdges(ver, mapWidth, mapHeight);
	update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
	QPoint points[maxRegions];
	int j = 0;
	for(vor::Vertices::iterator i = ver->begin(); i!= ver->end(); ++i) {
		points[j] = QPoint((*i)->x, (*i)->y);
		j++;
	}

	QPainter painter(this);
	//painter.setPen(QPen(Qt::blue, 5));
	//painter.setBrush(brush);
	//if (antialiased)
	//	painter.setRenderHint(QPainter::Antialiasing, true);

	//painter.save();
	// Draw Random Points
	painter.setPen(QPen(Qt::blue, 5));
	painter.drawPoints(points, numRegions);

	// Draw Voronoi Edges
	painter.setPen(palette().dark().color());
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i) {
		painter.drawLine((*i)->start->x, (*i)->start->y, (*i)->end->x, (*i)->end->y);
	}
	//painter.restore();


	//painter.setPen(palette().dark().color());
	//painter.setBrush(Qt::NoBrush);

	painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}