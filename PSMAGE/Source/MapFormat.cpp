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
}

MapFormat::~MapFormat()
{
}

void MapFormat::writeHeader(std::string name, int size)
{
	writeBytes(name);
	writeBytes(size);
}

void MapFormat::generateFile()
{
	// CHK format specification: 
	//	http://quantam.devklog.net/CHKFormat.htm
	//	http://www.staredit.net/starcraft/CHK

	// --------------------------------------------------------------------------------------------------
	// Section 'TYPE' - Specifies type of scenario file
	writeHeader("TYPE", 4);
	writeBytes((std::string)"RAWB");
	// --------------------------------------------------------------------------------------------------
	// Section 'VER ' [REQUIRED] - Identifies the file format version
	writeHeader("VER ", 2);
	writeBytes((short)205);
	// --------------------------------------------------------------------------------------------------
	// Section 'IVE2' - Additionally identifies the file format version
	writeHeader("IVE2", 2);
	writeBytes((short)11);
	// --------------------------------------------------------------------------------------------------
	// Section 'VCOD' [REQUIRED] - Verification code of the CHK file
	writeHeader("VCOD", 1040);
	writeBytes((__int64)0x7168DC9977CA1934);
	writeBytes((__int64)0xA775E7A7C3BF600A);
	writeBytes((__int64)0xBB3AB0D7A67D291F);
	writeBytes((__int64)0x0B134C17ED2431CC);
	writeBytes((__int64)0x6B18BD91B7A22065);
	writeBytes((__int64)0x37D57AE2DD5DC38D);
	writeBytes((__int64)0x0F129A63D46459F6);
	writeBytes((__int64)0x2AF874E3462E5C43);
	writeBytes((__int64)0x3BD6F63706376A08);
	writeBytes((__int64)0xEC5C67451663940E);
	writeBytes((__int64)0x9ED4FC1AB7F77BD7);
	writeBytes((__int64)0x0FE1C02E8C3FFA73);
	writeBytes((__int64)0xD764E395070974D1);
	writeBytes((__int64)0xDA4FA79974681675);
	writeBytes((__int64)0xBEA0E6E71F1820D5);
	writeBytes((__int64)0x70EF0CCA1FE3B6A6);
	writeBytes((__int64)0x3524B84D311AD531);
	writeBytes((__int64)0xDE581AE17DC7F8E3);
	writeBytes((__int64)0x07DBACBA432705F4);
	writeBytes((__int64)0x49EC8FA80ABE69DC);
	writeBytes((__int64)0x8AC1DBE53F1658D7);
	writeBytes((__int64)0x721CCA9D05C0CF41);
	writeBytes((__int64)0x9B7023C4A55FB1A2);
	writeBytes((__int64)0xDA907B8014E10484);
	writeBytes((__int64)0x400FF3A30669DBFA);
	writeBytes((__int64)0xD7CBC9E3D4CEF3BE);
	writeBytes((__int64)0xF81468F23401405A);
	writeBytes((__int64)0x4B3DD6FE1AC58E38);
	writeBytes((__int64)0x8E451034FA050553);
	writeBytes((__int64)0xF0EEE0AFFE6991DD);
	writeBytes((__int64)0x75DCAD9FDD7E48F3);
	writeBytes((__int64)0x67621B31E5AC7A62);
	writeBytes((__int64)0x742198E04D36CD20);
	writeBytes((__int64)0x7FCD6736717909FB);
	writeBytes((__int64)0xC6A6A2A23CD65F77);
	writeBytes((__int64)0x6CA9CD4E6ACEE31A);
	writeBytes((__int64)0xFD76F4B53B9DBA86);
	writeBytes((__int64)0x296EE92EBCF044F8);
	writeBytes((__int64)0x4427AB086B2F2523);
	writeBytes((__int64)0x75F2DCED99CC127A);
	writeBytes((__int64)0xC51B1CF77E383CC5);
	writeBytes((__int64)0xDD48C90665942DD1);
	writeBytes((__int64)0x8132C9B5AC2D32BE);
	writeBytes((__int64)0xDF153F3534D84A66);
	writeBytes((__int64)0x964DF604B6EBEEB2);
	writeBytes((__int64)0x61D38A629C944235);
	writeBytes((__int64)0xF4FC61DC6F7BA852);
	writeBytes((__int64)0x0AA4EA99FE2D146C);
	writeBytes((__int64)0x594448D013FED9E8);
	writeBytes((__int64)0x198DD934E3F36680);
	writeBytes((__int64)0x3A7E1830FE63D716);
	writeBytes((__int64)0x8CF5F012B10F8D9B);
	writeBytes((__int64)0x8CB8633EDB58780A);
	writeBytes((__int64)0x2E1A8A378EF3AA3A);
	writeBytes((__int64)0x7EE36DE3EFF9315C);
	writeBytes((__int64)0xB9C044C6133EBD9B);
	writeBytes((__int64)0x74B0ADA490DA3ABC);
	writeBytes((__int64)0x373FE647892757F8);
	writeBytes((__int64)0xEE8D43DF5A7942E4);
	writeBytes((__int64)0x1A88C33CE8490AB4);
	writeBytes((__int64)0xA3FDC38A766B0188);
	writeBytes((__int64)0xBACB7FA7564E7A16);
	writeBytes((__int64)0x76C9B9B0EC1C5E02);
	writeBytes((__int64)0xC557C93E39B1821E);
	writeBytes((__int64)0xB8542F5D4C382419);
	writeBytes((__int64)0x520AA1308E575D6F);
	writeBytes((__int64)0x59C306135E71186D);
	writeBytes((__int64)0xEBB5DADC623EDC1F);
	writeBytes((__int64)0xDAD591A7F995911B);
	writeBytes((__int64)0x017000F56BCE5333);
	writeBytes((__int64)0xCEF10AC0E8EED87F);
	writeBytes((__int64)0xA5CCEF78D3B6EB63);
	writeBytes((__int64)0xD2F2AB96A4BC5DAA);
	writeBytes((__int64)0xA2ED6AA89AEAFF61);
	writeBytes((__int64)0x9282C13961ED3EBD);
	writeBytes((__int64)0xE524A0B0B1233616);
	writeBytes((__int64)0x339B120DAAA79B05);
	writeBytes((__int64)0xFCECB025DA209283);
	writeBytes((__int64)0x74F295FC2338D024);
	writeBytes((__int64)0x447D509719E57380);
	writeBytes((__int64)0x691DADA2DB449345);
	writeBytes((__int64)0xFF877F2CE7EE1444);
	writeBytes((__int64)0xDA29BC4DF1329E38);
	writeBytes((__int64)0xA92BD2C1FE262742);
	writeBytes((__int64)0xD17CE8CB0E7A42F6);
	writeBytes((__int64)0x3161B76956EC5B0F);
	writeBytes((__int64)0x6D79344025F96DB4);
	writeBytes((__int64)0xCE82A4FA0BA753FA);
	writeBytes((__int64)0x8F2C450D614945C3);
	writeBytes((__int64)0x1EC97DF3F7604928);
	writeBytes((__int64)0xD3F85226C189D00F);
	writeBytes((__int64)0x0B5F9DBA14358F4D);
	writeBytes((__int64)0x2F2622F7004AA907);
	writeBytes((__int64)0xC6119CA11FFB673E);
	writeBytes((__int64)0x90153458665D4F69);
	writeBytes((__int64)0xD6635FAF4654E56C);
	writeBytes((__int64)0xAFE40DBDDF950C8A);
	writeBytes((__int64)0x7151F6A34C4040BF);
	writeBytes((__int64)0xD5222885F826ED29);
	writeBytes((__int64)0x517FC528FACFBEBF);
	writeBytes((__int64)0x298FBDEC076306B8);
	writeBytes((__int64)0x6632401A717E55FA);
	writeBytes((__int64)0x93FC5ED49DDED4E8);
	writeBytes((__int64)0x802E75CD3BD53D7A);
	writeBytes((__int64)0xEA8FCC1B87744F0A);
	writeBytes((__int64)0xEFE553167CDBA99A);
	writeBytes((__int64)0x5A8972A46EC178AB);
	writeBytes((__int64)0x1FDFA1FB50702C98);
	writeBytes((__int64)0x5682800744D9B76B);
	writeBytes((__int64)0x5BD0490E83C0BFFD);
	writeBytes((__int64)0x2F0BC29A0E6A681E);
	writeBytes((__int64)0xB2F60C99E1A0438E);
	writeBytes((__int64)0x45A0C82C5E1C7AE0);
	writeBytes((__int64)0xC696B9AC88E90B3C);
	writeBytes((__int64)0x65FA13BB2A83AE74);
	writeBytes((__int64)0xE18A8AB0A61F4FEB);
	writeBytes((__int64)0x4E1555D5B9B8E981);
	writeBytes((__int64)0x7E35C23E9BADF245);
	writeBytes((__int64)0x23685BB6722E925F);
	writeBytes((__int64)0xD4873BE90E45C66E);
	writeBytes((__int64)0xBE4405A8E3C041F4);
	writeBytes((__int64)0xF437C41A138A0FE4);
	writeBytes((__int64)0x4B1D799DEF55405A);
	writeBytes((__int64)0xCC3785769C3A794A);
	writeBytes((__int64)0x7E93A660B60F3D82);
	writeBytes((__int64)0x907FC772C4C25CBD);
	writeBytes((__int64)0x6868051310961B4D);
	writeBytes((__int64)0x2A438546FF7BC035);
	writeBytes((__int64)0x0205010206050401);
	writeBytes((__int64)0x0306040507070300);
	// --------------------------------------------------------------------------------------------------
	// Section 'IOWN' - each index represents a player (1 - 12)
	// 03 - Rescuable
	// 05 - Computer
	// 06 - Human
	// 07 - Neutral
	// Normally players 1 - 8 are set to HUMAN, and players 9 - 12 are set to INACTIVE
	writeHeader("IOWN", 12);
	writeBytes((__int32)0x06060606);
	writeBytes((__int32)0x06060606);
	writeBytes((__int32)0x00000000);
	// --------------------------------------------------------------------------------------------------
	// Section 'OWNR' [REQUIRED] - each index represents a player (1 - 12)
	// If a player has a starting location (or units?) on the map 
	// then his index = 6, otherwise his index = 0
	writeHeader("OWNR", 12);
	writeBytes((__int32)0x00000606);
	writeBytes((__int32)0x00000000);
	writeBytes((__int32)0x00000000);
	// --------------------------------------------------------------------------------------------------
	// Section 'ERA ' [REQUIRED] - Specifies tileset of the map
	//	BADLANDS = 0,
	//	SPACE_PLATFORM = 1,
	//	INSTALLATION = 2,
	//	ASH_WORLD = 3,
	//	JUNGLE_WORLD = 4,
	//	DESERT = 5,
	//	ICE = 6,
	//	TWILIGHT = 7
	writeHeader("ERA ", 2);
	writeBytes((short)0);
	// --------------------------------------------------------------------------------------------------
	// Section 'DIM ' [REQUIRED] - Specifies map dimensions
	writeHeader("DIM ", 4);
	writeBytes(width);
	writeBytes(height);
	// --------------------------------------------------------------------------------------------------
	// Section 'SIDE' [REQUIRED] - Designates species of each player
	//	ZERG = 0,
	//	TERRAN = 1,
	//	PROTOSS = 2,
	//	INDEPENDENT = 3,       // (unused)
	//	NEUTRAL = 4,
	//	USER_SELECTABLE = 5,
	//	INACTIVE = 7
	writeHeader("SIDE", 12);
	writeBytes((__int32)0x01020505);
	writeBytes((__int32)0x00010200);
	writeBytes((__int32)0x04070707);
	// --------------------------------------------------------------------------------------------------******* map
	// Section 'MTXM' [REQUIRED] - Graphical tile map section (includes doodads as terrain)
	// Used only by Starcraft (not on Staredit)
	writeHeader("MTXM", width*height*2);
	//for (int i = 0; i < width*height; i++) { writeBytes((short)37); }
	writeBytes(mapBuffer);

	// --------------------------------------------------------------------------------------------------
	// Section 'PUNI' [REQUIRED] - Player unit restrictions (all 1s for normal defaults)
	writeHeader("PUNI", 5700);
	for (int i = 0; i < 5700; i++) { writeBytes((char)0x01); }
	// --------------------------------------------------------------------------------------------------
	// Section 'UPGR' - Player upgrade restrictions (only present on SCM maps, PUPx for Brood War)

	// --------------------------------------------------------------------------------------------------
	// Section 'PTEC' - Player technology restrictions (only present on SCM maps, PTEx for Brood War)

	// --------------------------------------------------------------------------------------------------****** starting points
	// Section 'UNIT' [REQUIRED] - Units on map list and flags (36 bytes each)
	writeHeader("UNIT", 0);

	// --------------------------------------------------------------------------------------------------******* map
	// Section 'ISOM' - Isometric tile mapping
	// Used only by Staredit (diamond map information) size = (width / 2 + 1) * (height + 1) * 4 - 4 ints
	int isomSize = (width / 2 + 1) * (height + 1) * 4;
	writeHeader("ISOM", isomSize*2);
	for (int i = 0; i < isomSize; i++) { writeBytes((short)16); }

	// --------------------------------------------------------------------------------------------------******* map
	// Section 'TILE' - Tile map of level's terrain (NOT includes doodads, this info is stored in DD2)
	// Used only by Staredit. size = width * height ints - 1 int
	writeHeader("TILE", width*height*2);
	//for (int i = 0; i < width*height; i++) { writeBytes((short)37); }
	writeBytes(mapBuffer);

	// --------------------------------------------------------------------------------------------------
	// Section 'DD2 ' - Doodad map of level (used only by Staredit)
	writeHeader("DD2 ", 0);

	// --------------------------------------------------------------------------------------------------
	// Section 'THG2' [REQUIRED] - Doodad to unit map (Staredit write, Starcraft read)
	writeHeader("THG2", 0);

	// --------------------------------------------------------------------------------------------------
	// Section 'MASK' [REQUIRED] - Fog of War section (not required for melee maps)
	writeHeader("MASK", width * height);
	for (int i = 0; i < width * height; i++) { writeBytes((char)0xFF); }

	// --------------------------------------------------------------------------------------------------
	// Section 'STR ' - Strings section
	// Scenario Title, followed by scenario description
	// Each string is null terminated, and is placed at END of this space, like so:
	// [empty space][Scenario Title][null][ScenarioDescription][null]
	writeHeader("STR ", 2136);
	writeBytes((__int64)0x082f080a08030400);
	writeBytes((__int64)0x0850084808400838);
	for (int i = 0; i < 1017; i++) writeBytes((__int16)0x0802);
	writeBytes((char)0x00);
	writeBytes((std::string)"PSMAGE");writeBytes((char)0x00);
	writeBytes((std::string)"Map procedurally generated by PSMAGE");writeBytes((char)0x00);
	writeBytes((std::string)"Anywhere");writeBytes((char)0x00);
	writeBytes((std::string)"Force 1");writeBytes((char)0x00);
	writeBytes((std::string)"Force 2");writeBytes((char)0x00);
	writeBytes((std::string)"Force 3");writeBytes((char)0x00);
	writeBytes((std::string)"Force 4");writeBytes((char)0x00);


	// --------------------------------------------------------------------------------------------------
	// Section 'UPRP' [REQUIRED] - Trigger unit properties section
	writeHeader("UPRP", 1280);
	for (int i = 0; i < 1280 / 4; i++) writeBytes((__int32)0x00000000);

	// --------------------------------------------------------------------------------------------------
	// Section 'UPUS' [REQUIRED] - Trigger unit properties used section
	writeHeader("UPUS", 64);
	for (int i = 0; i < 64 / 4; i++) writeBytes((__int32)0x00000000);

	// --------------------------------------------------------------------------------------------------
	// Section 'MRGN' [REQUIRED] - Locations section
	writeHeader("MRGN", 5100);
	for (int i = 0; i < 5100 / 4; i++) writeBytes((__int32)0x00000000);

	// --------------------------------------------------------------------------------------------------
	// Section 'TRIG' [REQUIRED] - Trigger section (empty for no triggers)
	writeHeader("TRIG", 0);

	// --------------------------------------------------------------------------------------------------
	// Section 'MBRF' [REQUIRED] - Mission briefing section (empty for no triggers)
	writeHeader("MBRF", 0);

	// --------------------------------------------------------------------------------------------------
	// Section 'SPRP' [REQUIRED] - Decides which strings are the scenario properties
	writeHeader("SPRP", 4);
	writeBytes((short)1); // string scenario name pointer
	writeBytes((short)2); // string scenario description pointer

	// --------------------------------------------------------------------------------------------------????
	// Section 'FORC' - Specifies the forces
	writeHeader("FORC", 20);
	for (int i = 0; i < 20 / 4; i++) writeBytes((__int32)0x00000000);

	// --------------------------------------------------------------------------------------------------
	// Section 'WAV ' - Specifies the WAV files in the scenario
	writeHeader("WAV ", 2048);
	for (int i = 0; i < 2048 / 8; i++) writeBytes((__int64)0x0000000000000000);

	// --------------------------------------------------------------------------------------------------
	// Section 'UNIS' - Unit settings for level (only present on SCM maps, UNIx for Brood War)

	// --------------------------------------------------------------------------------------------------
	// Section 'UPGS' - Upgrade settings (only present on SCM maps, UPGx for Brood War)

	// --------------------------------------------------------------------------------------------------
	// Section 'TECS' - Technology/special abilities settings (only present on SCM maps, TECx for Brood War)

	// --------------------------------------------------------------------------------------------------
	// Section 'SWNM' - Switch renaming section
	writeHeader("SWNM", 1024);
	for (int i = 0; i < 1024 / 8; i++) writeBytes((__int64)0x0000000000000000);

	// --------------------------------------------------------------------------------------------------
	// Section 'COLR' - Color settings for each players (only present on SCX maps)
	writeHeader("COLR", 8);
	writeBytes((__int64)0x0706050403020100);

	// --------------------------------------------------------------------------------------------------
	// Section 'PUPx' - Extended upgrades section for the level (only present on SCX maps)
	writeHeader("PUPx", 2318);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0101010101000101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0100000101010101);
	writeBytes((__int64)0x0001010101000100);
	writeBytes((__int64)0x0303030000000000);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0001010303030303);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0001000100000101);
	writeBytes((__int64)0x0000000001010101);
	writeBytes((__int64)0x0303030303030000);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0101010001010303);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0001010101010101);
	writeBytes((__int64)0x0101010001000100);
	writeBytes((__int64)0x0300000000000001);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0103030303030303);
	writeBytes((__int64)0x0101010101010001);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0001000001010101);
	writeBytes((__int64)0x0000010101010001);
	writeBytes((__int64)0x0303030300000000);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0100010103030303);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0100010001000001);
	writeBytes((__int64)0x0000000000010101);
	writeBytes((__int64)0x0303030303030300);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0101010100010103);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0000010101010101);
	writeBytes((__int64)0x0101010100010001);
	writeBytes((__int64)0x0303000000000000);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0101030303030303);
	writeBytes((__int64)0x0101010101010100);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0100010000010101);
	writeBytes((__int64)0x0000000101010100);
	writeBytes((__int64)0x0303030303000000);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0101000101030303);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101000100010000);
	writeBytes((__int64)0x0000000000000101);
	for (int i = 0; i < 122; i++) writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0303030303030303);
	writeBytes((__int64)0x0101010101000101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0100000101010101);
	writeBytes((__int64)0x0001010101000100);
	for (int i = 0; i < 8; i++) writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0101010101010000);
	for (int i = 0; i < 90; i++) writeBytes((__int64)0x0101010101010101);
	writeBytes((__int32)0x01010101);
	writeBytes((__int16)0x0101);

	// --------------------------------------------------------------------------------------------------
	// Section 'PTEx' - Extended player technologies section (only present on SCX maps)
	writeHeader("PTEx", 1672);
	for (int i = 0; i < 66; i++) writeBytes((__int64)0x0101010101010101);
	for (int i = 0; i < 66; i++) writeBytes((__int64)0x0000000000000000);
	for (int i = 0; i < 5; i++) writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0000000001010101);
	for (int i = 0; i < 5; i++) writeBytes((__int64)0x0000000000000000);
	for (int i = 0; i < 66; i++) writeBytes((__int64)0x0101010101010101);

	// --------------------------------------------------------------------------------------------------
	// Section 'UNIx' - Extended unit settings section (only present on SCX maps)
	writeHeader("UNIx", 4168);
	for (int i = 0; i < 28; i++) writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0000280001010101);
	writeBytes((__int64)0x0000500000002D00);
	writeBytes((__int64)0x0000000000007D00);
	writeBytes((__int64)0x0000000000009600);
	writeBytes((__int64)0x0000780000003C00);
	writeBytes((__int64)0x0000A0000000C800);
	writeBytes((__int64)0x0001F40000009600);
	writeBytes((__int64)0x0000640000001400);
	writeBytes((__int64)0x0000FA0000002800);
	writeBytes((__int64)0x0000000000012C00);
	writeBytes((__int64)0x0000C80000012C00);
	writeBytes((__int64)0x000320000001F400);
	writeBytes((__int64)0x0000000000019000);
	writeBytes((__int64)0x0000000000019000);
	writeBytes((__int64)0x000352000003E800);
	writeBytes((__int64)0x000096000002BC00);
	writeBytes((__int64)0x0000320000000000);
	writeBytes((__int64)0x00003C0000000000);
	writeBytes((__int64)0x0000C80000001900);
	writeBytes((__int64)0x0000500000002300);
	writeBytes((__int64)0x00001E0000019000);
	writeBytes((__int64)0x0000C80000002800);
	writeBytes((__int64)0x0000960000007800);
	writeBytes((__int64)0x0000500000007800);
	writeBytes((__int64)0x0003200000001900);
	writeBytes((__int64)0x00003C0000012C00);
	writeBytes((__int64)0x0000FA0000019000);
	writeBytes((__int64)0x000078000000A000);
	writeBytes((__int64)0x0001900000012C00);
	writeBytes((__int64)0x0000C8000003E800);
	writeBytes((__int64)0x000064000000C800);
	writeBytes((__int64)0x0000FA0000005000);
	writeBytes((__int64)0x0000140000001900);
	writeBytes((__int64)0x0000640000005000);
	writeBytes((__int64)0x00000A0000002800);
	writeBytes((__int64)0x0000960000005000);
	writeBytes((__int64)0x00012C000000C800);
	writeBytes((__int64)0x0000280000002800);
	writeBytes((__int64)0x0000640000003C00);
	writeBytes((__int64)0x0000F0000000F000);
	writeBytes((__int64)0x0001900000005000);
	writeBytes((__int64)0x000320000000C800);
	writeBytes((__int64)0x0000280000006400);
	writeBytes((__int64)0x0002580000001400);
	writeBytes((__int64)0x0000FA0000005000);
	writeBytes((__int64)0x00003C0000003C00);
	writeBytes((__int64)0x00007D0000007D00);
	writeBytes((__int64)0x00003C0000003C00);
	writeBytes((__int64)0x00003C0000003C00);
	writeBytes((__int64)0x000064000000C800);
	writeBytes((__int64)0x0000FA000000C800);
	writeBytes((__int64)0x0002BC0000000100);
	writeBytes((__int64)0x00012C0000007D00);
	writeBytes((__int64)0x0005DC0000032000);
	writeBytes((__int64)0x000258000001F400);
	writeBytes((__int64)0x0002EE000001F400);
	writeBytes((__int64)0x000258000003E800);
	writeBytes((__int64)0x000514000004E200);
	writeBytes((__int64)0x000352000001F400);
	writeBytes((__int64)0x000258000002EE00);
	writeBytes((__int64)0x0002EE0000000000);
	writeBytes((__int64)0x0003520000000000);
	writeBytes((__int64)0x0000C8000002EE00);
	writeBytes((__int64)0x0002BC0000015E00);
	writeBytes((__int64)0x002710000007D000);
	writeBytes((__int64)0x0005DC0000271000);
	writeBytes((__int64)0x000708000004E200);
	writeBytes((__int64)0x0000FA000009C400);
	writeBytes((__int64)0x0003520000035200);
	writeBytes((__int64)0x000352000003E800);
	writeBytes((__int64)0x000258000002EE00);
	writeBytes((__int64)0x0002EE0000025800);
	writeBytes((__int64)0x0001900000019000);
	writeBytes((__int64)0x00012C0000000000);
	writeBytes((__int64)0x0009C40000138800);
	writeBytes((__int64)0x0000FA000002EE00);
	writeBytes((__int64)0x0005DC000005DC00);
	writeBytes((__int64)0x0002EE0000000000);
	writeBytes((__int64)0x00012C000001F400);
	writeBytes((__int64)0x00012C000001C200);
	writeBytes((__int64)0x0001F4000000FA00);
	writeBytes((__int64)0x0000640000000000);
	writeBytes((__int64)0x0001F4000001C200);
	writeBytes((__int64)0x000226000001F400);
	writeBytes((__int64)0x0007D00000025800);
	writeBytes((__int64)0x0001F4000001F400);
	writeBytes((__int64)0x0000C8000001C200);
	writeBytes((__int64)0x0005DC000186A000);
	writeBytes((__int64)0x0186A00000138800);
	writeBytes((__int64)0x0186A0000186A000);
	writeBytes((__int64)0x0003200000032000);
	writeBytes((__int64)0x0003200000032000);
	writeBytes((__int64)0x0003200000032000);
	writeBytes((__int64)0x0003200000032000);
	writeBytes((__int64)0x0186A00000032000);
	writeBytes((__int64)0x0007D0000002BC00);
	writeBytes((__int64)0x0186A0000186A000);
	writeBytes((__int64)0x0186A0000186A000);
	writeBytes((__int64)0x0186A0000186A000);
	writeBytes((__int64)0x0186A0000186A000);
	writeBytes((__int64)0x000320000186A000);
	writeBytes((__int64)0x000320000009C400);
	writeBytes((__int64)0x0186A00000003200);
	writeBytes((__int64)0x0186A0000186A000);
	writeBytes((__int64)0x0186A0000186A000);
	writeBytes((__int64)0x0000320000003200);
	writeBytes((__int64)0x0000320000003200);
	writeBytes((__int64)0x0003200000003200);
	writeBytes((__int64)0x000320000186A000);
	writeBytes((__int64)0x0003200000032000);
	writeBytes((__int64)0x0003200000032000);
	writeBytes((__int64)0x0003200000032000);
	writeBytes((__int64)0x0003200000032000);
	writeBytes((__int64)0x0003200000032000);
	writeBytes((__int64)0x0000000000032000);
	for (int i = 0; i < 14; i++) writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0028005000000000);
	writeBytes((__int64)0x0050001400C80000);
	writeBytes((__int64)0x003C015E00280050);
	writeBytes((__int64)0x0028009600960064);
	writeBytes((__int64)0x00F0032001900050);
	writeBytes((__int64)0x01900190012C00F0);
	writeBytes((__int64)0x000A0014005001F4);
	writeBytes((__int64)0x000000FA012C01F4);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x000000000000003C);
	for (int i = 0; i < 13; i++) writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x01C2012C01F402EE);
	writeBytes((__int64)0x000101F400FA012C);
	writeBytes((__int64)0x01F401F401C20064);
	writeBytes((__int64)0x01F4000002580226);
	writeBytes((__int64)0x000000C801C201F4);
	for (int i = 0; i < 13; i++) writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0100000000000000);
	writeBytes((__int64)0x0103010000000100);
	writeBytes((__int64)0x0300030300000003);
	writeBytes((__int64)0x0400030003040403);
	writeBytes((__int64)0x0A01000100010404);
	writeBytes((__int64)0x000000000100000A);
	writeBytes((__int64)0x0200030400010002);
	writeBytes((__int64)0x0002040403030203);
	writeBytes((__int64)0x0001010001020101);
	writeBytes((__int64)0x0000000401000100);
	writeBytes((__int64)0x0004030302030203);
	writeBytes((__int64)0x0100000302030000);
	writeBytes((__int64)0x02000A0000000001);
	writeBytes((__int64)0x0101000301040003);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0101000001010100);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0102010000010101);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0100010101010100);
	writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0000000001010101);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000010100);
	writeBytes((__int64)0x0000010100000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x025801C202EE0168);
	writeBytes((__int64)0x012C000002EE0000);
	writeBytes((__int64)0x02EE02D004B00384);
	writeBytes((__int64)0x000005DC00000960);
	writeBytes((__int64)0x0384000004B005DC);
	writeBytes((__int64)0x05DC096007080000);
	writeBytes((__int64)0x12C0000005DC0000);
	writeBytes((__int64)0x000002EE12C00960);
	writeBytes((__int64)0x000001C200000168);
	writeBytes((__int64)0x038401A401A40000);
	writeBytes((__int64)0x02580258012C0000);
	writeBytes((__int64)0x01C202EE02EE0258);
	writeBytes((__int64)0x05DC025805DC0708);
	writeBytes((__int64)0x04B00348030C05DC);
	writeBytes((__int64)0x0000038404B004B0);
	writeBytes((__int64)0x012C025802EE0258);
	writeBytes((__int64)0x02EE02580258012C);
	writeBytes((__int64)0x096004B00384012C);
	writeBytes((__int64)0x05DC02EE012C0834);
	writeBytes((__int64)0x05DC05DC04B00258);
	writeBytes((__int64)0x041A106807080960);
	writeBytes((__int64)0x05DC12C000690258);
	writeBytes((__int64)0x0258000000000960);
	writeBytes((__int64)0x0000000000000258);
	writeBytes((__int64)0x05DC02EE00000000);
	writeBytes((__int64)0x025812C0000005DC);
	writeBytes((__int64)0x02580708096005DC);
	writeBytes((__int64)0x04B00258025804B0);
	writeBytes((__int64)0x0258041A04B004B0);
	writeBytes((__int64)0x00000258025804B0);
	writeBytes((__int64)0x04B0038400000258);
	writeBytes((__int64)0x038412C001C201C2);
	writeBytes((__int64)0x0708070800000000);
	writeBytes((__int64)0x02580258070805DC);
	writeBytes((__int64)0x0258038407080384);
	writeBytes((__int64)0x012C04B0070804B0);
	writeBytes((__int64)0x0000012C0000012C);
	writeBytes((__int64)0x0000000002580000);
	writeBytes((__int64)0x04B0070800000000);
	writeBytes((__int64)0x01C20000025801C2);
	writeBytes((__int64)0x038402EE00000384);
	writeBytes((__int64)0x041A025803840384);
	writeBytes((__int64)0x01C2038403840000);
	writeBytes((__int64)0x12C00000000001C2);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x000012C009600000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000096009600960);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0064004B00190032);
	writeBytes((__int64)0x0032000100960001);
	writeBytes((__int64)0x0064006400640096);
	writeBytes((__int64)0x000000C800010190);
	writeBytes((__int64)0x0096000100C80032);
	writeBytes((__int64)0x012C003201900032);
	writeBytes((__int64)0x03200001012C0001);
	writeBytes((__int64)0x0001009603200320);
	writeBytes((__int64)0x0001003200000032);
	writeBytes((__int64)0x00C8004B00320001);
	writeBytes((__int64)0x0064006400320001);
	writeBytes((__int64)0x0019003200640032);
	writeBytes((__int64)0x00C8006400C80190);
	writeBytes((__int64)0x00C8006400960032);
	writeBytes((__int64)0x000100FA00C80064);
	writeBytes((__int64)0x00000096007D0096);
	writeBytes((__int64)0x0032007D00640032);
	writeBytes((__int64)0x0064012C00C80000);
	writeBytes((__int64)0x006400960019015E);
	writeBytes((__int64)0x0064012C00C80000);
	writeBytes((__int64)0x00C802BC01900258);
	writeBytes((__int64)0x00640032000F0019);
	writeBytes((__int64)0x0064000100010258);
	writeBytes((__int64)0x0001000100010064);
	writeBytes((__int64)0x00C8009600010001);
	writeBytes((__int64)0x00320320000000C8);
	writeBytes((__int64)0x0032019000FA00C8);
	writeBytes((__int64)0x0096006400640064);
	writeBytes((__int64)0x0032009600C800C8);
	writeBytes((__int64)0x0001003200320096);
	writeBytes((__int64)0x0064007D00010032);
	writeBytes((__int64)0x00C803200064004B);
	writeBytes((__int64)0x012C000100010001);
	writeBytes((__int64)0x0064009600C80096);
	writeBytes((__int64)0x004B009600640064);
	writeBytes((__int64)0x004B00C800C80096);
	writeBytes((__int64)0x0001003200010032);
	writeBytes((__int64)0x0000000000320001);
	writeBytes((__int64)0x00C8019000010000);
	writeBytes((__int64)0x0032000100640064);
	writeBytes((__int64)0x0096009600010096);
	writeBytes((__int64)0x00960096009600C8);
	writeBytes((__int64)0x009600C8012C0096);
	writeBytes((__int64)0x05DC00FA00FA0064);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x00FA03E802580001);
	writeBytes((__int64)0x003200FA00640032);
	writeBytes((__int64)0x0064003200FA0064);
	writeBytes((__int64)0x000100FA03E800C8);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000000010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x00320000004B0000);
	writeBytes((__int64)0x0000000100640001);
	writeBytes((__int64)0x0064003200E10064);
	writeBytes((__int64)0x000000C80000012C);
	writeBytes((__int64)0x0000000100640096);
	writeBytes((__int64)0x00C8025800C80000);
	writeBytes((__int64)0x0258000100C80001);
	writeBytes((__int64)0x0001006402580258);
	writeBytes((__int64)0x0001001900000019);
	writeBytes((__int64)0x00C8001900000001);
	writeBytes((__int64)0x0064000000000001);
	writeBytes((__int64)0x004B009600960064);
	writeBytes((__int64)0x012C0032012C0190);
	writeBytes((__int64)0x00C80000003200C8);
	writeBytes((__int64)0x0001007D000000C8);
	writeBytes((__int64)0x0000003200640064);
	writeBytes((__int64)0x0096003200000000);
	writeBytes((__int64)0x015E009600000000);
	writeBytes((__int64)0x012C0096000000FA);
	writeBytes((__int64)0x012C006400000000);
	writeBytes((__int64)0x0064025800C8012C);
	writeBytes((__int64)0x012C03E80000004B);
	writeBytes((__int64)0x006400010001012C);
	writeBytes((__int64)0x0001000100010064);
	writeBytes((__int64)0x004B006400010001);
	writeBytes((__int64)0x006402580000004B);
	writeBytes((__int64)0x0032000000FA004B);
	writeBytes((__int64)0x0000000000000064);
	writeBytes((__int64)0x0032006400640000);
	writeBytes((__int64)0x00010032003200C8);
	writeBytes((__int64)0x0032000000010032);
	writeBytes((__int64)0x0000025800000000);
	writeBytes((__int64)0x0000000100010001);
	writeBytes((__int64)0x0032000000960064);
	writeBytes((__int64)0x0000006400960064);
	writeBytes((__int64)0x00000000009600C8);
	writeBytes((__int64)0x0001000000010000);
	writeBytes((__int64)0x0000000000000001);
	writeBytes((__int64)0x00C8000000010000);
	writeBytes((__int64)0x0064000100000000);
	writeBytes((__int64)0x0064000000010000);
	writeBytes((__int64)0x0096000000C80000);
	writeBytes((__int64)0x0064009600C80000);
	writeBytes((__int64)0x01F4000000000000);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0000019000C80001);
	writeBytes((__int64)0x0032000000640032);
	writeBytes((__int64)0x0064003200000064);
	writeBytes((__int64)0x000100C801F40032);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000000010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0001000100010001);
	for (int i = 0; i < 57; i++) writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x001E000A00120006);
	writeBytes((__int64)0x000C007D001E0014);
	writeBytes((__int64)0x001E00140018000A);
	writeBytes((__int64)0x0014000000050046);
	writeBytes((__int64)0x0019001000280008);
	writeBytes((__int64)0x001E003200320019);
	writeBytes((__int64)0x004600100008001E);
	writeBytes((__int64)0x0000000000140096);
	writeBytes((__int64)0x0005000000000000);
	writeBytes((__int64)0x0014000A0032000A);
	writeBytes((__int64)0x0005000400320014);
	writeBytes((__int64)0x0028001400000000);
	writeBytes((__int64)0x0000000000120009);
	writeBytes((__int64)0x006E01F40028000F);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000500000000);
	writeBytes((__int64)0x002D001400140008);
	writeBytes((__int64)0x003C001E00140000);
	writeBytes((__int64)0x0014000E00080000);
	writeBytes((__int64)0x00060014000A001C);
	writeBytes((__int64)0x0000006400140014);
	writeBytes((__int64)0x0000002D00640000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000070007);
	writeBytes((__int64)0x000A0008000A000A);
	writeBytes((__int64)0x0006000000000005);
	writeBytes((__int64)0x0000000000000019);
	writeBytes((__int64)0x0028000000140000);
	writeBytes((__int64)0x001C001400190019);
	writeBytes((__int64)0x000000000000001E);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0001000100000000);
	writeBytes((__int64)0x0002000200010001);
	writeBytes((__int64)0x0001000200010000);
	writeBytes((__int64)0x0000000300030001);
	writeBytes((__int64)0x0002000100020000);
	writeBytes((__int64)0x0003000300030001);
	writeBytes((__int64)0x0001000300030003);
	writeBytes((__int64)0x0000000500050001);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0001000100010000);
	writeBytes((__int64)0x0003000300010001);
	writeBytes((__int64)0x0000000000000001);
	writeBytes((__int64)0x0001000100020002);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0001000100000000);
	writeBytes((__int64)0x0001000000020002);
	writeBytes((__int64)0x0001000000030003);
	writeBytes((__int64)0x0001000100010001);
	writeBytes((__int64)0x0000000000010001);
	writeBytes((__int64)0x0001000000000019);
	writeBytes((__int64)0x0000000000000001);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0001000100000000);
	writeBytes((__int64)0x0000000100010001);
	writeBytes((__int64)0x0000000200010000);
	writeBytes((__int64)0x0002000000000000);
	writeBytes((__int64)0x0001000100030000);
	writeBytes((__int64)0x0000000100010001);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0000000000000000);

	// --------------------------------------------------------------------------------------------------
	// Section 'UPGx' - Extended upgrades settings section (only present on SCX maps)
	writeHeader("UPGx", 794);
	for (int i = 0; i < 7; i++) writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x0064000101010101);
	writeBytes((__int64)0x0096009600960064);
	writeBytes((__int64)0x0064006400960064);
	writeBytes((__int64)0x0064006400640064);
	writeBytes((__int64)0x009600C800640064);
	writeBytes((__int64)0x0064009600C80064);
	writeBytes((__int64)0x00C8009600C80096);
	writeBytes((__int64)0x00C8006400960096);
	writeBytes((__int64)0x0096009600960096);
	writeBytes((__int64)0x00C800C800960096);
	writeBytes((__int64)0x00960096009600C8);
	writeBytes((__int64)0x0096006400C80064);
	writeBytes((__int64)0x0064006400000000);
	writeBytes((__int64)0x0096009600960096);
	writeBytes((__int64)0x00000000006400C8);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x004B004B004B004B);
	writeBytes((__int64)0x004B004B004B004B);
	writeBytes((__int64)0x003200320032004B);
	writeBytes((__int64)0x0064004B0032004B);
	for (int i = 0; i < 11; i++) writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0096006400640000);
	writeBytes((__int64)0x0096006400960096);
	writeBytes((__int64)0x0064006400640064);
	writeBytes((__int64)0x0064006400640064);
	writeBytes((__int64)0x00C80064009600C8);
	writeBytes((__int64)0x00C8009600640096);
	writeBytes((__int64)0x0096009600C80096);
	writeBytes((__int64)0x0096009600C80064);
	writeBytes((__int64)0x0096009600960096);
	writeBytes((__int64)0x009600C800C800C8);
	writeBytes((__int64)0x00C8006400960096);
	writeBytes((__int64)0x0000000000960064);
	writeBytes((__int64)0x0096009600640064);
	writeBytes((__int64)0x006400C800960096);
	writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x004B004B00000000);
	writeBytes((__int64)0x004B004B004B004B);
	writeBytes((__int64)0x0032004B004B004B);
	writeBytes((__int64)0x0032004B00320032);
	writeBytes((__int64)0x000000000064004B);
	for (int i = 0; i < 10; i++) writeBytes((__int64)0x0000000000000000);
	writeBytes((__int64)0x0F96000000000000);
	writeBytes((__int64)0x0F960F960F960F96);
	writeBytes((__int64)0x0F960F960F960F96);
	writeBytes((__int64)0x0F960F960F960F96);
	writeBytes((__int64)0x05DC0F960F960F96);
	writeBytes((__int64)0x09BA09BA09BA05DC);
	writeBytes((__int64)0x096009BA09BA09BA);
	writeBytes((__int64)0x05DC05DC07CB07CB);
	writeBytes((__int64)0x09BA09BA05DC05DC);
	writeBytes((__int64)0x09BA09BA07CB09BA);
	writeBytes((__int64)0x09BA07CB07CB09BA);
	writeBytes((__int64)0x09BA05DC09BA09BA);
	writeBytes((__int64)0x09BA09BA00000000);
	writeBytes((__int64)0x07CB09BA09BA09BA);
	writeBytes((__int64)0x0000000007CB07CB);
	writeBytes((__int64)0x0000000000000000);
	for (int i = 0; i < 4; i++) writeBytes((__int64)0x01E001E001E001E0);
	for (int i = 0; i < 11; i++) writeBytes((__int64)0x0000000000000000);
	writeBytes((__int16)0x0000);

	// --------------------------------------------------------------------------------------------------
	// Section 'TECx' - Extended technology section for the level (only present on SCX maps)
	writeHeader("TECx", 396);
	for (int i = 0; i < 5; i++) writeBytes((__int64)0x0101010101010101);
	writeBytes((__int64)0x00C8006401010101);
	writeBytes((__int64)0x00960000006400C8);
	writeBytes((__int64)0x0096006400C80096);
	writeBytes((__int64)0x0064006400640064);
	writeBytes((__int64)0x0064006400C80064);
	writeBytes((__int64)0x0096009600C80064);
	writeBytes((__int64)0x00C8006400960096);
	writeBytes((__int64)0x006400C800C80096);
	writeBytes((__int64)0x000000C800640064);
	writeBytes((__int64)0x00C800C800C80000);
	writeBytes((__int64)0x00C800C800C800C8);
	writeBytes((__int64)0x00C8006400C800C8);
	writeBytes((__int64)0x00960000006400C8);
	writeBytes((__int64)0x0096006400C80096);
	writeBytes((__int64)0x0064006400640064);
	writeBytes((__int64)0x0064006400C80064);
	writeBytes((__int64)0x0096009600C80064);
	writeBytes((__int64)0x00C8006400960096);
	writeBytes((__int64)0x006400C800C80096);
	writeBytes((__int64)0x000000C800640064);
	writeBytes((__int64)0x00C800C800C80000);
	writeBytes((__int64)0x00C800C800C800C8);
	writeBytes((__int64)0x05DC04B000C800C8);
	writeBytes((__int64)0x04B0000004B00708);
	writeBytes((__int64)0x05DC070804B005DC);
	writeBytes((__int64)0x04B004B004B004B0);
	writeBytes((__int64)0x04B005DC05DC04B0);
	writeBytes((__int64)0x070804B0070804B0);
	writeBytes((__int64)0x04B004B005DC05DC);
	writeBytes((__int64)0x0708070807080708);
	writeBytes((__int64)0x0000070805DC0708);
	writeBytes((__int64)0x0708070807080000);
	writeBytes((__int64)0x0708070807080708);
	writeBytes((__int64)0x0064000007080708);
	writeBytes((__int64)0x0000003200000064);
	writeBytes((__int64)0x00190096004B0064);
	writeBytes((__int64)0x0096000000000019);
	writeBytes((__int64)0x004B000000960064);
	writeBytes((__int64)0x00960064004B004B);
	writeBytes((__int64)0x007D003200000064);
	writeBytes((__int64)0x0032006400960032);
	writeBytes((__int64)0x000000640064004B);
	writeBytes((__int64)0x0064006400640001);
	writeBytes((__int64)0x0064006400640064);
	writeBytes((__int32)0x00640064);

	// Write buffer on file
	std::ofstream myfile("test.chk", std::ios::binary);
	myfile.write(&buffer[0], buffer.size());
	myfile.close();
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

	//editMapTile(50, 50, (short)0x0351);
	//short tileId = getMapTile(50, 50);
	//writeTile1(50, 50);
	//writeTile2(52, 50);
	//drawLineDownToHigh(5, 30, 20, 5);
	//drawLineDownToHigh(20, 5, 40, 60);
}

