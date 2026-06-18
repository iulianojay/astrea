/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <iostream>

#include <units/units.hpp>

namespace astrea {
namespace helios {

struct Point3 {
    double x;
    double y;
    double z;
};

using AnimationFrame = std::vector<Point3>;

std::ostream& operator<<(std::ostream& os, const Point3& p)
{
    os << "[" << p.x << "," << p.y << "," << p.z << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const AnimationFrame& frame)
{
    os << "[";
    for (const auto& object : frame) {
        if (&object != &frame[0]) { os << ","; }
        os << object;
    }
    os << "]";
    return os;
}

struct PropagationSettings {
    Time propTime;
    Time step;
    bool ten    = false;
    bool fourty = false;
    bool eighty = false;
    bool srp    = false;
    bool nBody  = false;
    bool drag   = false;
};

struct PropagationResult {
    std::vector<AnimationFrame> frames;
    std::size_t nFrames = 0;
    double elapsedMs    = 0.0;
    double maxRadiusKm  = 0.0;
};

} // namespace helios
} // namespace astrea