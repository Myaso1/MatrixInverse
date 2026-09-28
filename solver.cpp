#include "solver.h"

bool nullifyCell(Matrix& A, int n, int i, int j) {
    double ajj = A[j][j];
    double aij = A[i][j];

    double l = std::sqrt(ajj * ajj + aij * aij);
    if (l < 1e-14) {
        return false;
    }

    double cos = ajj / l;
    double sin = -aij / l;

    A[j][j] = -sin * aij + cos * ajj;

    DoublePair T;
    T.d = cos;
    if (T.ll == 0) {
        T.d = (sin > 0) ? 3 : 4;
    } else {
        T.ll = (T.ll & ~1ULL) | ((uint64_t)(sin < 0) & 1ULL);
    }
    A[i][j] = T.d;

    double* __restrict ri = A[i];
    double* __restrict rj = A[j];

    #pragma omp simd
    for (int k = j + 1; k < n; k++) {
        double temp = ri[k];
        ri[k] = sin * rj[k] + cos * temp;
        rj[k] = cos * rj[k] - sin * temp;
    }
    return true;
}

void nullifyMatrix(Matrix& A, int n) {
    for (int j = 0; j < n; j++) {
        for (int i = j + 1; i < n; i++) {
            if (std::abs(A[i][j]) < 1e-15 || !nullifyCell(A, n, i, j)) {
                A[i][j] = 2;
            }
        }
    }
}

bool isDet0(const Matrix& A, int n) {
    for (int i = 0; i < n; i++) {
        if (fabs(A[i][i]) < 1e-15) {
            return true;
        }
    }
    return false;
}


void invertMatrix(const Matrix& A, Matrix& B, int n) {
    DoublePair T;

    B.resize(n, n, 0);
    for (int i = 0; i < n; i++) {
        B[i][i] = 1;
    }

    for (int j = 0; j < n; j++) {
        for (int i = j + 1; i < n; i++) {
            double cos, sin;
            T.d = A[i][j];
            if (std::abs(T.d - 2) < 0.1) {continue;}
            if (std::abs(T.d - 3) < 0.1) {
                cos = 0; 
                sin = 1;
            } else if (std::abs(T.d - 4) < 0.1) {
                cos = 0; 
                sin = -1;
            } else {
                double sign = (T.ll & 1ULL) ? -1 : 1;
                T.ll &= ~1ULL;
                cos = T.d;
                sin = sign * std::sqrt(1 - cos * cos);
            }
            
            double* __restrict ri = B[i];
            double* __restrict rj = B[j];
            
            #pragma omp simd
            for (int k = 0; k < n; ++k) {
                double temp = ri[k];
                ri[k] = sin * rj[k] + cos * temp;
                rj[k] = cos * rj[k] - sin * temp;
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        double diag = A[i][i];
        if (std::abs(diag) < 1e-15) {
            return;
        }
        double invDiag = 1.0 / diag;

        double* __restrict bi = B[i];
        #pragma omp simd
        for (int k = 0; k < n; ++k) {
            bi[k] *= invDiag;
        }

        double* __restrict biNew = B[i]; 
        for (int row = i - 1; row >= 0; row--) {
            double factor = A[row][i];
            double* __restrict b_row = B[row];
            
            #pragma omp simd
            for (int k = 0; k < n; k++) {
                b_row[k] -= factor * biNew[k];
            }
        }
    }
}

double calculateError(const Matrix& A, const Matrix& B, int n) {
    double maxRowSum = 0;

    for (int i = 0; i < n; i++) {
        double rowSum = 0;
        
        for (int j = 0; j < n; j++) {
            double abij = 0;

            for (int k = 0; k < n; ++k) {
                abij += A[i][k] * B[k][j];
            }
            rowSum += std::abs(abij - ((i == j) ? 1 : 0));
        }
        maxRowSum = std::max(maxRowSum, rowSum);
    }
    return maxRowSum;
}