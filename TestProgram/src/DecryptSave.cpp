#include <string>
#include <memory>

#include "DecryptSave.h"

// Reference: https://stackoverflow.com/a/6417908
std::string remove_extension(const std::string& filename) {
	const size_t lastdot = filename.find_last_of('.');
	if (lastdot == std::string::npos) return filename;
	return filename.substr(0, lastdot);
}

bool DecryptSH2Save(SaveFileBlocks& file_data, SaveFileThings& saveThings, std::string file_name)
{
	std::string name_buffer = file_name;
	std::string hash_name = file_name;

	const auto decrypt = std::make_unique<Decrypt>(file_data,&saveThings);
	decrypt->run_process();

	name_buffer = name_buffer + ".decrypted";
	if (!file_operations::write_file(file_data, name_buffer))
	{
		return false;
	}
	hash_name = hash_name + ".hashkey";
	if (!file_operations::write_file(saveThings, hash_name))
	{
		return false;
	}
	return true;
}

bool EncryptSH2Save(SaveFileBlocks& file_data, SaveFileThings& saveThings, std::string name_buffer)
{
	std::string hash_name = remove_extension(name_buffer);
	hash_name = hash_name + ".hashkey";
	if (!file_operations::read_file(saveThings, hash_name))
	{
		return false;
	}

	const auto encrypt = std::make_unique<Encrypt>(file_data, &saveThings);
	const auto decrypt = std::make_unique<Decrypt>(file_data, &saveThings);

	encrypt->run_process();
	decrypt->run_process();
	encrypt->run_process();

	name_buffer = remove_extension(name_buffer) + ".encrypted";

	if (!file_operations::write_file(file_data, name_buffer))
	{
		return false;
	}
	return true;
}
