#pragma once

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <variant>

// Astro
#include <astro/astro.fwd.hpp>
#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/element_sets/orbital_elements/Equinoctial.hpp>
#include <astro/element_sets/orbital_elements/Keplerian.hpp>
#include <astro/types/detail.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/types/typeid_name_extract.hpp>
#include <astro/units/units.hpp>

namespace astro {

// class OrbitalElements;

template <typename T>
concept HasGetSetId = requires(const T elements)
{
    {
        elements.get_set_id()
        } -> std::same_as<EnumType>;
};

template <typename T, typename U>
concept IsConstructableTo = requires(T elements, const AstrodynamicsSystem& sys)
{
    { U(elements, sys) };
};

template <typename T>
concept HasDirectCartesianConversion = requires(const T elements, const AstrodynamicsSystem& sys)
{
    {
        elements.to_cartesian(sys)
        } -> std::same_as<Cartesian>;
};

template <typename T>
concept HasDirectKeplerianConversion = requires(const T elements, const AstrodynamicsSystem& sys)
{
    {
        elements.to_keplerian(sys)
        } -> std::same_as<Keplerian>;
};

template <typename T>
concept HasDirectEquinoctialConversion = requires(const T elements, const AstrodynamicsSystem& sys)
{
    {
        elements.to_equinoctial(sys)
        } -> std::same_as<Equinoctial>;
};

template <typename T>
concept HasIterpolate =
    requires(const T elements, const Time& thisTime, const Time& otherTime, const T& other, const AstrodynamicsSystem& sys, const Time& targetTime)
{
    {
        elements.interpolate(thisTime, otherTime, other, sys, targetTime)
        } -> std::same_as<T>;
};

template <typename T>
concept HasToVector = requires(const T elements)
{
    {
        elements.to_vector()
        } -> std::same_as<std::vector<Unitless>>;
};

template <typename T>
concept HasSize = requires(const T elements)
{
    {
        elements.size()
        } -> std::same_as<std::size_t>;
};

template <typename T>
concept HasMathOperators = requires(const T elements, const T other, const Unitless scalar)
{
    {
        elements + other
        } -> std::same_as<T>;
    {
        elements - other
        } -> std::same_as<T>;
    {
        elements* scalar
        } -> std::same_as<T>;
    {
        elements / scalar
        } -> std::same_as<T>;
};

template <typename T>
concept HasInPlaceMathOperators = requires(T elements, const T other, const Unitless scalar)
{
    { elements += other };
    { elements -= other };
    { elements *= scalar };
    { elements /= scalar };
};

template <typename T>
concept IsOrbitalElements = requires(T)
{
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires !std::is_same<T, OrbitalElements>::value;
    requires std::is_same<T, Cartesian>::value || IsConstructableTo<T, Cartesian> || HasDirectCartesianConversion<T>;
    requires HasGetSetId<T>;
    requires HasToVector<T>;
    requires HasSize<T>;
    requires HasMathOperators<T>;
    requires HasInPlaceMathOperators<T>;
};

class OrbitalElementPartials;

class OrbitalElements {

    using ElementVariant = std::variant<Cartesian, Keplerian, Equinoctial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElements& state);

  public:
    OrbitalElements() :
        _elements(Cartesian())
    {
    }
    OrbitalElements(Cartesian elements) :
        _elements(elements)
    {
    }
    OrbitalElements(Keplerian elements) :
        _elements(elements)
    {
    }
    OrbitalElements(Equinoctial elements) :
        _elements(elements)
    {
    }

    template <IsOrbitalElements T>
    OrbitalElements& convert(const AstrodynamicsSystem& sys)
    {
        _elements = in<T>(sys);
        return *this;
    }
    template <IsOrbitalElements T>
    OrbitalElements convert(const AstrodynamicsSystem& sys) const
    {
        return in<T>(sys);
    }

    template <IsOrbitalElements T>
    T in(const AstrodynamicsSystem& sys) const
    {
        return std::visit([&](const auto& x) -> T { return T(x, sys); }, _elements);
    }

    OrbitalElements operator+(const OrbitalElements& other) const;
    OrbitalElements& operator+=(const OrbitalElements& other);

    OrbitalElements operator-(const OrbitalElements& other) const;
    OrbitalElements& operator-=(const OrbitalElements& other);

    OrbitalElements operator*(const Unitless& multiplier) const;
    OrbitalElements& operator*=(const Unitless& multiplier);

    OrbitalElementPartials operator/(const Time& divisor) const;
    std::vector<Unitless> to_vector() const;
    OrbitalElements operator/(const Unitless& divisor) const;
    OrbitalElements& operator/=(const Unitless& divisor);

    OrbitalElements
        interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

    const ElementVariant& extract() const;
    ElementVariant& extract();

    constexpr std::size_t index() const { return _elements.index(); }

  private:
    ElementVariant _elements;

    void same_underlying_type(const OrbitalElements& other) const;
};

class OrbitalElementPartials {

    using PartialVariant = std::variant<CartesianPartial, KeplerianPartial, EquinoctialPartial>;

  public:
    OrbitalElementPartials() :
        _elements(CartesianPartial())
    {
    }
    OrbitalElementPartials(CartesianPartial elements) :
        _elements(elements)
    {
    }
    OrbitalElementPartials(KeplerianPartial elements) :
        _elements(elements)
    {
    }
    OrbitalElementPartials(EquinoctialPartial elements) :
        _elements(elements)
    {
    }

    OrbitalElements operator*(const Time& time) const;

    const PartialVariant& extract() const;
    PartialVariant& extract();

    constexpr std::size_t index() const;

  private:
    PartialVariant _elements;

    void same_underlying_type(const OrbitalElementPartials& other) const;
};

void throw_mismatched_types();
bool nearly_equal(const OrbitalElements& first, const OrbitalElements& second, bool ignoreFastVariable = false, Unitless relTol = 1.0e-5 * mp_units::one);

} // namespace astro