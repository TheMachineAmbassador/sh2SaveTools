#pragma once

#include "FileOperations/FileOperations.h"
#include "Encrypt/Encrypt.h"
#include "Decrypt/Decrypt.h"

bool DecryptSH2Save(SaveFileBlocks& file_data, SaveFileThings& saveThings, std::string file_name);
bool EncryptSH2Save(SaveFileBlocks& file_data, SaveFileThings& saveThings, std::string name_buffer);
bool check_file(GameMemory gameMemory);
std::string remove_extension(const std::string& filename);