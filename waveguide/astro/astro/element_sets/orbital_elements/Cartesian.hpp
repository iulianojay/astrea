/**
 * @file Cartesian.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Cartesian class and its associated methods.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <variant>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

// // avro
// #include <avro/Decoder.hh>
// #include <avro/Encoder.hh>
// #include <avro/Specific.hh>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Class representing a Cartesian state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Cartesian coordinates.
 */
class Cartesian {

    friend std::ostream& operator<<(std::ostream&, Cartesian const&);
    friend CartesianPartial;

  public:
    /**
     * @brief Default constructor for Cartesian.
     *
     * Initializes the Cartesian state vector with zero values.
     */
    Cartesian(Unitless scale = 0.0 * detail::unitless) :
        _x(scale * detail::distance_unit),
        _y(scale * detail::distance_unit),
        _z(scale * detail::distance_unit),
        _vx(scale * detail::distance_unit / detail::time_unit),
        _vy(scale * detail::distance_unit / detail::time_unit),
        _vz(scale * detail::distance_unit / detail::time_unit)
    {
    }

    /**
     * @brief Constructor for Cartesian with position and velocity vectors.
     *
     * @param r Radius vector (position)
     * @param v Velocity vector
     */
    Cartesian(const RadiusVector& r, const VelocityVector& v) :
        _x(r[0]),
        _y(r[1]),
        _z(r[2]),
        _vx(v[0]),
        _vy(v[1]),
        _vz(v[2])
    {
    }

    /**
     * @brief Constructor for Cartesian with individual position and velocity components.
     *
     * @param x X component of position
     * @param y Y component of position
     * @param z Z component of position
     * @param vx X component of velocity
     * @param vy Y component of velocity
     * @param vz Z component of velocity
     */
    Cartesian(const Distance& x, const Distance& y, const Distance& z, const Velocity& vx, const Velocity& vy, const Velocity& vz) :
        _x(x),
        _y(y),
        _z(z),
        _vx(vx),
        _vy(vy),
        _vz(vz)
    {
    }

    /**
     * @brief Constructor for Cartesian from another Cartesian object.
     *
     * @param elements Another Cartesian object
     * @param sys Astrodynamics system containing celestial body data
     */
    Cartesian(const Cartesian& elements, const AstrodynamicsSystem& sys) :
        Cartesian(elements)
    {
    }

    /**
     * @brief Constructor for Cartesian from Keplerian elements.
     *
     * @param elements Keplerian elements
     * @param sys Astrodynamics system containing celestial body data
     */
    Cartesian(const Keplerian& elements, const AstrodynamicsSystem& sys);

    /**
     * @brief Constructor for Cartesian from Equinoctial elements.
     *
     * @param elements Equinoctial elements
     * @param sys Astrodynamics system containing celestial body data
     */
    Cartesian(const Equinoctial& elements, const AstrodynamicsSystem& sys);

    /**
     * @brief A static method to create Cartesian state vectors for a LEO orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Cartesian Predefined Cartesian state vector for a LEO orbit.
     */
    static Cartesian LEO(const AstrodynamicsSystem& system);

    /**
     * @brief A static method to create Cartesian state vectors for a LMEO orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Cartesian Predefined Cartesian state vector for a LMEO orbit.
     */
    static Cartesian LMEO(const AstrodynamicsSystem& system);

    /**
     * @brief A static method to create Cartesian state vectors for a GPS orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Cartesian Predefined Cartesian state vector for a GPS orbit.
     */
    static Cartesian GPS(const AstrodynamicsSystem& system);

    /**
     * @brief A static method to create Cartesian state vectors for a HMEO orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Cartesian Predefined Cartesian state vector for a HMEO orbit.
     */
    static Cartesian HMEO(const AstrodynamicsSystem& system);

    /**
     * @brief A static method to create Cartesian state vectors for a GEO orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Cartesian Predefined Cartesian state vector for a GEO orbit.
     */
    static Cartesian GEO(const AstrodynamicsSystem& system);

    /**
     * @brief Copy constructor for Cartesian.
     *
     * @param other Another Cartesian object
     */
    Cartesian(const Cartesian&);

    /**
     * @brief Move constructor for Cartesian.
     *
     * @param other Another Cartesian object
     */
    Cartesian(Cartesian&&) noexcept;

