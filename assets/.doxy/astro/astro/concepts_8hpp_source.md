

# File concepts.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**types**](dir_81b398d2ba04cf47420d9ac22d356bcf.md) **>** [**concepts.hpp**](concepts_8hpp.md)

[Go to the documentation of this file](concepts_8hpp.md)


```C++

#pragma once

#include <concepts>

#include <astro/types/enums.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

template <typename T, typename U>
concept IsConstructableTo = requires(T elements, const GravParam& mu) {
    { U(elements, mu) };
};

template <typename T, IsFrame auto frame>
concept HasDirectCartesianConversion = requires(const T elements, const GravParam& mu) {
    { elements.to_cartesian(mu) } -> std::same_as<Cartesian<frame>>;
};

template <typename T, IsFrame auto frame>
concept HasDirectKeplerianConversion = requires(const T elements, const GravParam& mu) {
    { elements.to_keplerian(mu) } -> std::same_as<Keplerian<frame>>;
};

template <typename T, IsFrame auto frame>
concept HasDirectEquinoctialConversion = requires(const T elements, const GravParam& mu) {
    { elements.to_equinoctial(mu) } -> std::same_as<Equinoctial<frame>>;
};

template <typename T>
concept HasIterpolate =
    requires(const T elements, const Time& thisTime, const Time& otherTime, const T& other, const GravParam& mu, const Time& targetTime) {
        { elements.interpolate(thisTime, otherTime, other, mu, targetTime) } -> std::same_as<T>;
    };

template <typename T>
concept HasForceToDoubleVector = requires(const T elements) {
    { elements.force_to_double_vector() } -> std::same_as<std::vector<double>>;
};

template <typename T>
concept HasMathOperators = requires(const T elements, const T other, const Unitless scalar) {
    { elements + other } -> std::same_as<T>;
    { elements - other } -> std::same_as<T>;
    { elements * scalar } -> std::same_as<T>;
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
concept HasGetName = requires(const T event) {
    { event.get_name() } -> std::same_as<std::string>;
};

} // namespace astro
} // namespace astrea
```


