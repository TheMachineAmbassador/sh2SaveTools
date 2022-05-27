#include "inheritance.h"

void inheritance::create_hash_for_decryption()
{
	s32 counter = 0;

	buffer_to_hash = new u32[128];

	hash_crypt = reinterpret_cast<u8*>(buffer_to_hash);

	do {
		this->HASH_BYTE = *reinterpret_cast<u8*>(reinterpret_cast<s32>(saveFileThings->hash_second_part) + counter);
		this->hash_crypt[0] = this->HASH_BYTE;
		this->hash_crypt[1] = this->HASH_BYTE;
		this->hash_crypt[2] = this->HASH_BYTE;
		this->hash_crypt[3] = this->HASH_BYTE;
		this->hash_crypt[4] = this->HASH_BYTE;
		this->hash_crypt[5] = this->HASH_BYTE;
		this->hash_crypt[6] = this->HASH_BYTE;
		this->hash_crypt[7] = this->HASH_BYTE;
		this->hash_crypt = this->hash_crypt + 8;
		counter = counter + 1;
	} while (counter < 0x10);
}
