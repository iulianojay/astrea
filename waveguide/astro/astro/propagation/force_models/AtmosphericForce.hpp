#pragma once

#include <map>
#include <tuple>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/tuple_hash.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace waveguide {
namespace astro {

class AtmosphericForce : public Force {

    using TitanDensity = mp_units::quantity<mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm))>;

  public:
    AtmosphericForce()  = default;
    ~AtmosphericForce() = default;

    AccelerationVector
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

  private:
    const Density find_atmospheric_density(const Date& date, const Cartesian& state, const CelestialBodyUniquePtr& center) const;

    static const std::map<Altitude, Density> venutianAtmosphere;
    static const std::map<Altitude, std::tuple<Altitude, Density, Altitude>> earthAtmosphere;
    static const std::map<Altitude, Density> martianAtmosphere;
    static const std::map<Altitude, TitanDensity> titanicAtmosphere;
};

} // namespace astro
} // namespace waveguide