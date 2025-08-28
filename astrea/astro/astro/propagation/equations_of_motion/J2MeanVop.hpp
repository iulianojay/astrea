/**
 * @file J2MeanVop.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the J2 Mean VOP equations of motion class.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/CelestialBody.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/orbital_elements/OrbitalElementSet.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class implementing the J2 Mean VOP equations of motion.
 */
class J2MeanVop : public EquationsOfMotion {

  public:
    /**
     * @brief Constructor for the J2 Mean VOP class.
     *
     * @param system The astrodynamics system containing the central body and its properties.
     */
    J2MeanVop(const AstrodynamicsSystem& system) :
        EquationsOfMotion(system),
        mu(system.get_center()->get_mu()),
        J2(system.get_center()->get_j2()),
        equitorialR(system.get_center()->get_equitorial_radius()) {};

    /**
     * @brief Destructor for the J2 Mean VOP class.
     */
    ~J2MeanVop() = default;

    /**
     * @brief Computes the partial derivatives of the orbital elements using the J2 Mean VOP method.
     *
     * @param state The current orbital elements of the vehicle.
     * @param vehicle The vehicle for which the equations of motion are being computed.
     * @return OrbitalElementPartials The computed partial derivatives of the orbital elements.
     */
    OrbitalElementPartials operator()(const OrbitalElements& state, const Vehicle& vehicle) const override;

    /**
     * @brief Returns the expected set of orbital elements for this equations of motion class.
     *
     * @return const OrbitalElementSet& The expected set of orbital elements.
     */
    const OrbitalElementSet& get_expected_set() const override { return expectedSet; };

  private:
    mutable bool checkflag = false;                                        //!< Flag to check for degenerate conditions.
    Unitless eccTol        = 1e-10 * mp_units::one;                        //!< Tolerance for checking eccentricity.
    Angle incTol           = 1e-10 * mp_units::angular::unit_symbols::rad; //!< Tolerance for checking inclination.

    OrbitalElementSet expectedSet = OrbitalElementSet::KEPLERIAN; //!< Expected set of orbital elements for this method.

    GravParam mu;         //!< Gravitational parameter of the central body.
    Unitless J2;          //!< J2 coefficient of the central body.
    Distance equitorialR; //!< Equatorial radius of the central body.
};

} // namespace astro
} // namespace astrea