#pragma once

#ifndef SWIG
    #include <iostream>
    #include <cmath>
    #include <array>
#endif

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <iomanip>
#include <iostream>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

#include "fwd/systems/AstrodynamicsSystem.fwd.hpp"
class Keplerian;

class Cartesian {

    friend std::ostream& operator<<(std::ostream&, Cartesian const&);

    using RadiusVector = std::array<
        mp_units::quantity<
            mp_units::si::unit_symbols::km
        >,
    3>;

    using VelocityVector = std::array<
        mp_units::quantity<
            mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s
        >,
    3>;

public:

    Cartesian() :
        _radius{
            0.0 * mp_units::si::unit_symbols::km,
            0.0 * mp_units::si::unit_symbols::km,
            0.0 * mp_units::si::unit_symbols::km
        },
        _velocity{
            0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
            0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
            0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s
        }
    {}
    Cartesian(double x, double y, double z, double vx, double vy, double vz) :
        _radius{
            x * mp_units::si::unit_symbols::km,
            y * mp_units::si::unit_symbols::km,
            z * mp_units::si::unit_symbols::km
        },
        _velocity{
            vx * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
            vy * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
            vz * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s
        }
    {}
    Cartesian(RadiusVector r, VelocityVector v) :
        _radius(r),
        _velocity(v)
    {}
    Cartesian(const Keplerian& elements, const AstrodynamicsSystem& sys);

    // Copy constructor
    Cartesian(const Cartesian&);

    // Move constructor
    Cartesian(Cartesian&&) noexcept;

    // Move assignment operator
    Cartesian& operator=(Cartesian&&) noexcept;

    // Copy assignment operator
    Cartesian& operator=(const Cartesian&);

    ~Cartesian() = default;

    const RadiusVector& get__radius() const { return _radius; }
    const VelocityVector& get__velocity() const { return _velocity; }

    const auto& get_x() const { return _radius[0]; }
    const auto& get_y() const { return _radius[1]; }
    const auto& get_z() const { return _radius[2]; }
    const auto& get_vx() const { return _velocity[0]; }
    const auto& get_vy() const { return _velocity[1]; }
    const auto& get_vz() const { return _velocity[2]; }

private:

    RadiusVector _radius;
    VelocityVector _velocity;

};