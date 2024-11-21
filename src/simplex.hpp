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
    :_data(*data), _tablePtr(*data->get_table_ptr())
{
    m = _tablePtr.size();
    n = _tablePtr[0].size();
    _table.resize(m, std::vector<double>(n + m - 1));
    _result.resize(_tablePtr[0].size());

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
    n = _table[0].size();
}

void Simplex::calculate()
{
    int counter = 0;
    while(!is_it_end() && (counter < 30))
    {
        counter++;
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

    double func_result = 0;
    for (int i = 0; i < _result.size(); i++)
    {
        auto it = std::find(_basis.begin(), _basis.end(), i + 1);
        int k = (it != _basis.end()) ? std::distance(_basis.begin(), it) : -1;
        if (k != -1) { _result[i] = _table[k][0]; }
        else { _result[i] = 0; }
    }
    if (counter > 30)
    {
        std::cout << "too many iterations, probaly not solvable" << std::endl;
    }
    else { _data.write_to_file(&_result); }
}

bool Simplex::is_it_end()
{
    bool flag = true;

    for (int j = 1; j < n; j++)
    {
        if (_table[m-1][j] < 0)
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
    for (int j = 2; j < n; j++)
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
    for(int i = 0; i < (m - 1); i++)
    {
        if(_table[i][_mainCol] > 0)
        {
            _mainRow = i;
            break;
        }
    }

    for (int i = (_mainRow + 1); i < (m - 1); i++)
    {
        if((_table[i][_mainCol] > 0) && ((_table[i][0] / _table[i][_mainCol]) < (_table[_mainRow][0] / _table[_mainRow][_mainCol])))
        {
            _mainRow = i;
        }
    }
}