#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <variant>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace waveguide {
namespace astro {

class Tle {

    friend std::ostream& operator<<(std::ostream&, Tle const&);
    friend TlePartial;

  public:
    Tle(Unitless scale = 0.0 * waveguide::detail::unitless) :
        _x(scale * waveguide::detail::distance_unit),
        _y(scale * waveguide::detail::distance_unit),
        _z(scale * waveguide::detail::distance_unit),
        _vx(scale * waveguide::detail::distance_unit / waveguide::detail::time_unit),
        _vy(scale * waveguide::detail::distance_unit / waveguide::detail::time_unit),
        _vz(scale * waveguide::detail::distance_unit / waveguide::detail::time_unit)
    {
    }
    Tle(const RadiusVector<ECI>& r, const VelocityVector<ECI>& v) :
        _x(r[0]),
        _y(r[1]),
        _z(r[2]),
        _vx(v[0]),
        _vy(v[1]),
        _vz(v[2])
    {
    }
    Tle(const Distance& x, const Distance& y, const Distance& z, const Velocity& vx, const Velocity& vy, const Velocity& vz) :
        _x(x),
        _y(y),
        _z(z),
        _vx(vx),
        _vy(vy),
        _vz(vz)
    {
    }
    Tle(const Cartesian& elements, const AstrodynamicsSystem& sys) :
        Tle(elements)
    {
    }
    Tle(const Keplerian& elements, const AstrodynamicsSystem& sys);
    Tle(const Equinoctial& elements, const AstrodynamicsSystem& sys);

    // Copy constructor
    Tle(const Tle&);

    // Move constructor
    Tle(Tle&&) noexcept;

    // Move assignment operator
    Tle& operator=(Tle&&) noexcept;

    // Copy assignment operator
    Tle& operator=(const Tle&);

    ~Tle() = default;

    // Comparitors operators
    bool operator==(const Tle& other) const;
    bool operator!=(const Tle& other) const;

    // Mathmatical operators
    Tle operator+(const Tle& other) const;
    Tle& operator+=(const Tle& other);

    Tle operator-(const Tle& other) const;
    Tle& operator-=(const Tle& other);

    Tle operator*(const Unitless& multiplier) const;
    Tle& operator*=(const Unitless& multiplier);

    TlePartial operator/(const Time& time) const;
    std::vector<Unitless> operator/(const Tle& other) const;
    Tle operator/(const Unitless& divisor) const;
    Tle& operator/=(const Unitless& divisor);

    // Element access
    RadiusVector<ECI> get_radius() const { return { _x, _y, _z }; }
    VelocityVector<ECI> get_velocity() const { return { _vx, _vy, _vz }; }

    const Distance& get_x() const { return _x; }
    const Distance& get_y() const { return _y; }
    const Distance& get_z() const { return _z; }

    const Velocity& get_vx() const { return _vx; }
    const Velocity& get_vy() const { return _vy; }
    const Velocity& get_vz() const { return _vz; }

    std::size_t size() const { return 6; }

    std::vector<Unitless> to_vector() const;

    constexpr EnumType get_set_id() const { return _setId; }
    Tle interpolate(const Time& thisTime, const Time& otherTime, const Tle& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

  private:
    constexpr static EnumType _setId = std::to_underlying(ElementSet::CARTESIAN);

    Distance _x;
    Distance _y;
    Distance _z;
    Velocity _vx;
    Velocity _vy;
    Velocity _vz;

    // Input data
    std::array<std::string, 2> rawTLE;

    // Line 1
    unsigned catalogNumber;
    std::string classification;
    std::string launchYear;
    std::string launchNumber;
    std::string launchPiece;

    Date epoch;

    mp_units::quantity<mp_units::one / mp_units::pow<2>(mp_units::non_si::day)> meanMotion1st;
    mp_units::quantity<mp_units::one / mp_units::pow<3>(mp_units::non_si::day)> meanMotion2nd;

    mp_units::quantity<mp_units::pow<2>(mp_units::si::unit_symbols::m) / mp_units::si::unit_symbols::kg> ballisticCoefficient;

    size_t ephemerisType;
    size_t checkSum1;

    // Line 2
    Angle inclination;
    Angle rightAscension;
    Unitless eccentricity;
    Angle argumentOfPerigee;
    mp_units::quantity<mp_units::one / mp_units::non_si::day> meanMotion;

    unsigned revNumber;
    size_t checkSum2;
};

class TlePartial {

    using Acceleration =
        mp_units::quantity<mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s)>;

  public:
    TlePartial() = default;
    TlePartial(const Velocity& vx, const Velocity& vy, const Velocity& vz, const Acceleration& ax, const Acceleration& ay, const Acceleration& az) :
        _vx(vx),
        _vy(vy),
        _vz(vz),
        _ax(ax),
        _ay(ay),
        _az(az)
    {
    }

    Tle operator*(const Time& time) const;

  private:
    Velocity _vx;
    Velocity _vy;
    Velocity _vz;
    Acceleration _ax;
    Acceleration _ay;
    Acceleration _az;
};

} // namespace astro
} // namespace waveguide


// namespace avro {

// template <>
// struct codec_traits<astro::Tle> {
//     static void encode(Encoder& encoder, const astro::Tle& cartesian)
//     {
//         avro::encode(encoder, cartesian.get_x());
//         avro::encode(encoder, cartesian.get_y());
//         avro::encode(encoder, cartesian.get_z());
//         avro::encode(encoder, cartesian.get_vx());
//         avro::encode(encoder, cartesian.get_vy());
//         avro::encode(encoder, cartesian.get_vz());
//     }
//     static void decode(Decoder& decoder, astro::Tle& cartesian)
//     {
//         Distance x{}, y{}, z{};
//         Velocity vx{}, vy{}, vz{};

//         avro::decode(decoder, x);
//         avro::decode(decoder, y);
//         avro::decode(decoder, z);
//         avro::decode(decoder, vx);
//         avro::decode(decoder, vy);
//         avro::decode(decoder, vz);

//         cartesian = astro::Tle(x, y, z, vx, vy, vz);
//     }
// };

// } // namespace avro