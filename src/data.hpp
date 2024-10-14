#pragma once

#include<vector>

class Data
{
public:
    std::vector<float> goal_fn;
    bool is_max;
    std::vector<std::vector<float>> matrix;
    int size_x, size_y;

    Data(int x, int y); // data initialization
};


Data::Data(int x, int y)
{
    size_x = x;
    size_y = y;
}
