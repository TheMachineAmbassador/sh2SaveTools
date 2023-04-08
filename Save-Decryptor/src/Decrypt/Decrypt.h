#pragma once

#include "inheritance.h"
#include <SaveData.h>

class Decrypt : public inheritance
{
protected:
	void get_hash() const;
	void create_hash_list() const;
	void decrypt_save() const;
public:
	void run_process() override;

	Decrypt(SaveFileBlocks &file);
	~Decrypt() override
	{
		delete buffer_to_hash;
	}
};
