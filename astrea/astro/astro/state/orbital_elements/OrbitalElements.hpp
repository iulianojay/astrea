/**
 * @file OrbitalElements.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the OrbitalElements class and its associated methods.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <variant>

#include <units/units.hpp>

// Astro
#include <astro/astro.fwd.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Concept to check if a type has a method to get the set ID.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetSetId = requires(const T elements) {
    { elements.get_set_id() } -> std::same_as<EnumType>;
};

/**
 * @brief Concept to check if a type can be constructed from a set of orbital elements.
 *
 * @tparam T The type to check.
 * @tparam U The type to construct from.
 */
template <typename T, typename U>
concept IsConstructableTo = requires(T elements, const AstrodynamicsSystem& sys) {
    { U(elements, sys) };
};

/**
 * @brief Concept to check if a type can be converted to Cartesian elements.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasDirectCartesianConversion = requires(const T elements, const AstrodynamicsSystem& sys) {
    { elements.to_cartesian(sys) } -> std::same_as<Cartesian>;
};

/**
 * @brief Concept to check if a type can be converted to Keplerian elements.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasDirectKeplerianConversion = requires(const T elements, const AstrodynamicsSystem& sys) {
    { elements.to_keplerian(sys) } -> std::same_as<Keplerian>;
};

/**
 * @brief Concept to check if a type can be converted to Equinoctial elements.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasDirectEquinoctialConversion = requires(const T elements, const AstrodynamicsSystem& sys) {
    { elements.to_equinoctial(sys) } -> std::same_as<Equinoctial>;
};

/**
 * @brief Concept to check if a type can be converted to Cartesian elements.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasIterpolate =
    requires(const T elements, const Time& thisTime, const Time& otherTime, const T& other, const AstrodynamicsSystem& sys, const Time& targetTime) {
        { elements.interpolate(thisTime, otherTime, other, sys, targetTime) } -> std::same_as<T>;
    };

/**
 * @brief Concept to check if a type can be converted to a vector of Unitless.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasToVector = requires(const T elements) {
    { elements.to_vector() } -> std::same_as<std::vector<Unitless>>;
};

/**
 * @brief Concept to check if a type has mathematical operators defined.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasMathOperators = requires(const T elements, const T other, const Unitless scalar) {
    { elements + other } -> std::same_as<T>;
    { elements - other } -> std::same_as<T>;
    { elements * scalar } -> std::same_as<T>;
    { elements / scalar } -> std::same_as<T>;
};

/**
 * @brief Concept to check if a type has in-place mathematical operators defined.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasInPlaceMathOperators = requires(T elements, const T other, const Unitless scalar) {
    { elements += other };
    { elements -= other };
    { elements *= scalar };
    { elements /= scalar };
};

/**
 * @brief Concept to check if a type is an orbital elements type.
 *
 * This concept checks if a type is a valid orbital elements type, ensuring it meets
 * the requirements for being default constructible, copyable, movable, destructible,
 * and convertible to Cartesian elements.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsOrbitalElements = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires !std::is_same<T, OrbitalElements>::value;
    requires std::is_same<T, Cartesian>::value || IsConstructableTo<T, Cartesian> || HasDirectCartesianConversion<T>;
    requires HasGetSetId<T>;
    requires HasToVector<T>;
    requires HasMathOperators<T>;
    requires HasInPlaceMathOperators<T>;
};

class OrbitalElementPartials; // Forward declaration

/**
 * @brief Class representing a set of orbital elements.
 *
 * This class encapsulates different types of orbital elements (Cartesian, Keplerian, Equinoctial)
 * and provides methods for conversion, interpolation, and mathematical operations.
 */
class OrbitalElements {

