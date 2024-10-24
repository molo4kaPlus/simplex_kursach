#pragma once

#include "data.hpp"

#include <iomanip>
#include <iostream>

#include <algorithm>

class Simplex
{
private:
    Data &_data;
    std::vector<std::vector<double>> &_tablePtr;
    std::vector<std::vector<double>> _table;
    std::vector<double> &_funcPtr;
    std::vector<double> _basis;
    std::vector<double> _result;
    int _mainCol, _mainRow, n, m;

    void find_main_col();
    void find_main_row();
    bool is_it_end();
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
    _result.resize(_tablePtr[0].size());
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
    while(!is_it_end())
    {
        find_main_col();
        find_main_row();
        _basis[_mainRow] = _mainCol;

        std::vector<std::vector<double>> new_table(m, std::vector<double>(n));

        for (int j = 0; j < n; j++)
        {
            new_table[_mainRow][j] = _table[_mainRow][j] / _table[_mainRow][_mainCol];
        }

        for (int i = 0; i < m; i++)
        {
            if (i == _mainRow)
            {
                continue;
            }

            for(int j = 0; j < n; j++)
            {
                new_table[i][j] = _table[i][j] - _table[i][_mainCol] * new_table[_mainRow][j];
            }
        }

        _table = new_table;
    }

    for (int i = 0; i < _result.size(); i++)
    {
        auto k = std::find(_basis.begin(), _basis.end(), i+1);
        int l = k-_basis.begin();
        if (l != -1)
        {
            _result[i] = _table[l][0];
        }
        else
        {
            _result[i] = 0;
        }
    }

    double funcResult;
    for (int i = 0; i < _result.size() - 1; i++)
    {
        funcResult += _result[i] * _funcPtr[i];
    }
    _result[_result.size() - 1] = funcResult * -1;

    _data.write_to_file(&_result);
}

bool Simplex::is_it_end()
{
    bool flag = true;

    for (int j = 1; j < n; j++)
    {
        if (_table[m - 1][j] < 0)
        {
            flag = false;
            break;
        }
    }

    return flag;
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
}

void Simplex::find_main_row()
{
    _mainRow = 0;
    for(int i = 0; i < m - 1; i++)
    {
        if(_table[i][_mainCol] > 0)
        {
            _mainRow = i;
        }
    }

    for (int i = _mainRow + 1; i < m - 1; i++)
    {
        if((_table[i][_mainCol] > 0) && ((_table[i][0] / _table[i][_mainCol]) < _table[_mainRow][0] / _table[_mainRow][_mainCol]))
        {
            _mainRow = i;
        }
    }
}