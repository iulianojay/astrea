#pragma once

#include <gtest/gtest.h>

#include <math/test_util.hpp>

#include <astro/astro.hpp>

namespace astrea {

namespace astro {

void ASSERT_EQ_ORB_ELEM(
    const OrbitalElements& first,
    const OrbitalElements& second,
    const bool& ignoreFastVariable,
    const Unitless& relTol              = 0.0 * mp_units::one,
    const std::vector<Unitless>& absTol = { 0.0 * mp_units::one }
) noexcept
{
    if (first.index() != second.index()) { FAIL() << "Orbital element sets do not match"; }

    auto firstUnitless  = first.to_vector();
    auto secondUnitless = second.to_vector();
    const int maxIdx    = ignoreFastVariable ? 5 : 6;
    for (int ii = 0; ii < maxIdx; ii++) {
        ASSERT_EQ_QUANTITY(firstUnitless[ii], secondUnitless[ii], relTol, absTol.size() == 1 ? absTol[0] : absTol[ii]);
    }
}

void ASSERT_EQ_ORB_PART(
    const OrbitalElementPartials& first,
    const OrbitalElementPartials& second,
    const Unitless& relTol              = 0.0 * mp_units::one,
    const std::vector<Unitless>& absTol = { 0.0 * mp_units::one }
) noexcept
{
    if (first.index() != second.index()) { FAIL() << "Orbital element sets do not match"; }

    // arbitrary normalization. shouldn't affect relative size
    const Time scale                         = 1.0 * mp_units::si::unit_symbols::s;
    const std::vector<Unitless> firstScaled  = (first * scale).to_vector();
    const std::vector<Unitless> secondScaled = (second * scale).to_vector();
    for (int ii = 0; ii < 6; ii++) {
        ASSERT_EQ_QUANTITY(firstScaled[ii], secondScaled[ii], relTol, absTol.size() == 1 ? absTol[0] : absTol[ii]);
    }
}


template <typename Value_T, typename Frame_T>
void ASSERT_EQ_CART_VEC(
    const CartesianVector<Value_T, Frame_T>& vec,
    const CartesianVector<Value_T, Frame_T>& expected,
    const Unitless& relTol = 0.0 * mp_units::one,
    const Unitless& absTol = 0.0 * mp_units::one
) noexcept
{
    for (std::size_t ii = 0; ii < 3; ++ii) {
        ASSERT_EQ_QUANTITY(vec[ii], expected[ii], relTol, absTol);
    }
}

} // namespace astro
} // namespace astrea