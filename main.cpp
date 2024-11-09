#include "src/data_handler.hpp"
#include "src/data.hpp"
#include "src/simplex.hpp"
#include "src/task_creator.hpp"

#include <omp.h>

int main()
{
    //
    double t_start, t_end;

    t_start = omp_get_wtime();

    // create task
    TaskCreator creator;
    creator.generateMatrixFile(4, 4, "task.txt");

    // simplex
    Data data;
    data.read_from_file("task.txt");
    //data.print_to_console();
    Simplex simplex(&data);
    simplex.calculate();
    
    //
    t_end = omp_get_wtime();
    std::cout << "Work took " << t_end - t_start << " seconds" << std::endl;

}