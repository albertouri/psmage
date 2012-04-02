#include "MapFormat.h"



MapFormat::MapFormat()
{
	// CHK format specification: http://quantam.devklog.net/CHKFormat.htm

	// Section 'TYPE' - Specifies type of scenario file
	writeHeader("TYPE", 4);
	writeBytes("RAWB");
	// Section 'VER ' - Identifies the file format version
	writeHeader("VER ", 2);
	writeBytes((short)205);
	// Section 'IVE2' - Additionally identifies the file format version
	writeHeader("IVE2", 2);
	writeBytes((short)11);
	// Section 'VCOD' - Verification code of the CHK file
	writeHeader("VCOD", 1040);
	writeBytes((unsigned __int64)0x7168DC9977CA1934);
	writeBytes((unsigned __int64)0xA775E7A7C3BF600A);
	writeBytes((unsigned __int64)0xBB3AB0D7A67D291F);
	writeBytes((unsigned __int64)0x0B134C17ED2431CC);
	writeBytes((unsigned __int64)0x6B18BD91B7A22065);
	writeBytes((unsigned __int64)0x37D57AE2DD5DC38D);
	writeBytes((unsigned __int64)0x0F129A63D46459F6);
	writeBytes((unsigned __int64)0x2AF874E3462E5C43);
	writeBytes((unsigned __int64)0x3BD6F63706376A08);
	writeBytes((unsigned __int64)0xEC5C67451663940E);
	writeBytes((unsigned __int64)0x9ED4FC1AB7F77BD7);
	writeBytes((unsigned __int64)0x0FE1C02E8C3FFA73);
	writeBytes((unsigned __int64)0xD764E395070974D1);
	writeBytes((unsigned __int64)0xDA4FA79974681675);
	writeBytes((unsigned __int64)0xBEA0E6E71F1820D5);
	writeBytes((unsigned __int64)0x70EF0CCA1FE3B6A6);
	writeBytes((unsigned __int64)0x3524B84D311AD531);
	writeBytes((unsigned __int64)0xDE581AE17DC7F8E3);
	writeBytes((unsigned __int64)0x07DBACBA432705F4);
	writeBytes((unsigned __int64)0x49EC8FA80ABE69DC);
	writeBytes((unsigned __int64)0x8AC1DBE53F1658D7);
	writeBytes((unsigned __int64)0x721CCA9D05C0CF41);
	writeBytes((unsigned __int64)0x9B7023C4A55FB1A2);
	writeBytes((unsigned __int64)0xDA907B8014E10484);
	writeBytes((unsigned __int64)0x400FF3A30669DBFA);
	writeBytes((unsigned __int64)0xD7CBC9E3D4CEF3BE);
	writeBytes((unsigned __int64)0xF81468F23401405A);
	writeBytes((unsigned __int64)0x4B3DD6FE1AC58E38);
	writeBytes((unsigned __int64)0x8E451034FA050553);
	writeBytes((unsigned __int64)0xF0EEE0AFFE6991DD);
	writeBytes((unsigned __int64)0x75DCAD9FDD7E48F3);
	writeBytes((unsigned __int64)0x67621B31E5AC7A62);
	writeBytes((unsigned __int64)0x742198E04D36CD20);
	writeBytes((unsigned __int64)0x7FCD6736717909FB);
	writeBytes((unsigned __int64)0xC6A6A2A23CD65F77);
	writeBytes((unsigned __int64)0x6CA9CD4E6ACEE31A);
	writeBytes((unsigned __int64)0xFD76F4B53B9DBA86);
	writeBytes((unsigned __int64)0x296EE92EBCF044F8);
	writeBytes((unsigned __int64)0x4427AB086B2F2523);
	writeBytes((unsigned __int64)0x75F2DCED99CC127A);
	writeBytes((unsigned __int64)0xC51B1CF77E383CC5);
	writeBytes((unsigned __int64)0xDD48C90665942DD1);
	writeBytes((unsigned __int64)0x8132C9B5AC2D32BE);
	writeBytes((unsigned __int64)0xDF153F3534D84A66);
	writeBytes((unsigned __int64)0x964DF604B6EBEEB2);
	writeBytes((unsigned __int64)0x61D38A629C944235);
	writeBytes((unsigned __int64)0xF4FC61DC6F7BA852);
	writeBytes((unsigned __int64)0x0AA4EA99FE2D146C);
	writeBytes((unsigned __int64)0x594448D013FED9E8);
	writeBytes((unsigned __int64)0x198DD934E3F36680);
	writeBytes((unsigned __int64)0x3A7E1830FE63D716);
	writeBytes((unsigned __int64)0x8CF5F012B10F8D9B);
	writeBytes((unsigned __int64)0x8CB8633EDB58780A);
	writeBytes((unsigned __int64)0x2E1A8A378EF3AA3A);
	writeBytes((unsigned __int64)0x7EE36DE3EFF9315C);
	writeBytes((unsigned __int64)0xB9C044C6133EBD9B);
	writeBytes((unsigned __int64)0x74B0ADA490DA3ABC);
	writeBytes((unsigned __int64)0x373FE647892757F8);
	writeBytes((unsigned __int64)0xEE8D43DF5A7942E4);
	writeBytes((unsigned __int64)0x1A88C33CE8490AB4);
	writeBytes((unsigned __int64)0xA3FDC38A766B0188);
	writeBytes((unsigned __int64)0xBACB7FA7564E7A16);
	writeBytes((unsigned __int64)0x76C9B9B0EC1C5E02);
	writeBytes((unsigned __int64)0xC557C93E39B1821E);
	writeBytes((unsigned __int64)0xB8542F5D4C382419);
	writeBytes((unsigned __int64)0x520AA1308E575D6F);
	writeBytes((unsigned __int64)0x59C306135E71186D);
	writeBytes((unsigned __int64)0xEBB5DADC623EDC1F);
	writeBytes((unsigned __int64)0xDAD591A7F995911B);
	writeBytes((unsigned __int64)0x017000F56BCE5333);
	writeBytes((unsigned __int64)0xCEF10AC0E8EED87F);
	writeBytes((unsigned __int64)0xA5CCEF78D3B6EB63);
	writeBytes((unsigned __int64)0xD2F2AB96A4BC5DAA);
	writeBytes((unsigned __int64)0xA2ED6AA89AEAFF61);
	writeBytes((unsigned __int64)0x9282C13961ED3EBD);
	writeBytes((unsigned __int64)0xE524A0B0B1233616);
	writeBytes((unsigned __int64)0x339B120DAAA79B05);
	writeBytes((unsigned __int64)0xFCECB025DA209283);
	writeBytes((unsigned __int64)0x74F295FC2338D024);
	writeBytes((unsigned __int64)0x447D509719E57380);
	writeBytes((unsigned __int64)0x691DADA2DB449345);
	writeBytes((unsigned __int64)0xFF877F2CE7EE1444);
	writeBytes((unsigned __int64)0xDA29BC4DF1329E38);
	writeBytes((unsigned __int64)0xA92BD2C1FE262742);
	writeBytes((unsigned __int64)0xD17CE8CB0E7A42F6);
	writeBytes((unsigned __int64)0x3161B76956EC5B0F);
	writeBytes((unsigned __int64)0x6D79344025F96DB4);
	writeBytes((unsigned __int64)0xCE82A4FA0BA753FA);
	writeBytes((unsigned __int64)0x8F2C450D614945C3);
	writeBytes((unsigned __int64)0x1EC97DF3F7604928);
	writeBytes((unsigned __int64)0xD3F85226C189D00F);
	writeBytes((unsigned __int64)0x0B5F9DBA14358F4D);
	writeBytes((unsigned __int64)0x2F2622F7004AA907);
	writeBytes((unsigned __int64)0xC6119CA11FFB673E);
	writeBytes((unsigned __int64)0x90153458665D4F69);
	writeBytes((unsigned __int64)0xD6635FAF4654E56C);
	writeBytes((unsigned __int64)0xAFE40DBDDF950C8A);
	writeBytes((unsigned __int64)0x7151F6A34C4040BF);
	writeBytes((unsigned __int64)0xD5222885F826ED29);
	writeBytes((unsigned __int64)0x517FC528FACFBEBF);
	writeBytes((unsigned __int64)0x298FBDEC076306B8);
	writeBytes((unsigned __int64)0x6632401A717E55FA);
	writeBytes((unsigned __int64)0x93FC5ED49DDED4E8);
	writeBytes((unsigned __int64)0x802E75CD3BD53D7A);
	writeBytes((unsigned __int64)0xEA8FCC1B87744F0A);
	writeBytes((unsigned __int64)0xEFE553167CDBA99A);
	writeBytes((unsigned __int64)0x5A8972A46EC178AB);
	writeBytes((unsigned __int64)0x1FDFA1FB50702C98);
	writeBytes((unsigned __int64)0x5682800744D9B76B);
	writeBytes((unsigned __int64)0x5BD0490E83C0BFFD);
	writeBytes((unsigned __int64)0x2F0BC29A0E6A681E);
	writeBytes((unsigned __int64)0xB2F60C99E1A0438E);
	writeBytes((unsigned __int64)0x45A0C82C5E1C7AE0);
	writeBytes((unsigned __int64)0xC696B9AC88E90B3C);
	writeBytes((unsigned __int64)0x65FA13BB2A83AE74);
	writeBytes((unsigned __int64)0xE18A8AB0A61F4FEB);
	writeBytes((unsigned __int64)0x4E1555D5B9B8E981);
	writeBytes((unsigned __int64)0x7E35C23E9BADF245);
	writeBytes((unsigned __int64)0x23685BB6722E925F);
	writeBytes((unsigned __int64)0xD4873BE90E45C66E);
	writeBytes((unsigned __int64)0xBE4405A8E3C041F4);
	writeBytes((unsigned __int64)0xF437C41A138A0FE4);
	writeBytes((unsigned __int64)0x4B1D799DEF55405A);
	writeBytes((unsigned __int64)0xCC3785769C3A794A);
	writeBytes((unsigned __int64)0x7E93A660B60F3D82);
	writeBytes((unsigned __int64)0x907FC772C4C25CBD);
	writeBytes((unsigned __int64)0x6868051310961B4D);
	writeBytes((unsigned __int64)0x2A438546FF7BC035);
	writeBytes((unsigned __int64)0x0205010206050401);
	writeBytes((unsigned __int64)0x0306040507070300);
	// Section 'IOWN' - each index represents a player (1 - 12)
	// 03 - Rescuable
	// 05 - Computer
	// 06 - Human
	// 07 - Neutral
	// Normally players 1 - 8 are set to HUMAN, and players 9 - 12 are set to INACTIVE
	writeHeader("IOWN", 12);
	writeBytes((unsigned __int32)0x06060606);
	writeBytes((unsigned __int32)0x06060606);
	writeBytes((unsigned __int32)0x00000000);
	// Section 'OWNR' - each index represents a player (1 - 12)
	// If a player has a starting location (or units?) on the map 
	// then his index = 6, otherwise his index = 0
	writeHeader("OWNR", 12);
	writeBytes((unsigned __int32)0x00000606);
	writeBytes((unsigned __int32)0x00000000);
	writeBytes((unsigned __int32)0x00000000);
	// Section 'ERA ' - Specifies tileset of the map
	//	BADLANDS = 0,
	//	SPACE_PLATFORM = 1,
	//	INSTALLATION = 2,
	//	ASH_WORLD = 3,
	//	JUNGLE_WORLD = 4,
	//	DESERT = 5,
	//	ICE = 6,
	//	TWILIGHT = 7
	writeHeader("ERA ", 1);
	writeBytes((short)0);
	// Section 'DIM ' - Specifies map dimensions
	writeHeader("DIM ", 4);
	writeBytes((short)64); //width
	writeBytes((short)64); //height
	// Section 'SIDE' - Designates species of each player
	//	ZERG = 0,
	//	TERRAN = 1,
	//	PROTOSS = 2,
	//	INDEPENDENT = 3,       // (unused)
	//	NEUTRAL = 4,
	//	USER_SELECTABLE = 5,
	//	INACTIVE = 7
	writeHeader("SIDE", 12);
	writeBytes((unsigned __int32)0x01020505);
	writeBytes((unsigned __int32)0x00010200);
	writeBytes((unsigned __int32)0x04070707);
	// Section 'MTXM' - Graphical tile map section (only different than TILE if doodads present)
	// Used only by Starcraft (not on Staredit)

	// TODO

	// Section 'PUNI' - Player unit restrictions (all 1s for normal defaults)
	writeHeader("PUNI", 5700);
	for (int i = 0; i < 5700; i++) { writeBytes((char)0x01); }
	// Section 'UPGR' - Player upgrade restrictions (only present on SCM maps)
	// Section 'PTEC' - Player technology restrictions (only present on SCM maps)
	// Section 'UNIT' - Units on map list and flags (36 bytes each)

	// TODO insert starting points

	//Section 'ISOM' - Isometric tile mapping
	// Used only by Staredit (diamond map information) size = (width / 2 + 1) * (height + 1) * 4 - 4 ints

	// TODO

	// Section 'TILE' - Tile map of level's terrain
	// size = width * height ints - 1 int

	// TODO

	// Section 'DD2 ' - Doodad map of level (used only by Staredit)
	// Section 'THG2' - Doodad to unit map (Staredit write, Starcraft read)
	// Section 'MASK' - Fog of War section
	//writeHeader("MASK", width * height);
	//for (int i = 0; i < width * height; i++) { writeBytes((char)0xFF); }
	// Section 'STR ' - Strings section
	// Scenario Title, followed by scenario description
	// Each string is null terminated, and is placed at END of this space, like so:
	// [empty space][Scenario Title][null][ScenarioDescription][null]
	// Mission briefings also go in here, after the description
	// Size: 2107
	// m_bw.Write((UInt64)0x0832081508030400);
	// m_bw.Write((UInt64)0x0802080208020802);
	// Section 'UPRP' - Trigger unit properties section

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
	std::ofstream myfile("test.chk",std::ios::binary);
	myfile.write(&buffer[0], buffer.size());
	myfile.close();
	return;
}
