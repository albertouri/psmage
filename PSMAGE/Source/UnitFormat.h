#pragma once

#include <string>
#include <vector>

class UnitFormat
{
public:
						UnitFormat();
						~UnitFormat();

	std::vector<char>	buffer;

	void				newUnit(short x, short y);

private:
	template < class T >
	void writeBytes( const T s ) {
		buffer.insert(buffer.end(), reinterpret_cast<const char*>( &s ), reinterpret_cast<const char*>( &s ) + sizeof( T ));
	}
	void writeBytes( std::string text ) { buffer.insert( buffer.end(), text.begin(), text.end() ); }
	void writeBytes( std::vector<char> buffer2 ) { buffer.insert( buffer.end(), buffer2.begin(), buffer2.end() );  }
};
