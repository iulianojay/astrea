/**
 * @file OrbitalElements.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the OrbitalElements class and its associated methods.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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
#include <variant>

#include <units/units.hpp>

// Astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/frame_registry.hpp>
#include <astro/frames/primary_frame.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/types/concepts.hpp>
#include <astro/types/variant_util.hpp>

namespace astrea {
namespace astro {
/**
 * @brief Variant of all frame-indexed element types expanded over every registered frame.
 *
 * The first element type (Cartesian) is always included. Any additional
 * frame-indexed templates passed as FrameIndexedTypes are also expanded over
 * all registered frames. Typically used as:
 *
 * @code
 *   using ElementVariant = OrbitalElementVariant<Keplerian, Equinoctial>;
 * @endcode
 *
 * Adding a frame to ExtraRegisteredFrames automatically adds a new
 * instantiation of every listed template to this variant.
 *
 * To register frames from user code, see ExtraRegisteredFrames in
 * astro/frames/frame_registry.hpp.
 */
template <template <auto> class... FrameIndexedTypes>
using OrbitalElementVariant = typename detail::tuple_to_variant<typename detail::multi_tuple_cat<
    typename detail::apply_nttp_template<Cartesian, detail::AllRegisteredFrames>::type,
    typename detail::apply_nttp_template<FrameIndexedTypes, detail::AllRegisteredFrames>::type...>::type>::type;


