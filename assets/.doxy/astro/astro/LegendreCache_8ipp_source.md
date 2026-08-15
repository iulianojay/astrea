

# File LegendreCache.ipp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**LegendreCache.ipp**](LegendreCache_8ipp.md)

[Go to the documentation of this file](LegendreCache_8ipp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version. Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details. You should have received a copy of the GNU General
 * Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <math/trig.hpp>

#include <astro/astro.macros.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/systems/property_getters.hpp>

namespace astrea {
namespace astro {

using math::assoc_legendre;

using namespace mp_units;

template <IsCelestialBody auto _body_, std::size_t _degree_, std::size_t _order_>
LegendreCache<_body_, _degree_, _order_>::LegendreCache()
{
    // Open coefficients file
    // TODO: Change to binary files cause boy are these big
    static constexpr const char* filename = get_gravity_coefficient_file<_body_>();
    if ((filename != NULL) && (filename[0] == '\0')) { // "" is the default so check if it's overwritten
        throw std::invalid_argument(
            std::string("No gravity coefficient file set for ") + decltype(_body_)::name.portable().data()
        );
    }
    else if (!std::filesystem::exists(filename)) { // check the file actually exists
        throw std::invalid_argument(
            std::string("Legendre coefficient file for central body, ") + decltype(_body_)::name.portable().data() + ", not found at " + filename
        );
    }

    std::ifstream file(filename);
    if (file.fail()) { throw std::runtime_error(std::string("Failed to open Legendre coefficient file: ") + filename); }

    // Read coefficients from file
    std::string line;
    std::string cell;

    std::size_t n = 0, m = 0;
    while (file) {
        // Read line from stream
        std::getline(file, line);
        std::stringstream lineStream(line);
        std::vector<double> lineData;
        while (std::getline(lineStream, cell, ',')) {
            lineData.push_back(std::atof(cell.c_str()));
        }

        n = (std::size_t)lineData[0];
        m = (std::size_t)lineData[1];

        _C[n * _span + m] = lineData[2];
        _S[n * _span + m] = lineData[3];

        if (n >= _degree_ && m >= _order_) { break; }
    }
    file.close();

    // Calculate normalization coefficients after reading all coefficients
    if (_body_ == planets::Mars) {
        // The Mars file is already normalized, so skip this step for Mars
        return;
    }

    for (std::size_t n = 0; n <= _degree_; ++n) {
        Unitless previousRatio = 0.0 * one;
        for (std::size_t m = 0; m <= std::min(n, _order_); ++m) {
            // Calculate (n + m)!/(n - m)! = (n - m + 1)(n - m + 2)...(n + m)
            const Unitless ratio = (m == 0) ? 1.0 * one : previousRatio * (n + m) * (n - m + 1);
            previousRatio        = ratio;

            // sqrt( (2 - delta_m0) * (2n + 1) * (n - m)! / (n + m)! )
            // delta = 1 if m = 0, else 0
            const unsigned int delta = (m == 0) ? 1 : 0;
            const Unitless Nnm       = sqrt((2 - delta) * (2 * n + 1) / ratio);

            // Pre-normalize coefficients
            _C[n * _span + m] *= Nnm;
            _S[n * _span + m] *= Nnm;
        }
    }
}


template <IsCelestialBody auto _body_, std::size_t _degree_, std::size_t _order_>
const Unitless& LegendreCache<_body_, _degree_, _order_>::get_cosine_coefficient(const std::size_t& n, const std::size_t& m) const
{
    return _C[n * _span + m];
}


template <IsCelestialBody auto _body_, std::size_t _degree_, std::size_t _order_>
const Unitless& LegendreCache<_body_, _degree_, _order_>::get_sine_coefficient(const std::size_t& n, const std::size_t& m) const
{
    return _S[n * _span + m];
}

} // namespace astro
} // namespace astrea
```


