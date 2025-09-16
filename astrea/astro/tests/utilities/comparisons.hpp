#pragma once

#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {

namespace astro {

void ASSERT_EQ_ORB_ELEM(
    const OrbitalElements& first,
    const OrbitalElements& second,
    const bool& ignoreFastVariable,
    const Unitless& relTol              = 0.0 * mp_units::one,
    const std::vector<Unitless>& absTol = { 0.0 * mp_units::one }
) noexcept;

void ASSERT_EQ_ORB_PART(
    const OrbitalElementPartials& first,
    const OrbitalElementPartials& second,
    const Unitless& relTol              = 0.0 * mp_units::one,
    const std::vector<Unitless>& absTol = { 0.0 * mp_units::one }
) noexcept;


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