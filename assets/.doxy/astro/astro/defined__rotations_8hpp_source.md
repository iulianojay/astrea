

# File defined\_rotations.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**defined\_rotations.hpp**](defined__rotations_8hpp.md)

[Go to the documentation of this file](defined__rotations_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/DirectionCosineMatrixAccel.hpp>
#include <astro/frames/framework/DirectionCosineMatrixRate.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto frame, IsFrame auto frame_u>
    requires(equivalent(frame.axis, axes::icrf) && equivalent(frame_u.axis, axes::j2000))
inline constexpr DirectionCosineMatrix<frame, frame_u> get_dcm(const Date& date)
{
    using mp_units::angular::unit_symbols::rad;
    static const Angle zeta0   = -8.0561e-8 * rad;
    static const Angle eta0    = -3.3060e-8 * rad;
    static const Angle dalpha0 = 7.0783e-8 * rad;
    return DirectionCosineMatrix<frame, frame_u>::XYZ(-eta0, zeta0, dalpha0);
}

template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(IsBodyFixedFrame<decltype(out_frame)> && equivalent(in_frame.axis, axes::icrf) && in_frame.origin != planets::Earth)
inline constexpr DirectionCosineMatrix<in_frame, out_frame> get_dcm(const Date& date)
{
    const Angle gst = date.body_sidereal_time<out_frame.origin>();
    return DirectionCosineMatrix<in_frame, out_frame>::Z(-gst);
}

template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(IsBodyFixedFrame<decltype(out_frame)> && equivalent(in_frame.axis, axes::icrf) && in_frame.origin != planets::Earth)
inline constexpr DirectionCosineMatrix<in_frame, out_frame> get_dcm_rate(const Date& date)
{
    const Angle gst                    = date.body_sidereal_time<out_frame.origin>();
    const AngularVelocity rotationRate = get_rotation_rate<out_frame.origin>();
    return DirectionCosineMatrixRate<in_frame, out_frame>::Z(-gst, rotationRate);
}


template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(IsSynodicFrame<decltype(out_frame)> && equivalent(in_frame.axis, axes::icrf))
inline constexpr DirectionCosineMatrix<in_frame, out_frame> get_dcm(const Date& date)
{
    static constexpr auto primary   = out_frame.axis.primary;
    static constexpr auto secondary = out_frame.axis.secondary;

    const auto r = get_relative_position<secondary, primary>(date).direction(); // x-axis
    const auto v = get_relative_velocity<secondary, primary>(date).direction(); // nearly the y-axis but not quite
    const auto h = r.cross(v); // z-axis, normal to the plane of motion of the secondary around the primary
    const auto y = h.cross(r); // y-axis, normal to the plane of motion and the line connecting the primary and
                               // secondary, pointing in the direction of motion of the secondary around the primary

    return DirectionCosineMatrix<in_frame, out_frame>::from_vectors(r, y, h);
}

template <IsFrame auto frame, IsFrame auto parent>
    requires(IsFixedOffsetFrame<decltype(frame)> && equivalent(frame.parent.axis, parent.axis))
inline constexpr DirectionCosineMatrix<parent, frame> get_dcm()
{
    if constexpr (HasAngularOffset<decltype(frame)>) {
        return DirectionCosineMatrix<parent, frame>::template from_euler_angles<frame.axis.sequence>(
            frame.axis.misalignment.phi, frame.axis.misalignment.theta, frame.axis.misalignment.psi
        );
    }
    else {
        return DirectionCosineMatrix<parent, frame>::identity();
    }
}

} // namespace astro
} // namespace astrea
```


