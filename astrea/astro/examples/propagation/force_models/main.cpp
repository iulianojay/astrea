#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

int main()
{
    // A ForceModel is a factory for arbitrary Force objects. These forces are called during propagation
    // to compute accelerations on the spacecraft. Several forces are provided with Astrea, and users can add
    // more by inheriting from the Force class.
    struct ContinuousThrust : public Force {
        ContinuousThrust(const std::string& name = "Continuous Thrust Force") :
            _name(name)
        {
        }

        AccelerationVector<frames::earth::icrf>
            compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override
        {
            const astro::frames::dynamic::ric frame =
                frames::dynamic::ric::instantaneous(state.get_position(), state.get_velocity());
            const AccelerationVector<astro::frames::dynamic::ric> nadirAccel{ -1.0 * m / (s * s),
                                                                              0.0 * m / (s * s),
                                                                              0.0 * m / (s * s) };

            std::cout << "Applying continuous thrust force: " << _name << " at time " << date << std::endl;
            std::cout << nadirAccel << std::endl;

            return frame.rotate_out_of_this_frame(nadirAccel, date);
        }

      private:
        std::string _name;
    };

    // Input arguments are forwarded to the constructor of the Force subclass
    ForceModel forceModel;
    forceModel.add<ContinuousThrust>("My Continuous Thrust");

    // During propagation, the force model is queried for the total acceleration
    Cartesian state{ 7000.0 * km, 7000.0 * km, 0.0 * km, 0.0 * km / s, 7.5 * km / s, 1.0 * km / s };
    const auto totalAcceleration = forceModel.compute_forces(Date(), state, Vehicle(), AstrodynamicsSystem());
    std::cout << "Total Acceleration: " << totalAcceleration << std::endl;

    return 0;
}