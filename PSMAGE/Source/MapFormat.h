#ifndef MapFormat_h
#define MapFormat_h

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>


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
	short readMapTile(int x, int y);
	void writeTile1(int x, int y);
	void writeTile2(int x, int y);
	void writeTile3(int x, int y);
	void writeTile4(int x, int y);
	void writeTile5(int x, int y);
	void writeTile6(int x, int y);
	void writeTile7(int x, int y);
	void writeTile8(int x, int y);
	bool isTileXY(short tileId, int x, int y);

	short width;
	short height;
};

#endif
