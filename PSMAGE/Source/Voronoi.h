#pragma once
#ifndef Voronoi_h
#define Voronoi_h

#include <list>
#include <queue>
#include <set>

#include "VPoint.h"
#include "VEdge.h"
#include "VParabola.h"
#include "VEvent.h"
#include <functional>

#include <fstream>
extern std::ofstream fileLog;
#define LOG(Message) fileLog << Message << std::endl

typedef std::vector<VPoint *>	Vertices;
typedef std::list<VEdge *>		Edges;

class Voronoi {
public:
	Voronoi();
	
	Edges *			GetEdges(Vertices * v, int width, int height); // top left corner is (0, 0)

private:

	Vertices *		places;
	Edges *			edges;
	double			width;
	double			height;
	VParabola *		root;	// that represents a beachline sequence
	double			ly;		//current "y" position of the line (see Fortune's algorithm)

	std::set<VEvent *>	deleted; // set  of deleted (false) Events (since we can not delete from PriorityQueue)
	std::vector<VPoint *> points; // list of all new points that were created during the algorithm
	std::priority_queue<VEvent *, std::vector<VEvent *>, VEvent::CompareEvent> queue;  // events to process

	void		InsertParabola(VPoint * p); // processing the place event
	void		RemoveParabola(VEvent * e); // processing the circle event
	void		FinishEdge(VParabola * n); // recursively finishes all infinite edges in the tree
	double		GetXOfEdge(VParabola * par, double y); // returns the current x position of an intersection point of left and right parabolas
	VParabola * GetParabolaByX(double xx); // returns the Parabola that is under this "x" position in the current beachline
	double		GetY(VPoint * p, double x);
	void		CheckCircle(VParabola * b); // checks the circle event (disappearing) of this parabola
	VPoint *	GetEdgeIntersection(VEdge * a, VEdge * b);
};

#endif