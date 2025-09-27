#include <astro/utilities/conversions.hpp>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <units/units.hpp>

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;

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

Angle convert_eccentric_anomaly_to_mean_anomaly(const Angle& ea, const Unitless ecc)
{
    return ea - ecc * sin(ea) * isq_angle::cotes_angle;
}

Angle convert_mean_anomaly_to_eccentric_anomaly(const Angle& ma, const Unitless ecc)
{
    Angle ea        = ma - ecc * sin(ma) * isq_angle::cotes_angle;
    const Angle tol = 1.0e-10 * rad;
    unsigned iter   = 0;
    Angle deltaE    = 1.0 * rad;
    while (iter < 1e2 && abs(deltaE) > tol) {
        deltaE = ma - (ea - ecc * sin(ea) * isq_angle::cotes_angle) / (1.0 * one - ecc * cos(ea));
        ea += deltaE;
        ++iter;
    }
    return ea;
}


} // namespace astro
} // namespace astrea