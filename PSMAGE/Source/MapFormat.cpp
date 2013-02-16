#include "MapFormat.h"


MapFormat::MapFormat(short mapWidth, short mapHeight)
{
	width = mapWidth;
	height = mapHeight;
	static const short const1[] = {32,33,34,35,36,37,38,39,40,42,43,44,45,46,48,49,50,51,52,53,54,55,56,58,59,60,61,62};
	std::vector<short> vector1(const1, const1+sizeOfArray(const1));
	normalTerrain1.insert( normalTerrain1.end(), vector1.begin(), vector1.end() );

	static const short const2[] = {64,65,66,67,68,69,70,71,72,74,75,76,77,78,80,81,82,83,84,85,86,87,88,90,91,92,93,94};
	std::vector<short> vector2(const2, const2+sizeOfArray(const2));
	highTerrain1.insert( highTerrain1.end(), vector2.begin(), vector2.end() );

	static const short const3[] = {0x0341,0x0351,0x0361,0x0371,0x0381,0x0391};
	std::vector<short> vector3(const3, const3+sizeOfArray(const3));
	tile1.insert( tile1.end(), vector3.begin(), vector3.end() );

	static const short const4[] = {0x03a0,0x03b0,0x03c0,0x03d0,0x03e0,0x03f0};
	std::vector<short> vector4(const4, const4+sizeOfArray(const4));
	tile2.insert( tile2.end(), vector4.begin(), vector4.end() );

	static const short const5[] = {0x0410,0x0423,0x0433,0x0443,0x0453,0x042a,0x043a,0x044a,0x045a};
	std::vector<short> vector5(const5, const5+sizeOfArray(const5));
	tile3.insert( tile3.end(), vector5.begin(), vector5.end() );

	static const short const6[] = {0x04c1,0x04d1,0x0613,0x04e1,0x04f1};
	std::vector<short> vector6(const6, const6+sizeOfArray(const6));
	tile4.insert( tile4.end(), vector6.begin(), vector6.end() );

	static const short const7[] = {0x04c0,0x04d0,0x05d1,0x04e2,0x04f2};
	std::vector<short> vector7(const7, const7+sizeOfArray(const7));
	tile5.insert( tile5.end(), vector7.begin(), vector7.end() );

	static const short const8[] = {0x0462,0x0472,0x0482,0x0492,0x04a2,0x04b2};
	std::vector<short> vector8(const8, const8+sizeOfArray(const8));
	tile6.insert( tile6.end(), vector8.begin(), vector8.end() );

	static const short const9[] = {0x0502,0x0512,0x0521,0x0531,0x0623,0x0633};
	std::vector<short> vector9(const9, const9+sizeOfArray(const9));
	tile7.insert( tile7.end(), vector9.begin(), vector9.end() );

	static const short const10[] = {0x03a3,0x03b3,0x0500,0x0510,0x03c3,0x03d3,0x0522,0x0532,0x05e3,0x05f3};
	std::vector<short> vector10(const10, const10+sizeOfArray(const10));
	tile8.insert( tile8.end(), vector10.begin(), vector10.end() );

	static const short const11[] = {0x02e3,0x02f3,0x02c3,0x02d3};
	std::vector<short> vector11(const11, const11+sizeOfArray(const11));
	tile10.insert( tile10.end(), vector11.begin(), vector11.end() );

	static const short const12[] = {0x0322,0x0332,0x0302,0x0312,0x05a2};
	std::vector<short> vector12(const12, const12+sizeOfArray(const12));
	tile11.insert( tile11.end(), vector12.begin(), vector12.end() );

}

MapFormat::~MapFormat()
{
}

void MapFormat::importMap(short** mapInfo)
{
	int randomTile;
	for (int x=0; x<width; x++) {
		for (int y=0; y<height; y++) {
			if (mapInfo[x][y] == 1) {
				randomTile = rand() % normalTerrain1.size();
				writeMapBytes((short)normalTerrain1[randomTile]);
			} else if (mapInfo[x][y] == 2) {
				randomTile = rand() % highTerrain1.size();
				writeMapBytes((short)highTerrain1[randomTile]);
			} else {
				writeMapBytes((short)41);
			}
		}
	}
}

void MapFormat::editMapTile(int x, int y, short tileId)
{
	y = height - y; // adjust origin to left-down corner
	if (x >= width || y >= height || x < 0 || y < 0) return;
	const char *tile;
	tile = reinterpret_cast<const char*>( &tileId );
	buffer[(x*2)+(y*2*width)]	= tile[0];
	buffer[(x*2)+(y*2*width)+1]	= tile[1];
}

short MapFormat::getMapTile(int x, int y)
{
	y = height - y; // adjust origin to left-down corner
	if (x >= width || y >= height || x < 0 || y < 0) return 0;
	unsigned char tile[2];
	tile[0] = buffer[(x*2)+(y*2*width)];
	tile[1] = buffer[(x*2)+(y*2*width)+1];
	short result = (short(tile[1]) << 8) + short(tile[0]);
	return result;
}

void MapFormat::writeTileNormal(int x, int y)
{
	int randomTile = rand() % normalTerrain1.size();
	editMapTile(x, y, (short)normalTerrain1[randomTile]);
}

void MapFormat::writeTileHigh(int x, int y)
{
	int randomTile = rand() % highTerrain1.size();
	editMapTile(x, y, (short)highTerrain1[randomTile]);
}

void MapFormat::writeTile1(int x, int y)
{
	editMapTile(x, y  , (short)0x0341); editMapTile(x+1, y  , (short)0x0351);
	editMapTile(x, y-1, (short)0x0361); editMapTile(x+1, y-1, (short)0x0371);
	editMapTile(x, y-2, (short)0x0381); editMapTile(x+1, y-2, (short)0x0391);
	// sanitize check  // TODO it doesn't work
	if (isTileIdAtXY(21, x, y+1)) writeTileHigh(x, y+1);
	if (isTileIdAtXY(21, x+1, y+1)) writeTileHigh(x+1, y+1);
}

void MapFormat::writeTile2(int x, int y)
{
	editMapTile(x, y  , (short)0x03a0); editMapTile(x+1, y  , (short)0x03b0);
	editMapTile(x, y-1, (short)0x03c0); editMapTile(x+1, y-1, (short)0x03d0);
	editMapTile(x, y-2, (short)0x03e0); editMapTile(x+1, y-2, (short)0x03f0);
	// sanitize check  // TODO it doesn't work
	if (isTileIdAtXY(21, x, y+1)) writeTileHigh(x, y+1);
	if (isTileIdAtXY(21, x+1, y+1)) writeTileHigh(x+1, y+1);
}

void MapFormat::writeTile3(int x, int y)
{
	writeTileNormal(x, y+1); editMapTile(x+1, y+1, (short)0x0410);
	editMapTile(x, y  , (short)0x0423); editMapTile(x+1, y  , (short)0x0433);
	editMapTile(x, y-1, (short)0x0443); editMapTile(x+1, y-1, (short)0x0453);
	writeTile10(x+2, y+1);
}