    /**
     * @brief Move assignment operator for Cartesian.
     *
     * @param other Another Cartesian object
     * @return Cartesian& Reference to the current object
     */
    Cartesian& operator=(Cartesian&&) noexcept;

    /**
     * @brief Copy assignment operator for Cartesian.
     *
     * @param other Another Cartesian object
     * @return Cartesian& Reference to the current object
     */
    Cartesian& operator=(const Cartesian&);

    /**
     * @brief Default destructor for Cartesian.
     */
    ~Cartesian() = default;

    /**
     * @brief Compares two Cartesian objects for equality.
     *
     * @param other Another Cartesian object
     * @return true if the two Cartesian objects are equal
     * @return false if the two Cartesian objects are not equal
     */
    bool operator==(const Cartesian& other) const;

    /**
     * @brief Compares two Cartesian objects for inequality.
     *
     * @param other Another Cartesian object
     * @return true if the two Cartesian objects are not equal
     * @return false if the two Cartesian objects are equal
     */
    bool operator!=(const Cartesian& other) const;

    /**
     * @brief Adds two Cartesian objects.
     *
     * @param other Another Cartesian object
     * @return Resultant Cartesian sum.
     */
    Cartesian operator+(const Cartesian& other) const;

    /**
     * @brief Adds another Cartesian object to the current one.
     *
     * @param other Another Cartesian object
     * @return Reference to the current Cartesian object after addition.
     */
    Cartesian& operator+=(const Cartesian& other);

    /**
     * @brief Subtracts another Cartesian object from the current one.
     *
     * @param other Another Cartesian object
     * @return Resultant Cartesian difference.
     */
    Cartesian operator-(const Cartesian& other) const;

    /**
     * @brief Subtracts another Cartesian object from the current one.
     *
     * @param other Another Cartesian object
     * @return Reference to the current Cartesian object after subtraction.
     */
    Cartesian& operator-=(const Cartesian& other);

    /**
     * @brief Multiplies the Cartesian state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant Cartesian after multiplication.
     */
    Cartesian operator*(const Unitless& multiplier) const;

    /**
     * @brief Multiplies the Cartesian state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Reference to the current Cartesian object after multiplication.
     */
    Cartesian& operator*=(const Unitless& multiplier);

    /**
     * @brief Divides the Cartesian state vector by a time.
     *
     * @param time Time value to divide by
     * @return Resultant CartesianPartial after division.
     */
    CartesianPartial operator/(const Time& time) const;

    /**
     * @brief Divides the Cartesian state vector by another Cartesian object.
     *
     * @param other Another Cartesian object
     * @return Resultant vector of unitless values after division.
     */
    std::vector<Unitless> operator/(const Cartesian& other) const;

    /**
     * @brief Divides the Cartesian state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Resultant Cartesian after division.
     */
    Cartesian operator/(const Unitless& divisor) const;

    /**
     * @brief Divides the Cartesian state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Reference to the current Cartesian object after division.
     */
    Cartesian& operator/=(const Unitless& divisor);

    /**
     * @brief Converts the Cartesian state vector to a RadiusVector.
     *
     * @return RadiusVector The position vector in Cartesian coordinates.
     */
    RadiusVector get_radius() const { return { _x, _y, _z }; }

    /**
     * @brief Converts the Cartesian state vector to a VelocityVector.
     *
     * @return VelocityVector The velocity vector in Cartesian coordinates.
     */
    VelocityVector get_velocity() const { return { _vx, _vy, _vz }; }

    /**
     * @brief Get the x value of the Cartesian state vector.
     *
     * @return const Distance& Reference to the x component of the Cartesian state vector.
     */
    const Distance& get_x() const { return _x; }

    /**
     * @brief Get the y value of the Cartesian state vector.
     *
     * @return const Distance& Reference to the y component of the Cartesian state vector.
     */
    const Distance& get_y() const { return _y; }

    /**
     * @brief Get the z value of the Cartesian state vector.
     *
     * @return const Distance& Reference to the z component of the Cartesian state vector.
     */
    const Distance& get_z() const { return _z; }

    /**
     * @brief Get the vx value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vx component of the Cartesian state vector.
     */
    const Velocity& get_vx() const { return _vx; }

    /**
     * @brief Get the vy value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vy component of the Cartesian state vector.
     */
    const Velocity& get_vy() const { return _vy; }

    /**
     * @brief Get the vz value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vz component of the Cartesian state vector.
     */
    const Velocity& get_vz() const { return _vz; }

