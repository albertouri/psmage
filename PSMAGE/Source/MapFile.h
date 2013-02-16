#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Voronoi.h"
#include "MapFormat.h"
#include "UnitFormat.h"

class MapFile
{
public:
			MapFile(short mapWidth, short mapHeight);
			~MapFile();
	void	importMap(short** mapInfo);
	void	drawHills(Edges edgesDownToHigh, Edges edgesHighToDown, double scale);
	void	generateFile();

private:
	short				width;
	short				height;
	std::vector<char>	buffer;
	MapFormat *			map;
	UnitFormat *		units;

	void writeHeader(std::string name, int size);

	template < class T >
	void writeBytes( const T s ) {
		buffer.insert(buffer.end(), reinterpret_cast<const char*>( &s ), reinterpret_cast<const char*>( &s ) + sizeof( T ));
	}
	void writeBytes( std::string text ) { buffer.insert( buffer.end(), text.begin(), text.end() ); }
	void writeBytes( std::vector<char> buffer2 ) { buffer.insert( buffer.end(), buffer2.begin(), buffer2.end() );  }
};
