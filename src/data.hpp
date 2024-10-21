#pragma once

#include <vector>
#include <fstream>
#include <sstream>

#include <iomanip>

class Data
{
private:
    std::vector<std::vector<double>> _table;
    std::vector<double> _basis;
    std::vector<double> _func;
    int size_x, size_y;

public:
    Data(); // data initialization

    void read_from_file(std::string file_name);
    void write_to_file();
    void print_to_console();
    std::vector<std::vector<double>>* get_table_ptr();
    std::vector<std::vector<double>> get_table();
    std::vector<double>* get_basis_ptr();
    std::vector<double>* get_func_ptr();
};

Data::Data() {}

void Data::read_from_file(std::string file_name)
{
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
    _func.resize(size_y);

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
    ss.str("");
    ss.clear();

    std::getline(file, line);
    ss.str(line);
    for (int i = 0; i < _func.size(); i++)
    {
        ss >> _func[i];
        if (ss.peek() == ',')
        {
            ss.ignore();
        }
    }
}

void Data::write_to_file()
{
    throw noexcept("has no implementation");
}

void Data::print_to_console()
{
    for (int x = 0; x < size_x; ++x)
    {
        for (int y = 0; y < size_y; ++y)
        {
            std::cout << std::setw(5) << _table[x][y]; // setw(4) задает ширину поля вывода
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<double>>* Data::get_table_ptr()
{
    return &_table;
}

std::vector<double>* Data::get_basis_ptr()
{
    return &_basis;
}

std::vector<double>* Data::get_func_ptr()
{
    return &_func;
}

std::vector<std::vector<double>> Data::get_table()
{
    return _table;
}