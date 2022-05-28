#include "Encrypt.h"
#include <iostream>

void Encrypt::encrypt_data() const
{
	int index_multiplier1 = 0;
	int index_multiplier2 = 0;

	u32 decrypt_end_counter = saveFileThings->counter_for_loops;
	u32* file_data_buffer = saveFileThings->points_To_Save_File_After_8_Byte;

	saveFileThings->DAT_0093c008 = saveFileThings->uVar10;
	while (true)
	{
		file_data_buffer[0] = file_data_buffer[0] ^ saveFileThings->hash_first_part[index_multiplier1 * 2] ^ buffer_to_hash[index_multiplier2 * 2];
		file_data_buffer[1] = file_data_buffer[1] ^ saveFileThings->hash_first_part[index_multiplier1 * 2 + 1] ^ buffer_to_hash[index_multiplier2 * 2 + 1];

		index_multiplier1 = index_multiplier1 + 1;

		if (2 < index_multiplier1) {
			index_multiplier1 = 0;
			index_multiplier2 = index_multiplier2 + 1;
			if (0xf < index_multiplier2) {
				index_multiplier2 = 0;
			}
		}

		saveFileThings->DAT_0093c008 = saveFileThings->DAT_0093c008 - 
			(file_data_buffer[0] & 0xff) - (file_data_buffer[0] >> 8 & 0xff) - ((file_data_buffer[0] >> 8 & 0xff00) >> 8) - (file_data_buffer[0] >> 0x18) - 
			(file_data_buffer[1] & 0xff) - (file_data_buffer[1] >> 8 & 0xff) - (file_data_buffer[1] >> 0x10 & 0xff) - (file_data_buffer[1] >> 0x18);

		decrypt_end_counter = decrypt_end_counter - 1;
		if (decrypt_end_counter < 1) {
			break;
		}
		file_data_buffer = file_data_buffer + 2;
	}

	const u8 bVar4 = static_cast<s8>(saveFileThings->hash_location) & 0x1f;
	const u32 get_encryption_spot = (saveFileThings->hash_location - saveFileThings->DAT_0093c008) - saveFileThings->uVar10;
	const u8 bVar3 = static_cast<s8>(saveFileThings->DAT_0093c008) & 0x1f;

	fileData->file_header = saveFileThings->uVar10 >> (0x20 - bVar4 & 0x1f) | saveFileThings->uVar10 << bVar4;
	fileData->save_file_after_four_byte = get_encryption_spot >> (0x20 - bVar4 & 0x1f) | get_encryption_spot << bVar4;
	fileData->UINT_009361f8 = saveFileThings->uVar10 * saveFileThings->hash_location >> (0x20 - bVar3 & 0x1f) | saveFileThings->uVar10 * saveFileThings->hash_location << bVar3;
	saveFileThings->points_To_Save_File_After_8_Byte = reinterpret_cast<u32*>(reinterpret_cast<s32>(fileData->save_data) + 0x1fbc);
	saveFileThings->INT_0093c000 = saveFileThings->hash_location % 0x3f8;
	saveFileThings->counter_for_loops = saveFileThings->hash_location % 0x3f8;

#if _DEBUG
	std::cout << "Hash location: " << saveFileThings->hash_location << std::endl;
	std::cout << "0x93c008: " << saveFileThings->DAT_0093c008 << std::endl;
	std::cout << "uVar10: " << saveFileThings->uVar10 << std::endl;
	std::cout << "File header: " << fileData->file_header << std::endl;
	std::cout << "fileData->save_file_after_four_byte: " << fileData->save_file_after_four_byte << std::endl;
	std::cout << "fileData->UINT_009361f8: " << fileData->UINT_009361f8 << std::endl;
	std::cout << "saveFileThings->points_To_Save_File_After_8_Byte: "<< saveFileThings->points_To_Save_File_After_8_Byte << std::endl;
	std::cout << "saveFileThings->counter_for_loops: " << saveFileThings->counter_for_loops << std::endl;
#endif
}

void Encrypt::move_hashes_to_first_byte() const
{
	u32* file_data_buffer = saveFileThings->points_To_Save_File_After_8_Byte;
	u32* file_data_buffer2 = saveFileThings->points_To_Save_File_After_8_Byte;
	u32 counter = saveFileThings->counter_for_loops;
	if (0 < static_cast<s32>(saveFileThings->counter_for_loops)) {
		do {
			file_data_buffer = file_data_buffer2 + -2;
			counter = counter - 1;
			file_data_buffer2[8] = file_data_buffer2[-2];
			file_data_buffer2[9] = file_data_buffer2[-1];
			file_data_buffer2 = file_data_buffer;
		} while (counter != 0);
	}
	*file_data_buffer = saveFileThings->hash_first_part[0];
	file_data_buffer[1] = saveFileThings->hash_first_part[1];
	file_data_buffer[2] = saveFileThings->hash_first_part[2];
	file_data_buffer[3] = saveFileThings->hash_first_part[3];
	file_data_buffer[4] = saveFileThings->hash_first_part[4];
	file_data_buffer[5] = saveFileThings->hash_first_part[5];
	file_data_buffer[6] = saveFileThings->hash_second_part[0];
	file_data_buffer[7] = saveFileThings->hash_second_part[1];
	file_data_buffer[8] = saveFileThings->hash_second_part[2];
	file_data_buffer[9] = saveFileThings->hash_second_part[3];
}

void Encrypt::copy_first_header_bytes_to_last() const
{
	fileData->last_byte_after_four_byte = 0;
	fileData->last_four_byte_of_save = 0;
	u32* save_data_buffer = &fileData->save_file_after_eight_byte;
	s32 counter = 0x155;
	do {
		fileData->last_byte_after_four_byte =
			save_data_buffer[-2] ^ save_data_buffer[2] ^ fileData->last_byte_after_four_byte ^
			*save_data_buffer;
		fileData->last_four_byte_of_save =
			save_data_buffer[-1] ^ save_data_buffer[3] ^ fileData->last_four_byte_of_save ^ save_data_buffer[1]
			;
		save_data_buffer = save_data_buffer + 6;
		counter = counter + -1;
	} while (counter != 0);
}

void Encrypt::run_process()
{
	create_hash_for_decryption();
	encrypt_data();
	move_hashes_to_first_byte();
	copy_first_header_bytes_to_last();
}

Encrypt::Encrypt(SaveFileBlocks &file, SaveFileThings* save_file_things)
{
	fileData = &file;
	this->saveFileThings = save_file_things;

	saveFileThings->points_To_Save_File_After_8_Byte = &fileData->save_file_after_eight_byte;
	saveFileThings->counter_for_loops = 0x3f8;
}
