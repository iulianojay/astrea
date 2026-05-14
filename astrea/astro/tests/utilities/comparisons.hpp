#pragma once

#include <vector>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {

namespace astro {

/**
 * @brief Asserts that two OrbitalElements objects are equal within specified tolerances.
 *
 * This function checks if two OrbitalElements objects are equal within the given relative and absolute tolerances.
 * If they are not equal, it triggers a test failure.
 *
 * @param first The first OrbitalElements object to compare.
 * @param second The second OrbitalElements object to compare.
 * @param ignoreFastVariable If true, ignores fast-changing variables in the comparison.
 * @param relTol Relative tolerance for the comparison.
 * @param absTol Absolute tolerances for each element in the comparison.
 */
bool nearly_equal(
    const OrbitalElements& first,
    const OrbitalElements& second,
    const bool& ignoreFastVariable,
    const Unitless& relTol              = 0.0 * mp_units::one,
    const std::vector<Unitless>& absTol = { 0.0 * mp_units::one }
) noexcept;

/**
 * @brief Asserts that two OrbitalElementPartials objects are equal within specified tolerances.
 *
 * This function checks if two OrbitalElementPartials objects are equal within the given relative and absolute
 * tolerances. If they are not equal, it triggers a test failure.
 *
 * @param first The first OrbitalElementPartials object to compare.
 * @param second The second OrbitalElementPartials object to compare.
 * @param relTol Relative tolerance for the comparison.
 * @param absTol Absolute tolerances for each element in the comparison.
 */
bool nearly_equal(
    const OrbitalElementPartials& first,
    const OrbitalElementPartials& second,
    const Unitless& relTol              = 0.0 * mp_units::one,
    const std::vector<Unitless>& absTol = { 0.0 * mp_units::one }
) noexcept;

/**
 * @brief Asserts that two CartesianVector objects are equal within specified tolerances.
 *
 * This function checks if two CartesianVector objects are equal within the given relative and absolute tolerances.
 * If they are not equal, it triggers a test failure.
 *
 * @tparam Value_T The value type of the first CartesianVector.
 * @tparam _frame_ The frame type of the CartesianVectors.
 * @tparam Value_U The value type of the second CartesianVector.
 * @param vec The first CartesianVector to compare.
 * @param expected The second CartesianVector to compare.
 * @param relTol Relative tolerance for the comparison.
 * @param absTol Absolute tolerance for the comparison.
 */
template <typename Value_T, IsFrame auto _frame_, typename Value_U>
bool nearly_equal(
    const CartesianVector<Value_T, _frame_>& vec,
    const CartesianVector<Value_U, _frame_>& expected,
    const Unitless& relTol = 0.0 * mp_units::one,
    const Unitless& absTol = 0.0 * mp_units::one
) noexcept
{
    for (std::size_t ii = 0; ii < 3; ++ii) {
        if (!math::nearly_equal(vec[ii], expected[ii], relTol, absTol)) { return false; }
    }
    return true;
}

/**
 * @brief Asserts that two DirectionCosineMatrix objects are equal within specified tolerances.
 *
 * This function checks if two DirectionCosineMatrix objects are equal within the given relative and absolute
 * tolerances. If they are not equal, it triggers a test failure.
 *
 * @tparam _in_frame_ The input frame type of the DirectionCosineMatrix.
 * @tparam _out_frame_ The output frame type of the DirectionCosineMatrix.
 * @param dcm1 The first DirectionCosineMatrix to compare.
 * @param dcm2 The second DirectionCosineMatrix to compare.
 * @param relTol Relative tolerance for the comparison.
 * @param absTol Absolute tolerance for the comparison.
 */
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
bool nearly_equal(
    const DirectionCosineMatrix<_in_frame_, _out_frame_>& dcm1,
    const DirectionCosineMatrix<_in_frame_, _out_frame_>& dcm2,
    const Unitless& relTol = 0.0 * mp_units::one,
    const Unitless& absTol = 0.0 * mp_units::one
) noexcept
{
    for (std::size_t ii = 0; ii < 3; ++ii) {
        for (std::size_t jj = 0; jj < 3; ++jj) {
            if (!math::nearly_equal(dcm1[ii, jj], dcm2[ii, jj], relTol, absTol)) { return false; }
        }
    }
    return true;
}

} // namespace astro
} // namespace astrea