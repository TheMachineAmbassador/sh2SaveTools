#pragma once
#include <fstream>

namespace file_operations {

    template <typename DT>
	bool read_file(DT &file_data, const std::string& file_name)
	{
        if (std::ifstream input_file(file_name, std::ios::binary | std::ios::in); input_file.is_open())
        {
            input_file.read(reinterpret_cast<char*>(&file_data), sizeof(DT));
            input_file.close();
        }
        else
        {
            std::cout << "There is an issue while reading: " << file_name << std::endl;
            return false;
        }
        return true;
	}

    template <typename DT>
	bool write_file(DT &file_data, const std::string& file_name)
	{
        if (std::ofstream output_file(file_name, std::ios::out | std::ios::binary); output_file.is_open())
        {
            output_file.write(reinterpret_cast<char*>(&file_data), sizeof(DT));
            output_file.close();
        }
        else
        {
            std::cout << "There is an issue while writing file: " << file_name << std::endl;
            return false;
        }
        return true;
	}

    // Reference: https://stackoverflow.com/a/6417908
    inline std::string remove_extension(const std::string& filename) {
        const size_t lastdot = filename.find_last_of('.');
        if (lastdot == std::string::npos) return filename;
        return filename.substr(0, lastdot);
    }
}