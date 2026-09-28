#include "utils.h"

void Matrix::resize(int newRows, int newColumns, double init_val) {
    rows = newRows;
    columns = newColumns;
    data.resize(newRows * newColumns, init_val);
}

double* Matrix::operator[](int r) {
    return &data[r * columns];
}

const double* Matrix::operator[](int r) const {
    return &data[r * columns];
}

double* Matrix::data_ptr() {
    return data.data();
}

const double* Matrix::data_ptr() const {
    return data.data();
}