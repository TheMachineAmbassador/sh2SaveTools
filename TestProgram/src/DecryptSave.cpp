#include <iostream>
#include <string>

#include "FileOperations/FileOperations.h"
#include "Encrypt/Encrypt.h"
#include "Decrypt/Decrypt.h"

#define LOG_STRING(x) printf("%s",x)

#define DECRYPT_FILE 1
#define ENCRYPT_FILE 2

Decrypt* decrypt;
Encrypt* encrypt;

void choose(SaveFileBlocks &file_data, const char* file_name, const u8 type)
{
	SaveFileThings saveThings{};
	std::string name_buffer = file_name;
	std::string hash_name = file_name;
	hash_name = hash_name + ".hashkey";

	switch (type)
	{
	case 1:
		decrypt = new Decrypt(&file_data, &saveThings);
		decrypt->run_process();
		LOG_STRING("Successfully Decrypted!\n");
		name_buffer = name_buffer + ".decrypted";
		file_operations::write_file(file_data, name_buffer);
		hash_name = name_buffer + ".hashkey";
		file_operations::write_file(saveThings, hash_name);

		break;
	case 2:
		file_operations::read_file(saveThings, hash_name.c_str());
		encrypt = new Encrypt(file_data, &saveThings);
		encrypt->run_process();
		LOG_STRING("Successfully Encrypted!\n");

		decrypt = new Decrypt(&file_data,&saveThings);
		decrypt->run_process();

		hash_name = name_buffer + ".hashkey";
		file_operations::write_file(saveThings, hash_name);

		file_operations::read_file(saveThings, hash_name.c_str());
		encrypt = new Encrypt(file_data, &saveThings);
		encrypt->run_process();

		name_buffer = name_buffer + ".encrypted";
		file_operations::write_file(file_data, name_buffer);

		break; 
	default:
		LOG_STRING("Wrong Choice!\n");
		break;
	}
}

int main(int argc, char* argv[])
{
	SaveFileBlocks file_data = {};

	if (argc == 3)
	{
		const std::string arg1(argv[1]);

		if (arg1 == "--decrypt" || arg1 == "-d")
		{
			file_operations::read_file(file_data,argv[2]);
			choose(file_data, argv[2], DECRYPT_FILE);
		}
		if (arg1 == "--encrypt" || arg1 == "-e")
		{
			file_operations::read_file(file_data,argv[2]);
			choose(file_data, argv[2], ENCRYPT_FILE);
		}
	}
	else if(argc == 2)
	{
		LOG_STRING("What do you want to do with file you specified for?\n1-) For Decryption\n2-) For Encryption\n");
		LOG_STRING("Selection: ");
		int answer = 0;
		std::cin >> answer;

		std::cout << answer << std::endl;
		if(answer == 1)
		{
			file_operations::read_file(file_data, argv[1]);
			choose(file_data, argv[1], DECRYPT_FILE);
		}
		else if(answer == 2)
		{
			file_operations::read_file(file_data, argv[1]);
			choose(file_data, argv[1], ENCRYPT_FILE);
		}
		else
		{
			LOG_STRING("Usage: TestProgram.exe [Options] [FileName]\n");
			LOG_STRING("--decrypt - For Decrypting Save Files\n");
			LOG_STRING("--encrypt - For Re-Encrypting Save Files\n");
			LOG_STRING("Or you can simply hover your files on to exe\n");
		}
	}
	else
	{
		LOG_STRING("Usage: TestProgram.exe [Options] [FileName]\n");
		LOG_STRING("--decrypt - For Decrypting Save Files\n");
		LOG_STRING("--encrypt - For Re-Encrypting Save Files\n");
		LOG_STRING("Or you can simply hover your files on to exe\n");
	}

	#if _WIN32
		system("PAUSE");
	#endif
;	return 0;
}