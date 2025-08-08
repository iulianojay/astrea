#include <astro/frames/FrameReference.hpp>

#include <mp-units/systems/si.h>

#include <units/typedefs.hpp>

#include <astro/element_sets/CartesianVector.hpp>


namespace waveguide {
namespace astro {


AccelerationVector<EarthCenteredInertial> FrameReference::get_inertial_acceleration(const Date& date) const
{
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;
    return AccelerationVector<EarthCenteredInertial>{ 0.0 * km / s / s, 0.0 * km / s / s, 0.0 * km / s / s };
};


} // namespace astro
} // namespace waveguide