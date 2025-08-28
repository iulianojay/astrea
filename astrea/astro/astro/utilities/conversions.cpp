#include <astro/utilities/conversions.hpp>

#include <units/units.hpp>

#include <astro/state/CartesianVector.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::h;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::min;
using mp_units::si::unit_symbols::s;

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
    return ta - (2.0 * ecc * sin(ta) + (0.75 * pow<2>(ecc) + 0.125 * pow<4>(ecc)) * sin(2.0 * ta) -
                 1.0 / 3.0 * pow<3>(ecc) * sin(3.0 * ta) + 5.0 / 32.0 * pow<4>(ecc) * sin(4.0 * ta)) *
                    isq_angle::cotes_angle;
}

Angle sanitize_angle(const Angle& angle)
{
    Angle ang = angle;
    while (ang < 0.0 * astrea::detail::angle_unit) {
        ang += TWO_PI;
    }
    return fmod(ang, TWO_PI);
}

} // namespace astro
} // namespace astrea