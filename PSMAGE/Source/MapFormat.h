#ifndef MapFormat_h
#define MapFormat_h

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include "Voronoi.h"
#include "utils.h"


template <typename T, std::size_t N>
inline std::size_t sizeOfArray( T (&)[N] ) { return N; }

class MapFormat
{
public:
	MapFormat(short mapWidth, short mapHeight);
	~MapFormat();

	void generateFile();
	void importMap(short** mapInfo);
	void drawLineDownToHigh(int x0, int y0, int x1, int y1);
	void drawLineDownToHigh(vor::Edges edges, double scale);
	void drawLineHighToDown(int x0, int y0, int x1, int y1);
	void drawLineHighToDown(vor::Edges edges, double scale);
protected:
	std::string headerName;
	int dataSize;
	std::string charData;
	short intData;
	int longData;
	std::vector<char> buffer;
	std::vector<char> mapBuffer;
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
	void writeBytes( const T s ) {
		buffer.insert(buffer.end(), reinterpret_cast<const char*>( &s ), reinterpret_cast<const char*>( &s ) + sizeof( T ));
	}
	void writeBytes( std::string text ) { buffer.insert( buffer.end(), text.begin(), text.end() ); }
	void writeBytes( std::vector<char> buffer2 ) { buffer.insert( buffer.end(), buffer2.begin(), buffer2.end() );  }
	template < class T >
	void writeMapBytes( const T s ) {
		mapBuffer.insert(mapBuffer.end(), reinterpret_cast<const char*>( &s ), reinterpret_cast<const char*>( &s ) + sizeof( T ));
	}
	void writeMapBytes( std::string text ) { mapBuffer.insert( mapBuffer.end(), text.begin(), text.end() ); }

	void writeHeader(std::string name, int size);

	moveMapPoint rectifyInitialPoint1(int x, int y);
	moveMapPoint rectifyInitialPoint2(int x, int y);

	void editMapTile(int x, int y, short tileId);
	short getMapTile(int x, int y);
	void writeTileNormal(int x, int y);
	void writeTileHigh(int x, int y);
	void writeTile1(int x, int y);
	void writeTile2(int x, int y);
	void writeTile3(int x, int y);
	void writeTile4(int x, int y);
	void writeTile4b(int x, int y);
	void writeTile5(int x, int y);
	void writeTile6(int x, int y);
	void writeTile7(int x, int y);
	void writeTile7b(int x, int y);
	void writeTile8(int x, int y);
	void writeTile10(int x, int y);
	void writeTile11(int x, int y);
	void writeTile12(int x, int y);
	bool isTileIdAtXY(short tileId, int x, int y);

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
