#ifndef MapFormat_h
#define MapFormat_h

#include <fstream>
#include <string>
#include <vector>
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

	short width;
	short height;
};

#endif
