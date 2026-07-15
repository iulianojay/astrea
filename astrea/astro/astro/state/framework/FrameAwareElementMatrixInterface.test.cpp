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

#include <gtest/gtest.h>

#include <units/units.hpp>

#include <astro/frames.hpp>
#include <astro/state/framework/FrameAwareElementMatrixInterface.hpp>

using namespace astrea;
using namespace astro;

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

// ---------------------------------------------------------------------------
// Concrete CRTP test types
// ---------------------------------------------------------------------------

/**
 * @brief Concrete Keplerian-like type derived from OrbitalElements for testing.
 *
 * Provides a public element-wise constructor and an ArrayType constructor
 * so that arithmetic operator results (which return Derived_T) are constructible.
 */
template <IsFrame auto _frame_>
class TestKeplerian : public FaemInterface<TestKeplerian<_frame_>, _frame_, Distance, Unitless, Angle, Angle, Angle, Angle> {
    using Base = FaemInterface<TestKeplerian<_frame_>, _frame_, Distance, Unitless, Angle, Angle, Angle, Angle>;

  public:
    using Base::Base;
    using typename Base::ArrayType;

    TestKeplerian() = default;
};

/**
 * @brief A second Keplerian-like type with the same element signature but a different
 *        CRTP tag — used to verify that same-element, same-frame types satisfy
 *        IsCompatibleOrbitalElements across distinct derived types.
 */
template <IsFrame auto _frame_>
class TestKeplerian2 : public FaemInterface<TestKeplerian2<_frame_>, _frame_, Distance, Unitless, Angle, Angle, Angle, Angle> {
    using Base = FaemInterface<TestKeplerian2<_frame_>, _frame_, Distance, Unitless, Angle, Angle, Angle, Angle>;

  public:
    using Base::Base;
    using typename Base::ArrayType;

    TestKeplerian2() = default;
};

/**
 * @brief Uniform-element (all double) derived type for testing dot product.
 *
 * ElementMatrix::dot() requires IsUniform — mixed-type Keplerian elements do not
 * satisfy that constraint, so a separate scalar-element type is used here.
 */
template <IsFrame auto _frame_>
class TestUniform3 : public FaemInterface<TestUniform3<_frame_>, _frame_, double, double, double> {
    using Base = FaemInterface<TestUniform3<_frame_>, _frame_, double, double, double>;

  public:
    using Base::Base;
    using typename Base::ArrayType;

    TestUniform3() = default;
};

// Convenient aliases
using EarthKeplerian  = TestKeplerian<frames::earth::icrf>;
using EarthKeplerian2 = TestKeplerian2<frames::earth::icrf>;
using J2000Keplerian  = TestKeplerian<frames::earth::j2000>;
using EarthUniform3   = TestUniform3<frames::earth::icrf>;

// ---------------------------------------------------------------------------
// Test fixture
// ---------------------------------------------------------------------------