void MapFormat::writeTile4(int x, int y)
{
																				editMapTile(x, y  , (short)0x04c1); editMapTile(x+1, y  , (short)0x04d1);
										  editMapTile(x-1, y-1, (short)0x0613);	editMapTile(x, y-1, (short)0x04e1); editMapTile(x+1, y-1, (short)0x04f1);
	editMapTile(x-2, y-2, (short)0x0423); editMapTile(x-1, y-2, (short)0x0433);
	editMapTile(x-2, y-3, (short)0x0443); editMapTile(x-1, y-3, (short)0x0453);
}

void MapFormat::writeTile4b(int x, int y)
{
	writeTileNormal(x-2, y+1);			  editMapTile(x-1, y+1, (short)0x0410);
	editMapTile(x-2, y  , (short)0x0423); editMapTile(x-1, y  , (short)0x0433); editMapTile(x, y  , (short)0x04c1); editMapTile(x+1, y  , (short)0x04d1);
	editMapTile(x-2, y-1, (short)0x0443); editMapTile(x-1, y-1, (short)0x0613);	editMapTile(x, y-1, (short)0x04e1); editMapTile(x+1, y-1, (short)0x04f1);
}

void MapFormat::writeTile5(int x, int y)
{
																				editMapTile(x, y  , (short)0x04c0); editMapTile(x+1, y  , (short)0x04d0);
										  editMapTile(x-1, y-1, (short)0x05d1);	editMapTile(x, y-1, (short)0x04e2); editMapTile(x+1, y-1, (short)0x04f2);
	editMapTile(x-2, y-2, (short)0x042a); editMapTile(x-1, y-2, (short)0x043a);
	editMapTile(x-2, y-3, (short)0x044a); editMapTile(x-1, y-3, (short)0x045a);
}

void MapFormat::writeTile6(int x, int y)
{
	editMapTile(x, y  , (short)0x0462); editMapTile(x+1, y  , (short)0x0472);
	editMapTile(x, y-1, (short)0x0482); editMapTile(x+1, y-1, (short)0x0492);
	editMapTile(x, y-2, (short)0x04a2); editMapTile(x+1, y-2, (short)0x04b2);
}

void MapFormat::writeTile7(int x, int y)
{
																				editMapTile(x, y  , (short)0x0462); editMapTile(x+1, y  , (short)0x0472);
	editMapTile(x-2, y-1, (short)0x0502); editMapTile(x-1, y-1, (short)0x0512); editMapTile(x, y-1, (short)0x0482); editMapTile(x+1, y-1, (short)0x0492);
	editMapTile(x-2, y-2, (short)0x0521); editMapTile(x-1, y-2, (short)0x0531); editMapTile(x, y-2, (short)0x0623); editMapTile(x+1, y-2, (short)0x0633);
}

void MapFormat::writeTile7b(int x, int y)
{
	editMapTile(x-2, y-1, (short)0x0502); editMapTile(x-1, y-1, (short)0x0512); editMapTile(x, y-1, (short)0x0482); editMapTile(x+1, y-1, (short)0x0492);
	editMapTile(x-2, y-2, (short)0x0521); editMapTile(x-1, y-2, (short)0x0531); editMapTile(x, y-2, (short)0x0623); editMapTile(x+1, y-2, (short)0x0633);
}

void MapFormat::writeTile8(int x, int y)
{
																				editMapTile(x, y  , (short)0x03a3); editMapTile(x+1, y  , (short)0x03b3);
	editMapTile(x-2, y-1, (short)0x0500); editMapTile(x-1, y-1, (short)0x0510); editMapTile(x, y-1, (short)0x03c3); editMapTile(x+1, y-1, (short)0x03d3);
	editMapTile(x-2, y-2, (short)0x0522); editMapTile(x-1, y-2, (short)0x0532); editMapTile(x, y-2, (short)0x05e3); editMapTile(x+1, y-2, (short)0x05f3);
	// sanitize check
	writeTileHigh(x+1, y+1);
}

void MapFormat::writeTile10(int x, int y)
{
	editMapTile(x, y+1, (short)0x02e3); editMapTile(x+1, y+1, (short)0x02f3);
	editMapTile(x, y  , (short)0x02c3); editMapTile(x+1, y  , (short)0x02d3);
}

void MapFormat::writeTile11(int x, int y)
{
	editMapTile(x, y+1, (short)0x0322); editMapTile(x+1, y+1, (short)0x0332);
	editMapTile(x, y  , (short)0x0302); editMapTile(x+1, y  , (short)0x0312);
}

void MapFormat::writeTile12(int x, int y)
{
	editMapTile(x, y+1, (short)0x05a2); editMapTile(x+1, y+1, (short)0x05b2);
	editMapTile(x, y  , (short)0x0302); editMapTile(x+1, y  , (short)0x0312);
}


bool MapFormat::isTileIdAtXY(short tileId, int x, int y)
{
	short tileStored = getMapTile(x, y);
	switch (tileId) {
		case 0: return std::find(normalTerrain1.begin(), normalTerrain1.end(), tileStored)!=normalTerrain1.end() || 
					   std::find(highTerrain1.begin(), highTerrain1.end(), tileStored)!=highTerrain1.end() ||
					   tileStored == (short)41 || // special case while debugging
					   tileStored == 0; // out of map
		case 1: return std::find(tile1.begin(), tile1.end(), tileStored)!=tile1.end();
		case 2: return std::find(tile2.begin(), tile2.end(), tileStored)!=tile2.end();
		case 3: return std::find(tile3.begin(), tile3.end(), tileStored)!=tile3.end();
		case 4: return std::find(tile4.begin(), tile4.end(), tileStored)!=tile4.end();
		case 5: return std::find(tile5.begin(), tile5.end(), tileStored)!=tile5.end();
		case 6: return std::find(tile6.begin(), tile6.end(), tileStored)!=tile6.end();
		case 7: return std::find(tile7.begin(), tile7.end(), tileStored)!=tile7.end();
		case 8: return std::find(tile8.begin(), tile8.end(), tileStored)!=tile8.end();
		case 10: return std::find(tile10.begin(), tile10.end(), tileStored)!=tile10.end();
		case 11: return std::find(tile11.begin(), tile11.end(), tileStored)!=tile11.end();
		case 21: return std::find(normalTerrain1.begin(), normalTerrain1.end(), tileStored)!=normalTerrain1.end();
		case 22: return std::find(highTerrain1.begin(), highTerrain1.end(), tileStored)!=highTerrain1.end();
		default: return false;
	}
}

