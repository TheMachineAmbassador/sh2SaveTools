#include "Decrypt.h"

#include <cstring>

void Decrypt::get_hash() const
{
    this->saveFileThings->points_To_Save_File_After_8_Byte = &fileData->gameMemory.saveType;
    this->saveFileThings->counter_for_loops = 0x3fd;

    u32* file_data_buffer = saveFileThings->points_To_Save_File_After_8_Byte;

    u32 counter_loop = saveFileThings->counter_for_loops;
    u32 hash_location = 0;
    u32 uVar10 = 0;
    while (true)
    {
        if ((file_data_buffer[0] & 0xf) == 0) {
            hash_location = hash_location + 1;
        }
        if ((file_data_buffer[0] >> 8 & 0xf) == 0) {
            hash_location = hash_location + 1;
        }
        if ((file_data_buffer[0] >> 8 & 0xf00) == 0) {
            hash_location = hash_location + 1;
        }
        if ((file_data_buffer[0] >> 8 & 0xf0000) == 0) {
            hash_location = hash_location + 1;
        }
        if ((file_data_buffer[1] & 0xf) == 0) {
            hash_location = hash_location + 1;
        }
        if ((file_data_buffer[1] >> 8 & 0xf) == 0) {
            hash_location = hash_location + 1;
        }
        if ((file_data_buffer[1] >> 0x10 & 0xf) == 0) {
            hash_location = hash_location + 1;
        }
        if ((file_data_buffer[1] >> 0x18 & 0xf) == 0) {
            hash_location = hash_location + 1;
        }
        uVar10 = uVar10 + (file_data_buffer[0] & 0xff) + (file_data_buffer[0] >> 8 & 0xff) + ((file_data_buffer[0] >> 8 & 0xff00) >> 8) + (file_data_buffer[0] >> 0x18)
						+ (file_data_buffer[1] & 0xff) + (file_data_buffer[1] >> 8 & 0xff) + (file_data_buffer[1] >> 0x10 & 0xff) + (file_data_buffer[1] >> 0x18);

        counter_loop = counter_loop - 1;
        if (counter_loop < 1) break;
        file_data_buffer = file_data_buffer + 2;
    }

    u32* hold_hash_buffer = saveFileThings->hash_first_part;
    file_data_buffer = fileData->UINT_ARRAY_009361d0 + (hash_location % 0x3f8) * -2;
    saveFileThings->points_To_Save_File_After_8_Byte = file_data_buffer;
    memcpy(hold_hash_buffer, file_data_buffer, 0x28);
    saveFileThings->counter_for_loops = hash_location % 0x3f8;

    saveFileThings->uVar10 = uVar10;
    saveFileThings->hash_location = hash_location;
}

void Decrypt::create_hash_list() const
{
    if (0 < saveFileThings->counter_for_loops) {
        u32* some_points_to_data = saveFileThings->points_To_Save_File_After_8_Byte + 10;
        for (int what = (saveFileThings->counter_for_loops & 0x1fffffff) << 1; what != 0; what = what - 1) {
            *saveFileThings->points_To_Save_File_After_8_Byte = *some_points_to_data;
            some_points_to_data = some_points_to_data + 1;
            saveFileThings->points_To_Save_File_After_8_Byte = saveFileThings->points_To_Save_File_After_8_Byte + 1;
        }
    }
    saveFileThings->points_To_Save_File_After_8_Byte = &fileData->gameMemory.saveType;
    saveFileThings->counter_for_loops = 0x3f8;
}

void Decrypt::decrypt_save() const
{
    int index_multiplier1 = 0;
    int index_multiplier2 = 0;

    u32 decrypt_end_counter = saveFileThings->counter_for_loops;
    u32* file_data_buffer = saveFileThings->points_To_Save_File_After_8_Byte;

    while (true)
    {
        file_data_buffer[0] = file_data_buffer[0] ^ saveFileThings->hash_first_part[index_multiplier1 * 2] ^ buffer_to_hash[index_multiplier2 * 2];
        file_data_buffer[1] = file_data_buffer[1] ^ saveFileThings->hash_first_part[index_multiplier1 * 2 + 1] ^ buffer_to_hash[index_multiplier2 * 2 + 1];

        file_data_buffer = file_data_buffer + 2;
        index_multiplier1 = index_multiplier1 + 1;

        if (2 < index_multiplier1) {
            index_multiplier1 = 0;
            index_multiplier2 = index_multiplier2 + 1;
            if (0xf < index_multiplier2) {
                index_multiplier2 = 0;
            }
        }

        decrypt_end_counter = decrypt_end_counter - 1;
        if (decrypt_end_counter < 1) {
            return;
        }
    }
}

void Decrypt::run_process()
{
    get_hash();
    create_hash_for_decryption();
    create_hash_list();
    decrypt_save();
}

Decrypt::Decrypt(SaveFileBlocks& file, SaveFileThings* save_file_things)
{
    this->fileData = &file;
    this->saveFileThings = save_file_things;
}
