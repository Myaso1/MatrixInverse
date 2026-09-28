#include <chrono>

#include "input_output.h"
#include "solver.h"

int main(int argc, char** argv) {
    int n, m;
    Matrix matrix(1, 1, 0);
    Matrix inverseMatrix(1, 1, 0);

    if (!readMatrix(argc, argv, n, m, matrix)) {
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    nullifyMatrix(matrix, n);

    if (isDet0(matrix, n)) {
        std::cout << "Determinant of the matrix is 0\n";
        return 0;
    }

    invertMatrix(matrix, inverseMatrix, n);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << std::scientific << std::setprecision(3);
    printMatrix(inverseMatrix, m);

    std::chrono::duration<double> elapsedSeconds = end - start;
    std::cout << std::fixed << std::setprecision(6) << "Time: " << elapsedSeconds.count() << " seconds\n";

    readMatrix(argc, argv, n, m, matrix);

    std::cout << std::scientific << std::setprecision(3) << "Error: " << calculateError(matrix, inverseMatrix, n) << "\n";
    return 0;
}