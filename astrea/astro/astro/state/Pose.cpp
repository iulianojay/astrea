#include <astro/state/Pose.hpp>

namespace astrea {
namespace astro {

Pose::Pose(const OrbitalElements& orbit) :
    _orbit(orbit)
{
}

Pose::Pose(const OrbitalElements& orbit, const Quaternion& orientation) :
    _orbit(orbit),
    _orientation(orientation)
{
}

OrbitalElements& Pose::get_orbit() { return _orbit; }

const OrbitalElements& Pose::get_orbit() const { return _orbit; }

Quaternion& Pose::get_orientation() { return _orientation; }

const Quaternion& Pose::get_orientation() const { return _orientation; }

Pose& Pose::convert_to_orbital_set(const std::size_t idx, const AstrodynamicsSystem& sys)
{
    _orbit = _orbit.convert_to_orbital_set(idx, sys);
    return *this;
}

Pose Pose::convert_to_orbital_set(const std::size_t idx, const AstrodynamicsSystem& sys) const
{
    return Pose(_orbit.convert_to_orbital_set(idx, sys), _orientation);
}

bool Pose::operator==(const Pose& other) const
{
    return (_orbit == other._orbit) && (_orientation == other._orientation);
}

Pose Pose::operator+(const Pose& other) const { return Pose(_orbit + other._orbit, _orientation + other._orientation); }

Pose& Pose::operator+=(const Pose& other)
{
    _orbit += other._orbit;
    _orientation += other._orientation;
    return *this;
}

Pose Pose::operator-(const Pose& other) const { return Pose(_orbit - other._orbit, _orientation - other._orientation); }

Pose& Pose::operator-=(const Pose& other)
{
    _orbit -= other._orbit;
    _orientation -= other._orientation;
    return *this;
}

Pose Pose::operator*(const Unitless& multiplier) const { return Pose(_orbit * multiplier, _orientation * multiplier); }

Pose& Pose::operator*=(const Unitless& multiplier)
{
    _orbit *= multiplier;
    _orientation *= multiplier;
    return *this;
}

PosePartials Pose::operator/(const Time& time) const { return PosePartials(_orbit / time, _orientation / time); }

std::vector<Unitless> Pose::to_vector() const
{
    std::vector<Unitless> vec             = _orbit.to_vector();
    const std::vector<Unitless> orientVec = _orientation.to_vector();
    vec.insert(vec.end(), orientVec.begin(), orientVec.end());
    return vec;
}

Pose Pose::operator/(const Unitless& divisor) const { return Pose(_orbit / divisor, _orientation / divisor); }

Pose& Pose::operator/=(const Unitless& divisor)
{
    _orbit /= divisor;
    _orientation /= divisor;
    return *this;
}

Pose Pose::interpolate(const Time& thisTime, const Time& otherTime, const Pose& other, const AstrodynamicsSystem& sys, const Time& targetTime) const
{
    return Pose(
        _orbit.interpolate(thisTime, otherTime, other._orbit, sys, targetTime),
        _orientation.interpolate(thisTime, otherTime, other._orientation, sys, targetTime)
    );
}


PosePartials::PosePartials(const OrbitalElementPartials& orbitPartials) :
    _orbitPartials(orbitPartials),
    _orientationPartials(QuaternionPartials())
{
}

PosePartials::PosePartials(const OrbitalElementPartials& orbitPartials, const QuaternionPartials& orientationPartials) :
    _orbitPartials(orbitPartials),
    _orientationPartials(orientationPartials)
{
}

Pose PosePartials::operator*(const Time& time) const
{
    return Pose(_orbitPartials * time, _orientationPartials * time);
}


} // namespace astro
} // namespace astrea