int MapFormat::getMapTileId(int x, int y)
{
	short tileStored = getMapTile(x, y);
	if (std::find(normalTerrain1.begin(), normalTerrain1.end(), tileStored)!=normalTerrain1.end() || 
	    std::find(highTerrain1.begin(), highTerrain1.end(), tileStored)!=highTerrain1.end() ||
	    tileStored == (short)41 || // special case while debugging
	    tileStored == 0) // out of map
			return 0;
	else if (std::find(tile1.begin(), tile1.end(), tileStored)!=tile1.end())
		return 1;
	else if (std::find(tile2.begin(), tile2.end(), tileStored)!=tile2.end())
		return 2;
	else if (std::find(tile3.begin(), tile3.end(), tileStored)!=tile3.end())
		return 3;
	else if (std::find(tile4.begin(), tile4.end(), tileStored)!=tile4.end())
		return 4;
	else if (std::find(tile5.begin(), tile5.end(), tileStored)!=tile5.end())
		return 5;
	else if (std::find(tile6.begin(), tile6.end(), tileStored)!=tile6.end())
		return 6;
	else if (std::find(tile7.begin(), tile7.end(), tileStored)!=tile7.end())
		return 7;
	else if (std::find(tile8.begin(), tile8.end(), tileStored)!=tile8.end())
		return 8;
	else if (std::find(tile10.begin(), tile10.end(), tileStored)!=tile10.end())
		return 10;
	else if (std::find(tile11.begin(), tile11.end(), tileStored)!=tile11.end())
		return 11;
	else if (std::find(normalTerrain1.begin(), normalTerrain1.end(), tileStored)!=normalTerrain1.end())
		return 21;
	else if (std::find(highTerrain1.begin(), highTerrain1.end(), tileStored)!=highTerrain1.end())
		return 22;
	else
		return 99;
}

MapFormat::moveMapPoint MapFormat::rectifyInitialPoint1(int x, int y)
{
	moveMapPoint move;
	int x0 = x; 
	int y0 = y;
	LOG("rectifyInitialPoint1 head from: " << x << "," << y);
	LOG(getMapTile(x-3, y+3) << "\t" << getMapTile(x-2, y+3) << "\t" << getMapTile(x-1, y+3) << "\t" << getMapTile(x, y+3) << "\t" << getMapTile(x+1, y+3) << "\t" << getMapTile(x+2, y+3));
	LOG(getMapTile(x-3, y+2) << "\t" << getMapTile(x-2, y+2) << "\t" << getMapTile(x-1, y+2) << "\t" << getMapTile(x, y+2) << "\t" << getMapTile(x+1, y+2) << "\t" << getMapTile(x+2, y+2));
	LOG(getMapTile(x-3, y+1) << "\t" << getMapTile(x-2, y+1) << "\t" << getMapTile(x-1, y+1) << "\t" << getMapTile(x, y+1) << "\t" << getMapTile(x+1, y+1) << "\t" << getMapTile(x+2, y+1));
	LOG(getMapTile(x-3, y  ) << "\t" << getMapTile(x-2, y  ) << "\t" << getMapTile(x-1, y  ) << "\t[" << getMapTile(x, y  ) << "]\t" << getMapTile(x+1, y  ) << "\t" << getMapTile(x+2, y  ));
	LOG(getMapTile(x-3, y-1) << "\t" << getMapTile(x-2, y-1) << "\t" << getMapTile(x-1, y-1) << "\t" << getMapTile(x, y-1) << "\t" << getMapTile(x+1, y-1) << "\t" << getMapTile(x+2, y-1));
	LOG(getMapTile(x-3, y-2) << "\t" << getMapTile(x-2, y-2) << "\t" << getMapTile(x-1, y-2) << "\t" << getMapTile(x, y-2) << "\t" << getMapTile(x+1, y-2) << "\t" << getMapTile(x+2, y-2));

	// down to down conditions
	if (isTileIdAtXY(6, x, y) || isTileIdAtXY(6, x+1, y-1) || isTileIdAtXY(6, x+3, y-1) || isTileIdAtXY(8, x, y)) {
		if (!isTileIdAtXY(6, x, y) && !isTileIdAtXY(8, x, y)) {
			y -= 1;
			if (isTileIdAtXY(6, x+1, y)) x += 1;
			else if (isTileIdAtXY(6, x+3, y)) x += 3;
		}
		short moves = 1;
		while (moves != 0) {
			moves = 0;
			while (!isTileIdAtXY(0, x, y+1)) {
				y += 1;
				moves += 1;
			}
			while (!isTileIdAtXY(0, x+1, y)) {
				x += 1;
				moves += 1;
			}
		}
		move.x = x - x0;
		move.y = y - y0;
		if (isTileIdAtXY(6, x, y) && (isTileIdAtXY(2, x-2, y-1) || isTileIdAtXY(8, x-2, y-1))) {
			writeTileHigh(x,y); writeTileHigh(x-1,y);
			move.x -= 1;
		} else if (isTileIdAtXY(8, x, y)) {
			move.x += 1;
			move.y += 1;
		} else if (isTileIdAtXY(7, x-2, y-1)) {
			writeTile8(x-1,y);
			move.x += 1;
			move.y += 1;
		}
		move.printCorner = false;
		move.toDown = true;
		return move;
	}

	// down to up conditions
	else {
		if (isTileIdAtXY(0, x, y)) {
			if (!isTileIdAtXY(0, x-2, y)) x -= 2;
			else if (!isTileIdAtXY(0, x-3, y)) x -= 3;
			else if (!isTileIdAtXY(0, x+2, y)) x += 2;
			else if (!isTileIdAtXY(0, x, y-2)) y -= 2;
			else if (!isTileIdAtXY(0, x, y+2)) y += 2;
			else {
				move.x = 0;
				move.y = 0;
				move.printCorner = true;
				move.toDown = false;
				return move;
			}
		}
		short moves = 1;
		while (moves != 0) {
			moves = 0;
			while (!isTileIdAtXY(0, x, y-1)) {
				y -= 1;
				moves += 1;
			}
			while (!isTileIdAtXY(0, x+1, y)) {
				x += 1;
				moves += 1;
			}
		}

		move.x = x - x0;
		move.y = y - y0;
		if (isTileIdAtXY(1, x, y)) {
			move.x += 1;
			move.y += 2;
		} else if (isTileIdAtXY(2, x, y)) {
			LOG("Diference 1");
			writeTileHigh(x,y+2); writeTileHigh(x-1,y+2);
			move.x -= 1;
			move.y += 1;
		} else {
			LOG("[ERROR] finding initial position at rectifyInitialPoint1 " << x << "'" << y << " = " << getMapTile(x, y));
		}
		move.printCorner = false;
		move.toDown = false;
		return move;
	}
}

