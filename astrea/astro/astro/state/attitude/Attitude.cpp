/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/state/attitude/Attitude.hpp>

using namespace mp_units;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {


std::ostream& operator<<(std::ostream& os, const Attitude& attitude)
{
    os << attitude._orientation << " , " << attitude._angularVelocity;
    return os;
}

std::ostream& operator<<(std::ostream& os, const AttitudePartials& attitude)
{
    os << attitude._orientationRate << " , " << attitude._angularAcceleration;
    return os;
}

Attitude::Attitude(const BodyQuaternion& orientation, const BodyAngleVelocities& angularVelocity) :
    _orientation(orientation),
    _angularVelocity(angularVelocity)
{
}

bool Attitude::operator==(const Attitude& other) const
{
    return _orientation == other._orientation && _angularVelocity == other._angularVelocity;
}

Attitude Attitude::operator+(const Attitude& other) const
{
    return Attitude(_orientation + other._orientation, _angularVelocity + other._angularVelocity);
}

Attitude& Attitude::operator+=(const Attitude& other)
{
    _orientation += other._orientation;
    _angularVelocity += other._angularVelocity;
    return *this;
}

Attitude Attitude::operator-(const Attitude& other) const
{
    return Attitude(_orientation - other._orientation, _angularVelocity - other._angularVelocity);
}

Attitude& Attitude::operator-=(const Attitude& other)
{
    _orientation -= other._orientation;
    _angularVelocity -= other._angularVelocity;
    return *this;
}

Attitude Attitude::operator*(const Unitless& multiplier) const
{
    return Attitude(_orientation * multiplier, _angularVelocity * multiplier);
}

Attitude& Attitude::operator*=(const Unitless& multiplier)
{
    _orientation *= multiplier;
    _angularVelocity *= multiplier;
    return *this;
}

AttitudePartials Attitude::operator/(const Time& divisor) const
{
    return AttitudePartials(_orientation / divisor, _angularVelocity / divisor);
}

std::vector<double> Attitude::force_to_double_vector() const
{
    std::vector<double> retval    = _orientation.force_to_double_vector();
    const auto angularVelocityVec = _angularVelocity.force_to_double_vector();
    retval.insert(retval.end(), angularVelocityVec.begin(), angularVelocityVec.end());
    return retval;
}

Attitude Attitude::operator/(const Unitless& divisor) const
{
    return Attitude(_orientation / divisor, _angularVelocity / divisor);
}

Attitude& Attitude::operator/=(const Unitless& divisor)
{
    _orientation /= divisor;
    _angularVelocity /= divisor;
    return *this;
}

Attitude Attitude::interpolate(const Time& thisTime, const Time& otherTime, const Attitude& other, const Time& targetTime) const
{
    const auto& thisOrientation      = _orientation;
    const auto& otherOrientation     = other._orientation;
    const auto& thisAngularVelocity  = _angularVelocity;
    const auto& otherAngularVelocity = other._angularVelocity;

    return Attitude(
        thisOrientation.interpolate(thisTime, otherTime, otherOrientation, targetTime),
        thisAngularVelocity.interpolate(thisTime, otherTime, otherAngularVelocity, targetTime)
    );
}

Attitude Attitude::from_double_vector(const std::vector<double>& vec)
{
    if (vec.size() != 7) {
        throw std::runtime_error("Invalid vector size for Attitude conversion. Expected 7 elements (4 for quaternion, 3 for angular velocity).");
    }
    const BodyQuaternion orientation(vec[0], vec[1], vec[2], vec[3]);
    const BodyAngleVelocities angularVelocity(vec[4] * rad / s, vec[5] * rad / s, vec[6] * rad / s);
    return Attitude(orientation, angularVelocity);
}

AttitudePartials::AttitudePartials(const BodyQuaternionRate& orientationRate, const BodyAngularAcceleration& angularAcceleration) :
    _orientationRate(orientationRate),
    _angularAcceleration(angularAcceleration)
{
}

Attitude AttitudePartials::operator*(const Time& time) const
{
    return Attitude(_orientationRate * time, _angularAcceleration * time);
}

std::vector<double> AttitudePartials::force_to_double_vector() const
{
    std::vector<double> retval        = _orientationRate.force_to_double_vector();
    const auto angularAccelerationVec = _angularAcceleration.force_to_double_vector();
    retval.insert(retval.end(), angularAccelerationVec.begin(), angularAccelerationVec.end());
    return retval;
}

} // namespace astro
} // namespace astrea