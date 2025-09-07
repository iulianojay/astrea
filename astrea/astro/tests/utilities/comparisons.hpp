#pragma once

#include <gtest/gtest.h>

#include <math/test_util.hpp>

#include <astro/astro.hpp>

namespace astrea {

namespace astro {

void ASSERT_EQ_ORB_ELEM(const OrbitalElements& first, const OrbitalElements& second, const Unitless& relTol) noexcept
{
    if (first.index() != second.index()) { FAIL() << "Orbital element sets do not match"; }

    auto firstUnitless  = first.to_vector();
    auto secondUnitless = second.to_vector();
    for (int ii = 0; ii < 6; ii++) {
        ASSERT_EQ_QUANTITY(firstUnitless[ii], secondUnitless[ii], relTol);
    }
}

void ASSERT_EQ_ORB_PART(const OrbitalElementPartials& first, const OrbitalElementPartials& second, const Unitless& relTol) noexcept
{
    if (first.index() != second.index()) { FAIL() << "Orbital element sets do not match"; }

    // arbitrary normalization. shouldn't affect relative size
    const Time scale                         = 1.0 * mp_units::si::unit_symbols::s;
    const std::vector<Unitless> firstScaled  = (first * scale).to_vector();
    const std::vector<Unitless> secondScaled = (second * scale).to_vector();
    for (int ii = 0; ii < 6; ii++) {
        ASSERT_EQ_QUANTITY(firstScaled[ii], secondScaled[ii], relTol);
    }
}


template <typename Value_T, typename Frame_T>
void ASSERT_EQ_CART_VEC(const CartesianVector<Value_T, Frame_T>& vec, const CartesianVector<Value_T, Frame_T>& expected, const Unitless& relTol) noexcept
{
    for (std::size_t ii = 0; ii < 3; ++ii) {
        ASSERT_EQ_QUANTITY(vec[ii], expected[ii], relTol);
    }
}

} // namespace astro
} // namespace astrea