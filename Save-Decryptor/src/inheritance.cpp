#include "inheritance.h"

void inheritance::create_hash_for_decryption()
{
	s32 counter = 0;
	buffer_to_hash = new u32[32];
	hash_crypt = reinterpret_cast<u8*>(buffer_to_hash);

	while (counter < 0x10) {
		u8 hashByte = *reinterpret_cast<u8*>(reinterpret_cast<s32>(saveFileThings->hash_second_part) + counter);

		for (s32 i = 0; i < 8; ++i) {
			hash_crypt[i] = hashByte;
		}

		hash_crypt += 8;
		counter++;
	}
}