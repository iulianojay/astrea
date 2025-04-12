#pragma once

#include <map>
#include <tuple>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/tuple_hash.hpp>
#include <astro/types/typedefs.hpp>

class AtmosphericForce : public Force {

    using HeightQuantity = mp_units::quantity<mp_units::si::unit_symbols::km>;
    using DensityQuantity =
        mp_units::quantity<mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m))>;
    using TitanDensityQuantity =
        mp_units::quantity<mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm))>;

  public:
    AtmosphericForce()  = default;
    ~AtmosphericForce() = default;

    AccelerationVector
        compute_force(const JulianDate& julianDate, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

  private:
    const DensityQuantity
        find_atmospheric_density(const JulianDate& julianDate, const Cartesian& state, const CelestialBodyUniquePtr& center) const;

    static const std::map<HeightQuantity, DensityQuantity> venutianAtmosphere;
    static const std::map<HeightQuantity, std::tuple<HeightQuantity, DensityQuantity, HeightQuantity>> earthAtmosphere;
    static const std::map<HeightQuantity, DensityQuantity> martianAtmosphere;
    static const std::map<HeightQuantity, TitanDensityQuantity> titanicAtmosphere;
};