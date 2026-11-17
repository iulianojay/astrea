/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include "astro/systems/celestial_bodies/Earth/Earth.hpp"
#include "astro/systems/system_concepts.hpp"
#include "units/typedefs.hpp"
#include <gtest/gtest.h>

#include <units/units.hpp>

#include <astro/frames.hpp>
#include <astro/state/framework/AngularElementsInterface.hpp>

using namespace astrea;
using namespace astro;

using namespace mp_units;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

// ---------------------------------------------------------------------------
// Concrete CRTP test types
// ---------------------------------------------------------------------------

/**
 * @brief Concrete Geodetic-like type derived from AngularElements for testing.
 *
 * Provides a public element-wise constructor and an ArrayType constructor
 * so that arithmetic operator results (which return Derived_T) are constructible.
 */
template <IsCelestialBody auto _body_>
class TestGeodetic : public AngularElementsInterface<TestGeodetic<_body_>, Angle, Angle, Distance> {
    using BaseType = AngularElementsInterface<TestGeodetic<_body_>, Angle, Angle, Distance>;

  public:
    static constexpr auto body = _body_;
    using BaseType::BaseType;
    using BaseType::operator=;

    TestGeodetic() = default;
};

/**
 * @brief A second Geodetic-like type with the same element signature but a different
 *        CRTP tag — used to verify that same-element, same-frame types satisfy
 *        IsCompatibleAngularElements across distinct derived types.
 */
template <IsCelestialBody auto _body_>
class TestGeodetic2 : public AngularElementsInterface<TestGeodetic2<_body_>, Angle, Angle, Distance> {
    using BaseType = AngularElementsInterface<TestGeodetic2<_body_>, Angle, Angle, Distance>;

  public:
    static constexpr auto body = _body_;
    using BaseType::BaseType;
    using BaseType::operator=;

    TestGeodetic2() = default;
};

/**
 * @brief Uniform-element (all double) derived type for testing dot product.
 *
 * ElementMatrix::dot() requires IsUniform — mixed-type Geodetic elements do not
 * satisfy that constraint, so a separate scalar-element type is used here.
 */
template <IsCelestialBody auto _body_>
class TestUniform3 : public AngularElementsInterface<TestUniform3<_body_>, double, double, double> {
    using BaseType = AngularElementsInterface<TestUniform3<_body_>, double, double, double>;

  public:
    static constexpr auto body = _body_;
    using BaseType::BaseType;
    using BaseType::operator=;

    TestUniform3() = default;
};

// Convenient aliases
using EarthGeodetic  = TestGeodetic<planets::Earth>;
using EarthGeodetic2 = TestGeodetic2<planets::Earth>;
using EarthUniform3  = TestUniform3<planets::Earth>;

// ---------------------------------------------------------------------------
// Test fixture
// ---------------------------------------------------------------------------

class AngularElementsTest : public testing::Test {
  public:
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ---------------------------------------------------------------------------
// Construction
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, DefaultConstructor) { ASSERT_NO_THROW(EarthGeodetic()); }

TEST_F(AngularElementsTest, ElementConstructor)
{
    ASSERT_NO_THROW(EarthGeodetic(Angle(98.0 * deg), Angle(40.0 * deg), Distance{ 1.0 * km }));
}

TEST_F(AngularElementsTest, CopyConstructor)
{
    EarthGeodetic original(Angle(98.0 * deg), Angle(40.0 * deg), Distance{ 7000.0 * km });

    ASSERT_NO_THROW(EarthGeodetic copy(original));
    EarthGeodetic copy(original);

    ASSERT_EQ(copy.get<0>(), Angle(98.0 * deg));
    ASSERT_EQ(copy.get<1>(), Angle(40.0 * deg));
    ASSERT_EQ(copy.get<2>(), Distance{ 7000.0 * km });
}

TEST_F(AngularElementsTest, MoveConstructor)
{
    EarthGeodetic original(Angle(98.0 * deg), Angle(40.0 * deg), Distance{ 7000.0 * km });

    ASSERT_NO_THROW(EarthGeodetic moved(std::move(original)));
    EarthGeodetic moved(std::move(original));

    ASSERT_EQ(moved.get<0>(), Angle(98.0 * deg));
    ASSERT_EQ(moved.get<1>(), Angle(40.0 * deg));
    ASSERT_EQ(moved.get<2>(), Distance{ 7000.0 * km });
}

