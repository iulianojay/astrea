#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/CartesianVector.hpp>
#include <astro/frames/instances/EarthCenteredInertial.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/RotatingFrame.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

namespace waveguide {
namespace astro {

class EarthCenteredEarthFixed : public RotatingFrame {

  public:
    EarthCenteredEarthFixed() :
        RotatingFrame("Earth Centered Earth Fixed", "Earth", EarthCenteredInertial()){};
    ~EarthCenteredEarthFixed() = default;

    template <typename Value_T>
    static CartesianVector<Value_T, EarthCenteredEarthFixed>
        convert_to(const CartesianVector<Value_T, EarthCenteredEarthFixed>& ecefVec, const Date& date)
    {
        return ecefVec;
    }

    template <typename Value_T>
    static CartesianVector<Value_T, EarthCenteredEarthFixed>
        convert_to(const CartesianVector<Value_T, EarthCenteredInertial>& eciVec, const Date& date)
    {
        const Angle gst = julian_date_to_siderial_time(date.jd());
        const auto dcm  = DirectionCosineMatrix<EarthCenteredEarthFixed>::Z(gst);
        return dcm * eciVec;
    }
};

using ECEF = EarthCenteredEarthFixed; // Alias for convenience

} // namespace astro
} // namespace waveguide