

# File OrbitalElements.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**orbital\_elements**](dir_6eb62f1e639545772a8b9a71f7b1d0b7.md) **>** [**OrbitalElements.hpp**](OrbitalElements_8hpp.md)

[Go to the documentation of this file](OrbitalElements_8hpp.md)


```C++

#pragma once

#include <iosfwd>
#include <variant>

#include <units/units.hpp>

// Astro
#include <astro/astro.fwd.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/types/variant_util.hpp>

namespace astrea {
namespace astro {

template <typename T, typename U>
concept IsConstructableTo = requires(T elements, const GravParam& mu) {
    { U(elements, mu) };
};

template <typename T>
concept HasDirectCartesianConversion = requires(const T elements, const GravParam& mu) {
    { elements.to_cartesian(mu) } -> std::same_as<Cartesian>;
};

template <typename T>
concept HasDirectKeplerianConversion = requires(const T elements, const GravParam& mu) {
    { elements.to_keplerian(mu) } -> std::same_as<Keplerian>;
};

template <typename T>
concept HasDirectEquinoctialConversion = requires(const T elements, const GravParam& mu) {
    { elements.to_equinoctial(mu) } -> std::same_as<Equinoctial>;
};

template <typename T>
concept HasIterpolate =
    requires(const T elements, const Time& thisTime, const Time& otherTime, const T& other, const GravParam& mu, const Time& targetTime) {
        { elements.interpolate(thisTime, otherTime, other, mu, targetTime) } -> std::same_as<T>;
    };

template <typename T>
concept HasToVector = requires(const T elements) {
    { elements.force_to_vector() } -> std::same_as<std::vector<Unitless>>;
};

template <typename T>
concept HasMathOperators = requires(const T elements, const T other, const Unitless scalar) {
    { elements + other } -> std::same_as<T>;
    { elements - other } -> std::same_as<T>;
    { elements* scalar } -> std::same_as<T>;
    { elements / scalar } -> std::same_as<T>;
};

template <typename T>
concept HasInPlaceMathOperators = requires(T elements, const T other, const Unitless scalar) {
    { elements += other };
    { elements -= other };
    { elements *= scalar };
    { elements /= scalar };
};

template <typename T>
concept IsOrbitalElements = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires !std::is_same<T, OrbitalElements>::value;
    requires std::is_same<T, Cartesian>::value || IsConstructableTo<T, Cartesian> || HasDirectCartesianConversion<T>;
    requires HasToVector<T>;
    requires HasMathOperators<T>;
    requires HasInPlaceMathOperators<T>;
};

class OrbitalElementPartials; // Forward declaration

class OrbitalElements {

    using ElementVariant = std::variant<Cartesian, Keplerian, Equinoctial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElements& state);
    friend class StateTransitionMatrix;
    friend class State;

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

    OrbitalElements& convert_to_set(const std::size_t idx, const GravParam& mu);

    OrbitalElements convert_to_set(const std::size_t idx, const GravParam& mu) const;

    template <IsOrbitalElements T>
    OrbitalElements& convert_to_set(const GravParam& mu)
    {
        _elements = in_element_set<T>(mu);
        return *this;
    }

    template <IsOrbitalElements T>
    OrbitalElements convert_to_set(const GravParam& mu) const
    {
        return in_element_set<T>(mu);
    }

    template <IsOrbitalElements T>
    T in_element_set(const GravParam& mu) const
    {
        return std::visit([&](const auto& x) -> T { return T(x, mu); }, _elements);
    }

    bool operator==(const OrbitalElements& other) const;

    OrbitalElements operator+(const OrbitalElements& other) const;

    OrbitalElements& operator+=(const OrbitalElements& other);

    OrbitalElements operator-(const OrbitalElements& other) const;

    OrbitalElements& operator-=(const OrbitalElements& other);

    OrbitalElements operator*(const Unitless& multiplier) const;

    OrbitalElements& operator*=(const Unitless& multiplier);

    OrbitalElementPartials operator/(const Time& divisor) const;

    std::vector<Unitless> force_to_vector() const;

    OrbitalElements operator/(const Unitless& divisor) const;

    OrbitalElements& operator/=(const Unitless& divisor);

    OrbitalElements
        interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const GravParam& mu, const Time& targetTime) const;

    const ElementVariant& extract() const;

    ElementVariant& extract();

    constexpr std::size_t index() const { return _elements.index(); }

    template <typename T>
    static constexpr std::size_t get_set_id()
    {
        return get_variant_index<ElementVariant, T, 0>();
    }

  private:
    ElementVariant _elements; 

    OrbitalElements convert_to_set_impl(const std::size_t idx, const GravParam& mu) const;

    static OrbitalElements from_vector(const std::vector<Unitless>& vec, const std::size_t idx);
};

class OrbitalElementPartials {

    using PartialVariant = std::variant<CartesianPartial, KeplerianPartial, EquinoctialPartial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElementPartials& state);

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

    constexpr std::size_t index() const { return _elements.index(); }

    std::vector<Unitless> force_to_vector() const;

  private:
    PartialVariant _elements; 

    void same_underlying_type(const OrbitalElementPartials& other) const;
};

void throw_mismatched_types();

bool nearly_equal(const OrbitalElements& first, const OrbitalElements& second, bool ignoreFastVariable = false, Unitless relTol = 1.0e-5 * astrea::detail::unitless);

bool nearly_equal(
    const OrbitalElementPartials& first,
    const OrbitalElementPartials& second,
    bool ignoreFastVariable = false,
    Unitless relTol         = 1.0e-5 * astrea::detail::unitless
);

} // namespace astro
} // namespace astrea
```