MapFormat::moveMapPoint MapFormat::rectifyInitialPoint2(int x, int y)
{
	moveMapPoint move;
	int x0 = x; 
	int y0 = y;
 	LOG("rectifyInitialPoint2 head from: " << x << "," << y);
	LOG(getMapTileId(x-3, y+3) << "\t" << getMapTileId(x-2, y+3) << "\t" << getMapTileId(x-1, y+3) << "\t" << getMapTileId(x, y+3) << "\t" << getMapTileId(x+1, y+3) << "\t" << getMapTileId(x+2, y+3));
	LOG(getMapTileId(x-3, y+2) << "\t" << getMapTileId(x-2, y+2) << "\t" << getMapTileId(x-1, y+2) << "\t" << getMapTileId(x, y+2) << "\t" << getMapTileId(x+1, y+2) << "\t" << getMapTileId(x+2, y+2));
	LOG(getMapTileId(x-3, y+1) << "\t" << getMapTileId(x-2, y+1) << "\t" << getMapTileId(x-1, y+1) << "\t" << getMapTileId(x, y+1) << "\t" << getMapTileId(x+1, y+1) << "\t" << getMapTileId(x+2, y+1));
	LOG(getMapTileId(x-3, y  ) << "\t" << getMapTileId(x-2, y  ) << "\t" << getMapTileId(x-1, y  ) << "\t[" << getMapTileId(x, y  ) << "]\t" << getMapTileId(x+1, y  ) << "\t" << getMapTileId(x+2, y  ));
	LOG(getMapTileId(x-3, y-1) << "\t" << getMapTileId(x-2, y-1) << "\t" << getMapTileId(x-1, y-1) << "\t" << getMapTileId(x, y-1) << "\t" << getMapTileId(x+1, y-1) << "\t" << getMapTileId(x+2, y-1));
	LOG(getMapTileId(x-3, y-2) << "\t" << getMapTileId(x-2, y-2) << "\t" << getMapTileId(x-1, y-2) << "\t" << getMapTileId(x, y-2) << "\t" << getMapTileId(x+1, y-2) << "\t" << getMapTileId(x+2, y-2));

	// down to down conditions
// 	if (isTileIdAtXY(11, x, y) && isTileIdAtXY(6, x+3, y-1)) {
// 		writeTile8(x+2,y+1);
// 		move.x = 4;
// 		move.y = 2;
// 		move.printCorner = false;
// 		move.toDown = true;
// 		return move;
// 	}

	if (isTileIdAtXY(11, x, y)) {
		writeTile6(x,y+2);
		writeTile12(x,y-1);
		move.x = 0;
		move.y = 2;
		move.printCorner = false;
		move.toDown = true;
		return move;
	}

	else if (isTileIdAtXY(6, x, y) || isTileIdAtXY(6, x+1, y-1) || isTileIdAtXY(6, x+3, y-1)) {
		//LOG("Tile 6 detected");
		if (!isTileIdAtXY(6, x, y)) {
			y -= 1;
			if (isTileIdAtXY(6, x+1, y)) x += 1;
			else if (isTileIdAtXY(6, x+3, y)) x += 3;
		}
		short moves = 1;
		while (moves != 0) {
			moves = 0;
			while (!isTileIdAtXY(0, x, y+1)) {
				y += 1;
				moves += 1;
			}
			while (!isTileIdAtXY(0, x+1, y)) {
				x += 1;
				moves += 1;
			}
		}
		move.x = x - x0;
		move.y = y - y0;
		if (isTileIdAtXY(2, x-2, y-1) || isTileIdAtXY(8, x-2, y-1)) {
			writeTileHigh(x,y); writeTileHigh(x-1,y);
			move.x -= 1;
		} else if (isTileIdAtXY(7, x-2, y-1)) {
			writeTile8(x-1,y);
			move.x += 1;
			move.y += 1;
		}
		move.printCorner = false;
		move.toDown = true;
		return move;
	}

	// down to up conditions
	else {
		if (isTileIdAtXY(0, x, y)) {
			if (!isTileIdAtXY(0, x-2, y)) x -= 2;
			else if (!isTileIdAtXY(0, x-3, y)) x -= 3;
			else if (!isTileIdAtXY(0, x+2, y)) x += 2;
			else if (!isTileIdAtXY(0, x, y-2)) y -= 2;
			else if (!isTileIdAtXY(0, x, y+2)) y += 2;
			else {
				LOG("No neighboor tile found at " << x << "," << y);
				move.x = 0;
				move.y = 0;
				move.printCorner = true;
				move.toDown = false;
				return move;
			}
		}
		short moves = 1;
		while (moves != 0) {
			moves = 0;
			while (!isTileIdAtXY(0, x, y-1)) {
				y -= 1;
				moves += 1;
			}
			while (!isTileIdAtXY(0, x+1, y)) {
				x += 1;
				moves += 1;
			}
		}

		move.x = x - x0;
		move.y = y - y0;
		if (isTileIdAtXY(1, x, y)) {
			move.x += 1;
			move.y += 2;
		} else if (isTileIdAtXY(2, x, y)) {
			LOG("Diference 2");
			//writeTileHigh(x,y+2); writeTileHigh(x-1,y+2); // DIFERENCE FROM function1
			move.x -= 1;
			move.y += 2; // move.y += 1; DIFERENCE FROM function1
		}
		move.printCorner = false;
		move.toDown = false;
		return move;
	}
}

void MapFormat::drawHills(Edges edgesDownToHigh, Edges edgesHighToDown, double scale)
{
	edgesDownToHigh.sort(&MapFormat::sortEdgesByX);
	edgesHighToDown.sort(&MapFormat::sortEdgesByX);
	LOG ("Down to high size: " << edgesDownToHigh.size());
	LOG ("High to down size: " << edgesHighToDown.size());
	bool downToHigh;
	VEdge* actualEdge;
	VPointToIPoint::iterator found;
	int tmp = 0;
	IPoint start(0,0);
	IPoint end(0,0);
	Edges::iterator iDown = edgesDownToHigh.begin();
	Edges::iterator iHigh = edgesHighToDown.begin();
	bool iDownDone = false;
	bool iHighDone = false;
	int size = edgesDownToHigh.size() + edgesHighToDown.size();
	//while (iDown != edgesDownToHigh.end() && iHigh != edgesHighToDown.end()) {
	for(int i = 0; i < size; ++i) {
		if (iHigh == edgesHighToDown.end()) {
			downToHigh = true;
			actualEdge = *iDown;
			if (iDown == edgesDownToHigh.end()) iDownDone = true;
			else ++iDown;
		} else if (iDown == edgesDownToHigh.end()) {
			downToHigh = false;
			actualEdge = *iHigh;
			if (iHigh == edgesHighToDown.end()) iHighDone = true;
			else ++iHigh;
		}
		// select lower X
		else if ( sortEdgesByX( *iHigh, *iDown ) ) {
			downToHigh = false;
			actualEdge = *iHigh;
			if (iHigh == edgesHighToDown.end()) iHighDone = true;
			else ++iHigh;
		} else {
			downToHigh = true;
			actualEdge = *iDown;
			if (iDown == edgesDownToHigh.end()) iDownDone = true;
			else ++iDown;
		}

		// search if start was previously computed
		found = vertexMap.find(*(actualEdge->start));
		if(found != vertexMap.end()) {
			start = found->second;
			LOG("Start found it");
		} else {
			start.x = (int)round(actualEdge->start->x * scale);
			start.y = (int)round(actualEdge->start->y * scale);
			start.y = height - start.y + 1; // adjust origin x,y to down-left corner
		}

		// search if end was previously computed
		found = vertexMap.find(*(actualEdge->end));
		if(found != vertexMap.end()) {
			end = found->second;
			LOG("End found it!!!!!!!!");
		} else {
			end.x = (int)round(actualEdge->end->x * scale);
			end.y = (int)round(actualEdge->end->y * scale);
			end.y = height - end.y + 1; // adjust origin x,y to down-left corner
		}

		// check constrains
		if ((end.x-start.x) % 2) {
			if (end.x > start.x) end.x++;
			else start.x++;
		}
		// readjust if y is out of the map
// 		if ((start.y > height || end.y > height) && ((end.x-start.x) % 2)==0 ) {
// 			if (end.x > start.x) end.x--;
// 			else start.x--;
// 		}

		// Save positions
		vertexMap.insert(VPointToIPoint::value_type(*(actualEdge->end),end));
		vertexMap.insert(VPointToIPoint::value_type(*(actualEdge->start),start));

		// Draw line
		if (downToHigh) {
			LOG("drawLineDownToHigh(" << start.x << ", " << height-start.y << ", " << end.x << ", " << height-end.y << ");");
			drawLineDownToHigh(start.x, start.y, end.x, end.y);
		} else {
			LOG("drawLineHighToDown(" << start.x << ", " << height-start.y << ", " << end.x << ", " << height-end.y << ");");
			drawLineHighToDown(start.x, start.y, end.x, end.y);
		}

		// testing
// 		tmp++;
// 		if (tmp == 16) {
// 			editMapTile(start.x, start.y, (short)0x0000);
// 			editMapTile(end.x, end.y, (short)0x0000);
// 			break;
// 		}
	}
}

