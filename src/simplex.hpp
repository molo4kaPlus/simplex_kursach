#pragma once

#include "data.hpp"

#include <iomanip>
#include <iostream>

class Simplex
{
private:
    Data &_data;
public:
    Simplex(Data *data);
};

Simplex::Simplex(Data *data)
    :_data(*data)
{
    
}