    /**
     * @brief Returns the size of the Cartesian state vector.
     *
     * @return std::size_t The size of the Cartesian state vector, which is always 6.
     */
    std::size_t size() const { return 6; }

    /**
     * @brief Converts the Cartesian state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the x, y, z, vx, vy, and vz components of the Cartesian state vector.
     */
    std::vector<Unitless> to_vector() const;

    /**
     * @brief Returns the set ID of the Cartesian element set.
     *
     * @return EnumType The set ID of the Cartesian element set.
     */
    constexpr EnumType get_set_id() const { return _setId; }

    /**
     * @brief Interpolates between two Cartesian states at a given time.
     *
     * @param thisTime Time of the current state
     * @param otherTime Time of the other state
     * @param other Other Cartesian state to interpolate with
     * @param sys Astrodynamics system containing celestial body data
     * @param targetTime Target time for interpolation
     * @return Cartesian Interpolated Cartesian state at the target time.
     */
    Cartesian interpolate(const Time& thisTime, const Time& otherTime, const Cartesian& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

  private:
    constexpr static EnumType _setId = std::to_underlying(ElementSet::CARTESIAN); // !< Set ID for the Cartesian element set

    Distance _x;  //!< X component of the position vector
    Distance _y;  //!< Y component of the position vector
    Distance _z;  //!< Z component of the position vector
    Velocity _vx; //!< X component of the velocity vector
    Velocity _vy; //!< Y component of the velocity vector
    Velocity _vz; //!< Z component of the velocity vector
};

/**
 * @brief Class representing a partial derivative of a Cartesian state vector.
 *
 * This class encapsulates the velocity and acceleration components of a vehicle in Cartesian coordinates.
 */
class CartesianPartial {

    friend std::ostream& operator<<(std::ostream&, CartesianPartial const&);

  public:
    /**
     * @brief Default constructor for CartesianPartial.
     */
    CartesianPartial() = default;

    /**
     * @brief Constructor for CartesianPartial with velocity and acceleration components.
     *
     * @param vx X component of velocity
     * @param vy Y component of velocity
     * @param vz Z component of velocity
     * @param ax X component of acceleration
     * @param ay Y component of acceleration
     * @param az Z component of acceleration
     */
    CartesianPartial(const Velocity& vx, const Velocity& vy, const Velocity& vz, const Acceleration& ax, const Acceleration& ay, const Acceleration& az) :
        _vx(vx),
        _vy(vy),
        _vz(vz),
        _ax(ax),
        _ay(ay),
        _az(az)
    {
    }

    /**
     * @brief Multiplication operator for CartesianPartial.
     *
     * @param time Time to multiply the CartesianPartial by
     * @return Cartesian Resulting Cartesian state vector after multiplication.
     */
    Cartesian operator*(const Time& time) const;

  private:
    Velocity _vx;     //!< X component of velocity
    Velocity _vy;     //!< Y component of velocity
    Velocity _vz;     //!< Z component of velocity
    Acceleration _ax; //!< X component of acceleration
    Acceleration _ay; //!< Y component of acceleration
    Acceleration _az; //!< Z component of acceleration
};

} // namespace astro
} // namespace waveguide


// namespace avro {

// template <>
// struct codec_traits<waveguide::astro::Cartesian> {
//     static void encode(Encoder& encoder, const waveguide::astro::Cartesian& cartesian)
//     {
//         avro::encode(encoder, cartesian.get_x());
//         avro::encode(encoder, cartesian.get_y());
//         avro::encode(encoder, cartesian.get_z());
//         avro::encode(encoder, cartesian.get_vx());
//         avro::encode(encoder, cartesian.get_vy());
//         avro::encode(encoder, cartesian.get_vz());
//     }
//     static void decode(Decoder& decoder, waveguide::astro::Cartesian& cartesian)
//     {
//         waveguide::Distance x{}, y{}, z{};
//         waveguide::Velocity vx{}, vy{}, vz{};

//         avro::decode(decoder, x);
//         avro::decode(decoder, y);
//         avro::decode(decoder, z);
//         avro::decode(decoder, vx);
//         avro::decode(decoder, vy);
//         avro::decode(decoder, vz);

//         cartesian = waveguide::astro::Cartesian(x, y, z, vx, vy, vz);
//     }
// };

// } // namespace avro