class OrbitalElementsTest : public testing::Test {
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

TEST_F(OrbitalElementsTest, DefaultConstructor) { ASSERT_NO_THROW(EarthKeplerian()); }

TEST_F(OrbitalElementsTest, ElementConstructor)
{
    ASSERT_NO_THROW(EarthKeplerian(
        Distance{ 1.0 * km }, Unitless{ 0.01 * one }, Angle{ 98.0 * deg }, Angle{ 40.0 * deg }, Angle{ 80.0 * deg }, Angle{ 0.0 * deg }
    ));
}

TEST_F(OrbitalElementsTest, CopyConstructor)
{
    EarthKeplerian original(
        Distance{ 7000.0 * km }, Unitless{ 0.01 * one }, Angle{ 98.0 * deg }, Angle{ 40.0 * deg }, Angle{ 80.0 * deg }, Angle{ 0.0 * deg }
    );

    ASSERT_NO_THROW(EarthKeplerian copy(original));
    EarthKeplerian copy(original);

    ASSERT_EQ(copy.get<0>(), Distance{ 7000.0 * km });
    ASSERT_EQ(copy.get<1>(), Unitless{ 0.01 * one });
    ASSERT_EQ(copy.get<2>(), Angle{ 98.0 * deg });
    ASSERT_EQ(copy.get<3>(), Angle{ 40.0 * deg });
    ASSERT_EQ(copy.get<4>(), Angle{ 80.0 * deg });
    ASSERT_EQ(copy.get<5>(), Angle{ 0.0 * deg });
}

TEST_F(OrbitalElementsTest, MoveConstructor)
{
    EarthKeplerian original(
        Distance{ 7000.0 * km }, Unitless{ 0.01 * one }, Angle{ 98.0 * deg }, Angle{ 40.0 * deg }, Angle{ 80.0 * deg }, Angle{ 0.0 * deg }
    );

    ASSERT_NO_THROW(EarthKeplerian moved(std::move(original)));
    EarthKeplerian moved(std::move(original));

    ASSERT_EQ(moved.get<0>(), Distance{ 7000.0 * km });
    ASSERT_EQ(moved.get<1>(), Unitless{ 0.01 * one });
    ASSERT_EQ(moved.get<2>(), Angle{ 98.0 * deg });
    ASSERT_EQ(moved.get<3>(), Angle{ 40.0 * deg });
    ASSERT_EQ(moved.get<4>(), Angle{ 80.0 * deg });
    ASSERT_EQ(moved.get<5>(), Angle{ 0.0 * deg });
}

// ---------------------------------------------------------------------------
// Frame and type metadata
// ---------------------------------------------------------------------------

TEST_F(OrbitalElementsTest, FrameAccessor)
{
    static_assert(equivalent(EarthKeplerian::frame, frames::earth::icrf));
    static_assert(equivalent(J2000Keplerian::frame, frames::earth::j2000));
    static_assert(!equivalent(EarthKeplerian::frame, J2000Keplerian::frame));
}

TEST_F(OrbitalElementsTest, ArrayTypeSize)
{
    static_assert(EarthKeplerian::ArrayType::size == 6);
    static_assert(EarthKeplerian::ArrayType::n_row == 6);
    static_assert(EarthKeplerian::ArrayType::n_col == 1);
}

// ---------------------------------------------------------------------------
// Element access
// ---------------------------------------------------------------------------

TEST_F(OrbitalElementsTest, ElementAccess)
{
    EarthKeplerian state(
        Distance{ 7000.0 * km }, Unitless{ 0.01 * one }, Angle{ 98.0 * deg }, Angle{ 40.0 * deg }, Angle{ 80.0 * deg }, Angle{ 0.0 * deg }
    );

    ASSERT_EQ(state.get<0>(), Distance{ 7000.0 * km });
    ASSERT_EQ(state.get<1>(), Unitless{ 0.01 * one });
    ASSERT_EQ(state.get<2>(), Angle{ 98.0 * deg });
    ASSERT_EQ(state.get<3>(), Angle{ 40.0 * deg });
    ASSERT_EQ(state.get<4>(), Angle{ 80.0 * deg });
    ASSERT_EQ(state.get<5>(), Angle{ 0.0 * deg });
}

// ---------------------------------------------------------------------------
// Compatible-type concept
// ---------------------------------------------------------------------------

TEST_F(OrbitalElementsTest, CompatibleTypeConcept)
{
    // Same type is always compatible with itself.
    static_assert(IsCompatibleOrbitalElements<EarthKeplerian, EarthKeplerian>);

    // A distinct derived type with identical element types and the same frame is compatible.
    static_assert(IsCompatibleOrbitalElements<EarthKeplerian, EarthKeplerian2>);

    // Different frames → incompatible even if element types match.
    static_assert(!IsCompatibleOrbitalElements<EarthKeplerian, J2000Keplerian>);
}

// ---------------------------------------------------------------------------
// Arithmetic: addition and subtraction
// ---------------------------------------------------------------------------

TEST_F(OrbitalElementsTest, AdditionSubtraction)
{
    EarthKeplerian state1(
        Distance{ 1.0 * km }, Unitless{ 0.1 * one }, Angle{ 10.0 * deg }, Angle{ 20.0 * deg }, Angle{ 30.0 * deg }, Angle{ 40.0 * deg }
    );
    EarthKeplerian state2(
        Distance{ 1.0 * km }, Unitless{ 0.1 * one }, Angle{ 10.0 * deg }, Angle{ 20.0 * deg }, Angle{ 30.0 * deg }, Angle{ 40.0 * deg }
    );

    auto sum = state1 + state2;
    ASSERT_EQ(sum.get<0>(), Distance{ 2.0 * km });
    ASSERT_EQ(sum.get<1>(), Unitless{ 0.2 * one });
    ASSERT_EQ(sum.get<2>(), Angle{ 20.0 * deg });
    ASSERT_EQ(sum.get<3>(), Angle{ 40.0 * deg });
    ASSERT_EQ(sum.get<4>(), Angle{ 60.0 * deg });
    ASSERT_EQ(sum.get<5>(), Angle{ 80.0 * deg });

    auto diff = state1 - state2;
    ASSERT_EQ(diff.get<0>(), Distance{ 0.0 * km });
    ASSERT_EQ(diff.get<1>(), Unitless{ 0.0 * one });
    ASSERT_EQ(diff.get<2>(), Angle{ 0.0 * deg });
    ASSERT_EQ(diff.get<3>(), Angle{ 0.0 * deg });
    ASSERT_EQ(diff.get<4>(), Angle{ 0.0 * deg });
    ASSERT_EQ(diff.get<5>(), Angle{ 0.0 * deg });

    state1 += state2;
    ASSERT_EQ(state1, sum);

    state1 -= state2;
    ASSERT_EQ(state1, state2);
}

TEST_F(OrbitalElementsTest, UnaryNegation)
{
    EarthKeplerian state(
        Distance{ 1.0 * km }, Unitless{ 0.1 * one }, Angle{ 10.0 * deg }, Angle{ 20.0 * deg }, Angle{ 30.0 * deg }, Angle{ 40.0 * deg }
    );

    auto negated = -state;
    ASSERT_EQ(negated.get<0>(), Distance{ -1.0 * km });
    ASSERT_EQ(negated.get<1>(), Unitless{ -0.1 * one });
    ASSERT_EQ(negated.get<2>(), Angle{ -10.0 * deg });
    ASSERT_EQ(negated.get<3>(), Angle{ -20.0 * deg });
    ASSERT_EQ(negated.get<4>(), Angle{ -30.0 * deg });
    ASSERT_EQ(negated.get<5>(), Angle{ -40.0 * deg });
}

// ---------------------------------------------------------------------------
// Arithmetic: scalar multiplication and division
// ---------------------------------------------------------------------------

TEST_F(OrbitalElementsTest, MultiplicationDivisionByArithmeticScalar)
{
    EarthKeplerian state(Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg });

    auto scaled = state * 2.0;
    ASSERT_EQ(scaled.get<0>(), Distance{ 2.0 * km });
    ASSERT_EQ(scaled.get<1>(), Unitless{ 2.0 * one });
    ASSERT_EQ(scaled.get<2>(), Angle{ 2.0 * deg });
    ASSERT_EQ(scaled.get<3>(), Angle{ 2.0 * deg });
    ASSERT_EQ(scaled.get<4>(), Angle{ 2.0 * deg });
    ASSERT_EQ(scaled.get<5>(), Angle{ 2.0 * deg });
    // NOTE: scalar * state (free function) is not yet provided by OrbitalElements.

    auto halved = state / 2.0;
    ASSERT_EQ(halved.get<0>(), Distance{ 0.5 * km });
    ASSERT_EQ(halved.get<1>(), Unitless{ 0.5 * one });
    ASSERT_EQ(halved.get<2>(), Angle{ 0.5 * deg });
    ASSERT_EQ(halved.get<3>(), Angle{ 0.5 * deg });
    ASSERT_EQ(halved.get<4>(), Angle{ 0.5 * deg });
    ASSERT_EQ(halved.get<5>(), Angle{ 0.5 * deg });

    state *= 2.0;
    ASSERT_EQ(state, scaled);

    state /= 2.0;
    ASSERT_EQ(state, EarthKeplerian(Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }));
}

TEST_F(OrbitalElementsTest, MultiplicationDivisionByUnitedScalar)
{
    EarthKeplerian state(Distance{ 1.0 * km }, Unitless{ 1.0 * one }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg }, Angle{ 1.0 * deg });

    Distance scale = 2.0 * km;

    auto scaledByDist = state * scale;
    ASSERT_EQ(scaledByDist.get<0>(), Distance{ 1.0 * km } * scale);
    ASSERT_EQ(scaledByDist.get<1>(), Unitless{ 1.0 * one } * scale);
    ASSERT_EQ(scaledByDist.get<2>(), Angle{ 1.0 * deg } * scale);
    ASSERT_EQ(scaledByDist.get<3>(), Angle{ 1.0 * deg } * scale);
    ASSERT_EQ(scaledByDist.get<4>(), Angle{ 1.0 * deg } * scale);
    ASSERT_EQ(scaledByDist.get<5>(), Angle{ 1.0 * deg } * scale);
    // NOTE: scalar * state (free function) is not yet provided by OrbitalElements.

    auto dividedByDist = state / scale;
    ASSERT_EQ(dividedByDist.get<0>(), Distance{ 1.0 * km } / scale);
    ASSERT_EQ(dividedByDist.get<1>(), Unitless{ 1.0 * one } / scale);
    ASSERT_EQ(dividedByDist.get<2>(), Angle{ 1.0 * deg } / scale);
    ASSERT_EQ(dividedByDist.get<3>(), Angle{ 1.0 * deg } / scale);
    ASSERT_EQ(dividedByDist.get<4>(), Angle{ 1.0 * deg } / scale);
    ASSERT_EQ(dividedByDist.get<5>(), Angle{ 1.0 * deg } / scale);
}

