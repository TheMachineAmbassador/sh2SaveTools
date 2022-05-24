#pragma once
#include <fstream>

namespace file_operations {

    template <typename DT>
	void read_file(DT &file_data,const char* file_name)
	{
        if (std::ifstream input_file(file_name, std::ios::binary | std::ios::in); input_file.is_open())
        {
            input_file.read(reinterpret_cast<char*>(&file_data), sizeof(DT));
            input_file.close();
        }
        else
        {
            std::cout << "Can't read" << std::endl;
        }
	}

    template <typename DT>
	void write_file(DT &file_data, const std::string& file_name)
	{
        if (std::ofstream output_file(file_name, std::ios::out | std::ios::binary); output_file.is_open())
        {
            output_file.write(reinterpret_cast<char*>(&file_data), sizeof(DT));
            output_file.close();
        }
        else
        {
            std::cout << "Can't write" << std::endl;
        }
	}
}