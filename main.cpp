#include "src/data_handler.hpp"
#include "src/data.hpp"
#include "src/simplex.hpp"

int main()
{
    Data data;
    data.read_from_file("2.txt");
    data.print_to_console();
    Simplex simplex(&data);
    simplex.calculate();
}