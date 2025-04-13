#pragma once

#ifndef SWIG
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#endif

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>

class Cartesian {

    friend std::ostream& operator<<(std::ostream&, Cartesian const&);

    using Distance = mp_units::quantity<mp_units::si::unit_symbols::km>;
    using Velocity = mp_units::quantity<mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s>;

  public:
    Cartesian() :
        _radius{ 0.0 * mp_units::si::unit_symbols::km, 0.0 * mp_units::si::unit_symbols::km, 0.0 * mp_units::si::unit_symbols::km },
        _velocity{ 0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
                   0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
                   0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s }
    {
    }
    Cartesian(const std::vector<double>& r, const std::vector<double>& v) :
        _radius({ r[0] * mp_units::si::unit_symbols::km, r[1] * mp_units::si::unit_symbols::km, r[2] * mp_units::si::unit_symbols::km }),
        _velocity({ v[0] * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
                    v[1] * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
                    v[2] * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s })
    {
    }
    Cartesian(const RadiusVector& r, const VelocityVector& v) :
        _radius(r),
        _velocity(v)
    {
    }
    Cartesian(const Distance& x, const Distance& y, const Distance& z, const Velocity& vx, const Velocity& vy, const Velocity& vz) :
        _radius({ x, y, z }),
        _velocity({ vx, vy, vz })
    {
    }
    Cartesian(const Keplerian& elements, const AstrodynamicsSystem& sys);
    Cartesian(const Equinoctial& elements, const AstrodynamicsSystem& sys);

    // Copy constructor
    Cartesian(const Cartesian&);

    // Move constructor
    Cartesian(Cartesian&&) noexcept;

    // Move assignment operator
    Cartesian& operator=(Cartesian&&) noexcept;

    // Copy assignment operator
    Cartesian& operator=(const Cartesian&);

    ~Cartesian() = default;

    // Comparitors operators
    bool operator==(const Cartesian& other) const;
    bool operator!=(const Cartesian& other) const;

    // Mathmatical operators
    Cartesian operator+(const Cartesian& other) const;
    Cartesian& operator+=(const Cartesian& other);

    Cartesian operator-(const Cartesian& other) const;
    Cartesian& operator-=(const Cartesian& other);

    Cartesian operator*(const double& multiplier) const;
    Cartesian& operator*=(const double& multiplier);

    Cartesian operator/(const double& divisor) const;
    Cartesian& operator/=(const double& divisor);

    // Element access
    const RadiusVector& get_radius() const { return _radius; }
    const VelocityVector& get_velocity() const { return _velocity; }

    const Distance& get_x() const { return _radius[0]; }
    const Distance& get_y() const { return _radius[1]; }
    const Distance& get_z() const { return _radius[2]; }

    const Velocity& get_vx() const { return _velocity[0]; }
    const Velocity& get_vy() const { return _velocity[1]; }
    const Velocity& get_vz() const { return _velocity[2]; }

    size_t size() const { return 6; }

    std::vector<double> to_vector() const;
    void update_from_vector(const std::vector<double>& vec);

    constexpr EnumType get_set_id() const { return _setId; }
    OrbitalElements
        interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

  private:
    constexpr static EnumType _setId = std::to_underlying(ElementSet::CARTESIAN);

    RadiusVector _radius;
    VelocityVector _velocity;
};