

# File Axis.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**Axis.hpp**](Axis_8hpp.md)

[Go to the documentation of this file](Axis_8hpp.md)


```C++

#pragma once

#include <type_traits>

#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>

#include <astro/frames/framework/frame_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct AxisBase {
    template <IsAxis Lhs, IsAxis Rhs>
    [[nodiscard]] friend consteval bool operator==(Lhs, Rhs)
    {
        return std::is_same_v<Lhs, Rhs>;
    }
    template <IsAxis Lhs, IsAxis Rhs>
    [[nodiscard]] friend consteval bool equivalent(Lhs, Rhs)
    {
        return std::is_same_v<Lhs, Rhs>;
    }
};

} // namespace detail

enum class Coordinate { X, Y, Z };

template <mp_units::symbol_text, auto...>
struct Axis;

template <mp_units::symbol_text _name_>
struct Axis<_name_> : detail::AxisBase {
    static constexpr auto name = _name_; 
};

template <mp_units::symbol_text _name_, IsAxis auto _parent_>
struct Axis<_name_, _parent_> : detail::AxisBase {
    static constexpr auto name   = _name_;   
    static constexpr auto parent = _parent_; 
};


struct DynamicAxis : Axis<"dynamic"> {};

template <IsFrame Frame_T, IsAxis Axis_T>
inline consteval auto has_axis(Frame_T, Axis_T)
{
    return std::is_same_v<decltype(Frame_T::axis), Axis_T>;
}

template <IsFrame T, IsFrame U>
consteval bool has_same_axis(T t, U u)
{
    return T::axis == U::axis;
}

namespace axes {

inline constexpr struct icrf final : Axis<"ICRF"> {
    // x - Measured, meant to coincide with EME2000 X-axis at J2000
    // z - Measured, meant to coincide with EME2000 Z-axis at J2000
} icrf;

inline constexpr struct j2000 final : Axis<"EME2000", icrf> {
    // x - mean equator and equinox of date at J2000
    // z - mean pole of date at J2000
} j2000;

} // namespace axes


} // namespace astro
} // namespace astrea
```


