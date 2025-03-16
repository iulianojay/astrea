#include <math/interpolation.hpp>

#include <cmath>
#include <stdexcept>

using namespace math;


// Cubic Spline
/*
    x is the input knot vector with corresponding points y
    sx is the desired output vector to interpolate to
*/
std::vector<double> cubic_spline(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sx)
{

    // Sizes
    const size_t n = x.size();
    const size_t m = sx.size();

    // Catch spline x values outside the knots
    for (size_t ii = 0; ii < m; ++ii) {
        if (sx[ii] < x[0] || sx[ii] > x[n - 1]) {
            throw std::runtime_error("Error: Requested spline values outside of input knots. Exiting.");
        }
    }

    // Build arrays
    double h[n - 1];
    double b[n - 1];
    double u[n];
    double v[n];
    double z[n + 1];

    std::vector<double> sy;
    sy.resize(m);

    // Solve for spline coefficients
    for (size_t ii = 0; ii < n - 1; ++ii) {
        h[ii] = x[ii + 1] - x[ii];
        b[ii] = 6 * (y[ii + 1] - y[ii]) / h[ii];
    }

    u[1] = 2 * (h[0] + h[1]);
    v[1] = b[1] - b[0];
    for (size_t ii = 1; ii < n - 1; ++ii) {
        u[ii + 1] = 2 * (h[ii + 1] + h[ii]) - h[ii] * h[ii] / u[ii];
        v[ii + 1] = b[ii + 1] - b[ii] - h[ii] * v[ii] / u[ii];
    }

    for (size_t ii = n - 2; ii >= 0; --ii) {
        z[ii + 1] = (v[ii + 1] - h[ii + 1] * z[ii + 2]) / u[ii + 1];
    }

    // Create spline
    for (size_t ii = 0; ii < m; ++ii) {
        // Find nearest knot
        size_t jj   = 0;
        double xRef = x[0];
        for (size_t kk = 1; kk < n; ++kk) {
            if (abs(sx[ii] - x[kk]) < abs(sx[ii] - xRef) && x[kk] < sx[ii]) {
                jj   = kk;
                xRef = x[kk];
            }
        }
        // Precalculate repeated calcs
        const double dx   = sx[ii] - x[jj];
        const double dxp1 = x[jj + 1] - sx[ii];

        const double zDiv6   = z[jj] / 6.0;
        const double zp1Div6 = z[jj + 1] / 6.0;
        const double h2      = h[jj] * h[jj];

        // Spline
        sy[ii] = (zDiv6 * std::pow(dxp1, 3) + zp1Div6 * std::pow(dx, 3) + (y[jj + 1] - zp1Div6 * h2) * dx +
                     (y[jj] - h2 * zDiv6) * dxp1) /
                 h[jj];
    }

    return sy;
}
