#pragma once

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>

namespace astrea {
namespace astro {
namespace frames {

template <typename Frame_T, typename Frame_U>
    requires(HasSameOrigin<Frame_T, Frame_U>)
CartesianVector<Distance, Frame_T> get_center_offset(const Date& date)
{
    return CartesianVector<Distance, Frame_T>(
        0.0 * mp_units::si::unit_symbols::m, 0.0 * mp_units::si::unit_symbols::m, 0.0 * mp_units::si::unit_symbols::m
    );
}

template <typename Frame_T, typename Frame_U>
    requires(!HasSameOrigin<Frame_T, Frame_U> && HasSameAxis<Frame_T, Frame_U>)
CartesianVector<Distance, Frame_T> get_center_offset(const Date& date)
{
    // Build a system out of these bodies
    static const AstrodynamicsSystem sys(CelestialBodyId::SUN, { Frame_T::get_origin(), Frame_U::get_origin() });

    // Forcing the frame change here doesn't matter since the offset is just a difference and it's already implied that
    // these two frames share an axis.
    return sys.get_relative_position(date, Frame_T::get_origin(), Frame_U::get_origin()).template force_frame_conversion<Frame_T>();
}

template <typename Value_T, typename Frame_T, typename Frame_U>
CartesianVector<Value_T, Frame_U> rotate_vector_into_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
{
    const auto dcm = DcmManager::get_dcm<Frame_T, Frame_U>(date);
    return dcm * vec;
}

template <typename Frame_T, typename Frame_U>
CartesianVector<Distance, Frame_U> transform_vector_into_frame(const CartesianVector<Distance, Frame_T>& vec, const Date& date)
{
    const auto offset = get_center_offset<Frame_T, Frame_U>(date);
    const auto dcm    = DcmManager::get_dcm<Frame_T, Frame_U>(date);
    return CartesianVector<Distance, Frame_U>(dcm * (vec + offset));
}


} // namespace frames
} // namespace astro
} // namespace astrea