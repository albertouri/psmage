#ifndef MapFormat_h
#define MapFormat_h

#include <fstream>
#include <string>
#include <vector>

class MapFormat
{
public:
	MapFormat();
	~MapFormat();

	void generateFile();
protected:
	std::string headerName;
	//byte byteData;
	int dataSize;
	std::string charData;
	short intData;
	int longData;
	std::vector<char> buffer;
	
private:
	template < class T >
	void writeBytes( const T s ) {
		buffer.insert(buffer.end(), reinterpret_cast<const char*>( &s ), reinterpret_cast<const char*>( &s ) + sizeof( T ));
	}

	void writeBytes( std::string text ) { buffer.insert( buffer.end(), text.begin(), text.end() ); }
	void writeHeader(std::string name, int size);
};

#endif
