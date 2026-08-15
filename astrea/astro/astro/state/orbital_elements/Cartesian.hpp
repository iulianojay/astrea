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
#include <astro/state/framework/OrbitalElementsInterface.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a Cartesian state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Cartesian coordinates.
 */
template <IsFrame auto _frame_>
class Cartesian
    : public OrbitalElementsInterface<Cartesian<_frame_>, _frame_, Distance, Distance, Distance, Velocity, Velocity, Velocity> {

    using Base_T = OrbitalElementsInterface<Cartesian<_frame_>, _frame_, Distance, Distance, Distance, Velocity, Velocity, Velocity>;

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, Cartesian<frame> const&);
    friend class OrbitalElements;

  public:
    using Base_T::Base_T;

    /**
     * @brief Default constructor for Cartesian.
     *
     * Initializes the Cartesian state vector with zero values.
     */
    Cartesian() = default;

    /**
     * @brief Constructor for Cartesian with position and velocity vectors.
     *
     * @param r Radius vector (position)
     * @param v Velocity vector
     */
    Cartesian(const RadiusVector<_frame_>& r, const VelocityVector<_frame_>& v) :
        Base_T(r[0], r[1], r[2], v[0], v[1], v[2])
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
     * @brief Adds a RadiusVector to the Cartesian state vector.
     *
     * @param r Radius vector to add
     * @return Resultant Cartesian sum.
     */
    Cartesian operator+(const RadiusVector<_frame_>& r) const;

    /**
     * @brief Adds a VelocityVector to the Cartesian state vector.
     *
     * @param v Velocity vector to add
     * @return Resultant Cartesian sum.
     */
    Cartesian operator+(const VelocityVector<_frame_>& v) const;

    /**
     * @brief Adds a RadiusVector to the current Cartesian state vector.
     *
     * @param r Radius vector to add
     * @return Reference to the current Cartesian object after addition.
     */
    Cartesian& operator+=(const RadiusVector<_frame_>& r);

    /**
     * @brief Adds a VelocityVector to the current Cartesian state vector.
     *
     * @param v Velocity vector to add
     * @return Reference to the current Cartesian object after addition.
     */
    Cartesian& operator+=(const VelocityVector<_frame_>& v);

    /**
     * @brief Subtracts a RadiusVector from the Cartesian state vector.
     *
     * @param r Radius vector to subtract
     * @return Resultant Cartesian difference.
     */
    Cartesian operator-(const RadiusVector<_frame_>& r) const;

    /**
     * @brief Subtracts a VelocityVector from the Cartesian state vector.
     *
     * @param v Velocity vector to subtract
     * @return Resultant Cartesian difference.
     */
    Cartesian operator-(const VelocityVector<_frame_>& v) const;

    /**
     * @brief Subtracts a RadiusVector from the current Cartesian state vector.
     *
     * @param r Radius vector to subtract
     * @return Reference to the current Cartesian object after subtraction.
     */
    Cartesian& operator-=(const RadiusVector<_frame_>& r);

    /**
     * @brief Subtracts a VelocityVector from the current Cartesian state vector.
     *
     * @param v Velocity vector to subtract
     * @return Reference to the current Cartesian object after subtraction.
     */
    Cartesian& operator-=(const VelocityVector<_frame_>& v);

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
        const auto r = get_position();
        const auto v = get_velocity();

        const CartesianVector<Distance, target_frame> rTarget = r.template in_frame<target_frame>(epoch);
        const CartesianVector<Velocity, target_frame> vTarget = v.template in_frame<target_frame>(epoch, r);

        return Cartesian<target_frame>(rTarget, vTarget);
    }

    /**
     * @brief Converts this Cartesian state to an equivalent Cartesian state in a different frame.
     *
     * Uses proper physical frame transformation (translation and rotation) via in_frame on each
     * component vector. The gravitational parameter is accepted but not used; it exists so that
     * Cartesian shares a uniform in_frame(epoch, mu) signature with Keplerian and Equinoctial.
     *
     * @tparam target_frame The target frame.
     * @param epoch The epoch at which to evaluate the frame transformation.
     * @param mu The gravitational parameter of the central body (not used).
     * @return Cartesian<target_frame> This state expressed in the target frame.
     */
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
    RadiusVector<_frame_>& get_position() { return { get_x(), get_y(), get_z() }; }

    /**
     * @brief Converts the Cartesian state vector to a VelocityVector<_frame_>.
     *
     * @return VelocityVector<_frame_> The velocity vector in Cartesian coordinates.
     */
    VelocityVector<_frame_>& get_velocity() { return { get_vx(), get_vy(), get_vz() }; }

    /**
     * @brief Converts the Cartesian state vector to a RadiusVector<_frame_>.
     *
     * @return RadiusVector<_frame_> The position vector in Cartesian coordinates.
     */
    const RadiusVector<_frame_>& get_position() const { return { get_x(), get_y(), get_z() }; }

    /**
     * @brief Converts the Cartesian state vector to a VelocityVector<_frame_>.
     *
     * @return VelocityVector<_frame_> The velocity vector in Cartesian coordinates.
     */
    const VelocityVector<_frame_>& get_velocity() const { return { get_vx(), get_vy(), get_vz() }; }

    /**
     * @brief Get the x value of the Cartesian state vector.
     *
     * @return  Distance& Reference to the x component of the Cartesian state vector.
     */
    Distance& get_x() { return this->template get<0>(); }

    /**
     * @brief Get the y value of the Cartesian state vector.
     *
     * @return  Distance& Reference to the y component of the Cartesian state vector.
     */
    Distance& get_y() { return this->template get<1>(); }

    /**
     * @brief Get the z value of the Cartesian state vector.
     *
     * @return  Distance& Reference to the z component of the Cartesian state vector.
     */
    Distance& get_z() { return this->template get<2>(); }

    /**
     * @brief Get the x value of the Cartesian state vector.
     *
     * @return const Distance& Reference to the x component of the Cartesian state vector.
     */
    const Distance& get_x() const { return this->template get<0>(); }

    /**
     * @brief Get the y value of the Cartesian state vector.
     *
     * @return const Distance& Reference to the y component of the Cartesian state vector.
     */
    const Distance& get_y() const { return this->template get<1>(); }

    /**
     * @brief Get the z value of the Cartesian state vector.
     *
     * @return const Distance& Reference to the z component of the Cartesian state vector.
     */
    const Distance& get_z() const { return this->template get<2>(); }

    /**
     * @brief Get the vx value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vx component of the Cartesian state vector.
     */
    Velocity& get_vx() { return this->template get<3>(); }

    /**
     * @brief Get the vy value of the Cartesian state vector.
     *
     * @return Velocity& Reference to the vy component of the Cartesian state vector.
     */
    Velocity& get_vy() { return this->template get<4>(); }

    /**
     * @brief Get the vz value of the Cartesian state vector.
     *
     * @return Velocity& Reference to the vz component of the Cartesian state vector.
     */
    Velocity& get_vz() { return this->template get<5>(); }

    /**
     * @brief Get the vx value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vx component of the Cartesian state vector.
     */
    const Velocity& get_vx() const { return this->template get<3>(); }

    /**
     * @brief Get the vy value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vy component of the Cartesian state vector.
     */
    const Velocity& get_vy() const { return this->template get<4>(); }

    /**
     * @brief Get the vz value of the Cartesian state vector.
     *
     * @return const Velocity& Reference to the vz component of the Cartesian state vector.
     */
    const Velocity& get_vz() const { return this->template get<5>(); }

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
};

