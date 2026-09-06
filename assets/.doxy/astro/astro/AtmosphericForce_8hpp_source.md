

# File AtmosphericForce.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**AtmosphericForce.hpp**](AtmosphericForce_8hpp.md)

[Go to the documentation of this file](AtmosphericForce_8hpp.md)


```C++

#pragma once

#include <memory>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>
#include <astro/propagation/force_models/space_weather/atmosphere.hpp>
#include <astro/systems/system_concepts.hpp>

namespace astrea {
namespace astro {

template <IsCelestialBody auto _body_, EarthAtmosphereModel _model_ = EarthAtmosphereModel::HARRIS_PRIESTER>
class AtmosphericForce : public PerturbingForce {

  public:
    static constexpr auto center = _body_;

    AtmosphericForce() = default;

    ~AtmosphericForce() = default;

    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
    {
        using namespace mp_units;
        using mp_units::pow;
        using mp_units::si::atan2;
        using mp_units::si::sin;
        using mp_units::si::unit_symbols::rad;
        using mp_units::si::unit_symbols::s;

        // Extract
        const RadiusVector<frames::primary>& r   = state.get_position();
        const VelocityVector<frames::primary>& v = state.get_velocity();

        const Distance& x = r.get_x();
        const Distance& y = r.get_y();
        const Distance R  = r.norm();

        const Velocity& vx = v.get_x();
        const Velocity& vy = v.get_y();
        const Velocity& vz = v.get_z();

        // Find velocity relative to atmosphere
        static const AngularVelocity& bodyRotationRate    = get_rotation_rate<center>();
        const VelocityVector<frames::primary> relVelocity = { vx + y * bodyRotationRate.in(rad / s) / rad,
                                                              vy - x * bodyRotationRate.in(rad / s) / rad,
                                                              vz };

        // Exponential Drag Model
        Density atmosphericDensity;
        if constexpr (center == planets::Earth) {
            if constexpr (_model_ == EarthAtmosphereModel::NRLMSISE00) {
                static const auto& spaceWeatherData = get_space_weather_data();
                if (!spaceWeatherData) {
                    throw std::runtime_error("Space weather data is required for NRLMSISE-00 atmospheric model.");
                }
                const auto& spaceWeatherParameters = spaceWeatherData->at(state.get_epoch());
                atmosphericDensity = find_atmospheric_density<center, _model_>(state, spaceWeatherParameters);
            }
            else {
                atmosphericDensity = find_atmospheric_density<center, _model_>(state);
            }
        }
        else {
            atmosphericDensity = find_atmospheric_density<center>(state);
        }

        // Accel due to drag
        const Velocity relVelMag         = relVelocity.norm();
        const Unitless coefficientOfDrag = vehicle.get_coefficient_of_drag(state);
        const SurfaceArea areaRam        = vehicle.get_ram_area(state);
        const Force dragForceMag         = -0.5 * coefficientOfDrag * areaRam * atmosphericDensity * pow<2>(relVelMag);

        const ForceVector<frames::primary> forceDrag = dragForceMag * (relVelocity / relVelMag);

        // Accel due to lift
        const Angle angleOfAttack        = atan2(relVelocity.get_z(), relVelocity.get_x());
        const Unitless coefficientOfLift = vehicle.get_coefficient_of_lift(state);
        const SurfaceArea areaLift       = vehicle.get_lift_area(state);
        const Force liftForceMag = 0.5 * coefficientOfLift * areaLift * atmosphericDensity * pow<2>(relVelMag) * sin(angleOfAttack);
        const ForceVector<frames::primary> forceLift = liftForceMag * (r / R); // just assume radial lift for now

        return { .force = forceDrag + forceLift };
    }

    std::unique_ptr<PerturbingForce> clone() const override { return std::make_unique<AtmosphericForce>(*this); }
};

} // namespace astro
} // namespace astrea
```


