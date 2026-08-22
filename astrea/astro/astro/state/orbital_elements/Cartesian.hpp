/**
 * @file Cartesian.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Cartesian class and its associated methods.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <iosfwd>

// // avro
// #include <avro/Decoder.hh>
// #include <avro/Encoder.hh>
// #include <avro/Specific.hh>

#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a Cartesian state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Cartesian coordinates.
 */
template <IsFrame auto _frame_>
class Cartesian {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, Cartesian<frame> const&);
    friend class OrbitalElements;

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Cartesian state vector.

    /**
     * @brief Default constructor for Cartesian.
     *
     * Initializes the Cartesian state vector with zero values.
     */
    Cartesian(Unitless scale = 0.0 * astrea::detail::unitless) :
        _r(scale * astrea::detail::distance_unit, scale * astrea::detail::distance_unit, scale * astrea::detail::distance_unit),
        _v(scale * astrea::detail::distance_unit / astrea::detail::time_unit,
           scale * astrea::detail::distance_unit / astrea::detail::time_unit,
           scale * astrea::detail::distance_unit / astrea::detail::time_unit)
    {
    }

    /**
     * @brief Constructor for Cartesian with position and velocity vectors.
     *
     * @param r Radius vector (position)
     * @param v Velocity vector
     */
    Cartesian(const RadiusVector<_frame_>& r, const VelocityVector<_frame_>& v) :
        _r(r),
        _v(v)
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
        _r(x, y, z),
        _v(vx, vy, vz)
    {
    }

    /**
     * @brief Constructor for Cartesian from another Cartesian object.
     *
     * @param elements Another Cartesian object
     * @param sys Astrodynamics system containing celestial body data
     */
    Cartesian(const Cartesian& elements, const GravParam& mu) :
        Cartesian(elements)
    {
    }

    /**
     * @brief Constructor for Cartesian from Keplerian elements.
     *
     * @param elements Keplerian elements
     * @param sys Astrodynamics system containing celestial body data
     */
    Cartesian(const Keplerian<_frame_>& elements, const GravParam& mu);

    /**
     * @brief Constructor for Cartesian from Equinoctial elements.
     *
     * @param elements Equinoctial elements
     * @param sys Astrodynamics system containing celestial body data
     */
    Cartesian(const Equinoctial<_frame_>& elements, const GravParam& mu);

    /**
     * @brief A static method to create Cartesian state vectors for a LEO orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Cartesian Predefined Cartesian state vector for a LEO orbit.
     */
    static Cartesian LEO(const GravParam& mu);

    /**
     * @brief A static method to create Cartesian state vectors for a LMEO orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Cartesian Predefined Cartesian state vector for a LMEO orbit.
     */
    static Cartesian LMEO(const GravParam& mu);

    /**
     * @brief A static method to create Cartesian state vectors for a GPS orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Cartesian Predefined Cartesian state vector for a GPS orbit.
     */
    static Cartesian GPS(const GravParam& mu);

    /**
     * @brief A static method to create Cartesian state vectors for a HMEO orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Cartesian Predefined Cartesian state vector for a HMEO orbit.
     */
    static Cartesian HMEO(const GravParam& mu);

    /**
     * @brief A static method to create Cartesian state vectors for a GEO orbit.
     *
     * This method return predefined Cartesian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Cartesian Predefined Cartesian state vector for a GEO orbit.
     */
    static Cartesian GEO(const GravParam& mu);

    /**
     * @brief Copy constructor for Cartesian.
     *
     * @param other Another Cartesian object
     */
    Cartesian(const Cartesian<_frame_>&);

    /**
     * @brief Move constructor for Cartesian.
     *
     * @param other Another Cartesian object
     */
    Cartesian(Cartesian<_frame_>&&) noexcept = default;

    /**
     * @brief Move assignment operator for Cartesian.
     *
     * @param other Another Cartesian object
     * @return Cartesian& Reference to the current object
     */
    Cartesian& operator=(Cartesian<_frame_>&&) noexcept;

    /**
     * @brief Copy assignment operator for Cartesian.
     *
     * @param other Another Cartesian object
     * @return Cartesian& Reference to the current object
     */
    Cartesian& operator=(const Cartesian<_frame_>&);

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
    bool operator==(const Cartesian<_frame_>& other) const;

    /**
     * @brief Compares two Cartesian objects for inequality.
     *
     * @param other Another Cartesian object
     * @return true if the two Cartesian objects are not equal
     * @return false if the two Cartesian objects are equal
     */
    bool operator!=(const Cartesian<_frame_>& other) const;

    /**
     * @brief Adds two Cartesian objects.
     *
     * @param other Another Cartesian object
     * @return Resultant Cartesian sum.
     */
    Cartesian operator+(const Cartesian<_frame_>& other) const;

    Cartesian operator+(const RadiusVector<_frame_>& r) const;
    Cartesian operator+(const VelocityVector<_frame_>& v) const;

    /**
     * @brief Adds another Cartesian object to the current one.
     *
     * @param other Another Cartesian object
     * @return Reference to the current Cartesian object after addition.
     */
    Cartesian& operator+=(const Cartesian<_frame_>& other);

    Cartesian& operator+=(const RadiusVector<_frame_>& r);
    Cartesian& operator+=(const VelocityVector<_frame_>& v);

    /**
     * @brief Subtracts another Cartesian object from the current one.
     *
     * @param other Another Cartesian object
     * @return Resultant Cartesian difference.
     */
    Cartesian operator-(const Cartesian<_frame_>& other) const;

    Cartesian operator-(const RadiusVector<_frame_>& r) const;
    Cartesian operator-(const VelocityVector<_frame_>& v) const;

    /**
     * @brief Subtracts another Cartesian object from the current one.
     *
     * @param other Another Cartesian object
     * @return Reference to the current Cartesian object after subtraction.
     */
    Cartesian& operator-=(const Cartesian<_frame_>& other);

    Cartesian& operator-=(const RadiusVector<_frame_>& r);
    Cartesian& operator-=(const VelocityVector<_frame_>& v);

    /**
     * @brief Multiplies the Cartesian state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant Cartesian after multiplication.
     */
    Cartesian operator*(const Unitless& multiplier) const; // TODO: Add left-hand version (i.e. scalar * state)

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
    CartesianPartial<_frame_> operator/(const Time& time) const;

    /**
     * @brief Divides the Cartesian state vector by another Cartesian object.
     *
     * @param other Another Cartesian object
     * @return Resultant vector of unitless values after division.
     */
    std::vector<Unitless> operator/(const Cartesian<_frame_>& other) const;

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
     * @brief Converts this Cartesian state to an equivalent Cartesian state in a different frame.
     *
     * Uses proper physical frame transformation (translation and rotation) via in_frame on each
     * component vector. The gravitational parameter is accepted but not used; it exists so that
     * Cartesian shares a uniform in_frame(epoch, mu) signature with Keplerian and Equinoctial.
     *
     * @tparam target_frame The target frame.
     * @param epoch The epoch at which to evaluate the frame transformation.
     * @return Cartesian<target_frame> This state expressed in the target frame.
     */
    template <IsFrame auto target_frame>
    Cartesian<target_frame> in_frame(const Date& epoch) const
    {
        if constexpr (equivalent(frame, target_frame)) { return *this; }
        const CartesianVector<Distance, target_frame> rTarget = _r.template in_frame<target_frame>(epoch);
        const CartesianVector<Velocity, target_frame> vTarget = _v.template in_frame<target_frame>(epoch, _r);
        return Cartesian<target_frame>(rTarget, vTarget);
    }

    template <IsFrame auto target_frame>
    Cartesian<target_frame> in_frame(const Date& epoch, const GravParam& /*mu*/) const
    {
        return in_frame<target_frame>(epoch);
    }

    /**
     * @brief Converts the Cartesian state vector to a RadiusVector<_frame_>.
     *
     * @return RadiusVector<_frame_> The position vector in Cartesian coordinates.
     */
    const RadiusVector<_frame_>& get_position() const { return _r; }

    /**
     * @brief Converts the Cartesian state vector to a VelocityVector<_frame_>.
     *
     * @return VelocityVector<_frame_> The velocity vector in Cartesian coordinates.
     */
    const VelocityVector<_frame_>& get_velocity() const { return _v; }

    /**
     * @brief Get the x value of the Cartesian state vector.
     *
     * @return const Distance& Reference to the x component of the Cartesian state vector.
     */
    const Distance& get_x() const { return _r.get_x(); }

    /**
     * @brief Get the y value of the Cartesian state vector.
     *
     * @return const Distance& Reference to the y component of the Cartesian state vector.
     */
    const Distance& get_y() const { return _r.get_y(); }

    /**
     * @brief Get the z value of the Cartesian state vector.
     *
     * @return const Distance& Reference to the z component of the Cartesian state vector.
     */
    const Distance& get_z() const { return _r.get_z(); }

    /**
     * @brief Get the vx value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vx component of the Cartesian state vector.
     */
    const Velocity& get_vx() const { return _v.get_x(); }

    /**
     * @brief Get the vy value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vy component of the Cartesian state vector.
     */
    const Velocity& get_vy() const { return _v.get_y(); }

    /**
     * @brief Get the vz value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vz component of the Cartesian state vector.
     */
    const Velocity& get_vz() const { return _v.get_z(); }

    /**
     * @brief Converts the Cartesian state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the x, y, z, vx, vy, and vz components of the Cartesian state vector.
     */
    std::vector<double> force_to_double_vector() const;

    /**
     * @brief Interpolates between two Cartesian states at a given time.
     *
     * @param thisTime Time of the current state
     * @param otherTime Time of the other state
     * @param other Other Cartesian state to interpolate with
     * @param mu Gravitational parameter of the central body
     * @param targetTime Target time for interpolation
     * @return Cartesian Interpolated Cartesian state at the target time.
     */
    Cartesian interpolate(const Time& thisTime, const Time& otherTime, const Cartesian<_frame_>& other, const GravParam& mu, const Time& targetTime) const;

  private:
    RadiusVector<_frame_> _r;   //!< Position vector
    VelocityVector<_frame_> _v; //!< Velocity vector

    /**
     * @brief Creates a Cartesian object from a vector of unitless values.
     *
     * @param vec Vector containing the x, y, z, vx, vy, and vz components of the Cartesian state vector.
     * @return Cartesian Constructed Cartesian object.
     */
    static Cartesian from_double_vector(const std::vector<double>& vec);
};

