/**
 * @file Equinoctial.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Equinoctial class and its associated methods.
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
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace astrea {
namespace astro {

/**
 * @brief The Equinoctial class represents the equinoctial orbital elements.
 *
 * The equinoctial elements are a set of orbital elements that are particularly useful for
 * describing orbits in a way that avoids singularities, especially for near-circular orbits.
 * They are defined in terms of the semilatus rectum and the components of the eccentricity vector.
 */
class Equinoctial {

    friend std::ostream& operator<<(std::ostream&, Equinoctial const&);

  public:
    /**
     * @brief Constructs an Equinoctial object with default values.
     *
     * @param scale A scaling factor to initialize the elements, typically used for unit conversion.
     */
    Equinoctial(Unitless scale = 0.0 * detail::unitless) :
        _semilatus(scale * detail::distance_unit),
        _f(scale * detail::unitless),
        _g(scale * detail::unitless),
        _h(scale * detail::unitless),
        _k(scale * detail::unitless),
        _trueLongitude(scale * detail::angle_unit)
    {
    }

    /**
     * @brief Constructs an Equinoctial object with specified values.
     *
     * @param semilatus The semilatus rectum of the orbit.
     * @param f The first component of the eccentricity vector.
     * @param g The second component of the eccentricity vector.
     * @param h The the first component of the planar vector.
     * @param k The the second component of the planar vector.
     * @param trueLongitude The true longitude of the orbit.
     */
    Equinoctial(const Distance& semilatus, const Unitless& f, const Unitless& g, const Unitless& h, const Unitless& k, const Angle& trueLongitude) :
        _semilatus(semilatus),
        _f(f),
        _g(g),
        _h(h),
        _k(k),
        _trueLongitude(trueLongitude)
    {
    }

    /**
     * @brief Constructs an Equinoctial object from another Equinoctial object.
     *
     * @param elements The Equinoctial object to copy.
     * @param sys The astrodynamics system context for conversion.
     */
    Equinoctial(const Equinoctial& elements, const AstrodynamicsSystem& sys) :
        Equinoctial(elements)
    {
    }

    /**
     * @brief Constructs an Equinoctial object from Keplerian elements.
     *
     * @param elements The Keplerian elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Equinoctial(const Keplerian& elements, const AstrodynamicsSystem& sys);

    /**
     * @brief Constructs an Equinoctial object from Cartesian elements.
     *
     * @param elements The Cartesian elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Equinoctial(const Cartesian& elements, const AstrodynamicsSystem& sys);

    /**
     * @brief A static method to create Equinoctial state vectors for a LEO orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Equinoctial Predefined Equinoctial state vector for a LEO orbit.
     */
    static Equinoctial LEO(const AstrodynamicsSystem& system);

    /**
     * @brief A static method to create Equinoctial state vectors for a LMEO orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Equinoctial Predefined Equinoctial state vector for a LMEO orbit.
     */
    static Equinoctial LMEO(const AstrodynamicsSystem& system);

    /**
     * @brief A static method to create Equinoctial state vectors for a GPS orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Equinoctial Predefined Equinoctial state vector for a GPS orbit.
     */
    static Equinoctial GPS(const AstrodynamicsSystem& system);

    /**
     * @brief A static method to create Equinoctial state vectors for a HMEO orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Equinoctial Predefined Equinoctial state vector for a HMEO orbit.
     */
    static Equinoctial HMEO(const AstrodynamicsSystem& system);

    /**
     * @brief A static method to create Equinoctial state vectors for a GEO orbit.
     *
     * This method return predefined Equinoctial state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Equinoctial Predefined Equinoctial state vector for a GEO orbit.
     */
    static Equinoctial GEO(const AstrodynamicsSystem& system);

    /**
     * @brief Copy constructor for Equinoctial.
     *
     */
    Equinoctial(const Equinoctial&);

    /**
     * @brief Move constructor for Equinoctial.
     *
     * @param other Another Equinoctial object
     */
    Equinoctial(Equinoctial&& other) noexcept;

    /**
     * @brief Move assignment operator for Equinoctial.
     *
     * @param other Another Equinoctial object
     * @return Equinoctial& Reference to the current object
     */
    Equinoctial& operator=(Equinoctial&& other) noexcept;

    /**
     * @brief Copy assignment operator for Equinoctial.
     *
     * @param other Another Equinoctial object
     * @return Equinoctial& Reference to the current object
     */
    Equinoctial& operator=(const Equinoctial& other);

    /**
     * @brief Default destructor for Equinoctial.
     */
    ~Equinoctial() = default;

    /**
     * @brief Checks if two Equinoctial objects are equal.
     *
     * @param other Another Equinoctial object
     * @return true if the two Equinoctial objects are equal, false otherwise.
     */
    bool operator==(const Equinoctial& other) const;

    /**
     * @brief Checks if two Equinoctial objects are not equal.
     *
     * @param other Another Equinoctial object
     * @return true if the two Equinoctial objects are not equal, false otherwise.
     */
    bool operator!=(const Equinoctial& other) const;

    /**
     * @brief Adds two Equinoctial objects.
     *
     * @param other Another Equinoctial object
     * @return Resultant Equinoctial sum.
     */
    Equinoctial operator+(const Equinoctial& other) const;

    /**
     * @brief Adds another Equinoctial object to the current one.
     *
     * @param other Another Equinoctial object
     * @return Reference to the current Equinoctial object after addition.
     */
    Equinoctial& operator+=(const Equinoctial& other);

    /**
     * @brief Subtracts another Equinoctial object from the current one.
     *
     * @param other Another Equinoctial object
     * @return Resultant Equinoctial after subtraction.
     */
    Equinoctial operator-(const Equinoctial& other) const;

