#pragma once

#include <vector>
#include <fstream>
#include <sstream>

#include <iomanip>

class Data
{
private:
    std::vector<std::vector<double>> _table;
    int size_x, size_y;
    std::string _fileName;
public:
    Data();

    void read_from_file(std::string file_name);
    void write_to_file(std::vector<double> *result);
    void print_to_console();
    std::vector<std::vector<double>>* get_table_ptr();
    std::vector<std::vector<double>> get_table();
    std::vector<double>* get_func_ptr();
    std::vector<double> get_func();
};

Data::Data() {}

void Data::read_from_file(std::string file_name)
{
    _fileName = file_name;
    std::ifstream file(file_name.c_str());
    if (!file.is_open())
    {
        std::cout << "cannot open file" << std::endl;
        throw noexcept("could not read the file");
    }

    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);

    char comma;

    ss >> size_x >> comma >> size_y;

    _table.resize(size_x, std::vector<double>(size_y));

    for (int i = 0; i < size_x; ++i)
    {
        std::getline(file, line);
        std::stringstream ss(line);
        for (int j = 0; j < size_y; ++j)
        {
            ss >> _table[i][j];
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }
    }

    if (_table[_table.size() - 1][0] == 0)
    {
        for (int i = 1; i < _table[0].size(); i++)
        {
            _table[_table.size() - 1][i] *= -1;
        }
    }

}

void Data::write_to_file(std::vector<double> *result)
{
    std::ofstream out;
    out.open("result_" + _fileName);
    if (out.is_open())
    {
        for (int i = 0; i < result->size() - 1; i ++)
        {
            out << std::setw(4) << "x" << i + 1 << " | ";
        }
        out << std::setw(5) << "F ="  << " | " << std::endl;
        for (int i = 0; i < result->size() - 1; i ++)
        {
            out << std::setw(5) <<  (*result)[i] << " | ";
        }
        out << std::setw(5) << (*result)[result->size() - 1]  << " | " << std::endl;
    }
    else 
    { 
        std::cout << "cannot open file" << std::endl; 
        throw noexcept("could not read the file"); 
    }
}

void Data::print_to_console()
{
    std::cout << "matrix:" << std::endl;   
    for (int x = 0; x < _table[0].size(); x++)
    {
        if (x == 0) { std::cout << std::setw(5) << " <="  << " | "; }
        else { std::cout << std::setw(4) << "x" << x + 1 << " | "; }
    }
    std::cout << std::endl;
    for (int x = 0; x < size_x; ++x)
    {
        for (int y = 0; y < size_y; ++y)
        {
            std::cout << std::setw(5) << _table[x][y] << " | ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "----------------------------------------------" << std:: endl;
}

std::vector<std::vector<double>>* Data::get_table_ptr()
{
    return &_table;
}


std::vector<std::vector<double>> Data::get_table()
{
    return _table;
}
