#pragma once

#include<vector>
#include<fstream>
#include<sstream>

#include <iomanip>

class Data
{
private:
    std::vector<std::vector<double>> table;
    std::vector<double> basis;
    std::vector<double> goal_fn;
    std::vector<double> B;
    bool is_max;
    int size_x, size_y;

public:
    Data(); // data initialization

    void read_from_file(std::string file_name);
    void write_to_file();
    void print_to_console();
};

Data::Data()
{

}

void Data::read_from_file(std::string file_name)
{
    std::ifstream file(file_name.c_str());
    if(!file.is_open()) 
    {
        std::cout << "cannot open file" << std::endl;
        throw noexcept("dodelat' potom");
    }

    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);

    char comma;

    ss >> size_y >> comma >> size_x;

    table.resize(size_x, std::vector<double>(size_y));

    for (int i = 0; i < size_x; ++i) {
        std::getline(file, line);
        std::stringstream ss(line);
        for (int j = 0; j < size_y; ++j) {
            ss >> table[i][j];
            if (ss.peek() == ',') {
                ss.ignore();
            }
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
            std::cout << std::setw(5) << table[x][y];  // setw(4) задает ширину поля вывода
        }
        std::cout << std::endl;
    }
}