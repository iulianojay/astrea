#pragma once

#include <units/units.hpp>

#include <astro/frames/frames.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.
 *
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<Frame_T, Frame_U> The DCM from Frame_U to Frame_T.
 */
template <typename Frame_T, typename Frame_U>
    requires(Frame_T::get_axis() == FrameAxis::J2000 && Frame_U::get_axis() == FrameAxis::ICRF && HasSameOrigin<Frame_T, Frame_U>)
inline DCM<Frame_T, Frame_U> get_dcm(const Date& date)
{
    using mp_units::angular::unit_symbols::deg;
    static const Angle obliquity = Angle(23.43928 * deg); // obliquity at J2000
    return DCM<Frame_T, Frame_U>::X(obliquity);
}

/**
 * @brief Get the Direction Cosine Matrix (DCM) for the ECEF frame at a given date.
 *
 * @param date The date for which to get the DCM.
 * @return DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed> The DCM from ECI to ECEF.
 */
template <>
inline DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>
    get_dcm<frames::earth::icrf, frames::earth::earth_fixed>(const Date& date)
{
    const Angle gst = julian_date_to_sidereal_time(date.jd());
    return DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>::Z(gst);
}

} // namespace astro
} // namespace astrea