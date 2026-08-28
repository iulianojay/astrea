/**
 * @file Equinoctial.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Equinoctial class and its associated methods.
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/framework/OrbitalElementsInterface.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief The Equinoctial class represents the equinoctial orbital elements.
 *
 * The equinoctial elements are a set of orbital elements that are particularly useful for
 * describing orbits in a way that avoids singularities, especially for near-circular orbits.
 * They are defined in terms of the semilatus rectum and the components of the eccentricity vector.
 */
template <IsFrame auto _frame_>
class Equinoctial
    : public OrbitalElementsInterface<Equinoctial<_frame_>, _frame_, Distance, Unitless, Unitless, Unitless, Unitless, Angle> {

    using Base_T =
        OrbitalElementsInterface<Equinoctial<_frame_>, _frame_, Distance, Unitless, Unitless, Unitless, Unitless, Angle>;

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, Equinoctial<frame> const&);
    friend class OrbitalElements;

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Equinoctial state vector.
    template <IsFrame auto F>
    using BaseType = Equinoctial<F>;
    using Base_T::Base_T;

    /**
     * @brief Default constructor for Equinoctial.
     */
    Equinoctial() = default;

    /**
     * @brief Constructs an Equinoctial object from another Equinoctial object.
     *
     * @param elements The Equinoctial object to copy.
     * @param sys The astrodynamics system context for conversion.
     */
    Equinoctial(const Equinoctial<_frame_>& elements, const GravParam& mu) :
        Equinoctial(elements)
    {
    }

    /**
     * @brief Constructs an Equinoctial object from Keplerian elements.
     *
     * @param elements The Keplerian elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Equinoctial(const Keplerian<_frame_>& elements, const GravParam& mu);

    /**
     * @brief Constructs an Equinoctial object from Cartesian elements.
     *
     * @param elements The Cartesian elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Equinoctial(const Cartesian<_frame_>& elements, const GravParam& mu) :
        Equinoctial(Keplerian<_frame_>(elements, mu), mu)
    {
    }

    /**
     * @brief A static method to create Equinoctial state vectors for a LEO orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Equinoctial Predefined Equinoctial state vector for a LEO orbit.
     */
    static Equinoctial LEO(const GravParam& mu);

    /**
     * @brief A static method to create Equinoctial state vectors for a LMEO orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Equinoctial Predefined Equinoctial state vector for a LMEO orbit.
     */
    static Equinoctial LMEO(const GravParam& mu);

    /**
     * @brief A static method to create Equinoctial state vectors for a GPS orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Equinoctial Predefined Equinoctial state vector for a GPS orbit.
     */
    static Equinoctial GPS(const GravParam& mu);

    /**
     * @brief A static method to create Equinoctial state vectors for a HMEO orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Equinoctial Predefined Equinoctial state vector for a HMEO orbit.
     */
    static Equinoctial HMEO(const GravParam& mu);

    /**
     * @brief A static method to create Equinoctial state vectors for a GEO orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Equinoctial Predefined Equinoctial state vector for a GEO orbit.
     */
    static Equinoctial GEO(const GravParam& mu);

    /**
     * @brief Copy constructor for Equinoctial.
     *
     */
    Equinoctial(const Equinoctial<_frame_>&);

    /**
     * @brief Move constructor for Equinoctial.
     *
     * @param other Another Equinoctial object
     */
    Equinoctial(Equinoctial<_frame_>&& other) noexcept;

    /**
     * @brief Move assignment operator for Equinoctial.
     *
     * @param other Another Equinoctial object
     * @return Equinoctial<_frame_>& Reference to the current object
     */
    Equinoctial& operator=(Equinoctial<_frame_>&& other) noexcept;

    /**
     * @brief Copy assignment operator for Equinoctial.
     *
     * @param other Another Equinoctial object
     * @return Equinoctial& Reference to the current object
     */
    Equinoctial& operator=(const Equinoctial<_frame_>& other);

    /**
     * @brief Default destructor for Equinoctial.
     */
    ~Equinoctial() = default;

    /**
     * @brief Converts this Equinoctial state to Equinoctial elements expressed in a different frame.
     *
     * First converts to Cartesian in the native frame, applies the physical frame transformation,
     * then converts the result back to Equinoctial elements.
     *
     * @tparam target_frame The target frame.
     * @param epoch The epoch at which to evaluate the frame transformation.
     * @param mu The gravitational parameter of the central body.
     * @return Equinoctial<target_frame> This state expressed in the target frame.
     */
    template <IsFrame auto target_frame>
    Equinoctial<target_frame> in_frame(const Date& epoch, const GravParam& mu) const;

    /**
     * @brief Get the semilatus value of the Equinoctial state vector.
     *
     * @return const Distance& Reference to the semilatus component of the Equinoctial state vector.
     */
    Distance& get_semilatus() { return this->template get<0>(); }

    /**
     * @brief Get the f value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the f component of the Equinoctial state vector.
     */
    Unitless& get_f() { return this->template get<1>(); }

    /**
     * @brief Get the g value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the g component of the Equinoctial state vector.
     */
    Unitless& get_g() { return this->template get<2>(); }

    /**
     * @brief Get the h value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the h component of the Equinoctial state vector.
     */
    Unitless& get_h() { return this->template get<3>(); }

    /**
     * @brief Get the k value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the k component of the Equinoctial state vector.
     */
    Unitless& get_k() { return this->template get<4>(); }

    /**
     * @brief Get the true longitude value of the Equinoctial state vector.
     *
     * @return const Angle& Reference to the true longitude component of the Equinoctial state vector.
     */
    Angle& get_true_longitude() { return this->template get<5>(); }

    /**
     * @brief Get the semilatus value of the Equinoctial state vector.
     *
     * @return const Distance& Reference to the semilatus component of the Equinoctial state vector.
     */
    const Distance& get_semilatus() const { return this->template get<0>(); }

    /**
     * @brief Get the f value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the f component of the Equinoctial state vector.
     */
    const Unitless& get_f() const { return this->template get<1>(); }

    /**
     * @brief Get the g value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the g component of the Equinoctial state vector.
     */
    const Unitless& get_g() const { return this->template get<2>(); }

    /**
     * @brief Get the h value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the h component of the Equinoctial state vector.
     */
    const Unitless& get_h() const { return this->template get<3>(); }

    /**
     * @brief Get the k value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the k component of the Equinoctial state vector.
     */
    const Unitless& get_k() const { return this->template get<4>(); }

    /**
     * @brief Get the true longitude value of the Equinoctial state vector.
     *
     * @return const Angle& Reference to the true longitude component of the Equinoctial state vector.
     */
    const Angle& get_true_longitude() const { return this->template get<5>(); }
};

/**
 * @brief Class representing a partial derivative of an Equinoctial state vector.
 *
 */
template <IsFrame auto _frame_>
class EquinoctialPartial
    : public OrbitalElementsInterface<EquinoctialPartial<_frame_>, _frame_, Velocity, UnitlessPerTime, UnitlessPerTime, UnitlessPerTime, UnitlessPerTime, AngularVelocity> {

    using Base_T =
        OrbitalElementsInterface<EquinoctialPartial<_frame_>, _frame_, Velocity, UnitlessPerTime, UnitlessPerTime, UnitlessPerTime, UnitlessPerTime, AngularVelocity>;

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, EquinoctialPartial<frame> const&);

  public:
    using Base_T::Base_T;

    /**
     * @brief Default constructor for EquinoctialPartial.
     *
     * Initializes the EquinoctialPartial with zero values.
     */
    EquinoctialPartial() = default;
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/Equinoctial.ipp>