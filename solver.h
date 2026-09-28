#include <vector>
#include <cmath>
#include <cstdint>
#include <stdexcept>

#include "utils.h"

using std::vector;

union DoublePair {
    double d;
    uint64_t ll;
};

bool nullifyCell(Matrix& A, int n, int i, int j);
void nullifyMatrix(Matrix& A, int n);
bool isDet0(const Matrix& A, int n);
void invertMatrix(const Matrix& A, Matrix& B, int n);
double calculateError(const Matrix& A, const Matrix& B, int n);