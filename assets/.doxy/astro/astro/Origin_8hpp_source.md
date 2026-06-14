

# File Origin.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**Origin.hpp**](Origin_8hpp.md)

[Go to the documentation of this file](Origin_8hpp.md)


```C++

#pragma once

#include <type_traits>

#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>

#include <astro/frames/framework/frame_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct OriginBase {
    template <IsOrigin Lhs, IsOrigin Rhs>
    [[nodiscard]] friend consteval bool operator==(Lhs, Rhs)
    {
        return std::is_same_v<Lhs, Rhs>;
    }
    template <IsOrigin Lhs, IsOrigin Rhs>
    [[nodiscard]] friend consteval bool equivalent(Lhs, Rhs)
    {
        return std::is_same_v<Lhs, Rhs>;
    }
};

} // namespace detail

template <mp_units::symbol_text, auto...>
struct Origin;

template <mp_units::symbol_text _name_>
struct Origin<_name_> : detail::OriginBase {
    static constexpr auto name = _name_; 
};

template <mp_units::symbol_text _name_, IsOrigin auto _parent_>
struct Origin<_name_, _parent_> : detail::OriginBase {
    static constexpr auto name   = _name_;   
    static constexpr auto parent = _parent_; 
};

struct DynamicOrigin : Origin<"dynamic"> {};

template <IsFrame Frame_T, IsOrigin Origin_T>
inline consteval auto has_origin(Frame_T, Origin_T)
{
    return std::is_same_v<decltype(Frame_T::origin), Origin_T>;
}

template <IsFrame T, IsFrame U>
consteval bool has_same_origin(T t, U u)
{
    return T::origin == U::origin;
}

} // namespace astro
} // namespace astrea
```


