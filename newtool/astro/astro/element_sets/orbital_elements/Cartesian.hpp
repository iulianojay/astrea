#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <variant>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

class Cartesian {

    friend std::ostream& operator<<(std::ostream&, Cartesian const&);
    friend CartesianPartial;

  public:
    Cartesian() :
        _x(0.0 * mp_units::si::unit_symbols::km),
        _y(0.0 * mp_units::si::unit_symbols::km),
        _z(0.0 * mp_units::si::unit_symbols::km),
        _vx(0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s),
        _vy(0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s),
        _vz(0.0 * mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s)
    {
    }
    Cartesian(const RadiusVector& r, const VelocityVector& v) :
        _x(r[0]),
        _y(r[1]),
        _z(r[2]),
        _vx(v[0]),
        _vy(v[1]),
        _vz(v[2])
    {
    }
    Cartesian(const Distance& x, const Distance& y, const Distance& z, const Velocity& vx, const Velocity& vy, const Velocity& vz) :
        _x(x),
        _y(y),
        _z(z),
        _vx(vx),
        _vy(vy),
        _vz(vz)
    {
    }
    Cartesian(const OrbitalElements& elements, const AstrodynamicsSystem& sys);
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

    Cartesian operator*(const Unitless& multiplier) const;
    Cartesian& operator*=(const Unitless& multiplier);

    Cartesian operator/(const Unitless& divisor) const;
    Cartesian& operator/=(const Unitless& divisor);

    // Element access
    RadiusVector get_radius() const { return { _x, _y, _z }; }
    VelocityVector get_velocity() const { return { _vx, _vy, _vz }; }

    const Distance& get_x() const { return _x; }
    const Distance& get_y() const { return _y; }
    const Distance& get_z() const { return _z; }

    const Velocity& get_vx() const { return _vx; }
    const Velocity& get_vy() const { return _vy; }
    const Velocity& get_vz() const { return _vz; }

    size_t size() const { return 6; }

    std::vector<double> to_vector() const;

    constexpr EnumType get_set_id() const { return _setId; }
    OrbitalElements
        interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

  private:
    constexpr static EnumType _setId = std::to_underlying(ElementSet::CARTESIAN);

    Distance _x;
    Distance _y;
    Distance _z;
    Velocity _vx;
    Velocity _vy;
    Velocity _vz;
};

class CartesianPartial {

    using Acceleration =
        mp_units::quantity<mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s)>;

  public:
    CartesianPartial() = default;
    CartesianPartial(const Velocity& vx, const Velocity& vy, const Velocity& vz, const Acceleration& ax, const Acceleration& ay, const Acceleration& az) :
        _vx(vx),
        _vy(vy),
        _vz(vz),
        _ax(ax),
        _ay(ay),
        _az(az)
    {
    }

    Cartesian operator*(const Time& time) const;

  private:
    Velocity _vx;
    Velocity _vy;
    Velocity _vz;
    Acceleration _ax;
    Acceleration _ay;
    Acceleration _az;
};