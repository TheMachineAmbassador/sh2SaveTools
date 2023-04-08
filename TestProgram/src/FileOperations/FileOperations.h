#pragma once
#include <iostream>
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
}