// ---------------------------------------------------------------------------
// Body and type metadata
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, BodyAccessor) { static_assert(equivalent(EarthGeodetic::body, planets::Earth)); }

TEST_F(AngularElementsTest, ArrayTypeSize)
{
    static_assert(EarthGeodetic::ArrayType::size == 3);
    static_assert(EarthGeodetic::ArrayType::n_row == 3);
    static_assert(EarthGeodetic::ArrayType::n_col == 1);
}

// ---------------------------------------------------------------------------
// Element access
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, ElementAccess)
{
    EarthGeodetic state(Angle(98.0 * deg), Angle(40.0 * deg), Distance{ 7000.0 * km });

    ASSERT_EQ(state.get<0>(), Angle(98.0 * deg));
    ASSERT_EQ(state.get<1>(), Angle(40.0 * deg));
    ASSERT_EQ(state.get<2>(), Distance{ 7000.0 * km });
}

// ---------------------------------------------------------------------------
// Compatible-type concept
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, CompatibleTypeConcept)
{
    // Same type is always compatible with itself.
    static_assert(IsCompatibleAngularElements<EarthGeodetic, EarthGeodetic>);

    // A distinct derived type with identical element types and the same frame is compatible.
    static_assert(IsCompatibleAngularElements<EarthGeodetic, EarthGeodetic2>);
}

// ---------------------------------------------------------------------------
// Arithmetic: addition and subtraction
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, AdditionSubtraction)
{
    EarthGeodetic state1(Angle(10.0 * deg), Angle(20.0 * deg), Distance{ 1.0 * km });
    EarthGeodetic state2(Angle(10.0 * deg), Angle(20.0 * deg), Distance{ 1.0 * km });

    auto sum = state1 + state2;
    ASSERT_EQ(sum.get<0>(), Angle(20.0 * deg));
    ASSERT_EQ(sum.get<1>(), Angle(40.0 * deg));
    ASSERT_EQ(sum.get<2>(), Distance{ 2.0 * km });

    auto diff = state1 - state2;
    ASSERT_EQ(diff.get<0>(), Angle(0.0 * deg));
    ASSERT_EQ(diff.get<1>(), Angle(0.0 * deg));
    ASSERT_EQ(diff.get<2>(), Distance{ 0.0 * km });

    state1 += state2;
    ASSERT_EQ(state1, sum);

    state1 -= state2;
    ASSERT_EQ(state1, state2);
}

TEST_F(AngularElementsTest, UnaryNegation)
{
    EarthGeodetic state(Angle(10.0 * deg), Angle(20.0 * deg), Distance{ 1.0 * km });

    auto negated = -state;
    ASSERT_EQ(negated.get<0>(), Angle(-10.0 * deg));
    ASSERT_EQ(negated.get<1>(), Angle(-20.0 * deg));
    ASSERT_EQ(negated.get<2>(), Distance{ -1.0 * km });
}

// ---------------------------------------------------------------------------
// Arithmetic: scalar multiplication and division
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, MultiplicationDivisionByArithmeticScalar)
{
    EarthGeodetic state(Angle(1.0 * deg), Angle(1.0 * deg), Distance{ 1.0 * km });

    auto scaled = state * 2.0;
    ASSERT_EQ(scaled.get<0>(), Angle(2.0 * deg));
    ASSERT_EQ(scaled.get<1>(), Angle(2.0 * deg));
    ASSERT_EQ(scaled.get<2>(), Distance{ 2.0 * km });
    // NOTE: scalar * state (free function) is not yet provided by AngularElements.

    auto halved = state / 2.0;
    ASSERT_EQ(halved.get<0>(), Angle(0.5 * deg));
    ASSERT_EQ(halved.get<1>(), Angle(0.5 * deg));
    ASSERT_EQ(halved.get<2>(), Distance{ 0.5 * km });

    state *= 2.0;
    ASSERT_EQ(state, scaled);

    state /= 2.0;
    ASSERT_EQ(state, EarthGeodetic(Angle(1.0 * deg), Angle(1.0 * deg), Distance{ 1.0 * km }));
}