//double MapFormat::round(double d)
//{
//	return floor(d + 0.5);
//}

void MapFormat::editMapTile(int x, int y, short tileId)
{
	y = height - y; // adjust origin to left-down corner
	if (x >= width || y >= height || x < 0 || y < 0) return;
	const char *tile;
	tile = reinterpret_cast<const char*>( &tileId );
	mapBuffer[(x*2)+(y*2*width)]	= tile[0];
	mapBuffer[(x*2)+(y*2*width)+1]	= tile[1];
}

short MapFormat::getMapTile(int x, int y)
{
	y = height - y; // adjust origin to left-down corner
	if (x >= width || y >= height || x < 0 || y < 0) return 0;
	unsigned char tile[2];
	tile[0] = mapBuffer[(x*2)+(y*2*width)];
	tile[1] = mapBuffer[(x*2)+(y*2*width)+1];
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
}

void MapFormat::writeTile4(int x, int y)
{
																				editMapTile(x, y  , (short)0x04c1); editMapTile(x+1, y  , (short)0x04d1);
										  editMapTile(x-1, y-1, (short)0x0613);	editMapTile(x, y-1, (short)0x04e1); editMapTile(x+1, y-1, (short)0x04f1);
	editMapTile(x-2, y-2, (short)0x0423); editMapTile(x-1, y-2, (short)0x0433);
	editMapTile(x-2, y-3, (short)0x0443); editMapTile(x-1, y-3, (short)0x0453);
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

void MapFormat::writeTile8(int x, int y)
{
																				editMapTile(x, y  , (short)0x03a3); editMapTile(x+1, y  , (short)0x03b3);
	editMapTile(x-2, y-1, (short)0x0500); editMapTile(x-1, y-1, (short)0x0510); editMapTile(x, y-1, (short)0x03c3); editMapTile(x+1, y-1, (short)0x03d3);
	editMapTile(x-2, y-2, (short)0x0522); editMapTile(x-1, y-2, (short)0x0532); editMapTile(x, y-2, (short)0x05e3); editMapTile(x+1, y-2, (short)0x05f3);
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
		case 21: return std::find(normalTerrain1.begin(), normalTerrain1.end(), tileStored)!=normalTerrain1.end();
		case 22: return std::find(highTerrain1.begin(), highTerrain1.end(), tileStored)!=highTerrain1.end();
		default: return false;
	}
}

