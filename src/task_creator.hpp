#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>  
#include <ctime>    

class TaskCreator
{
public:
    TaskCreator();

    void generateMatrixFile(int width, int height, const std::string& filename);
};

TaskCreator::TaskCreator() {}

void TaskCreator::generateMatrixFile(int width, int height, const std::string& filename)
{
    std::srand(static_cast<unsigned int>(std::time(0)));

        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "err opening file " << filename << std::endl;
            return;
        }

        file << width << ", " << height << std::endl;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int randomValue;
                if (i == height - 1 && j == 0) {
                    // Первый элемент в последней строке всегда равен нулю
                    randomValue = 0;
                } else {
                    randomValue = std::rand() % 31 - 15;  // Генерация случайного числа от -15 до 15
                }
                file << randomValue;
                if (j < width - 1) {
                    file << ", ";
                }
            }
            file << std::endl;
        }

        file.close();
}