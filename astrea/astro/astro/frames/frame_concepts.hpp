#pragma once

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/// Frame types ///
template <typename Frame_T>
concept IsInertialFrame = requires {
    { Frame_T::get_axis() == FrameAxis::ICRF || Frame_T::get_axis() == FrameAxis::J2000 };
};

template <typename Frame_T>
concept IsBodyFixedFrame = requires {
    { Frame_T::get_axis() == FrameAxis::BODY_FIXED };
};

template <typename Frame_T>
concept IsStaticFrame = requires {
    {
        Frame_T::get_axis() == FrameAxis::ICRF || Frame_T::get_axis() == FrameAxis::J2000 || Frame_T::get_axis() == FrameAxis::BODY_FIXED
    };
};

template <typename Frame_T>
concept IsDynamicFrame = requires {
    {
        Frame_T::get_axis() == FrameAxis::LVLH || Frame_T::get_axis() == FrameAxis::RIC || Frame_T::get_axis() == FrameAxis::VNB
    };
};

/// Frame comparitors ///
template <typename Frame_T, typename Frame_U>
concept HasSameOrigin = requires {
    { Frame_T::get_origin() == Frame_U::get_origin() };
};

template <typename Frame_T, typename Frame_U>
concept HasSameAxis = requires {
    { Frame_T::get_axis() == Frame_U::get_axis() };
};

template <typename Frame_T, typename Frame_U>
concept IsSameFrame = requires {
    requires HasSameOrigin<Frame_T, Frame_U>;
    requires HasSameAxis<Frame_T, Frame_U>;
    { Frame_T::get_origin() != CelestialBodyId::CUSTOM }; // dynamic frames will look the same
    { Frame_U::get_origin() != CelestialBodyId::CUSTOM };
};

// DCM logic
template <typename Frame_T, typename Frame_U>
concept HasDcm = requires(const Date& date) {
    { get_dcm<Frame_T, Frame_U>(date) };
};

template <typename Frame_T, typename Frame_U>
concept HasDcmMethod = requires(const Frame_T& frame, const Date& date) {
    { frame.template get_dcm<Frame_T, Frame_U>(date) };
};

} // namespace astro
} // namespace astrea