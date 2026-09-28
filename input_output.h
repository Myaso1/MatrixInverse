#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

#include "utils.h"

using std::vector;

bool readDouble(double& number, std::istream& stream);
bool readMatrix(int argc, char** argv, int& n, int& m, Matrix& matrix);
void printMatrix(Matrix& matrix, int m);