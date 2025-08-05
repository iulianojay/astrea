#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/InertialFrame.hpp>

namespace waveguide {
namespace astro {


class EarthCenteredInertial : public InertialFrame {

  public:
    EarthCenteredInertial() :
        InertialFrame("Earth Centered Inertial", "Earth")
    {
    }

    template <typename Value_T>
    static CartesianVector<Value_T, EarthCenteredInertial>
        convert_to(const CartesianVector<Value_T, EarthCenteredInertial>& eciVec, const Date& date)
    {
        return eciVec;
    }

    template <typename Value_T>
    static CartesianVector<Value_T, EarthCenteredInertial>
        convert_to(const CartesianVector<Value_T, EarthCenteredEarthFixed>& ecefVec, const Date& date)
    {
        const Angle gst = julian_date_to_siderial_time(date.jd());
        const auto dcm  = DirectionCosineMatrix<EarthCenteredInertial>::Z(-gst);
        return dcm * ecefVec;
    }
};

using ECI = EarthCenteredInertial; // Alias for convenience

} // namespace astro
} // namespace waveguide