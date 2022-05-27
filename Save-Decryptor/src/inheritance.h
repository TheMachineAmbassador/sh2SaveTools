#pragma once

#include "typedef.h"
#include "SaveData.h"

class inheritance
{
protected:
	SaveFileThings* saveFileThings = nullptr;
	u32* buffer_to_hash = nullptr;
	u8 HASH_BYTE{};
	u8* hash_crypt = nullptr;
	SaveFileBlocks* fileData = nullptr;
public:
	inheritance() = default;
	virtual ~inheritance() = default;

	virtual void run_process(){}

	void create_hash_for_decryption();
};
