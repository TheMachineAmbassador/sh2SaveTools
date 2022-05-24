#pragma once

#include "typedef.h"

struct SaveFileBlocks
{
	uint32_t file_header;
	uint32_t save_file_after_four_byte;
	uint32_t save_file_after_eight_byte;
	char save_data[8164];
	uint32_t UINT_009361f8;
	uint32_t UINT_009361fc;
	uint32_t last_byte_after_four_byte;
	uint32_t last_four_byte_of_save;
};

struct SaveFileThings
{
	uint32_t hash_first_part[6];
	uint32_t hash_second_part[4];
	uint32_t INT_0093bff0;
	uint32_t* points_To_Save_File_After_8_Byte;
	uint32_t counter_for_loops;
	uint32_t INT_0093c000;
	uint32_t DAT_0093c004;
	uint32_t DAT_0093c008;
	uint32_t junk04;
	uint32_t DAT_0093c010;
	uint32_t DAT_0093c014;
	u32 uVar10;
	u32 hash_location;
};