/**
 * @brief Class representing a partial derivative of a Cartesian state vector.
 *
 * This class encapsulates the velocity and acceleration components of a vehicle in Cartesian coordinates.
 */
template <IsFrame auto _frame_>
class CartesianPartial {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, CartesianPartial<frame> const&);

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Cartesian state vector.

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
        _v(vx, vy, vz),
        _a(ax, ay, az)
    {
    }

    /**
     * @brief Constructor for CartesianPartial with velocity and acceleration vectors.
     *
     * @param v Velocity vector
     * @param a Acceleration vector
     */
    CartesianPartial(const VelocityVector<_frame_>& v, const AccelerationVector<_frame_>& a) :
        _v(v),
        _a(a)
    {
    }

    /**
     * @brief Get the vx value of the CartesianPartial state vector.
     *
     * @return Velocity The vx component of the CartesianPartial state vector.
     */
    Velocity get_vx() const { return _v.get_x(); }

    /**
     * @brief Get the vy value of the CartesianPartial state vector.
     *
     * @return Velocity The vy component of the CartesianPartial state vector.
     */
    Velocity get_vy() const { return _v.get_y(); }

    /**
     * @brief Get the vz value of the CartesianPartial state vector.
     *
     * @return Velocity The vz component of the CartesianPartial state vector.
     */
    Velocity get_vz() const { return _v.get_z(); }

    /**
     * @brief Get the ax value of the CartesianPartial state vector.
     *
     * @return Acceleration The ax component of the CartesianPartial state vector.
     */
    Acceleration get_ax() const { return _a.get_x(); }

    /**
     * @brief Get the ay value of the CartesianPartial state vector.
     *
     * @return Acceleration The ay component of the CartesianPartial state vector.
     */
    Acceleration get_ay() const { return _a.get_y(); }

    /**
     * @brief Get the az value of the CartesianPartial state vector.
     *
     * @return Acceleration The az component of the CartesianPartial state vector.
     */
    Acceleration get_az() const { return _a.get_z(); }

    /**
     * @brief Multiplication operator for CartesianPartial.
     *
     * @param time Time to multiply the CartesianPartial by
     * @return Cartesian Resulting Cartesian state vector after multiplication.
     */
    Cartesian<_frame_> operator*(const Time& time) const;

    /**
     * @brief Converts the CartesianPartial state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the components of the CartesianPartial state vector.
     */
    std::vector<double> force_to_double_vector() const;

  private:
    VelocityVector<_frame_> _v;     //!< Velocity vector
    AccelerationVector<_frame_> _a; //!< Acceleration vector
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/Cartesian.ipp>