/**
 * @brief Class representing a partial derivative of a Cartesian state vector.
 *
 * This class encapsulates the velocity and acceleration components of a vehicle in Cartesian coordinates.
 */
template <IsFrame auto _frame_>
class CartesianPartial
    : public OrbitalElementsInterface<CartesianPartial<_frame_>, _frame_, Velocity, Velocity, Velocity, Acceleration, Acceleration, Acceleration> {

    using Base_T =
        OrbitalElementsInterface<CartesianPartial<_frame_>, _frame_, Velocity, Velocity, Velocity, Acceleration, Acceleration, Acceleration>;

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, CartesianPartial<frame> const&);

  public:
    using Base_T::Base_T;

    /**
     * @brief Default constructor for CartesianPartial.
     */
    CartesianPartial() = default;

    /**
     * @brief Constructor for CartesianPartial with velocity and acceleration vectors.
     *
     * @param v Velocity vector
     * @param a Acceleration vector
     */
    CartesianPartial(const VelocityVector<_frame_>& v, const AccelerationVector<_frame_>& a) :
        Base_T(v[0], v[1], v[2], a[0], a[1], a[2])
    {
    }

    /**
     * @brief Get the vx value of the CartesianPartial state vector.
     *
     * @return Velocity The vx component of the CartesianPartial state vector.
     */
    Velocity get_vx() const { return this->template get<0>(); }

    /**
     * @brief Get the vy value of the CartesianPartial state vector.
     *
     * @return Velocity The vy component of the CartesianPartial state vector.
     */
    Velocity get_vy() const { return this->template get<1>(); }

    /**
     * @brief Get the vz value of the CartesianPartial state vector.
     *
     * @return Velocity The vz component of the CartesianPartial state vector.
     */
    Velocity get_vz() const { return this->template get<2>(); }

    /**
     * @brief Get the ax value of the CartesianPartial state vector.
     *
     * @return Acceleration The ax component of the CartesianPartial state vector.
     */
    const Acceleration& get_ax() const { return this->template get<3>(); }

    /**
     * @brief Get the ay value of the CartesianPartial state vector.
     *
     * @return Acceleration The ay component of the CartesianPartial state vector.
     */
    const Acceleration& get_ay() const { return this->template get<4>(); }

    /**
     * @brief Get the az value of the CartesianPartial state vector.
     *
     * @return Acceleration The az component of the CartesianPartial state vector.
     */
    const Acceleration& get_az() const { return this->template get<5>(); }

    /**
     * @brief Get the ax value of the CartesianPartial state vector.
     *
     * @return Acceleration The ax component of the CartesianPartial state vector.
     */
    Acceleration& get_ax() { return this->template get<3>(); }

    /**
     * @brief Get the ay value of the CartesianPartial state vector.
     *
     * @return Acceleration The ay component of the CartesianPartial state vector.
     */
    Acceleration& get_ay() { return this->template get<4>(); }

    /**
     * @brief Get the az value of the CartesianPartial state vector.
     *
     * @return Acceleration The az component of the CartesianPartial state vector.
     */
    Acceleration& get_az() { return this->template get<5>(); }
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/Cartesian.ipp>