#include "src/data_handler.hpp"
#include "src/data.hpp"
#include "iostream"

int main()
{
    Data data;
    data.read_from_file("1.txt");
    data.print_to_console();
    std::cout << "xueta" << std::endl;
}