#ifndef MapFormat_h
#define MapFormat_h

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <time.h>
#include "Voronoi.h"
#include "utils.h"

struct IPoint {
	int x,y;
	IPoint(int nx, int ny) {
		x = nx; 
		y = ny;
	}
};

template <typename T, std::size_t N>
inline std::size_t sizeOfArray( T (&)[N] ) { return N; }
typedef std::map<VPoint, IPoint> VPointToIPoint;

class MapFormat {
public:
	MapFormat(short mapWidth, short mapHeight);
	~MapFormat();

	void importMap(short** mapInfo);
	void drawLineDownToHigh(int x0, int y0, int x1, int y1);
	void drawLineHighToDown(int x0, int y0, int x1, int y1);
	void drawHills(Edges edgesDownToHigh, Edges edgesHighToDown, double scale);

	std::vector<char> buffer;

	VPointToIPoint vertexMap;

protected:
	std::vector<short> normalTerrain1;
	std::vector<short> highTerrain1;
	std::vector<short> tile1;
	std::vector<short> tile2;
	std::vector<short> tile3;
	std::vector<short> tile4;
	std::vector<short> tile5;
	std::vector<short> tile6;
	std::vector<short> tile7;
	std::vector<short> tile8;
	std::vector<short> tile10;
	std::vector<short> tile11;
	
private:
	struct moveMapPoint {
		short x;
		short y;
		bool printCorner;
		bool toDown;
	};
	
	template < class T >
	void writeMapBytes( const T s ) {
		buffer.insert(buffer.end(), reinterpret_cast<const char*>( &s ), reinterpret_cast<const char*>( &s ) + sizeof( T ));
	}
	void writeMapBytes( std::string text ) { buffer.insert( buffer.end(), text.begin(), text.end() ); }

	moveMapPoint rectifyInitialPoint1(int x, int y);
	moveMapPoint rectifyInitialPoint2(int x, int y);
	moveMapPoint rectifyInitialPoint3(int x, int y);

	void	editMapTile(int x, int y, short tileId);
	int		getMapTileId(int x, int y);
	short	getMapTile(int x, int y);
	void	writeTileNormal(int x, int y);
	void	writeTileHigh(int x, int y);
	void	writeTile1(int x, int y);
	void	writeTile2(int x, int y);
	void	writeTile3(int x, int y);
	void	writeTile4(int x, int y);
	void	writeTile4b(int x, int y);
	void	writeTile5(int x, int y);
	void	writeTile6(int x, int y);
	void	writeTile7(int x, int y);
	void	writeTile7b(int x, int y);
	void	writeTile8(int x, int y);
	void	writeTile10(int x, int y);
	void	writeTile11(int x, int y);
	void	writeTile12(int x, int y);
	bool	isTileIdAtXY(short tileId, int x, int y);
	VPoint	searchTile(int seedX, int seedY, short tileId);

	bool static sortEdgesByX (const VEdge *edge1, const VEdge *edge2)
	{
		short minX1 = (short)edge1->start->x;
		if (minX1 > edge1->end->x) minX1 = (short)edge1->end->x;
		short minX2 = (short)edge2->start->x;
		if (minX2 > edge2->end->x) minX2 = (short)edge2->end->x;
		return (minX1<minX2); 
	};

	short width;
	short height;
};

#endif
