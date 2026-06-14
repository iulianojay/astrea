

# File Frame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**Frame.hpp**](Frame_8hpp.md)

[Go to the documentation of this file](Frame_8hpp.md)


```C++

#pragma once

#include <type_traits>

#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>

#include <astro/frames/framework/Axis.hpp>
#include <astro/frames/framework/Origin.hpp>
#include <astro/frames/framework/frame_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct FrameBase {
    template <IsFrame Lhs, IsFrame Rhs>
    [[nodiscard]] friend consteval bool operator==(Lhs, Rhs)
    {
        return std::is_same_v<Lhs, Rhs>;
    }
};

} // namespace detail

template <mp_units::symbol_text, auto...>
struct Frame;

// /**
//  * @brief Frame with origin and axis only (no name, no parent).
//  */
// template <IsOrigin auto _origin_, IsAxis auto _axis_>
// struct Frame<_origin_, _axis_> : detail::FrameBase {
//     static constexpr auto origin = _origin_; //!< The central body associated with the frame.
//     static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
// };

template <mp_units::symbol_text _name_, IsOrigin auto _origin_, IsAxis auto _axis_>
struct Frame<_name_, _origin_, _axis_> : detail::FrameBase {
    static constexpr auto name   = _name_;   
    static constexpr auto origin = _origin_; 
    static constexpr auto axis   = _axis_;   
};

// /**
//  * @brief Frame with origin, axis, and parent (no name).
//  */
// template <IsOrigin auto _origin_, IsAxis auto _axis_, IsFrame auto _parent_>
// struct Frame<_origin_, _axis_, _parent_> : detail::FrameBase {
//     static constexpr auto origin = _origin_; //!< The central body associated with the frame.
//     static constexpr auto axis   = _axis_;   //!< The axis type of the frame.
//     static constexpr auto parent = _parent_; //!< The parent frame of this frame.
// };

template <mp_units::symbol_text _name_, IsOrigin auto _origin_, IsAxis auto _axis_, IsFrame auto _parent_>
struct Frame<_name_, _origin_, _axis_, _parent_> : detail::FrameBase {
    static constexpr auto name   = _name_;   
    static constexpr auto origin = _origin_; 
    static constexpr auto axis   = _axis_;   
    static constexpr auto parent = _parent_; 
};


template <IsFrame Lhs, IsFrame Rhs>
[[nodiscard]] consteval bool equivalent(Lhs t, Rhs u)
{
    return equivalent(t.origin, u.origin) && equivalent(t.axis, u.axis) && has_same_parent(t, u);
}

} // namespace astro
} // namespace astrea
```