    /**
     * @brief Variant type to hold different orbital element types.
     */
    using ElementVariant = std::variant<Cartesian, Keplerian, Equinoctial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElements& state);

  public:
    /**
     * @brief Default constructor initializing to Cartesian elements.
     */
    OrbitalElements() :
        _elements(Cartesian())
    {
    }
    /**
     * @brief Constructor initializing with Cartesian elements.
     *
     * @param elements The orbital elements to initialize with.
     */
    OrbitalElements(Cartesian elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Constructor initializing with Keplerian elements.
     *
     * @param elements The orbital elements to initialize with.
     */
    OrbitalElements(Keplerian elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Constructor initializing with Equinoctial elements.
     *
     * @param elements The orbital elements to initialize with.
     */
    OrbitalElements(Equinoctial elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Converts the current orbital elements to a specific type.
     *
     * @tparam T The type to convert to.
     * @param sys The astrodynamics system to use for the conversion.
     * @return A reference to the current orbital elements after conversion.
     */
    template <IsOrbitalElements T>
    OrbitalElements& convert(const AstrodynamicsSystem& sys)
    {
        _elements = in<T>(sys);
        return *this;
    }

    /**
     * @brief Converts the current orbital elements to a specific type.
     *
     * @tparam T The type to convert to.
     * @param sys The astrodynamics system to use for the conversion.
     * @return The converted orbital elements.
     */
    template <IsOrbitalElements T>
    OrbitalElements convert(const AstrodynamicsSystem& sys) const
    {
        return in<T>(sys);
    }

    /**
     * @brief Converts the current orbital elements to a specified type.
     *
     * @param sys The astrodynamics system to use for the conversion.
     * @return The converted orbital elements.
     */
    template <IsOrbitalElements T>
    T in(const AstrodynamicsSystem& sys) const
    {
        return std::visit([&](const auto& x) -> T { return T(x, sys); }, _elements);
    }

    /**
     * @brief Compares two OrbitalElements objects for equality.
     *
     * @param other Another OrbitalElements object to compare with.
     * @return true if the two OrbitalElements objects are equal
     * @return false if the two OrbitalElements objects are not equal
     */
    bool operator==(const OrbitalElements& other) const;

    /**
     * @brief Adds two OrbitalElements objects.
     *
     * @param other Another OrbitalElements object
     * @return Resultant OrbitalElements sum.
     */
    OrbitalElements operator+(const OrbitalElements& other) const;

    /**
     * @brief Adds another OrbitalElements object to the current one.
     *
     * @param other Another OrbitalElements object
     * @return Reference to the current OrbitalElements object after addition.
     */
    OrbitalElements& operator+=(const OrbitalElements& other);

    /**
     * @brief Subtracts another OrbitalElements object from the current one.
     *
     * @param other Another OrbitalElements object
     * @return Resultant OrbitalElements difference.
     */
    OrbitalElements operator-(const OrbitalElements& other) const;

    /**
     * @brief Subtracts another OrbitalElements object from the current one.
     *
     * @param other Another OrbitalElements object
     * @return Reference to the current OrbitalElements object after subtraction.
     */
    OrbitalElements& operator-=(const OrbitalElements& other);

    /**
     * @brief Multiplies the OrbitalElements by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant OrbitalElements after multiplication.
     */
    OrbitalElements operator*(const Unitless& multiplier) const;

    /**
     * @brief Multiplies the OrbitalElements by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Reference to the current OrbitalElements object after multiplication.
     */
    OrbitalElements& operator*=(const Unitless& multiplier);

    /**
     * @brief Divides the OrbitalElements by a time.
     *
     * @param divisor Time value to divide by
     * @return Resultant OrbitalElementPartials after division.
     */
    OrbitalElementPartials operator/(const Time& divisor) const;

    /**
     * @brief Divides the OrbitalElements by another OrbitalElements object.
     *
     * @param other Another OrbitalElements object
     * @return Resultant vector of unitless values after division.
     */
    std::vector<Unitless> to_vector() const;

    /**
     * @brief Divides the OrbitalElements by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Resultant OrbitalElements after division.
     */
    OrbitalElements operator/(const Unitless& divisor) const;

    /**
     * @brief Divides the OrbitalElements by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Reference to the current OrbitalElements object after division.
     */
    OrbitalElements& operator/=(const Unitless& divisor);

    /**
     * @brief Interpolates between two OrbitalElements at a given time.
     *
     * @param thisTime Time of the current state
     * @param otherTime Time of the other state
     * @param other Another OrbitalElements object to interpolate with
     * @param sys The astrodynamics system to use for the interpolation
     * @param targetTime The target time for interpolation
     * @return Interpolated OrbitalElements at the target time.
     */
    OrbitalElements
        interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

    /**
     * @brief Extracts the underlying orbital elements as a variant.
     *
     * @return const ElementVariant& Reference to the underlying orbital elements variant.
     */
    const ElementVariant& extract() const;

    /**
     * @brief Extracts the underlying orbital elements as a variant.
     *
     * @return ElementVariant& Reference to the underlying orbital elements variant.
     */
    ElementVariant& extract();

    /**
     * @brief Returns the index of the current orbital elements in the variant.
     *
     * @return std::size_t The index of the current orbital elements in the variant.
     */
    constexpr std::size_t index() const { return _elements.index(); }

  private:
    ElementVariant _elements; //!< Variant holding the orbital elements (Cartesian, Keplerian, Equinoctial)

    /**
     * @brief Checks if the underlying types of two OrbitalElements objects are the same.
     *
     * @param other Another OrbitalElements object to compare with.
     * @throws std::runtime_error if the underlying types are not the same.
     */
    void same_underlying_type(const OrbitalElements& other) const;
};

/**
 * @brief Class representing partial derivatives of orbital elements.
 *
 * This class encapsulates the partial derivatives of orbital elements, allowing for
 * operations such as multiplication by time to obtain Cartesian state vectors.
 */
class OrbitalElementPartials {

    /**
     * @brief Variant type to hold different partial element types.
     */
    using PartialVariant = std::variant<CartesianPartial, KeplerianPartial, EquinoctialPartial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElementPartials& state);

  public:
    /**
     * @brief Default constructor initializing to CartesianPartial elements.
     */
    OrbitalElementPartials() :
        _elements(CartesianPartial())
    {
    }

    /**
     * @brief Constructor initializing with CartesianPartial elements.
     *
     * @param elements The orbital element partials to initialize with.
     */
    OrbitalElementPartials(CartesianPartial elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Constructor initializing with KeplerianPartial elements.
     *
     * @param elements The orbital element partials to initialize with.
     */
    OrbitalElementPartials(KeplerianPartial elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Constructor initializing with EquinoctialPartial elements.
     *
     * @param elements The orbital element partials to initialize with.
     */
    OrbitalElementPartials(EquinoctialPartial elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Converts the current orbital element partials to a specific type.
     *
     * @tparam T The type to convert to.
     * @param sys The astrodynamics system to use for the conversion.
     * @return A reference to the current orbital element partials after conversion.
     */
    OrbitalElements operator*(const Time& time) const;

    /**
     * @brief Extracts the underlying orbital element partials as a variant.
     *
     * @return const PartialVariant& Reference to the underlying orbital element partials variant.
     */
    const PartialVariant& extract() const;

    /**
     * @brief Extracts the underlying orbital element partials as a variant.
     *
     * @return PartialVariant& Reference to the underlying orbital element partials variant.
     */
    PartialVariant& extract();

    /**
     * @brief Returns the index of the current orbital element partials in the variant.
     *
     * @return std::size_t The index of the current orbital element partials in the variant.
     */
    constexpr std::size_t index() const;

  private:
    PartialVariant _elements; //!< Variant holding the orbital element partials (CartesianPartial, KeplerianPartial, EquinoctialPartial)

    /**
     * @brief Checks if the underlying types of two OrbitalElementPartials objects are the same.
     *
     * @param other Another OrbitalElementPartials object to compare with.
     * @throws std::runtime_error if the underlying types are not the same.
     */
    void same_underlying_type(const OrbitalElementPartials& other) const;
};

/**
 * @brief Throws an exception for mismatched types in orbital elements.
 *
 * This function is used to throw an exception when the types of two orbital elements do not match.
 * @throws std::runtime_error with a message indicating the mismatch.
 */
void throw_mismatched_types();

/**
 * @brief Checks if two OrbitalElements objects are nearly equal.
 *
 * This function compares two OrbitalElements objects for equality within a specified tolerance.
 *
 * @param first The first OrbitalElements object to compare.
 * @param second The second OrbitalElements object to compare.
 * @param ignoreFastVariable If true, ignores fast-changing variables in the comparison.
 * @param relTol Relative tolerance for the comparison.
 * @return true if the two OrbitalElements objects are nearly equal
 * @return false if the two OrbitalElements objects are not nearly equal
 */
bool nearly_equal(const OrbitalElements& first, const OrbitalElements& second, bool ignoreFastVariable = false, Unitless relTol = 1.0e-5 * mp_units::one);

/**
 * @brief Checks if two OrbitalElementPartials objects are nearly equal.
 *
 * This function compares two OrbitalElementPartials objects for equality within a specified tolerance.
 *
 * @param first The first OrbitalElementPartials object to compare.
 * @param second The second OrbitalElementPartials object to compare.
 * @param ignoreFastVariable If true, ignores fast-changing variables in the comparison.
 * @param relTol Relative tolerance for the comparison.
 * @return true if the two OrbitalElementPartials objects are nearly equal
 * @return false if the two OrbitalElementPartials objects are not nearly equal
 */
bool nearly_equal(
    const OrbitalElementPartials& first,
    const OrbitalElementPartials& second,
    bool ignoreFastVariable = false,
    Unitless relTol         = 1.0e-5 * mp_units::one
);

} // namespace astro
} // namespace astrea