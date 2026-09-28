#pragma once

#include <vector>

using std::vector;

class Matrix {
private:
    int rows;
    int columns;
    std::vector<double> data;
public:
    void resize(int newRows, int newColumns, double init_val = 0);
    double* operator[](int r);
    const double* operator[](int r) const;
    double* data_ptr();
    const double* data_ptr() const;

    Matrix(int r, int c, double init_val = 0) : rows(r), columns(c), data(r * c, init_val) {}
};