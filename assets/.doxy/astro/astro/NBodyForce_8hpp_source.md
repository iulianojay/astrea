

# File NBodyForce.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**NBodyForce.hpp**](NBodyForce_8hpp.md)

[Go to the documentation of this file](NBodyForce_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

template <IsCelestialBody auto... bodies>
class NBodyForce : public PerturbingForce {
  public:
    NBodyForce() = default;

    ~NBodyForce() = default;

    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
    {
        // Extract
        const Date date                                       = state.get_epoch();
        const RadiusVector<frames::primary>& rCenterToVehicle = state.get_position();

        // Center body properties
        constexpr static auto center = frames::primary.origin;

        // Reset perturbation
        AccelerationVector<frames::primary> accelNBody{ Acceleration::zero() };
        (
            [&]<auto body>() {
                if constexpr (body == center) {
                    return; // Skip central body
                }

                // Find center to nth body and spacecraft to nth body
                // NOTE: The forced frame conversion here is fine since it's just a relative translation, no rotation or velocity
                const RadiusVector<frames::primary> rCenterToNbody =
                    get_relative_position<body, center>(date).template force_frame_conversion<frames::primary>();
                const RadiusVector<frames::primary> rVehicleToNbody = rCenterToNbody - rCenterToVehicle;

                // Normalize
                const Distance rMagVehicleToNbody = rVehicleToNbody.norm();
                const Distance rMagCenterToNbody  = rCenterToNbody.norm();

                // Perturbational force from nth body
                using mp_units::quantity;
                const GravParam mu          = get_mu<body>();
                const quantity directTerm   = mu / pow<3>(rMagVehicleToNbody);
                const quantity indirectTerm = mu / pow<3>(rMagCenterToNbody);

                accelNBody += directTerm * rVehicleToNbody - indirectTerm * rCenterToNbody;
            }.template operator()<bodies>(),
            ...
        );

        return { .force = accelNBody * vehicle.get_mass(state) };
    }

    std::unique_ptr<PerturbingForce> clone() const override { return std::make_unique<NBodyForce<bodies...>>(*this); }
};

} // namespace astro
} // namespace astrea
```