TEST_F(AngularElementsTest, MultiplicationDivisionByUnitedScalar)
{
    EarthGeodetic state(Angle(1.0 * deg), Angle(1.0 * deg), Distance{ 1.0 * km });

    Distance scale = 2.0 * km;

    auto scaledByDist = state * scale;
    ASSERT_EQ(scaledByDist.get<0>(), Angle(1.0 * deg) * scale);
    ASSERT_EQ(scaledByDist.get<1>(), Angle(1.0 * deg) * scale);
    ASSERT_EQ(scaledByDist.get<2>(), Distance{ 1.0 * km } * scale);
    // NOTE: scalar * state (free function) is not yet provided by AngularElements.

    auto dividedByDist = state / scale;
    ASSERT_EQ(dividedByDist.get<0>(), Angle(1.0 * deg) / scale);
    ASSERT_EQ(dividedByDist.get<1>(), Angle(1.0 * deg) / scale);
    ASSERT_EQ(dividedByDist.get<2>(), Distance{ 1.0 * km } / scale);
}

// ---------------------------------------------------------------------------
// Equality
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, Equality)
{
    EarthGeodetic state1(Angle(98.0 * deg), Angle(40.0 * deg), Distance{ 7000.0 * km });
    EarthGeodetic state2(Angle(98.0 * deg), Angle(40.0 * deg), Distance{ 7000.0 * km });
    EarthGeodetic state3(Angle(0.0 * deg), Angle(0.0 * deg), Distance{ 7000.0 * km });

    ASSERT_EQ(state1, state2);
    ASSERT_NE(state1, state3);
}

// ---------------------------------------------------------------------------
// Dot product
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, DotProduct)
{
    // dot() requires IsUniform — use TestUniform3 (all-double elements).
    EarthUniform3 a(1.0, 2.0, 3.0);
    EarthUniform3 b(4.0, 5.0, 6.0);

    auto d = a.dot(b); // 1*4 + 2*5 + 3*6 = 32
    ASSERT_EQ(d, 32.0);
}

// ---------------------------------------------------------------------------
// Transpose
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, Transpose)
{
    EarthGeodetic col(Angle(3.0 * rad), Angle(4.0 * rad), Distance{ 1.0 * km });

    auto row = col.transpose();

    // Transposing a 6×1 column vector yields a 1×6 row vector.
    static_assert(decltype(row)::n_row == 1);
    static_assert(decltype(row)::n_col == 3);

    ASSERT_EQ(row.get<0>(), Angle(3.0 * rad));
    ASSERT_EQ(row.get<1>(), Angle(4.0 * rad));
    ASSERT_EQ(row.get<2>(), Distance{ 1.0 * km });
}

// ---------------------------------------------------------------------------
// Conversion helpers
// ---------------------------------------------------------------------------

TEST_F(AngularElementsTest, ForceToTuple)
{
    EarthGeodetic state(Angle(98.0 * deg), Angle(40.0 * deg), Distance{ 7000.0 * km });

    auto t = state.force_to_tuple();

    static_assert(std::is_same_v<decltype(t), EarthGeodetic::ArrayType::TupleType>);

    ASSERT_EQ(std::get<0>(t), Angle(98.0 * deg));
    ASSERT_EQ(std::get<1>(t), Angle(40.0 * deg));
    ASSERT_EQ(std::get<2>(t), Distance{ 7000.0 * km });
}

TEST_F(AngularElementsTest, ForceToElementMatrix)
{
    EarthGeodetic state(Angle(98.0 * deg), Angle(40.0 * deg), Distance{ 7000.0 * km });

    auto arr = state.force_to_element_array();

    static_assert(std::is_same_v<decltype(arr), EarthGeodetic::ArrayType>);

    ASSERT_EQ(arr.get<0>(), Angle(98.0 * deg));
    ASSERT_EQ(arr.get<1>(), Angle(40.0 * deg));
    ASSERT_EQ(arr.get<2>(), Distance{ 7000.0 * km });
}