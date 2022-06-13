#include "DecryptSave.h"

#define LOG_STRING(x)    printf("%s",x);
#define LOG_STRING_NL(x) printf("%s\n",x);

void printHelp()
{
	LOG_STRING_NL("Usage: TestProgram.exe [Options] [FileName]");
	LOG_STRING_NL("--decrypt - For Decrypting Save Files");
	LOG_STRING_NL("--encrypt - For Re-Encrypting Save Files");
	LOG_STRING_NL("Or you can simply hover your files on to exe");
}

bool Decrypt_Func(SaveFileBlocks &file_data, SaveFileThings &saveThings, std::string file_name)
{
	if (!DecryptSH2Save(file_data, saveThings, file_name))
	{
		LOG_STRING_NL("Invalid File!");
		return false;
	}

	LOG_STRING_NL("Decryption completed, now writing to a file!");

	std::string name_buffer = remove_extension(file_name) + ".decrypted";
	std::string hash_name =   remove_extension(file_name) + ".hashkey";

	if (file_operations::write_file(file_data, name_buffer))
	{
		printf("File %s is succesfully written\n", name_buffer.c_str());
	} else printf("Can't write %s file\n", name_buffer.c_str());

	if (file_operations::write_file(saveThings, hash_name))
	{
		printf("File %s is succesfully written\n", hash_name.c_str());
	} else printf("Can't write %s file\n", hash_name.c_str());

	return true;
}

bool Encrypt_Func(SaveFileBlocks& file_data, SaveFileThings& saveThings, std::string file_name)
{
	std::string name_buffer = remove_extension(file_name) + ".encrypted";
	std::string hash_name =   remove_extension(file_name) + ".hashkey";

	if (file_operations::read_file(saveThings, hash_name))
	{
		if (!EncryptSH2Save(file_data, saveThings, file_name))
		{
			LOG_STRING_NL("Invalid File!");
			return false;
		}

		LOG_STRING_NL("Encryption completed, now writing to a file!");
		
		if (file_operations::write_file(file_data, name_buffer))
		{
			printf("File %s is succesfully written\n", name_buffer.c_str());
		} else printf("Can't write %s file\n", name_buffer.c_str());
	}

	return true;
}

int main(int argc, char* argv[])
{
	SaveFileBlocks file_data = {};
	SaveFileThings saveThings = {};

	if (argc == 3)
	{
		const std::string arg1(argv[1]);
		if (file_operations::read_file(file_data, argv[2]))
		{
			if (arg1 == "--decrypt" || arg1 == "-d")
			{
				if (Decrypt_Func(file_data, saveThings, argv[2]))
				{
					LOG_STRING_NL("Decryption Completed");
				}
			}

			else if (arg1 == "--encrypt" || arg1 == "-e")
			{
				if (Encrypt_Func(file_data, saveThings, argv[2]))
				{
					LOG_STRING_NL("Encryption Completed");
				}
			}
			else printHelp();
		}
	}

	else if (argc == 2)
	{
		LOG_STRING_NL("What do you want to do with file you specified for?\n1-) For Decryption\n2-) For Encryption\n");
		LOG_STRING("Selection: ");
		u16 answer = 0;
		std::cin >> answer;

		if (answer == 1)
		{
			if (file_operations::read_file(file_data, argv[1]))
			{
				if (Decrypt_Func(file_data, saveThings, argv[1]))
				{
					LOG_STRING_NL("Decryption Completed");
				}
			}
		}

		else if (answer == 2)
		{
			if (file_operations::read_file(file_data, argv[1]))
			{
				if (Encrypt_Func(file_data, saveThings, argv[1]))
				{
					LOG_STRING_NL("Encryption Completed");
				}
			}
		}

		else LOG_STRING_NL("Invalid Option");
	}
	else printHelp();

#if _WIN32
	system("PAUSE");
#endif
		return 0;
}