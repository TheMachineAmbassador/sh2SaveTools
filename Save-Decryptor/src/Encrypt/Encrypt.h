#pragma once

#include "SaveData.h"
#include "inheritance.h"

class Encrypt : public inheritance
{
protected:
	void encrypt_data() const;
	void move_hashes_to_first_byte() const;
	void copy_first_header_bytes_to_last();
public:
	void run_process() override;

	Encrypt(SaveFileBlocks &file, SaveFileThings* save_file_things);
};
