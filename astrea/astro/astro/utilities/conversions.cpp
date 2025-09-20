#include <astro/utilities/conversions.hpp>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <units/units.hpp>

using namespace mp_units;
using namespace mp_units::angular;

namespace astrea {
namespace astro {

Angle convert_mean_anomaly_to_true_anomaly(const Angle& ma, const Unitless ecc)
{
    return ma + ((2.0 * ecc - 0.25 * pow<3>(ecc)) * sin(ma) + 1.25 * pow<2>(ecc) * sin(2.0 * ma) +
                 13.0 / 12.0 * pow<3>(ecc) * sin(3.0 * ma)) *
                    (isq_angle::cotes_angle);
}

Angle convert_true_anomaly_to_mean_anomaly(const Angle& ta, const Unitless ecc)
{
    return ta + (-2.0 * ecc * sin(ta) + (0.75 * pow<2>(ecc) + 0.125 * pow<4>(ecc)) * sin(2.0 * ta) -
                 1.0 / 3.0 * pow<3>(ecc) * sin(3.0 * ta) + 5.0 / 32.0 * pow<4>(ecc) * sin(4.0 * ta)) *
                    isq_angle::cotes_angle;
}

} // namespace astro
} // namespace astrea