MapFormat::moveMapPoint MapFormat::rectifyInitialPoint1(int x, int y)
{
	moveMapPoint move;
	int x0 = x; 
	int y0 = y;

	// down to down conditions
	if (isTileIdAtXY(6, x, y) || isTileIdAtXY(6, x+1, y-1) || isTileIdAtXY(6, x+3, y-1)) {
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
			writeTileHigh(x,y+2); writeTileHigh(x-1,y+2);
			move.x -= 1;
			move.y += 1;
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

	// down to down conditions
	if (isTileIdAtXY(6, x, y) || isTileIdAtXY(6, x+1, y-1) || isTileIdAtXY(6, x+3, y-1)) {
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
			//writeTileHigh(x,y+2); writeTileHigh(x-1,y+2); // DIFERENCE FROM function1
			move.x -= 1;
			move.y += 2; // move.y += 1; DIFERENCE FROM function1
		}
		move.printCorner = false;
		move.toDown = false;
		return move;
	}
}

void MapFormat::drawLineDownToHigh(vor::Edges edges, double scale)
{
	edges.sort(&MapFormat::sortEdgesByX);
	for(vor::Edges::iterator i = edges.begin(); i!= edges.end(); ++i) {
		// scale points
		double x0 = (*i)->start->x * scale;
		double y0 = (*i)->start->y * scale;
		double x1 = (*i)->end->x * scale;
		double y1 = (*i)->end->y * scale;
		// adjust origin x,y to down-left corner
		y0 = height - y0 + 1;
		y1 = height - y1 + 1;

		drawLineDownToHigh(int(round(x0)), int(round(y0)), int(round(x1)), int(round(y1)));
		LOG("[ " << (int)round(x0) << ", " << (int)round(y0) << ", " << (int)round(x1) << ", " << (int)round(y1) << "]");
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
		double D = 2 * dx - dy;

		// Adjust start point looking neighbors
		moveMapPoint move = rectifyInitialPoint2(x,y);
		D += 2 * ((dx*move.y) - (dy*move.x));
		x += move.x;
		y += move.y;

		if (D <= 0 || (move.toDown && D > 0) ) {
			writeTile2(x,y);
			x += 2;
			y += 1;
			D += 2 * (dx - (dy*2));
		}

		while (y <= y1) {
			if (D <= 0) {
				if (isTileIdAtXY(6, x, y-2)) writeTile7(x,y);
				else writeTile6(x,y);
				xSteps = 0;
				ySteps = 2;
				lastStepUp = false;
			} else {
				if (isTileIdAtXY(6, x, y-2)) writeTile8(x,y);
				else writeTile2(x,y);
				xSteps = 2;
				ySteps = 1;
				lastStepUp = true;
			}
			D += 2 * ((dx*ySteps) - (dy*xSteps));
			x += xSteps;
			y += ySteps;
		}

		// Add final corner
		if (lastStepUp) writeTile6(x,y);

	} else if (slope > 0 || (slope == 0 && x0 < x1)) { // always +x, conditionally +y
		double D = 2 * dy - dx;

		// Adjust start point  looking neighbors
		moveMapPoint move = rectifyInitialPoint2(x,y);
		D += 2 * ((dy*move.x) - (dx*move.y));
		x += move.x;
		y += move.y;

		if (D <= 0) {
			D += 2 * (dy*-2);
			x -= 2;
		} else {
			D += 2 * (- (dx*-1));
			y += -1;
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
		}

		while (x <= x1) {
			if (D <= 0) {
				writeTile1(x,y);
				xSteps = 2;
				ySteps = -1;
				lastStepUp = false;
			} else {
				writeTile2(x,y+1);
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
			writeTile6(x,y+1);
		} else {
			writeTile6(x-2,y+2);
			writeTileNormal(x-2,y-1);
		}

	} else if (slope > -0.5 && slope != 0) { // always +x, conditionally -y
		dy = abs(dy);
		double D = 2 * dy - dx;

		// Add initial corner
		moveMapPoint move = rectifyInitialPoint1(x,y);
		D += 2 * ((dy*move.x) - (dx*move.y));
		x += move.x;
		y += move.y;

		if (move.printCorner) {
			if (D <= 0) {
				if (!isTileIdAtXY(22,x,y)) writeTile3(x,y);
				else writeTile1(x,y+1);
				D += 2 * ((dy*2) - (dx*-1));
				x += 2;
				y -= -1;
			} else {
				if (!isTileIdAtXY(22,x-2,y-1)) writeTile3(x-2,y-1);
				else writeTile1(x-2,y);
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
		dy = abs(dy);
		double D = 2 * dx - dy;

		// Add initial corner
		moveMapPoint move = rectifyInitialPoint1(x,y);
		D += 2 * ((dx*move.y) - (dy*move.x));
		x += move.x;
		y += move.y;

		if (move.printCorner) {
			if (D > 0) {
				if (!isTileIdAtXY(22,x,y-1)) writeTile3(x,y-1);
				else writeTile1(x,y);
				D += 2 * ((dx*1) - (dy*2));
				x += 2;
				y -= 1;
				writeTileNormal(x,y);
			}
		} else { 
			if (!isTileIdAtXY(2, x, y)) {
				D += 2 * ((dx*-1));
				y += -1;
			}
			if (move.toDown && D <= 0) {
				writeTile1(x,y-1);
				D += 2 * ((dx*1) - (dy*2));
				x += 2;
				y -= 1;
			}
		}

		while (y > y1) {
			if (D <= 0) {
				if (isTileIdAtXY(3, x-1, y)) writeTile4(x,y);
				else if (isTileIdAtXY(1, x-1, y)) writeTile5(x,y);
				else writeTile3(x-2,y-2);
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

}