void MapFormat::drawLineDownToHigh(int x0, int y0, int x1, int y1)
{
	if (x0 > x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;

	// check assumption 2 (slope)
	double slope = 0;
	if (dx!=0) slope = double(dy) / double(dx);

	int x = x0;
	int y = y0;
	int xSteps = 0;
	int ySteps = 0;
	bool lastStepUp = true;
	bool lastStepDown = true;

	if (slope > 0.5 || (slope == 0 && y0 < y1)){ // always +y, conditionally +x
		//return;
		double D = 2 * dx - dy;

		// Adjust start point looking neighbors
		moveMapPoint move = rectifyInitialPoint2(x,y);
		D += 2 * ((dx*move.y) - (dy*move.x));
		x += move.x;
		y += move.y;
		//if (move.x != 0) {
		//	LOG("Move head from: " << x0 << "," << y0 << " to: " << x << "," << y);
		//}

		if (D <= 0 || (move.toDown && D > 0) ) {
			writeTile2(x,y);
			x += 2;
			y += 1;
			D += 2 * (dx - (dy*2));
		}

		while (y <= y1) {
			if (D <= 0) {
				LOG("Check position " << x << "," << height-y);
				if (isTileIdAtXY(6, x, y-2)) writeTile7(x,y);
				else if (y+1 >= y1 && isTileIdAtXY(11, x-1, y+2)) { //addjust final corner
					writeTile6(x,y);
					writeTile7(x,y+2);
				} else writeTile6(x,y);
				xSteps = 0;
				ySteps = 2;
				lastStepUp = false;
			} else {
				if (isTileIdAtXY(6, x, y-2)) {
					writeTile8(x,y);
					LOG("Write tile 8 at " << x << "," << height-y);
				} else if (y+1 > y1)  {
					LOG("Final corner 6 at " << x << "," << height-y);
					writeTile6(x,y); // final corner
				} else writeTile2(x,y);
				xSteps = 2;
				ySteps = 1;
				lastStepUp = true;
			}
			D += 2 * ((dx*ySteps) - (dy*xSteps));
			x += xSteps;
			y += ySteps;
		}

		// Add final corner
		//if (lastStepUp) writeTile6(x,y);

	} else if (slope > 0 || (slope == 0 && x0 < x1)) { // always +x, conditionally +y
		//return;
		double D = 2 * dy - dx;

		LOG("Checking position: " << x << "," << height-y);
		// Adjust start point  looking neighbors
		moveMapPoint move = rectifyInitialPoint2(x,y);
		D += 2 * ((dy*move.x) - (dx*move.y));
		x += move.x;
		y += move.y;

		LOG("Checking position: " << x << "," << height-y);
		LOG(getMapTileId(x-3, y+3) << "\t" << getMapTileId(x-2, y+3) << "\t" << getMapTileId(x-1, y+3) << "\t" << getMapTileId(x, y+3) << "\t" << getMapTileId(x+1, y+3) << "\t" << getMapTileId(x+2, y+3));
		LOG(getMapTileId(x-3, y+2) << "\t" << getMapTileId(x-2, y+2) << "\t" << getMapTileId(x-1, y+2) << "\t" << getMapTileId(x, y+2) << "\t" << getMapTileId(x+1, y+2) << "\t" << getMapTileId(x+2, y+2));
		LOG(getMapTileId(x-3, y+1) << "\t" << getMapTileId(x-2, y+1) << "\t" << getMapTileId(x-1, y+1) << "\t" << getMapTileId(x, y+1) << "\t" << getMapTileId(x+1, y+1) << "\t" << getMapTileId(x+2, y+1));
		LOG(getMapTileId(x-3, y  ) << "\t" << getMapTileId(x-2, y  ) << "\t" << getMapTileId(x-1, y  ) << "\t[" << getMapTileId(x, y  ) << "]\t" << getMapTileId(x+1, y  ) << "\t" << getMapTileId(x+2, y  ));
		LOG(getMapTileId(x-3, y-1) << "\t" << getMapTileId(x-2, y-1) << "\t" << getMapTileId(x-1, y-1) << "\t" << getMapTileId(x, y-1) << "\t" << getMapTileId(x+1, y-1) << "\t" << getMapTileId(x+2, y-1));
		LOG(getMapTileId(x-3, y-2) << "\t" << getMapTileId(x-2, y-2) << "\t" << getMapTileId(x-1, y-2) << "\t" << getMapTileId(x, y-2) << "\t" << getMapTileId(x+1, y-2) << "\t" << getMapTileId(x+2, y-2));


		/*if (D <= 0) {
			writeTile2(x,y);
			D += 2 * ((dy*2) - (dx));
			x += 2;
			y += 1;
		}

		if (move.toDown && D <= 0) {
			// undo moves
			D -= 2 * (dy*-2);
			x += 2;
			D += 2 * (- (dx*-1));
			y += -1;
			// write tile 2
			writeTile2(x,y+1);
			D += 2 * ((dy*2) - dx);
			x += 2;
			y += 1;
		}*/

		LOG("Checking position: " << x << "," << height-y);

		while (x <= x1) {
			if (D <= 0) {
				writeTile1(x,y-1);
				xSteps = 2;
				ySteps = -1;
				lastStepUp = false;
			} else {
				//if (x+2 > x1) writeTile6(x,y); // final corner
				//else writeTile2(x,y);
				writeTile2(x,y);
				xSteps = 2;
				ySteps = 1;
				lastStepUp = true;
			}
			D += 2 * ((dy*xSteps) - (dx*ySteps));
			x += xSteps;
			y += ySteps;
		}

		// Add final corner
		if (lastStepUp) {
			writeTile6(x,y);
		} else {
		//if (!lastStepUp) {
			writeTile6(x-2,y+1);
			LOG("Last position: " << x << "," << height-y);
			writeTileNormal(x-2,y-2);
			writeTileNormal(x-1,y-2);
		}

	} else if (slope > -0.5 && slope != 0) { // always +x, conditionally -y
		//return;
		dy = abs(dy);
		double D = 2 * dy - dx;

		// Add initial corner
		moveMapPoint move = rectifyInitialPoint1(x,y);
		D += 2 * ((dy*move.x) - (dx*-move.y));
		x += move.x;
		y += move.y;

		if (move.printCorner) {
			if (D <= 0) {
				if (x==0 && isTileIdAtXY(22,x,y)) writeTile1(x,y+1);
				else writeTile3(x,y);
				D += 2 * ((dy*2) - (dx*-1));
				x += 2;
				y -= -1;
			} else {
				if (x==0 && isTileIdAtXY(22,x-2,y-1)) writeTile1(x-2,y);
				else writeTile3(x-2,y-1);
			}
		}

		while (x < x1) {
			if (D <= 0) {
				writeTile2(x,y);
				xSteps = 2;
				ySteps = -1;
				lastStepDown = false;
			} else {
				writeTile1(x,y-1);
				xSteps = 2;
				ySteps = 1;
				lastStepDown = true;
			}
			D += 2 * ((dy*xSteps) - (dx*ySteps));
			x += xSteps;
			y -= ySteps;
		}

	} else { // always -y, conditionally +x
		//return;
		dy = abs(dy);
		double D = 2 * dx - dy;

		// Add initial corner
		moveMapPoint move = rectifyInitialPoint1(x,y);
		D += 2 * ((dx*-move.y) - (dy*move.x));
		x += move.x;
		y += move.y;
		if (move.x != 0) {
			LOG("Move head from: " << x0 << "," << y0 << " to: " << x << "," << y);
		}

		if (move.printCorner) {
			//if (D > 0) {
				if (!isTileIdAtXY(22,x,y-1)) writeTile3(x,y-1);
				else writeTile1(x,y);
				D += 2 * ((dx*1) - (dy*2));
				x += 2;
				y -= 1;
				//writeTileNormal(x,y);
			//} else {

			//}
		} else { 
			if (!isTileIdAtXY(2, x, y)) {
				D += 2 * dx;
				y -= 1;
			}
			if (move.toDown && D <= 0) {
				writeTile1(x,y);
				D += 2 * (dx - (dy*2));
				x += 2;
				y -= 1;
			}
		}

		while (y > y1) {
			if (D <= 0) {
				if (y-1 <= y1) break;
				if (isTileIdAtXY(3, x-1, y)) writeTile4(x,y);
				else if (isTileIdAtXY(1, x-1, y)) writeTile5(x,y);
				//else writeTile3(x-2,y-2);
				xSteps = 0;
				ySteps = 2;
				lastStepDown = true;
			} else {
				writeTile1(x,y);
				xSteps = 2;
				ySteps = 1;
				lastStepDown = false;
			}
			D += 2 * ((dx*ySteps) - (dy*xSteps));
			x += xSteps;
			y -= ySteps;
		}

		// end line
		if (lastStepDown) writeTile1(x,y);
	}
	//editMapTile(x0, y0, (short)0x1881);
	//editMapTile(x1, y1, (short)0x1881);
}

void MapFormat::drawLineHighToDown(int x0, int y0, int x1, int y1)
{
	if (x0 > x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;

	// check assumption 2 (slope)
	double slope = 0;
	if (dx!=0) slope = double(dy) / double(dx);

	int x = x0;
	int y = y0;
	int xSteps = 0;
	int ySteps = 0;
	bool lastStepUp = true;
	bool lastStepDown = true;

	if (slope > 0.5 || (slope == 0 && y0 < y1)){ // always +y, conditionally +x
		//return;
		double D = 2 * dx - dy;

		// Adjust start point looking neighbors
		moveMapPoint move = rectifyInitialPoint3(x,y);
		if (move.printCorner) {
			if (move.toDown) {
				move.x += 1;
				move.y += 1;
			} else {
				move.x += 1;
				move.y += 2;
			}
			D += 2 * ((dx*move.y) - (dy*move.x));
			x += move.x;
			y += move.y;
		}

		if (D <= 0) {
			writeTile10(x,y-1);
			x += 2;
			y += 1;
			D += 2 * (dx - (dy*2));
		}

		while (y <= y1) {
			if (D <= 0) {
				writeTile4b(x,y);
				xSteps = 0;
				ySteps = 2;
				lastStepUp = true;
			} else {
				writeTile10(x,y-1);
				xSteps = 2;
				ySteps = 1;
				lastStepUp = false;
			}
			D += 2 * ((dx*ySteps) - (dy*xSteps));
			x += xSteps;
			y += ySteps;
		}

		// Add final corner
		if (lastStepUp) writeTile10(x,y-1);

	} else if (slope > 0 || (slope == 0 && x0 < x1)) { // always +x, conditionally +y
		//return;
		double D = 2 * dy - dx;

		moveMapPoint move = rectifyInitialPoint3(x,y);
		if (move.printCorner) {
			if (move.toDown) {
				move.x += 1;
				//move.y += -1;
			} else {
				move.x += -1;
				//move.y += -1;
			}
			D += 2 * ((dy*move.x) - (dx*move.y));
			x += move.x;
			y += move.y;
		}

		if (D <= 0) {
			writeTile10(x,y);
			D += 2 * ((dy*2) - dx);
			x += 2;
			y += 1;
		}

		while (x <= x1) {
			if (D <= 0) {
				writeTile11(x,y-1);
				xSteps = 2;
				ySteps = -1;
				lastStepUp = false;
			} else {
				writeTile10(x,y);
				xSteps = 2;
				ySteps = 1;
				lastStepUp = true;
			}
			D += 2 * ((dy*xSteps) - (dx*ySteps));
			x += xSteps;
			y += ySteps;
		}

		// Add final corner
// 		if (!lastStepUp) {
// 			writeTile10(x,y); // TODO this can be improved, instead of add one extra tile, rectify previous ones
// 		}

	} else if (slope > -0.5 && slope != 0) { // always +x, conditionally -y
		//return;
		dy = abs(dy);
		double D = 2 * dy - dx;

		moveMapPoint move = rectifyInitialPoint3(x,y);
		if (move.printCorner) {
			if (move.toDown) {
				move.x += 1;
				//move.y += -1;
			} else {
				move.x += 1;
				move.y += 1;
			}
			D += 2 * ((dy*move.x) - (dx*-move.y));
			x += move.x;
			y += move.y;
		}

		if (D <= 0) {
			writeTile11(x,y-1);
			D += 2 * ((dy*2) - (dx));
			x += 2;
			y -= 1;
		}

		while (x < x1) {
			if (D <= 0) {
				writeTile10(x,y);
				xSteps = 2;
				ySteps = -1;
				lastStepDown = false;
			} else {
				writeTile11(x,y-1);
				xSteps = 2;
				ySteps = 1;
				lastStepDown = true;
			}
			D += 2 * ((dy*xSteps) - (dx*ySteps));
			x += xSteps;
			y -= ySteps;
		}

		// TODO matching ending needed (1: rearrange end point, 2: force ending with tile 11)

	} else { // always -y, conditionally +x
		//return;
		dy = abs(dy);
		double D = 2 * dx - dy;
		//double D = 2 * dx - (dy*5); // testing
		
		//// Add initial corner
		moveMapPoint move = rectifyInitialPoint3(x,y);
		LOG("Checking position: " << x << "," << height-y);
		/*if (move.printCorner) {
			if (move.toDown) {
				move.x += -1;
				move.y += 1;
			} else {
				move.x += 1;
				move.y += 1;
				//editMapTile(move.x, move.y+1, (short)0x0322);
			}
			D += 2 * ((dx*-move.y) - (dy*move.x));
			x += move.x;
			y += move.y;
		}
		//LOG("Start point: " << getMapTile(x, y) << isTileIdAtXY(8, x, y));
		if (!move.toDown && D <= 0) {
			writeTile11(x,y-1);
			D += 2 * (dx - (dy*2));
			x += 2;
			y -= 1;
		}*/
		D += 2 * ((dx*-move.y) - (dy*move.x));
		x += move.x;
		y += move.y;
		LOG("Checking position: " << x << "," << height-y);
		LOG(getMapTileId(x-3, y+3) << "\t" << getMapTileId(x-2, y+3) << "\t" << getMapTileId(x-1, y+3) << "\t" << getMapTileId(x, y+3) << "\t" << getMapTileId(x+1, y+3) << "\t" << getMapTileId(x+2, y+3));
		LOG(getMapTileId(x-3, y+2) << "\t" << getMapTileId(x-2, y+2) << "\t" << getMapTileId(x-1, y+2) << "\t" << getMapTileId(x, y+2) << "\t" << getMapTileId(x+1, y+2) << "\t" << getMapTileId(x+2, y+2));
		LOG(getMapTileId(x-3, y+1) << "\t" << getMapTileId(x-2, y+1) << "\t" << getMapTileId(x-1, y+1) << "\t" << getMapTileId(x, y+1) << "\t" << getMapTileId(x+1, y+1) << "\t" << getMapTileId(x+2, y+1));
		LOG(getMapTileId(x-3, y  ) << "\t" << getMapTileId(x-2, y  ) << "\t" << getMapTileId(x-1, y  ) << "\t[" << getMapTileId(x, y  ) << "]\t" << getMapTileId(x+1, y  ) << "\t" << getMapTileId(x+2, y  ));
		LOG(getMapTileId(x-3, y-1) << "\t" << getMapTileId(x-2, y-1) << "\t" << getMapTileId(x-1, y-1) << "\t" << getMapTileId(x, y-1) << "\t" << getMapTileId(x+1, y-1) << "\t" << getMapTileId(x+2, y-1));
		LOG(getMapTileId(x-3, y-2) << "\t" << getMapTileId(x-2, y-2) << "\t" << getMapTileId(x-1, y-2) << "\t" << getMapTileId(x, y-2) << "\t" << getMapTileId(x+1, y-2) << "\t" << getMapTileId(x+2, y-2));

		while (y > y1) {
			//LOG(D<<" <= 0 && "<<y<<"-1 > "<<y1);
			if (D <= 0 && y-1 > y1) {
				if (isTileIdAtXY(7, x, y) || isTileIdAtXY(8, x, y)) writeTile7b(x,y);
				else writeTile7(x,y);
				xSteps = 0;
				ySteps = 2;
				lastStepDown = true;
			} else {
				if (isTileIdAtXY(7, x, y) || isTileIdAtXY(8, x, y)) writeTile12(x,y-1);
				else writeTile11(x,y-1);
				xSteps = 2;
				ySteps = 1;
				lastStepDown = false;
			}
			D += 2 * ((dx*ySteps) - (dy*xSteps));
			x += xSteps;
			y -= ySteps;
		}

		// end line // TODO matching ending needed (1: rearrange end point, 2: force ending with tile 11)
// 		if (lastStepDown) {
// 			writeTile12(x,y+1);
// 		}
	}
	//editMapTile(x0, y0, (short)0x1881);
	//editMapTile(x1, y1, (short)0x1881);

}

VPoint MapFormat::searchTile(int seedX, int seedY, short tileId)
{
	//search a tileId near a seed point and return its location
	//searches outward in a spiral.
	int x      = seedX+2;
	int y      = seedY;
	int length = 1;
	int j      = 0;
	bool first = true;
	int dx     = 0;
	int dy     = 1;	
	while (length < 12) //We'll ride the spiral at most 12 tiles away
	{
		//if this is the tile, return this tile position
		if (getMapTile(x, y) == tileId)
			return VPoint(x, y);

		//otherwise, move to another position
		x = x + dx;
		y = y + dy;
		//count how many steps we take in this direction
		j++;
		if (j == length) { //if we've reached the end, its time to turn
			j = 0;	//reset step counter

			//Spiral out. Keep going.
			if (!first)
				length++; //increment step counter if needed


			first =! first; //first=true for every other turn so we spiral out at the right rate

			//turn counter clockwise 90 degrees:
			if (dx == 0) {
				dx = dy;
				dy = 0;
			} else {
				dy = -dx;
				dx = 0;
			}
		}
		//Spiral out. Keep going.
	}
	return VPoint(-1, -1);
}

MapFormat::moveMapPoint MapFormat::rectifyInitialPoint3(int x, int y)
{
	moveMapPoint move;
	move.x = 0;
	move.y = 0;
	move.printCorner = true; // true if we found a previous line
	move.toDown = false;
	int x0 = x; 
	int y0 = y;
	VPoint tileFound(-1, -1);

 	LOG("rectifyInitialPoint3 head from: " << x << "," << y);
	LOG(getMapTileId(x-3, y+3) << "\t" << getMapTileId(x-2, y+3) << "\t" << getMapTileId(x-1, y+3) << "\t" << getMapTileId(x, y+3) << "\t" << getMapTileId(x+1, y+3) << "\t" << getMapTileId(x+2, y+3));
	LOG(getMapTileId(x-3, y+2) << "\t" << getMapTileId(x-2, y+2) << "\t" << getMapTileId(x-1, y+2) << "\t" << getMapTileId(x, y+2) << "\t" << getMapTileId(x+1, y+2) << "\t" << getMapTileId(x+2, y+2));
	LOG(getMapTileId(x-3, y+1) << "\t" << getMapTileId(x-2, y+1) << "\t" << getMapTileId(x-1, y+1) << "\t" << getMapTileId(x, y+1) << "\t" << getMapTileId(x+1, y+1) << "\t" << getMapTileId(x+2, y+1));
	LOG(getMapTileId(x-3, y  ) << "\t" << getMapTileId(x-2, y  ) << "\t" << getMapTileId(x-1, y  ) << "\t[" << getMapTileId(x, y  ) << "]\t" << getMapTileId(x+1, y  ) << "\t" << getMapTileId(x+2, y  ));
	LOG(getMapTileId(x-3, y-1) << "\t" << getMapTileId(x-2, y-1) << "\t" << getMapTileId(x-1, y-1) << "\t" << getMapTileId(x, y-1) << "\t" << getMapTileId(x+1, y-1) << "\t" << getMapTileId(x+2, y-1));
	LOG(getMapTileId(x-3, y-2) << "\t" << getMapTileId(x-2, y-2) << "\t" << getMapTileId(x-1, y-2) << "\t" << getMapTileId(x, y-2) << "\t" << getMapTileId(x+1, y-2) << "\t" << getMapTileId(x+2, y-2));



	// search tile 2
	if (isTileIdAtXY(2, x, y)) {
		LOG("[rectifyInitialPoint3] Initial point found: 2");
		editMapTile(x-2, y-1, (short)0x0502); editMapTile(x-1, y-1, (short)0x0512);
		editMapTile(x-2, y-2, (short)0x0521); editMapTile(x-1, y-2, (short)0x0531); editMapTile(x, y-2, (short)0x05a2);
																					editMapTile(x, y-3, (short)0x0302); editMapTile(x+1, y-3, (short)0x0312);
		
		move.x = 2;
		move.y = -3;
		move.toDown = false;
		return move;
	}

	// search tile 7
	if (isTileIdAtXY(7, x, y)) {
		LOG("[rectifyInitialPoint3] Initial point found: 7");
		int xOffSet = 0;
		if (!isTileIdAtXY(7, x+1, y)) xOffSet++;
		editMapTile(x-xOffSet, y, (short)0x05a2);
		editMapTile(x-xOffSet, y-1, (short)0x0302); editMapTile(x+2-xOffSet, y-1, (short)0x0312);
		
		move.x = 2-xOffSet;
		move.y = -1;
		move.toDown = false;
		return move;
	}

	// search tile 11
	if (isTileIdAtXY(11, x, y)) {
		LOG("[rectifyInitialPoint3] Initial point found: 11");
		
		move.x = 1;
		move.y = -1;
		move.toDown = false;
		return move;
	}


	// search tile 10
	tileFound = searchTile(x, y, (short)0x02d3);
	if (tileFound.x != -1) {
		LOG("[rectifyInitialPoint3] Initial point found: 10");
		if (getMapTile((int)tileFound.x+2, (int)tileFound.y+2) == (short)0x02d3) { // adjust extra step
			tileFound.x += 2;
			tileFound.y += 2;
		}
		move.x = (short)tileFound.x - x0;
		move.y = (short)tileFound.y - y0 + 1;
		move.toDown = true;
		return move;
	}

	// search tile 11/12
	tileFound = searchTile(x, y, (short)0x0312);
	if (tileFound.x != -1) {
		LOG("[rectifyInitialPoint3] Initial point found: 11/12");
		//x = (short)tileFound.x;
		//y = (short)tileFound.y;
		//LOG(getMapTile(x-3, y+3) << "\t" << getMapTile(x-2, y+3) << "\t" << getMapTile(x-1, y+3) << "\t" << getMapTile(x, y+3) << "\t" << getMapTile(x+1, y+3) << "\t" << getMapTile(x+2, y+3));
		//LOG(getMapTile(x-3, y+2) << "\t" << getMapTile(x-2, y+2) << "\t" << getMapTile(x-1, y+2) << "\t" << getMapTile(x, y+2) << "\t" << getMapTile(x+1, y+2) << "\t" << getMapTile(x+2, y+2));
		//LOG(getMapTile(x-3, y+1) << "\t" << getMapTile(x-2, y+1) << "\t" << getMapTile(x-1, y+1) << "\t" << getMapTile(x, y+1) << "\t" << getMapTile(x+1, y+1) << "\t" << getMapTile(x+2, y+1));
		//LOG(getMapTile(x-3, y  ) << "\t" << getMapTile(x-2, y  ) << "\t" << getMapTile(x-1, y  ) << "\t[" << getMapTile(x, y  ) << "]\t" << getMapTile(x+1, y  ) << "\t" << getMapTile(x+2, y  ));
		//LOG(getMapTile(x-3, y-1) << "\t" << getMapTile(x-2, y-1) << "\t" << getMapTile(x-1, y-1) << "\t" << getMapTile(x, y-1) << "\t" << getMapTile(x+1, y-1) << "\t" << getMapTile(x+2, y-1));
		//LOG(getMapTile(x-3, y-2) << "\t" << getMapTile(x-2, y-2) << "\t" << getMapTile(x-1, y-2) << "\t" << getMapTile(x, y-2) << "\t" << getMapTile(x+1, y-2) << "\t" << getMapTile(x+2, y-2));
		//LOG(getMapTile(x-3, y-3) << "\t" << getMapTile(x-2, y-3) << "\t" << getMapTile(x-1, y-3) << "\t" << getMapTile(x, y-3) << "\t" << getMapTile(x+1, y-3) << "\t" << getMapTile(x+2, y-3));
		if (getMapTile((int)tileFound.x+2, (int)tileFound.y-3) == (short)0x0312) { // adjust extra step
			tileFound.x += 2;
			tileFound.y += -3;
			LOG("ADJUST extra step");
			//x = (short)tileFound.x;
			//y = (short)tileFound.y;
			//LOG(getMapTile(x-3, y+3) << "\t" << getMapTile(x-2, y+3) << "\t" << getMapTile(x-1, y+3) << "\t" << getMapTile(x, y+3) << "\t" << getMapTile(x+1, y+3) << "\t" << getMapTile(x+2, y+3));
			//LOG(getMapTile(x-3, y+2) << "\t" << getMapTile(x-2, y+2) << "\t" << getMapTile(x-1, y+2) << "\t" << getMapTile(x, y+2) << "\t" << getMapTile(x+1, y+2) << "\t" << getMapTile(x+2, y+2));
			//LOG(getMapTile(x-3, y+1) << "\t" << getMapTile(x-2, y+1) << "\t" << getMapTile(x-1, y+1) << "\t" << getMapTile(x, y+1) << "\t" << getMapTile(x+1, y+1) << "\t" << getMapTile(x+2, y+1));
			//LOG(getMapTile(x-3, y  ) << "\t" << getMapTile(x-2, y  ) << "\t" << getMapTile(x-1, y  ) << "\t[" << getMapTile(x, y  ) << "]\t" << getMapTile(x+1, y  ) << "\t" << getMapTile(x+2, y  ));
			//LOG(getMapTile(x-3, y-1) << "\t" << getMapTile(x-2, y-1) << "\t" << getMapTile(x-1, y-1) << "\t" << getMapTile(x, y-1) << "\t" << getMapTile(x+1, y-1) << "\t" << getMapTile(x+2, y-1));
			//LOG(getMapTile(x-3, y-2) << "\t" << getMapTile(x-2, y-2) << "\t" << getMapTile(x-1, y-2) << "\t" << getMapTile(x, y-2) << "\t" << getMapTile(x+1, y-2) << "\t" << getMapTile(x+2, y-2));
			//LOG(getMapTile(x-3, y-3) << "\t" << getMapTile(x-2, y-3) << "\t" << getMapTile(x-1, y-3) << "\t" << getMapTile(x, y-3) << "\t" << getMapTile(x+1, y-3) << "\t" << getMapTile(x+2, y-3));
		}
		move.x = (short)tileFound.x - x0;
		move.y = (short)tileFound.y - y0;
		move.toDown = true;
		return move;
	}

	// search tile 6
	tileFound = searchTile(x, y, (short)0x04b2);
	if (tileFound.x != -1) {
		LOG("[rectifyInitialPoint3] Initial point found: 6");
		//if (getMapTile((int)tileFound.x+2, (int)tileFound.y+2) == (short)0x02d3) { // adjust extra step
		//	tileFound.x += 2;
		//	tileFound.y += 2;
		//}
		if (!isTileIdAtXY(22, x, y-2)) writeTileHigh(x,y-2);
		if (!isTileIdAtXY(22, x+1, y-2)) writeTileHigh(x+1,y-2);
		move.x = (short)tileFound.x - x0;
		move.y = (short)tileFound.y - y0 +1;
		move.toDown = true;
		return move;
	}

	// we didn't found a previous line
	//LOG("[rectifyInitialPoint3] No initial point found");
	move.printCorner = false;
	return move;
}
