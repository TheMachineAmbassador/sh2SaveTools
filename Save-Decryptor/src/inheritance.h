#pragma once

class inheritance
{
protected:
	SaveFileThings* saveFileThings = nullptr;
	u32* buffer_to_hash = nullptr;
	u8 HASH_BYTE{};
	u8* hash_crypt = nullptr;
	SaveFileBlocks* fileData = nullptr;
public:
	virtual void run_process()
	{
		return;
	}
	
	void create_hash_for_decryption();
};
