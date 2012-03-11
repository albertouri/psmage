#include <QtGui>
#include <time.h>
#include "renderArea.h"
#include "Voronoi.h"
#include "VPoint.h"

#include <fstream>

RenderArea::RenderArea(QWidget *parent)
:	QWidget(parent)
{
	mapWidth = 20;
	mapHeight = 20;
	numRegions = 2;

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
	return QSize(600, 600);
	//return QSize(mapWidth, mapHeight);
}

QSize RenderArea::sizeHint() const
{
	return QSize(600, 600);
	//return QSize(mapWidth, mapHeight);
}

int RenderArea::getMapSize() const
{
	return mapHeight;
}

void RenderArea::setMapSize(int size)
{
	mapWidth = size;
	mapHeight = size;
}

int RenderArea::getNumRegions() const
{
	return numRegions;
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
		points[j] = QPoint((*i)->x*(600/mapWidth), (*i)->y*(600/mapWidth));
		j++;
	}

	QPainter painter(this);

	// Draw mark
	painter.setPen(palette().dark().color());
	painter.drawRect(QRect(0, 0, width()-1, height()-1));

	// Draw Random Points
	painter.setPen(QPen(Qt::blue, 3));
	painter.drawPoints(points, numRegions);

	painter.scale(600/mapWidth, 600/mapHeight);
	// Draw Voronoi Edges
	painter.setPen(palette().dark().color());
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i) {
		painter.drawLine((*i)->start->x, (*i)->start->y, (*i)->end->x, (*i)->end->y);
	}

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
	for(vor::Edges::iterator i = edg->begin(); i!= edg->end(); ++i) {
		painter.drawLine((*i)->start->x, (*i)->start->y, (*i)->end->x, (*i)->end->y);
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