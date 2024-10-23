#pragma once

#include "data.hpp"

#include <iomanip>
#include <iostream>

class Simplex
{
private:
    Data &_data;
    std::vector<std::vector<double>> &_tablePtr;
    std::vector<std::vector<double>> _table;
    std::vector<double> &_funcPtr;
    std::vector<double> _basis;
    int _mainCol, _mainRow, n, m;

    void find_main_col();
    void find_main_row();
public:
    Simplex(Data *data);
    void calculate();
};

Simplex::Simplex(Data *data)
    :_data(*data), _tablePtr(*data->get_table_ptr()), _funcPtr(*data->get_func_ptr())
{
    n = _tablePtr[0].size();
    m = _tablePtr.size();
    _table.resize(m, std::vector<double>(n + m - 1));

    //добавляем базисные переменыне
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < _table[0].size(); j++)
        {
            if (j < n)
                _table[i][j] = _tablePtr[i][j];
            else
                _table[i][j] = { 0.0 };
        }
        if ((n + i) < _table[0].size())
        {
            _table[i][n+i] = { 1.0 };
            _basis.push_back(n + i);
        }
    }

    n = _table.size();
}

void Simplex::calculate()
{
    find_main_col();
}

void Simplex::find_main_col()
{
    _mainCol = 1;
    for (int j = 0; j < n; j++)
    {
        if (_table[m-1][j] < _table[m-1][_mainCol])
        {
            _mainCol = j;
        }
    }
    std::cout << _mainCol << std::endl;
}

void Simplex::find_main_row()
{
    _mainRow = 0;
    for(int i = 0; i < m - 1; i++)
    {

    }
}