
#include <math/utils.hpp>

#include <iostream>

using namespace math;

double array_mean(double* vec, int arraySize) {
    double mean = 0.0;
    for (int ii = 0; ii < arraySize; ii++) {
        mean += vec[ii];
    }
    return mean/((double)arraySize);
}

double atan3(double a, double b) {

    double sa{}, sb{};

    if (a >= 0) { sa =  1; }
    else        { sa = -1; }
    if (b >= 0) { sb =  1; }
    else        { sb = -1; }

    if (abs(a) < 1e-10) {
        return (1 - sb)*M_PI/2;
    }
    else if (abs(b) < 1e-10) {
        return (2 - sa)*M_PI/2;
    }
    else {
        return (2 - sa)*M_PI/2 + sa*sb*(abs(atan(a/b)) - M_PI/2);
    }
}
