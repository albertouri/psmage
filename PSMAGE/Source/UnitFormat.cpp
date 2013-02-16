#include "UnitFormat.h"

UnitFormat::UnitFormat()
{
	newUnit(64,32);
}

UnitFormat::~UnitFormat()
{

}

void UnitFormat::newUnit(short x, short y)
{
	// 	1 long - Serial number for the unit.
	writeBytes((__int32)0x01ad9e08);
	// 	1 int - X coordinate of unit
	writeBytes(x);
	// 	1 int - Y coordinate of unit
	writeBytes(y);
	// 	1 int - Unit type
	writeBytes((__int16)0x00bc);
	// 	1 byte - Unknown/unused. Maybe padding?
	// 	1 byte - Paired building type
	writeBytes((__int16)0x0000);
	// 	1 int - Flag of which special properties can be applied to unit, and are valid
	writeBytes((__int16)0x0018);
	// 	1 int - I think this is a flag for which elements of the unit data are valid.
	writeBytes((__int16)0x0013);
	// 	1 byte - Player number that owns unit(0-based.)
	writeBytes((__int8)0x00);
	// 	1 byte - Hit points %(1-100)
	writeBytes((__int8)0x64);
	// 	1 byte - Shield points %(1-100)
	writeBytes((__int8)0x64);
	// 	1 byte - Energy points %(1-100)
	writeBytes((__int8)0x64);
	// 	1 long - Resource amount(for resources only)
	writeBytes((__int32)0x00001388);
	// 	1 int - No. of units in hanger
	writeBytes((__int16)0x0000);
	// 	1 int - Unit state flags
	writeBytes((__int16)0x0000);
	// 	4 bytes - Unknown/unused. Maybe padding?
	writeBytes((__int32)0x00000000);
	// 	1 long - Serial number of paired building target. 0 if not paired.
	writeBytes((__int32)0x00000000);
}
