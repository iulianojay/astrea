#include <astro/element_sets/Frame.hpp>

#include <mp-units/systems/si.h>

#include <units/typedefs.hpp>

#include <astro/element_sets/CartesianVector.hpp>


namespace waveguide {
namespace astro {

VelocityVector FrameReference::get_velocity(const Date& date) const
{
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;
    return VelocityVector{ 0.0 * km / s, 0.0 * km / s, 0.0 * km / s };
};

AccelerationVector FrameReference::get_acceleration(const Date& date) const
{
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;
    return AccelerationVector{ 0.0 * km / s / s, 0.0 * km / s / s, 0.0 * km / s / s };
};


} // namespace astro
} // namespace waveguide