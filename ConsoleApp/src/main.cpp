#include "DecryptSave.h"

#define LOG_STRING(x) printf("%s",x);
#define LOG_STRING_NL(x) printf("%s\n",x);

void printHelp()
{
	LOG_STRING_NL("Usage: TestProgram.exe [Options] [FileName]");
	LOG_STRING_NL("--decrypt - For Decrypting Save Files");
	LOG_STRING_NL("--encrypt - For Re-Encrypting Save Files");
	LOG_STRING_NL("Or you can simply hover your files on to exe");
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

				if (!DecryptSH2Save(file_data, saveThings, argv[2]))
				{
					LOG_STRING_NL("Decryption Unsuccessfull!");
				}
				else LOG_STRING_NL("Decryption Completed!");
			}
			if (arg1 == "--encrypt" || arg1 == "-e")
			{
				if (!EncryptSH2Save(file_data, saveThings, argv[2]))
				{
					LOG_STRING_NL("Encryption Unsuccessfull!");
				}
				else LOG_STRING_NL("Encryption Completed!");
			}
			else printHelp();
		}
	}
	else if (argc == 2)
	{
		LOG_STRING_NL("What do you want to do with file you specified for?\n1-) For Decryption\n2-) For Encryption\n");
		LOG_STRING("Selection: ");
		s32 answer = 0;
		std::cin >> answer;
		if (file_operations::read_file(file_data, argv[1]))
		{
			if (answer == 1)
			{
				if (!DecryptSH2Save(file_data, saveThings, argv[1]))
				{
					LOG_STRING_NL("Decryption Unsuccessfull!");
				}
				else LOG_STRING_NL("Decryption Completed!");
			}
			else if (answer == 2)
			{
				if (!EncryptSH2Save(file_data, saveThings, argv[1]))
				{
					LOG_STRING_NL("Encryption Unsuccessfull!");
				}
				else LOG_STRING_NL("Encryption Completed!");
			}
		}
	}
	else printHelp();

#if _WIN32
	system("PAUSE");
#endif
	;	return 0;
}