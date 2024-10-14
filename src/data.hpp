#pragma once

#include<vector>
#include<fstream>
#include<sstream>

class Data
{
private:
    std::vector<std::vector<float>> table;
    std::vector<float> basis;
    std::vector<float> goal_fn;
    std::vector<float> B;
    bool is_max;
    int size_x, size_y;

public:
    Data(); // data initialization

    void read_from_file(std::string file_name);
    void write_to_file();
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

    ss << size_x << comma << size_y;

    std::cout << size_x << " " << size_y << std::endl;
}

void Data::write_to_file()
{
    throw noexcept("has no implementation");
}
