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

class Cartesian {

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
        r{
            0.0 * mp_units::si::unit_symbols::km,
            0.0 * mp_units::si::unit_symbols::km,
            0.0 * mp_units::si::unit_symbols::km
        },
        v{
            0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
            0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
            0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s
        }
    {}
    Cartesian(double x, double y, double z, double vx, double vy, double vz) :
        r{
            x * mp_units::si::unit_symbols::km,
            y * mp_units::si::unit_symbols::km,
            z * mp_units::si::unit_symbols::km
        },
        v{
            vx * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
            vy * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s,
            vz * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s
        }
    {}
    Cartesian(RadiusVector r, VelocityVector v) :
        r(r),
        v(v)
    {}

    ~Cartesian() = default;

    const RadiusVector& get_radius() const { return r; }
    const VelocityVector& get_velocity() const { return v; }

    const auto& get_x() const { return r[0]; }
    const auto& get_y() const { return r[1]; }
    const auto& get_z() const { return r[2]; }
    const auto& get_vx() const { return v[0]; }
    const auto& get_vy() const { return v[1]; }
    const auto& get_vz() const { return v[2]; }

private:

    RadiusVector r;
    VelocityVector v;

};