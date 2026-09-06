

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
#include <astro/frames/definitions/frame_registry.hpp>
#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/state/orbital_elements/Equinoctial.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/types/concepts.hpp>
#include <astro/types/variant_util.hpp>

namespace astrea {
namespace astro {
template <template <auto> class... FrameIndexedTypes>
using OrbitalElementVariant = typename detail::tuple_to_variant<typename detail::multi_tuple_cat<
    typename detail::apply_nttp_template<Cartesian, detail::AllRegisteredFrames>::type,
    typename detail::apply_nttp_template<FrameIndexedTypes, detail::AllRegisteredFrames>::type...>::type>::type;

template <typename T>
concept IsFrameAware = requires { T::frame; };

template <typename T>
concept IsOrbitalElements = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires !std::is_same<T, OrbitalElements>::value;
    requires IsFrameAware<T>;
    requires std::is_same<T, Cartesian<T::frame>>::value || IsConstructableTo<T, Cartesian<T::frame>> ||
                 HasDirectCartesianConversion<T, T::frame>;
    requires HasForceToDoubleVector<T>;
    requires HasMathOperators<T>;
    requires HasInPlaceMathOperators<T>;
};

class OrbitalElementPartials; // Forward declaration

template <auto...>
struct BadConversionRequest;

class OrbitalElements {

    using ElementVariant = OrbitalElementVariant<Keplerian, Equinoctial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElements& state);
    friend class StateTransitionMatrix;
    friend class State;

  public:
    OrbitalElements() :
        _elements(Cartesian<frames::primary>())
    {
    }

    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElements(Cartesian<frame> elements) :
        _elements(elements)
    {
    }

    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElements(Keplerian<frame> elements) :
        _elements(elements)
    {
    }

    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElements(Equinoctial<frame> elements) :
        _elements(elements)
    {
    }

    OrbitalElements& convert_to_set(const std::size_t idx, const GravParam& mu);

    OrbitalElements convert_to_set(const std::size_t idx, const GravParam& mu) const;

    template <IsOrbitalElements T>
    OrbitalElements& convert_to_set(const GravParam& mu)
    {
        if constexpr (!equivalent(T::frame, frames::primary)) {
            static_assert(always_false<BadConversionRequest<T::frame.name.portable(), frames::primary.name.portable()>>, "In-place set conversion requires the target set be in the primary frame.");
        }
        _elements = in_element_set<T>(mu);
        return *this;
    }

    template <IsOrbitalElements T>
    OrbitalElements convert_to_set(const GravParam& mu) const
    {
        if constexpr (!equivalent(T::frame, frames::primary)) {
            static_assert(always_false<BadConversionRequest<T::frame.name.portable(), frames::primary.name.portable()>>, "In-place set conversion requires the target set be in the primary frame.");
        }
        return in_element_set<T>(mu);
    }

    template <IsOrbitalElements T>
    T in_element_set(const GravParam& mu) const
    {
        return std::visit([&](const auto& x) -> T { return T(x, mu); }, _elements);
    }

    template <IsFrame auto target_frame>
    auto in_frame(const Date& epoch, const GravParam& mu) const
    {
        return std::visit(
            [&](const auto& x) -> decltype(x.template in_frame<target_frame>(epoch, mu)) {
                return x.template in_frame<target_frame>(epoch, mu);
            },
            _elements
        );
    }

    bool operator==(const OrbitalElements& other) const;

    OrbitalElements operator+(const OrbitalElements& other) const;

    OrbitalElements& operator+=(const OrbitalElements& other);

    OrbitalElements operator-(const OrbitalElements& other) const;

    OrbitalElements& operator-=(const OrbitalElements& other);

    OrbitalElements operator*(const Unitless& multiplier) const;

    OrbitalElements& operator*=(const Unitless& multiplier);

    OrbitalElementPartials operator/(const Time& divisor) const;

    std::vector<double> force_to_double_vector() const;

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

    static OrbitalElements from_double_vector(const std::vector<double>& vec, const std::size_t idx);
};

template <template <auto> class... FrameIndexedTypes>
using OrbitalElementPartialVariant = typename detail::tuple_to_variant<typename detail::multi_tuple_cat<
    typename detail::apply_nttp_template<CartesianPartial, detail::AllRegisteredFrames>::type,
    typename detail::apply_nttp_template<FrameIndexedTypes, detail::AllRegisteredFrames>::type...>::type>::type;


class OrbitalElementPartials {

    using PartialVariant = OrbitalElementPartialVariant<KeplerianPartial, EquinoctialPartial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElementPartials& state);

  public:
    OrbitalElementPartials() :
        _elements(CartesianPartial<frames::primary>())
    {
    }

    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElementPartials(CartesianPartial<frame> elements) :
        _elements(elements)
    {
    }

    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElementPartials(KeplerianPartial<frame> elements) :
        _elements(elements)
    {
    }

    template <IsFrame auto frame>
        requires(IsRegisteredFrame<frame>)
    OrbitalElementPartials(EquinoctialPartial<frame> elements) :
        _elements(elements)
    {
    }

    OrbitalElements operator*(const Time& time) const;

    const PartialVariant& extract() const;

    PartialVariant& extract();

    constexpr std::size_t index() const { return _elements.index(); }

    std::vector<double> force_to_double_vector() const;

  private:
    PartialVariant _elements; 

    void same_underlying_type(const OrbitalElementPartials& other) const;
};

void throw_mismatched_types();

} // namespace astro
} // namespace astrea
```


