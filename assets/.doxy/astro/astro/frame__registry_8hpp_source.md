

# File frame\_registry.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**frame\_registry.hpp**](frame__registry_8hpp.md)

[Go to the documentation of this file](frame__registry_8hpp.md)


```C++

#pragma once

#include <tuple>
#include <variant>

#include <astro/frames/definitions/frame_registry.fwd.hpp>
#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/frames/definitions/transformations.hpp>
#include <astro/frames/framework/frame_concepts.hpp>

namespace astrea {
namespace astro {

using AutomaticallyRegisteredFrames = std::tuple<std::decay_t<decltype(frames::primary)>>;

namespace detail {

// Concatenate two tuples into one tuple
template <typename TupleA, typename TupleB>
struct tuple_cat_types;

template <typename... As, typename... Bs>
struct tuple_cat_types<std::tuple<As...>, std::tuple<Bs...>> {
    using type = std::tuple<As..., Bs...>;
};

// Apply a class template T<> to every element of a tuple (type-parameter version)
template <template <typename> class T, typename Tuple>
struct apply_template;

template <template <typename> class T, typename... Frames>
struct apply_template<T, std::tuple<Frames...>> {
    using type = std::tuple<T<Frames>...>;
};

// Apply a non-type-parameter template T<val> to every frame type in a tuple,
// constructing values via T<Frame{}> (usable with IsFrame auto templates).
template <template <auto> class T, typename Tuple>
struct apply_nttp_template;

template <template <auto> class T, typename... Frames>
struct apply_nttp_template<T, std::tuple<Frames...>> {
    using type = std::tuple<T<Frames{}>...>;
};

// Concatenate an arbitrary number of std::tuple types into one.
template <typename... Tuples>
struct multi_tuple_cat;

template <>
struct multi_tuple_cat<> {
    using type = std::tuple<>;
};

template <typename Only>
struct multi_tuple_cat<Only> {
    using type = Only;
};

template <typename First, typename... Rest>
struct multi_tuple_cat<First, Rest...> {
    using type = typename tuple_cat_types<First, typename multi_tuple_cat<Rest...>::type>::type;
};

// Convert a tuple of types + extra types into a std::variant
template <typename Tuple, typename... Extra>
struct tuple_to_variant;

template <typename... Ts, typename... Extra>
struct tuple_to_variant<std::tuple<Ts...>, Extra...> {
    using type = std::variant<Ts..., Extra...>;
};

using AllRegisteredFrames = typename tuple_cat_types<AutomaticallyRegisteredFrames, typename ExtraRegisteredFrames<>::type>::type;

} // namespace detail


// Concept: true if frame is one of the types in AllRegisteredFrames
template <IsFrame auto frame>
concept IsRegisteredFrame = []<std::size_t... I>(std::index_sequence<I...>) {
    return (std::same_as<decltype(frame), std::tuple_element_t<I, detail::AllRegisteredFrames>> || ...);
}(std::make_index_sequence<std::tuple_size_v<detail::AllRegisteredFrames>>{});

// Enforce: all ExtraRegisteredFrames can be transformed into frames::primary
template <typename Tuple, typename Primary, std::size_t... I>
constexpr bool all_have_valid_transformation_impl(std::index_sequence<I...>)
{
    return (frames::HasValidFrameTransformation<std::tuple_element_t<I, Tuple>{}, Primary{}> && ...);
}

template <typename Tuple, typename Primary>
constexpr bool all_have_valid_transformation()
{
    return all_have_valid_transformation_impl<Tuple, Primary>(std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

static_assert(
    all_have_valid_transformation<ExtraRegisteredFrames<>::type, std::decay_t<decltype(frames::primary)>>(),
    "All ExtraRegisteredFrames must be transformable into frames::primary (HasValidFrameTransformation)."
);

} // namespace astro
} // namespace astrea
```


