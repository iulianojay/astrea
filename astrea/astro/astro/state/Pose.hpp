#pragma once

#include <astro/state/angular_elements/Quaternion.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>

namespace astrea {
namespace astro {

class PosePartials;

class Pose {

    friend std::ostream& operator<<(std::ostream& os, const Pose& pose);

  public:
    Pose() = default;
    Pose(const OrbitalElements& orbit);
    Pose(const OrbitalElements& orbit, const Quaternion& orientation);
    ~Pose() = default;

    OrbitalElements& get_orbit();
    const OrbitalElements& get_orbit() const;

    Quaternion& get_orientation();
    const Quaternion& get_orientation() const;

    Pose& convert_to_orbital_set(const std::size_t idx, const AstrodynamicsSystem& sys);
    Pose convert_to_orbital_set(const std::size_t idx, const AstrodynamicsSystem& sys) const;

    template <IsOrbitalElements T>
    Pose& convert_to_orbital_set(const AstrodynamicsSystem& sys)
    {
        _orbit = _orbit.convert_to_orbital_set<T>(sys);
        return *this;
    }

    template <IsOrbitalElements T>
    Pose convert_to_orbital_set(const AstrodynamicsSystem& sys) const
    {
        return Pose(_orbit.in_orbital_set<T>(sys), _orientation);
    }

    template <IsOrbitalElements T>
    T in_orbital_set(const AstrodynamicsSystem& sys) const
    {
        return _orbit.in_orbital_set<T>(sys);
    }

    bool operator==(const Pose& other) const;

    Pose operator+(const Pose& other) const;

    Pose& operator+=(const Pose& other);

    Pose operator-(const Pose& other) const;

    Pose& operator-=(const Pose& other);

    Pose operator*(const Unitless& multiplier) const;

    Pose& operator*=(const Unitless& multiplier);

    PosePartials operator/(const Time& time) const;

    std::vector<Unitless> to_vector() const;

    Pose operator/(const Unitless& divisor) const;

    Pose& operator/=(const Unitless& divisor);

    Pose interpolate(const Time& thisTime, const Time& otherTime, const Pose& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

  private:
    OrbitalElements _orbit;
    Quaternion _orientation;
};

class PosePartials {

    friend std::ostream& operator<<(std::ostream& os, const PosePartials& posePartials);

  public:
    PosePartials() = default;
    PosePartials(const OrbitalElementPartials& orbitPartials);
    PosePartials(const OrbitalElementPartials& orbitPartials, const QuaternionPartials& orientationPartials);
    ~PosePartials() = default;

    Pose operator*(const Time& time) const;

  private:
    OrbitalElementPartials _orbitPartials;
    QuaternionPartials _orientationPartials;
};

} // namespace astro
} // namespace astrea