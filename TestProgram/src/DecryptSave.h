#pragma once

#include "FileOperations/FileOperations.h"
#include "Encrypt/Encrypt.h"
#include "Decrypt/Decrypt.h"

bool DecryptSH2Save(SaveFileBlocks& file_data);
bool EncryptSH2Save(SaveFileBlocks& file_data);
bool check_file(GameMemory gameMemory);