/**
 * @brief Concept to check if a type is an orbital elements type.
 *
 * This concept checks if a type is a valid orbital elements type, ensuring it meets
 * the requirements for being default constructible, copyable, movable, destructible,
 * and convertible to Cartesian<frames::primary> elements.
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
    requires std::is_same<T, Cartesian<frames::primary>>::value || IsConstructableTo<T, Cartesian<frames::primary>> ||
                 HasDirectCartesianConversion<T, Cartesian<frames::primary>>;
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
     *
     * Extended at compile time via ExtraRegisteredFrames<> specialization.
     * See cartesianframeregistry.hpp for details.
     */
    using ElementVariant = OrbitalElementVariant<Keplerian, Equinoctial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElements& state);
    friend class StateTransitionMatrix;
    friend class State;

  public:
    /**
     * @brief Default constructor initializing to Cartesian<frames::primary> elements.
     */
    OrbitalElements() :
        _elements(Cartesian<frames::primary>())
    {
    }

    /**
     * @brief Constructor initializing with Cartesian<frame> elements.
     *
     * @param elements The orbital elements to initialize with.
     */
    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElements(Cartesian<frame> elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Constructor initializing with Keplerian<frame> elements.
     *
     * @param elements The orbital elements to initialize with.
     */
    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElements(Keplerian<frame> elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Constructor initializing with Equinoctial<frame> elements.
     *
     * @param elements The orbital elements to initialize with.
     */
    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElements(Equinoctial<frame> elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Converts the current orbital elements to a specific type.
     *
     * @tparam index The index of the orbital element type to convert to.
     * @param mu The gravitational parameter to use for the conversion.
     * @return OrbitalElements& Reference to the current orbital elements after conversion.
     */
    OrbitalElements& convert_to_set(const std::size_t idx, const GravParam& mu);

    /**
     * @brief Converts the current orbital elements to a specific type.
     *
     * @tparam index The index of the orbital element type to convert to.
     * @param mu The gravitational parameter to use for the conversion.
     * @return OrbitalElements Orbital elements after conversion.
     */
    OrbitalElements convert_to_set(const std::size_t idx, const GravParam& mu) const;

    /**
     * @brief Converts the current orbital elements to a specific type.
     *
     * @tparam T The type to convert to.
     * @param mu The gravitational parameter to use for the conversion.
     * @return A reference to the current orbital elements after conversion.
     */
    template <IsOrbitalElements T>
    OrbitalElements& convert_to_set(const GravParam& mu)
    {
        _elements = in_element_set<T>(mu);
        return *this;
    }

    /**
     * @brief Converts the current orbital elements to a specific type.
     *
     * @tparam T The type to convert to.
     * @param mu The gravitational parameter to use for the conversion.
     * @return The converted orbital elements.
     */
    template <IsOrbitalElements T>
    OrbitalElements convert_to_set(const GravParam& mu) const
    {
        return in_element_set<T>(mu);
    }

    /**
     * @brief Converts the current orbital elements to a specified type.
     *
     * @param mu The gravitational parameter to use for the conversion.
     * @return The converted orbital elements.
     */
    template <IsOrbitalElements T>
    T in_element_set(const GravParam& mu) const
    {
        return std::visit([&](const auto& x) -> T { return T(x, mu); }, _elements);
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
     * @brief Converts the OrbitalElements to a vector of Unitless values.
     *
     * @return std::vector<Unitless> Vector containing the orbital elements as unitless values.
     */
    std::vector<Unitless> force_to_vector() const;

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
     * @param mu The gravitational parameter to use for the interpolation
     * @param targetTime The target time for interpolation
     * @return Interpolated OrbitalElements at the target time.
     */
    OrbitalElements
        interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const GravParam& mu, const Time& targetTime) const;

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

    /**
     * @brief Returns the set ID for a specific type of orbital elements.
     *
     * @tparam T The type of orbital elements.
     * @return std::size_t The set ID for the specified type.
     */
    template <typename T>
    static constexpr std::size_t get_set_id()
    {
        return get_variant_index<ElementVariant, T, 0>();
    }

  private:
    ElementVariant _elements; //!< Variant holding the orbital elements (Cartesian, Keplerian, Equinoctial)

    /**
     * @brief Implementation of the conversion to a specific type.
     *
     * @param idx The index of the orbital element type to convert to.
     * @param mu The gravitational parameter to use for the conversion.
     * @return The converted orbital elements.
     */
    OrbitalElements convert_to_set_impl(const std::size_t idx, const GravParam& mu) const;

    /**
     * @brief Creates an OrbitalElements object from a vector of Unitless values.
     *
     * @param vec The vector of Unitless values.
     * @param idx The index of the orbital element type to create.
     * @return OrbitalElements The created OrbitalElements object.
     */
    static OrbitalElements from_vector(const std::vector<Unitless>& vec, const std::size_t idx);
};

template <template <auto> class... FrameIndexedTypes>
using OrbitalElementPartialVariant = typename detail::tuple_to_variant<typename detail::multi_tuple_cat<
    typename detail::apply_nttp_template<CartesianPartial, detail::AllRegisteredFrames>::type,
    typename detail::apply_nttp_template<FrameIndexedTypes, detail::AllRegisteredFrames>::type...>::type>::type;


/**
 * @brief Class representing partial derivatives of orbital elements.
 *
 * This class encapsulates the partial derivatives of orbital elements, allowing for
 * operations such as multiplication by time to obtain Cartesian<frames::primary> state vectors.
 */
class OrbitalElementPartials {

    /**
     * @brief Variant type to hold different partial element types.
     */
    using PartialVariant = OrbitalElementPartialVariant<KeplerianPartial, EquinoctialPartial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElementPartials& state);

  public:
    /**
     * @brief Default constructor initializing to CartesianPartial elements.
     */
    OrbitalElementPartials() :
        _elements(CartesianPartial<frames::primary>())
    {
    }

    /**
     * @brief Constructor initializing with CartesianPartial elements.
     *
     * @param elements The orbital element partials to initialize with.
     */
    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElementPartials(CartesianPartial<frame> elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Constructor initializing with KeplerianPartial elements.
     *
     * @param elements The orbital element partials to initialize with.
     */
    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElementPartials(KeplerianPartial<frame> elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Constructor initializing with EquinoctialPartial elements.
     *
     * @param elements The orbital element partials to initialize with.
     */
    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElementPartials(EquinoctialPartial<frame> elements) :
        _elements(elements)
    {
    }

    /**
     * @brief Converts the current orbital element partials to a specific type.
     *
     * @tparam T The type to convert to.
     * @param mu The gravitational parameter to use for the conversion.
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
    constexpr std::size_t index() const { return _elements.index(); }

    /**
     * @brief Converts the OrbitalElementPartials to a vector of Unitless values.
     *
     * @return std::vector<Unitless> Vector containing the orbital elements as unitless values.
     */
    std::vector<Unitless> force_to_vector() const;

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

} // namespace astro
} // namespace astrea