// ---------------------------------------------------------------------------
// Equality
// ---------------------------------------------------------------------------

TEST_F(OrbitalElementsTest, Equality)
{
    EarthKeplerian state1(
        Distance{ 7000.0 * km }, Unitless{ 0.01 * one }, Angle{ 98.0 * deg }, Angle{ 40.0 * deg }, Angle{ 80.0 * deg }, Angle{ 0.0 * deg }
    );
    EarthKeplerian state2(
        Distance{ 7000.0 * km }, Unitless{ 0.01 * one }, Angle{ 98.0 * deg }, Angle{ 40.0 * deg }, Angle{ 80.0 * deg }, Angle{ 0.0 * deg }
    );
    EarthKeplerian state3(
        Distance{ 6371.0 * km }, Unitless{ 0.0 * one }, Angle{ 0.0 * deg }, Angle{ 0.0 * deg }, Angle{ 0.0 * deg }, Angle{ 0.0 * deg }
    );

    ASSERT_EQ(state1, state2);
    ASSERT_NE(state1, state3);
}

// ---------------------------------------------------------------------------
// Dot product
// ---------------------------------------------------------------------------

TEST_F(OrbitalElementsTest, DotProduct)
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

TEST_F(OrbitalElementsTest, Transpose)
{
    EarthKeplerian col(Distance{ 1.0 * km }, Unitless{ 2.0 * one }, Angle{ 3.0 * rad }, Angle{ 4.0 * rad }, Angle{ 5.0 * rad }, Angle{ 6.0 * rad });

    auto row = col.transpose();

    // Transposing a 6×1 column vector yields a 1×6 row vector.
    static_assert(decltype(row)::n_row == 1);
    static_assert(decltype(row)::n_col == 6);

    ASSERT_EQ(row.get<0>(), Distance{ 1.0 * km });
    ASSERT_EQ(row.get<1>(), Unitless{ 2.0 * one });
    ASSERT_EQ(row.get<2>(), Angle{ 3.0 * rad });
    ASSERT_EQ(row.get<3>(), Angle{ 4.0 * rad });
    ASSERT_EQ(row.get<4>(), Angle{ 5.0 * rad });
    ASSERT_EQ(row.get<5>(), Angle{ 6.0 * rad });
}

// ---------------------------------------------------------------------------
// Conversion helpers
// ---------------------------------------------------------------------------

TEST_F(OrbitalElementsTest, ForceToTuple)
{
    EarthKeplerian state(
        Distance{ 7000.0 * km }, Unitless{ 0.01 * one }, Angle{ 98.0 * deg }, Angle{ 40.0 * deg }, Angle{ 80.0 * deg }, Angle{ 0.0 * deg }
    );

    auto t = state.force_to_tuple();

    static_assert(std::is_same_v<decltype(t), EarthKeplerian::ArrayType::tuple_type>);

    ASSERT_EQ(std::get<0>(t), Distance{ 7000.0 * km });
    ASSERT_EQ(std::get<1>(t), Unitless{ 0.01 * one });
    ASSERT_EQ(std::get<2>(t), Angle{ 98.0 * deg });
    ASSERT_EQ(std::get<3>(t), Angle{ 40.0 * deg });
    ASSERT_EQ(std::get<4>(t), Angle{ 80.0 * deg });
    ASSERT_EQ(std::get<5>(t), Angle{ 0.0 * deg });
}

TEST_F(OrbitalElementsTest, ForceToElementMatrix)
{
    EarthKeplerian state(
        Distance{ 7000.0 * km }, Unitless{ 0.01 * one }, Angle{ 98.0 * deg }, Angle{ 40.0 * deg }, Angle{ 80.0 * deg }, Angle{ 0.0 * deg }
    );

    auto arr = state.force_to_element_array();

    static_assert(std::is_same_v<decltype(arr), EarthKeplerian::ArrayType>);

    ASSERT_EQ(arr.get<0>(), Distance{ 7000.0 * km });
    ASSERT_EQ(arr.get<1>(), Unitless{ 0.01 * one });
    ASSERT_EQ(arr.get<2>(), Angle{ 98.0 * deg });
    ASSERT_EQ(arr.get<3>(), Angle{ 40.0 * deg });
    ASSERT_EQ(arr.get<4>(), Angle{ 80.0 * deg });
    ASSERT_EQ(arr.get<5>(), Angle{ 0.0 * deg });
}