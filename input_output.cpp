#include "input_output.h"

bool readDouble(double& number, std::istream& stream) {
    if (!(stream >> number)) {
        return false;
    }
    return true;
}

bool readMatrix(int argc, char** argv, int& n, int& m, Matrix& matrix) {
    int k;
    
    if (argc < 4) {
        std::cout << "Invalid number of arguments\n";
        return false;
    }

    try {
        size_t pos1, pos2, pos3;
        n = std::stoi(argv[1], &pos1);
        m = std::stoi(argv[2], &pos2);
        k = std::stoi(argv[3], &pos3);

        if (argv[1][pos1] != '\0' || argv[2][pos2] != '\0' || argv[3][pos3] != '\0' || n < 1 || m < 0 || k < 0 || k > 4 || m > n) {
            throw std::runtime_error("Invalid argument values");
        }
    } catch (const std::exception& e) {
        std::cout << "Arguments error: " << e.what() << "\n";
        return false;
    }

    matrix.resize(n, n, 0);

    if (k == 0) {
        std::ifstream inputFile;

        if (argc < 5) {
            std::cout << "No input file name\n";
            return false;
        }
        
        inputFile.open(argv[4]);
        if (!inputFile.is_open()) {
            std::cout << "Could not open file\n";
            return false;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!readDouble(matrix[i][j], inputFile)) {
                    std::cout << "Invalid matrix element\n";
                    return false;
                }
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (k == 1) {
                    matrix[i][j] = n - std::max(i, j);
                } else if (k == 2) {
                    matrix[i][j] = std::max(i, j) + 1;
                } else if (k == 3) {
                    matrix[i][j] = std::abs(i - j);
                } else if (k == 4) {
                    matrix[i][j] = 1.0 / (i + j + 1);
                }
            }
        }
    }

    return true;
}

void printMatrix(Matrix& matrix, int m) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << std::setw(10) << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}