    /**
     * @brief Subtracts another Equinoctial object from the current one.
     *
     * @param other Another Equinoctial object
     * @return Reference to the current Equinoctial object after subtraction.
     */
    Equinoctial& operator-=(const Equinoctial& other);

    /**
     * @brief Multiplies the Equinoctial state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant Equinoctial after multiplication.
     */
    Equinoctial operator*(const Unitless& multiplier) const;

    /**
     * @brief Multiplies the Equinoctial state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Reference to the current Equinoctial object after multiplication.
     */
    Equinoctial& operator*=(const Unitless& multiplier);

    /**
     * @brief Divides the Equinoctial state vector by a time.
     *
     * @param time Time value to divide by
     * @return Resultant EquinoctialPartial after division.
     */
    EquinoctialPartial operator/(const Time& time) const;

    /**
     * @brief Divides the Equinoctial state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Resultant Equinoctial after division.
     */
    Equinoctial operator/(const Unitless& divisor) const;

    /**
     * @brief Divides the Equinoctial state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Reference to the current Equinoctial object after division.
     */
    Equinoctial& operator/=(const Unitless& divisor);

    /**
     * @brief Get the semilatus value of the Equinoctial state vector.
     *
     * @return const Distance& Reference to the semilatus component of the Equinoctial state vector.
     */
    const Distance& get_semilatus() const { return _semilatus; }

    /**
     * @brief Get the f value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the f component of the Equinoctial state vector.
     */
    const Unitless& get_f() const { return _f; }

    /**
     * @brief Get the g value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the g component of the Equinoctial state vector.
     */
    const Unitless& get_g() const { return _g; }

    /**
     * @brief Get the h value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the h component of the Equinoctial state vector.
     */
    const Unitless& get_h() const { return _h; }

    /**
     * @brief Get the k value of the Equinoctial state vector.
     *
     * @return const Unitless& Reference to the k component of the Equinoctial state vector.
     */
    const Unitless& get_k() const { return _k; }

    /**
     * @brief Get the true longitude value of the Equinoctial state vector.
     *
     * @return const Angle& Reference to the true longitude component of the Equinoctial state vector.
     */
    const Angle& get_true_longitude() const { return _trueLongitude; }

    /**
     * @brief Returns the size of the Equinoctial state vector.
     *
     * @return std::size_t The size of the Equinoctial state vector, which is always 6.
     */
    std::size_t size() const { return 6; }

    /**
     * @brief Converts the Equinoctial state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the semilatus, f, g, h, k, and true longitude components of the Equinoctial state vector.
     */
    constexpr EnumType get_set_id() const { return _setId; }

    /**
     * @brief Converts the Equinoctial state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the semilatus, f, g, h, k, and true longitude components of the Equinoctial state vector.
     */
    Equinoctial
        interpolate(const Time& thisTime, const Time& otherTime, const Equinoctial& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

    /**
     * @brief Converts the Equinoctial state vector to a vector of unitless values.
     */
    std::vector<Unitless> to_vector() const;

  private:
    constexpr static EnumType _setId = std::to_underlying(ElementSet::EQUINOCTIAL); //!< Set ID for the Equinoctial element set

    Distance _semilatus;  //!< Semilatus rectum of the orbit
    Unitless _f;          //!< First component of the eccentricity vector
    Unitless _g;          //!< Second component of the eccentricity vector
    Unitless _h;          //!< The first component of the planar vector
    Unitless _k;          //!< The second component of the planar vector
    Angle _trueLongitude; //!< True longitude of the orbit
};

/**
 * @brief Class representing a partial derivative of an Equinoctial state vector.
 *
 */
class EquinoctialPartial {

    friend std::ostream& operator<<(std::ostream&, EquinoctialPartial const&);

  public:
    /**
     * @brief Default constructor for EquinoctialPartial.
     *
     * Initializes the EquinoctialPartial with zero values.
     */
    EquinoctialPartial() = default;

    /**
     * @brief Constructor for EquinoctialPartial with velocity and acceleration components.
     *
     * @param semilatusPartial Semilatus rectum partial derivative
     * @param fPartial First component of the eccentricity vector partial derivative
     * @param gPartial Second component of the eccentricity vector partial derivative
     * @param hPartial First component of the planar vector partial derivative
     * @param kPartial Second component of the planar vector partial derivative
     * @param trueLongitudePartial True longitude partial derivative
     */
    EquinoctialPartial(
        const Velocity& semilatusPartial,
        const UnitlessPerTime& fPartial,
        const UnitlessPerTime& gPartial,
        const UnitlessPerTime& hPartial,
        const UnitlessPerTime& kPartial,
        const AngularRate& trueLongitudePartial
    ) :
        _semilatusPartial(semilatusPartial),
        _fPartial(fPartial),
        _gPartial(gPartial),
        _hPartial(hPartial),
        _kPartial(kPartial),
        _trueLongitudePartial(trueLongitudePartial)
    {
    }

    /**
     * @brief Multiplication operator for EquinoctialPartial.
     *
     * @param time Time to multiply the EquinoctialPartial by
     * @return Equinoctial Resulting Equinoctial state vector after multiplication.
     */
    Equinoctial operator*(const Time& time) const;

  private:
    Velocity _semilatusPartial;        //!< Semilatus rectum partial derivative
    UnitlessPerTime _fPartial;         //!< First component of the eccentricity vector partial derivative
    UnitlessPerTime _gPartial;         //!< Second component of the eccentricity vector partial derivative
    UnitlessPerTime _hPartial;         //!< First component of the planar vector partial derivative
    UnitlessPerTime _kPartial;         //!< Second component of the planar vector partial derivative
    AngularRate _trueLongitudePartial; //!< True longitude partial derivative
};

} // namespace astro
} // namespace astrea