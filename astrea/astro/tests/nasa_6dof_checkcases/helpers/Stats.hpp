/**
 * @file Stats.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Stats class, which computes statistical measures for a dataset.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <vector>

#include <mp-units/math.h>
#include <mp-units/systems/international.h>
#include <mp-units/systems/si/math.h>

namespace astrea {
namespace astro {
namespace tests {

template <auto R, typename Rep>
class Stats {
  public:
    Stats()  = default;
    ~Stats() = default;

    Stats(const std::vector<mp_units::quantity<R, Rep>>& data) :
        _data(data)
    {
    }

    Stats(std::vector<mp_units::quantity<R, Rep>>&& data) :
        _data(std::move(data))
    {
    }

    mp_units::quantity<R, Rep> mean() const
    {
        mp_units::quantity<R, Rep> sum = 0.0 * R;
        for (const auto& val : _data) {
            sum += val;
        }
        return sum / static_cast<Rep>(_data.size());
    }

    mp_units::quantity<R, Rep> stddev() const
    {
        const mp_units::quantity<R, Rep> mu = mean();
        mp_units::quantity<R * R, Rep> sum  = 0.0 * R * R;
        for (const auto& val : _data) {
            sum += (val - mu) * (val - mu);
        }
        return mp_units::sqrt(sum / static_cast<Rep>(_data.size() - 1));
    }

    mp_units::quantity<R, Rep> max() const
    {
        mp_units::quantity<R, Rep> maxVal = _data[0];
        for (const auto& val : _data) {
            if (val > maxVal) { maxVal = val; }
        }
        return maxVal;
    }

    mp_units::quantity<R, Rep> min() const
    {
        mp_units::quantity<R, Rep> minVal = _data[0];
        for (const auto& val : _data) {
            if (val < minVal) { minVal = val; }
        }
        return minVal;
    }

    template <auto R2>
    void add_value(const mp_units::quantity<R2, Rep>& value)
    {
        _data.push_back(value);
    }

  private:
    std::vector<mp_units::quantity<R, Rep>> _data;
};

} // namespace tests
} // namespace astro
} // namespace astrea