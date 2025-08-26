/**
 * @file AtmosphericForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the AtmosphericForce class, which computes the atmospheric force on a vehicle.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <map>
#include <tuple>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/tuple_hash.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to compute the atmospheric force on a vehicle.
 *
 * This class computes the atmospheric force on a vehicle based on its state and the celestial body's atmosphere.
 */
class AtmosphericForce : public Force {

    /**
     * @brief Type alias for Density on Titan.
     */
    using TitanDensity = mp_units::quantity<mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm))>;

  public:
    /**
     * @brief Default constructor for AtmosphericForce.
     */
    AtmosphericForce() = default;

    /**
     * @brief Default destructor for AtmosphericForce.
     */
    ~AtmosphericForce() = default;

    /**
     * @brief Computes the atmospheric force on a vehicle.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @param sys Astrodynamics system containing celestial body data
     * @return AccelerationVector<ECI> The computed acceleration vector due to atmospheric force.
     */
    AccelerationVector<ECI>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

  private:
    /**
     * @brief Finds the atmospheric density at a given altitude.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param center Celestial body around which the vehicle is orbiting
     * @return Density The atmospheric density at the given altitude.
     */
    const Density find_atmospheric_density(const Date& date, const Cartesian& state, const CelestialBodyUniquePtr& center) const;

    static const std::map<Altitude, Density> venutianAtmosphere; //!< Map of atmospheric densities for Venus at different altitudes
    static const std::map<Altitude, std::tuple<Altitude, Density, Altitude>> earthAtmosphere; //!< Map of atmospheric densities for Earth at different altitudes
    static const std::map<Altitude, Density> martianAtmosphere; //!< Map of atmospheric densities for Mars at different altitudes
    static const std::map<Altitude, TitanDensity> titanicAtmosphere; //!< Map of atmospheric densities for Titan at different altitudes
};

} // namespace astro
} // namespace astrea