
#include "math_c.hpp"

#include <iostream>

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------------- Norms --------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

// Default vector norm
double math_c::normalize(const double* vec) {
    // default to 2 norm
    double norm = 0.0;
    for (int ii = 0; ii < 3; ++ii) {
        norm += vec[ii]*vec[ii];
    }

    return std::sqrt(norm);
}

double math_c::normalize(double* vec, int startIndex, int endIndex) {
    // default to 2 norm
    double norm = 0.0;
    for (int ii = startIndex; ii < endIndex+1; ++ii) {
        norm += vec[ii]*vec[ii];
    }

    return std::sqrt(norm);
}

// Vector p-norm
double math_c::normalize(double* vec, int startIndex, int endIndex, int p) {
    if (p <= 0) {
        std::cout << "Error: p must be >= 1 \n\n";
        return -1.0;
    }

    // p norm
    double norm = 0.0;
    for (int ii = startIndex; ii < endIndex+1; ++ii) {
        norm += std::pow(abs(vec[ii]),p);
    }
    return std::pow(norm, 1/p);
}

// Default matrix norm
double math_c::normalize(double** matrix, int startRow, int endRow, int startColumn, int endColumn) {
    // default to 2 norm
    double norm = 0.0;
    for (int ii = startRow; ii < endRow+1; ++ii) {
        for (int jj = startColumn; jj < endColumn+1; ++jj){
            norm += matrix[ii][jj]*matrix[ii][jj];
        }
    }

    return std::sqrt(norm);
}

// Matrix p-norm
double math_c::normalize(double** matrix, int startRow, int endRow, int startColumn, int endColumn, int p) {
    if (p <= 0) {
        std::cout << "Error: p must be >= 1 \n\n";
        return -1.0;
    }

    // p norm
    double norm = 0.0;
    for (int ii = startRow; ii < endRow+1; ++ii) {
        for (int jj = startColumn; jj < endColumn+1; ++jj) {
            norm += std::pow(abs(matrix[ii][jj]),p);
        }
    }
    return std::pow(norm, 1/p);
}

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------- Vector and Matrix Math -----------------------------------------//
//----------------------------------------------------------------------------------------------------------//

double math_c::array_mean(double* vec, int arraySize) {
    double mean = 0.0;
    for (int ii = 0; ii < arraySize; ii++) {
        mean += vec[ii];
    }
    return mean/((double)arraySize);
}

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------- Miscallaneous Functions ----------------------------------------//
//----------------------------------------------------------------------------------------------------------//

double math_c::atan3(double a, double b) {

    double sa{}, sb{};

    if (a >= 0) { sa =  1; }
    else        { sa = -1; }
    if (b >= 0) { sb =  1; }
    else        { sb = -1; }

    if (abs(a) < 1e-10) {
        return (1 - sb)*PI/2;
    }
    else if (abs(b) < 1e-10) {
        return (2 - sa)*PI/2;
    }
    else {
        return (2 - sa)*PI/2 + sa*sb*(abs(atan(a/b)) - PI/2);
    }
}
