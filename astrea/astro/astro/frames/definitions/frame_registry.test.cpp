/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <tuple>
#include <type_traits>
#include <variant>

#include <astro/frames/definitions/frame_registry.hpp>

using namespace astrea::astro;

template <typename A, typename B>
inline constexpr bool same_type_v = std::is_same_v<A, B>;

// A simple wrapper template to use in tests
template <typename T>
struct Wrapped {};

namespace {

/// Represents a frame a user might define in their own mission code.
struct UserMissionFrame {};

} // namespace

class FrameRegistryTest : public testing::Test {
  public:
    FrameRegistryTest() {}

    void SetUp() override {}
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(FrameRegistryTest, AutomaticallyRegisteredFramesIsTuple)
{
    // Must be a std::tuple (instantiation of the template)
    constexpr bool is_tuple =
        same_type_v<AutomaticallyRegisteredFrames, std::tuple<std::decay_t<decltype(frames::earth::icrf)>>>;
    static_assert(is_tuple, "AutomaticallyRegisteredFrames must be std::tuple<std::decay_t<decltype(frames::earth::icrf)>>");
    SUCCEED();
}

TEST_F(FrameRegistryTest, AutomaticallyRegisteredFramesContainsEarthICRF)
{
    constexpr bool has_earth_icrf =
        same_type_v<std::tuple_element_t<0, AutomaticallyRegisteredFrames>, std::decay_t<decltype(frames::earth::icrf)>>;
    static_assert(has_earth_icrf, "First element of AutomaticallyRegisteredFrames must be frames::earth::icrf");
    SUCCEED();
}

TEST_F(FrameRegistryTest, AutomaticallyRegisteredFramesSize)
{
    constexpr std::size_t size = std::tuple_size_v<AutomaticallyRegisteredFrames>;
    static_assert(size == 1, "AutomaticallyRegisteredFrames must contain exactly 1 frame");
    EXPECT_EQ(size, 1u);
}

TEST_F(FrameRegistryTest, ExtraRegisteredFramesDefaultIsEmptyTuple)
{
    constexpr bool is_empty = same_type_v<ExtraRegisteredFrames<>::type, std::tuple<>>;
    static_assert(is_empty, "Default ExtraRegisteredFrames<>::type must be std::tuple<>");
    SUCCEED();
}

TEST_F(FrameRegistryTest, ExtraRegisteredFramesDefaultSize)
{
    constexpr std::size_t size = std::tuple_size_v<ExtraRegisteredFrames<>::type>;
    static_assert(size == 0, "Default ExtraRegisteredFrames<>::type must be empty");
    EXPECT_EQ(size, 0u);
}

TEST_F(FrameRegistryTest, TupleCatTypesTwoNonEmptyTuples)
{
    using A      = std::tuple<int, float>;
    using B      = std::tuple<double, char>;
    using Result = astrea::astro::detail::tuple_cat_types<A, B>::type;
    using Expect = std::tuple<int, float, double, char>;
    static_assert(same_type_v<Result, Expect>, "tuple_cat_types should concatenate both tuples");
    SUCCEED();
}

TEST_F(FrameRegistryTest, TupleCatTypesFirstEmpty)
{
    using A      = std::tuple<>;
    using B      = std::tuple<int, float>;
    using Result = astrea::astro::detail::tuple_cat_types<A, B>::type;
    using Expect = std::tuple<int, float>;
    static_assert(same_type_v<Result, Expect>, "tuple_cat_types with empty first tuple should return second tuple");
    SUCCEED();
}

TEST_F(FrameRegistryTest, TupleCatTypesSecondEmpty)
{
    using A      = std::tuple<int, float>;
    using B      = std::tuple<>;
    using Result = astrea::astro::detail::tuple_cat_types<A, B>::type;
    using Expect = std::tuple<int, float>;
    static_assert(same_type_v<Result, Expect>, "tuple_cat_types with empty second tuple should return first tuple");
    SUCCEED();
}

TEST_F(FrameRegistryTest, TupleCatTypesBothEmpty)
{
    using Result = astrea::astro::detail::tuple_cat_types<std::tuple<>, std::tuple<>>::type;
    static_assert(same_type_v<Result, std::tuple<>>, "tuple_cat_types of two empty tuples should be empty");
    SUCCEED();
}

TEST_F(FrameRegistryTest, ApplyTemplateTransformsEachElement)
{
    using Input  = std::tuple<int, float, double>;
    using Result = astrea::astro::detail::apply_template<Wrapped, Input>::type;
    using Expect = std::tuple<Wrapped<int>, Wrapped<float>, Wrapped<double>>;
    static_assert(same_type_v<Result, Expect>, "apply_template should wrap each element");
    SUCCEED();
}

TEST_F(FrameRegistryTest, ApplyTemplateEmptyTuple)
{
    using Result = astrea::astro::detail::apply_template<Wrapped, std::tuple<>>::type;
    static_assert(same_type_v<Result, std::tuple<>>, "apply_template on empty tuple should be empty");
    SUCCEED();
}

TEST_F(FrameRegistryTest, ApplyTemplateSingleElement)
{
    using Result = astrea::astro::detail::apply_template<Wrapped, std::tuple<int>>::type;
    using Expect = std::tuple<Wrapped<int>>;
    static_assert(same_type_v<Result, Expect>, "apply_template on single-element tuple");
    SUCCEED();
}

TEST_F(FrameRegistryTest, TupleToVariantBasicConversion)
{
    using Input  = std::tuple<int, float, double>;
    using Result = astrea::astro::detail::tuple_to_variant<Input>::type;
    using Expect = std::variant<int, float, double>;
    static_assert(same_type_v<Result, Expect>, "tuple_to_variant should produce a matching variant");
    SUCCEED();
}

TEST_F(FrameRegistryTest, TupleToVariantWithExtraTypes)
{
    using Input  = std::tuple<int, float>;
    using Result = astrea::astro::detail::tuple_to_variant<Input, double, char>::type;
    using Expect = std::variant<int, float, double, char>;
    static_assert(same_type_v<Result, Expect>, "tuple_to_variant with extras should append them");
    SUCCEED();
}

TEST_F(FrameRegistryTest, TupleToVariantSingleElement)
{
    using Result = astrea::astro::detail::tuple_to_variant<std::tuple<int>>::type;
    using Expect = std::variant<int>;
    static_assert(same_type_v<Result, Expect>, "tuple_to_variant of single-element tuple");
    SUCCEED();
}

TEST_F(FrameRegistryTest, AllRegisteredFramesDefaultEqualsAutoFrames)
{
    // With no user specialization of ExtraRegisteredFrames, AllRegisteredFrames
    // must equal AutomaticallyRegisteredFrames.
    constexpr bool equal = same_type_v<astrea::astro::detail::AllRegisteredFrames, AutomaticallyRegisteredFrames>;
    static_assert(equal, "AllRegisteredFrames with no extra frames must equal AutomaticallyRegisteredFrames");
    SUCCEED();
}

TEST_F(FrameRegistryTest, AllRegisteredFramesContainsEarthICRF)
{
    constexpr bool has_earth_icrf =
        same_type_v<std::tuple_element_t<0, astrea::astro::detail::AllRegisteredFrames>, std::decay_t<decltype(frames::earth::icrf)>>;
    static_assert(has_earth_icrf, "AllRegisteredFrames[0] must be frames::earth::icrf");
    SUCCEED();
}

TEST_F(FrameRegistryTest, AllRegisteredFramesSizeEqualsAutoSize)
{
    constexpr std::size_t all_size  = std::tuple_size_v<astrea::astro::detail::AllRegisteredFrames>;
    constexpr std::size_t auto_size = std::tuple_size_v<AutomaticallyRegisteredFrames>;
    static_assert(all_size == auto_size, "AllRegisteredFrames size must match AutomaticallyRegisteredFrames when no extras are registered");
    EXPECT_EQ(all_size, auto_size);
}

// We cannot specialize ExtraRegisteredFrames<> here (the primary template's
// default is already instantiated), but we can exercise tuple_cat_types directly
// to verify that the extension mechanism produces the expected combined tuple.

TEST_F(FrameRegistryTest, ManualExtensionCombinesAutoAndExtraFrames)
{
    // Simulate what AllRegisteredFrames would be if the user had registered
    // frames::moon::icrf and frames::mars::icrf as extra frames.
    using SimulatedExtra = std::tuple<std::decay_t<decltype(frames::moon::icrf)>, std::decay_t<decltype(frames::mars::icrf)>>;
    using SimulatedAll = astrea::astro::detail::tuple_cat_types<AutomaticallyRegisteredFrames, SimulatedExtra>::type;
    using Expected =
        std::tuple<std::decay_t<decltype(frames::earth::icrf)>, std::decay_t<decltype(frames::moon::icrf)>, std::decay_t<decltype(frames::mars::icrf)>>;

    static_assert(same_type_v<SimulatedAll, Expected>, "Simulated extension must produce earth::icrf, moon::icrf, mars::icrf in order");
    constexpr std::size_t size = std::tuple_size_v<SimulatedAll>;
    static_assert(size == 3, "Simulated combined registry must have 3 frames");
    EXPECT_EQ(size, 3u);
    SUCCEED();
}

// ---------------------------------------------------------------------------
// Simulated external user registration
//
// Including frame_registry.hpp eagerly evaluates the AllRegisteredFrames alias,
// which instantiates ExtraRegisteredFrames<void> from the primary template.
// Adding an explicit specialization afterward (in the same TU) would violate
// [temp.expl.spec] — the specialization must precede the first use.
//
// These tests instead exercise the identical mechanism (tuple_cat_types) that
// AllRegisteredFrames uses, with a user-defined frame type substituted in place
// of ExtraRegisteredFrames<>::type.  This is precisely what happens at compile
// time when a real user specializes ExtraRegisteredFrames<> in their own TU.
// ---------------------------------------------------------------------------

TEST_F(FrameRegistryTest, SingleFrameAppearsAfterBuiltins)
{
    // Mirrors:
    //   template <> struct ExtraRegisteredFrames<> {
    //       using type = std::tuple<UserMissionFrame>;
    //   };
    using UserExtra     = std::tuple<UserMissionFrame>;
    using UserAllFrames = astrea::astro::detail::tuple_cat_types<AutomaticallyRegisteredFrames, UserExtra>::type;
    using Expected      = std::tuple<std::decay_t<decltype(frames::earth::icrf)>, UserMissionFrame>;

    static_assert(same_type_v<UserAllFrames, Expected>, "User frame must be appended after built-in frames");
    EXPECT_EQ((std::tuple_size_v<UserAllFrames>), 2u);
    SUCCEED();
}

TEST_F(FrameRegistryTest, BuiltinFramesNotDisplacedByUserRegistration)
{
    using UserExtra     = std::tuple<UserMissionFrame>;
    using UserAllFrames = astrea::astro::detail::tuple_cat_types<AutomaticallyRegisteredFrames, UserExtra>::type;

    static_assert(same_type_v<std::tuple_element_t<0, UserAllFrames>, std::decay_t<decltype(frames::earth::icrf)>>, "Built-in earth::icrf must remain at index 0 after user registration");
    static_assert(same_type_v<std::tuple_element_t<1, UserAllFrames>, UserMissionFrame>, "User frame must appear at index 1");
    SUCCEED();
}

TEST_F(FrameRegistryTest, MultipleUserFramesRegisteredInOrder)
{
    // Mirrors registering two extra frames:
    //   using type = std::tuple<std::decay_t<decltype(frames::moon::icrf)>, UserMissionFrame>;
    using UserExtra     = std::tuple<std::decay_t<decltype(frames::moon::icrf)>, UserMissionFrame>;
    using UserAllFrames = astrea::astro::detail::tuple_cat_types<AutomaticallyRegisteredFrames, UserExtra>::type;

    constexpr std::size_t size = std::tuple_size_v<UserAllFrames>;
    static_assert(size == 3, "Three frames expected after registering two user frames");
    static_assert(same_type_v<std::tuple_element_t<0, UserAllFrames>, std::decay_t<decltype(frames::earth::icrf)>>);
    static_assert(same_type_v<std::tuple_element_t<1, UserAllFrames>, std::decay_t<decltype(frames::moon::icrf)>>);
    static_assert(same_type_v<std::tuple_element_t<2, UserAllFrames>, UserMissionFrame>);
    EXPECT_EQ(size, 3u);
    SUCCEED();
}

TEST_F(FrameRegistryTest, ExtraRegisteredFramesDefaultRemainsEmptyWithoutSpecialization)
{
    // Confirm the default specialization is still empty (no global side effects
    // from the simulation tests above).
    constexpr bool empty = same_type_v<ExtraRegisteredFrames<>::type, std::tuple<>>;
    static_assert(empty, "ExtraRegisteredFrames<>::type must still be empty tuple in this TU");
    SUCCEED();
}
