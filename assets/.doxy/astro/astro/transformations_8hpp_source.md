

# File transformations.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**transformations.hpp**](transformations_8hpp.md)

[Go to the documentation of this file](transformations_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/instances/defined_rotations.hpp>
#include <astro/frames/types/BodyFixedFrame.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/InertialFrame.hpp>
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

namespace {

template <typename Frame_T, typename Frame_U>
DCM<Frame_T, Frame_U> get_dcm_impl(const Date& date)
{
    static_assert(!(HasDcm<Frame_T, Frame_U> && HasDcm<Frame_U, Frame_T>), "DCM defined in both directions, please define only one to avoid symmetry issues.");
    static_assert(IsStaticFrame<Frame_T> && IsStaticFrame<Frame_U>, "Dynamic frame conversions cannot be called statically. Dynamic frames must be created at runtime with a platform to reference.");
    static_assert(HasDcm<Frame_T, Frame_U> || HasDcm<Frame_U, Frame_T> || IsSameFrame<Frame_T, Frame_U>, "No DCM defined between these two frames.");

    if constexpr (IsSameFrame<Frame_T, Frame_U>) {
        return DCM<Frame_T, Frame_U>::identity(); // TODO: Figure out how to do this earlier to avoid unnecessary matrix math
    }
    else if constexpr (HasDcm<Frame_T, Frame_U>) {
        return get_dcm<Frame_T, Frame_U>(date);
    }
    else if constexpr (HasDcm<Frame_U, Frame_T>) {
        return get_dcm<Frame_U, Frame_T>(date).transpose();
    }
    throw std::logic_error("How did you get here?");
}

} // namespace

template <typename Value_T, typename Frame_T, typename Frame_U>
CartesianVector<Value_T, Frame_U> rotate_vector_into_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
{
    const auto dcm = get_dcm_impl<Frame_T, Frame_U>(date);
    return dcm * vec;
}

// template <typename Value_T, typename Frame_T, typename Frame_U>
// CartesianVector<Value_T, Frame_U> transform_vector_into_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
// {
//     static_assert(std::is_same_v<Value_T, Distance>, "Transformations with respect to a frame are only implemented for Distance vectors at this time.");

//     const auto offset = get_center_offset<Frame_T, Frame_U>(date);
//     const auto dcm    = DcmManager::get_dcm<Frame_T, Frame_U>(date);
//     return CartesianVector<Value_T, Frame_U>(dcm * vec + offset);
// }


} // namespace frames
} // namespace astro
} // namespace astrea
```


