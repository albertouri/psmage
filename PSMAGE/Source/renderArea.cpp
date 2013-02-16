#include "renderArea.h"

RenderArea::RenderArea(QWidget *parent)
:	QWidget(parent)
{
	renderMapWidth = 600;
	renderMapHeight = 600;
	numRegions = 10;
	minDistance = 150;
	elevations = false;
	mapMirrored = false;

	generator = new MapGenerator(renderMapWidth, renderMapHeight);
	generator->generateRandomPoints(numRegions, (double)minDistance);
	generator->generateVoroni();

	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);

	generateElevations();
	mirroringMap();
}

void RenderArea::generateRegions(int numRegions, int minDistance)
{
	elevations = false;
	mapMirrored = false;
	generator->generateRandomPoints(numRegions, (double)minDistance);
	generator->generateVoroni();
	update();
}

void RenderArea::generateElevations()
{
	mapMirrored = false;
	elevations = true;
	generator->generateElevations();
	update();
}

void RenderArea::mirroringMap()
{
	if (!mapMirrored) {
		mapMirrored = true;
		generator->mirroringMap();
		update();
	}
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
	RegionSet regions = generator->getRegions();
	Edges downToHigh = generator->getDownToHigh();
	Edges highToDown = generator->getHighToDown();
	QPainter painter(this);

	// Draw mark
	//painter.setPen(palette().dark().color());
	//painter.drawRect(QRect(0, 0, width()-1, height()-1));

	if (mapMirrored) {
		painter.scale(0.5, 0.5);
	}

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
			for(Edges::iterator j = (*i)->borders.begin(); j!= (*i)->borders.end(); ++j) {
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
	painter.setPen(palette().dark().color());
	for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
		for(Edges::iterator j = (*i)->borders.begin(); j!= (*i)->borders.end(); ++j) {
			painter.drawLine((*j)->start->x, (*j)->start->y, (*j)->end->x, (*j)->end->y);
		}
	}

	// Draw down to high edges
	painter.setPen(QPen(Qt::red));
	for(Edges::iterator j = downToHigh.begin(); j!= downToHigh.end(); ++j) {
		painter.drawLine((*j)->start->x, (*j)->start->y, (*j)->end->x, (*j)->end->y);
	}

	// Draw high to down edges
	painter.setPen(QPen(Qt::blue));
	for(Edges::iterator j = highToDown.begin(); j!= highToDown.end(); ++j) {
		painter.drawLine((*j)->start->x, (*j)->start->y, (*j)->end->x, (*j)->end->y);
	}


	// Draw Seed Points
	painter.resetTransform();
	QPoint points[maxRegions*4]; // TODO better use of memory
	int j = 0;
	for(RegionSet::iterator i = regions.begin(); i!= regions.end(); ++i) {
		if (mapMirrored) points[j] = QPoint((*i)->seed->x*0.5, (*i)->seed->y*0.5);
		else points[j] = QPoint((*i)->seed->x, (*i)->seed->y);
		j++;
	}
	painter.setPen(QPen(Qt::blue, 3));
	painter.drawPoints(points, j);
}

void RenderArea::generateTXT(int size)
{
	RegionSet regions = generator->getRegions();
	Edges downToHigh = generator->getDownToHigh();
	Edges highToDown = generator->getHighToDown();
	// Paint ******
	// Color brushes
	QColor *Qblack = new QColor(Qt::black);
	QColor *Qblue = new QColor(Qt::blue);
	QColor *Qgreen = new QColor(Qt::green);
	QColor *Qyellow = new QColor(Qt::yellow);
	QImage myQImage(renderMapWidth*2, renderMapHeight*2, QImage::Format_RGB32);
	QPainter painter(&myQImage);
	// Set background
	painter.fillRect(0, 0, renderMapWidth*2, renderMapHeight*2, Qt::white);
	// Draw Voronoi Edges
	painter.setBrush(Qt::black);
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
			for(Edges::iterator j = (*i)->borders.begin(); j!= (*i)->borders.end(); ++j) {
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
	painter.end();

	// Scale image
	myQImage = myQImage.scaled(size, size);

	// Build Map Info ************
	QColor *color = new QColor;
	//std::ofstream fileTxt("map.txt");
	mapInfo = new short*[size];
	for (int i=0; i<size; i++) { //finalWidth
		mapInfo[i] = new short[size];
		for (int j=0; j<size; j++) { //finalHeight
			color->setRgb(myQImage.pixel(j,i));
			if (color->name() == Qblue->name())
				//fileTxt << 0;
				mapInfo[i][j] = 0;
			else if (color->name() == Qgreen->name())
				//fileTxt << 1;
				mapInfo[i][j] = 1;
			else if (color->name() == Qyellow->name())
				//fileTxt << 2;
				mapInfo[i][j] = 2;
			else
				//fileTxt << 0;
				mapInfo[i][j] = 0;
		}
		//fileTxt << std::endl;
	}
	//fileTxt.close();


	MapFile mapFile(size, size);

	mapFile.importMap(mapInfo);

	double scale = ((double)size/(double)2)/(double)renderMapWidth;
	mapFile.drawHills(downToHigh, highToDown, scale);

	mapFile.generateFile();
}