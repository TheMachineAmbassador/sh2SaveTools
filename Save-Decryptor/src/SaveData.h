#pragma once

#include "typedef.h"

struct SaveFileBlocks
{
	u32 file_header;
	u32 save_file_after_four_byte;
	u32 save_file_after_eight_byte;
	s8 save_data[8164];
	u32 UINT_009361f8;
	u32 UINT_009361fc;
	u32 last_byte_after_four_byte;
	u32 last_four_byte_of_save;
};

struct SaveFileThings
{
	u32 hash_first_part[6];
	u32 hash_second_part[4];
	u32 INT_0093bff0;
	u32* points_To_Save_File_After_8_Byte;
	u32 counter_for_loops;
	u32 INT_0093c000;
	u32 DAT_0093c004;
	u32 DAT_0093c008;
	u32 junk04;
	u32 DAT_0093c010;
	u32 DAT_0093c014;
	u32 uVar10;
	u32 hash_location;
};
