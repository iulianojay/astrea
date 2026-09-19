/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
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

#include <nlohmann/json.hpp>

#include <units/units.hpp>

namespace astrea {
namespace helios {

/**
 * @brief Represents a 3D point in space.
 */
struct Point3 {
    double x; //!< The x-coordinate of the point.
    double y; //!< The y-coordinate of the point.
    double z; //!< The z-coordinate of the point.
};

/**
 * @brief Represents a frame of animation, which is a collection of 3D points.
 */
using AnimationFrame = std::vector<Point3>;

inline std::ostream& operator<<(std::ostream& os, const Point3& p)
{
    os << "[" << p.x << "," << p.y << "," << p.z << "]";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const AnimationFrame& frame)
{
    os << "[";
    for (const auto& object : frame) {
        if (&object != &frame[0]) { os << ","; }
        os << object;
    }
    os << "]";
    return os;
}

/**
 * @brief Represents the settings for propagating objects in space.
 */
struct PropagationSettings {

    Time propTime;       //!< The total propagation time.
    Time step;           //!< The time step for each propagation iteration.
    bool ten    = false; //!< Flag indicating whether to use a 10x10 gravity model.
    bool fourty = false; //!< Flag indicating whether to use a 40x40 gravity model.
    bool eighty = false; //!< Flag indicating whether to use an 80x80 gravity model.
    bool srp    = false; //!< Flag indicating whether to include solar radiation pressure effects.
    bool nBody  = false; //!< Flag indicating whether to include n-body gravitational effects.
    bool drag   = false; //!< Flag indicating whether to include atmospheric drag effects.

    PropagationSettings(const Time propTime, const Time step) :
        propTime(propTime),
        step(step)
    {
    }

    PropagationSettings(nlohmann::json data) :
        propTime(minutes(data["propMin"].get<double>())),
        step(minutes(data["stepMin"].get<double>())),
        ten(data["ten"].get<bool>()),
        fourty(data["fourty"].get<bool>()),
        eighty(data["eighty"].get<bool>()),
        srp(data["srp"].get<bool>()),
        nBody(data["nbody"].get<bool>()),
        drag(data["drag"].get<bool>())
    {
    }
};

/**
 * @brief Represents the result of propagating objects in space.
 */
struct PropagationResult {
    std::vector<AnimationFrame> frames; //!< A vector of animation frames representing the propagated states of the objects.
    std::size_t nFrames = 0;            //!< The total number of frames generated during the propagation.
    double elapsedMs    = 0.0;          //!< The elapsed time in milliseconds for the propagation process.
    double maxRadiusKm = 0.0; //!< The maximum radius in kilometers of the propagated objects from the origin during the propagation process.
};

} // namespace helios
} // namespace astrea