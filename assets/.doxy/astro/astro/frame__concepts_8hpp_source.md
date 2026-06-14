

# File frame\_concepts.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**frame\_concepts.hpp**](frame__concepts_8hpp.md)

[Go to the documentation of this file](frame__concepts_8hpp.md)


```C++

#pragma once

#include <concepts>

namespace astrea {
namespace astro {


namespace detail {

// Base classes for each frame component type, used to identify them in concepts. These are not intended to be used directly by users.
struct FrameBase;
struct OriginBase;
struct AxisBase;
struct CoordinateLineBase;
struct BodyFixedFrameBase;
struct SynodicFrameBase;

template <typename T>
concept SymbolicConstant = (!std::is_const_v<T>) && (!std::is_reference_v<T>) && std::is_empty_v<T> &&
                           std::is_trivially_default_constructible_v<T> && std::is_trivially_copy_constructible_v<T> &&
                           std::is_trivially_move_constructible_v<T> && std::is_trivially_destructible_v<T>;

} // namespace detail

template <typename T>
concept IsFrame = std::derived_from<T, detail::FrameBase> && detail::SymbolicConstant<T>;

template <typename T>
concept IsOrigin = std::derived_from<T, detail::OriginBase> && detail::SymbolicConstant<T>;

template <typename T>
concept IsAxis = std::derived_from<T, detail::AxisBase> && detail::SymbolicConstant<T>;

template <typename T>
concept IsInertialFrame = true; // IsFrame<T> && (T::axis == axes::icrf || T::axis == axes::j2000); // TODO: Generalize this idea

template <typename T>
concept IsBodyFixedFrame = std::derived_from<T, detail::BodyFixedFrameBase> && detail::SymbolicConstant<T>;

template <typename T>
concept IsSynodicFrame = std::derived_from<T, detail::SynodicFrameBase> && detail::SymbolicConstant<T>;

template <typename T>
concept IsStaticFrame = (IsInertialFrame<T> || IsBodyFixedFrame<T>);

template <typename T>
concept IsDynamicFrame = !IsStaticFrame<T>;

template <typename T>
concept IsDerivedOrigin = IsOrigin<T> && requires { T::parent; };

template <typename T>
concept IsRootOrigin = IsOrigin<T> && !IsDerivedOrigin<T>;

template <typename T>
concept IsDerivedAxis = IsAxis<T> && requires { T::parent; };

template <typename T>
concept IsRootAxis = IsAxis<T> && !IsDerivedAxis<T>;

template <typename>
inline constexpr bool always_false = false;

template <typename T>
concept IsDerivedFrame = IsFrame<T> && (requires { T::parent; } || IsDerivedOrigin<T> || IsDerivedAxis<T>);

template <typename T>
concept IsRootFrame = IsFrame<T> && !IsDerivedFrame<T>;

template <typename T>
concept HasSpatialOffset = requires { T::origin.offset; } || requires { T::offset; };

template <typename T>
concept HasAngularOffset = requires { T::axis.misalignment; } || requires { T::misalignment; };

template <typename T>
concept IsFixedOffsetFrame = IsDerivedFrame<T> && (HasSpatialOffset<T> || HasAngularOffset<T>);

template <IsFrame T, IsFrame U>
consteval bool has_same_parent(T t, U u)
{
    return false;
}

template <IsFrame T, IsFrame U>
    requires(IsDerivedFrame<T> && IsDerivedFrame<U>)
consteval bool has_same_parent(T t, U u)
{
    return std::is_same_v<decltype(T::parent), decltype(U::parent)>;
}

template <IsFrame T, IsFrame U>
    requires(IsRootFrame<T> && IsRootFrame<U>)
consteval bool has_same_parent(T t, U u)
{
    return true;
}

} // namespace astro
} // namespace astrea
```


