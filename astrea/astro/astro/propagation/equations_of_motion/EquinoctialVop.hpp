/**
 * @file EquinoctialVop.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Equinoctial VOP equations of motion class.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/typedefs.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class implementing the Equinoctial VOP equations of motion.
 */
class EquinoctialVop : public EquationsOfMotion {

  public:
    /**
     * @brief Constructor for the Equinoctial VOP class.
     *
     * @param system The astrodynamics system containing the central body and its properties.
     * @param forces The force model to be used in the equations of motion.
     */
    EquinoctialVop(const AstrodynamicsSystem& system, const ForceModel& forces) :
        EquationsOfMotion(system),
        forces(&forces),
        mu(system.get_center()->get_mu()) {};

    /**
     * @brief Destructor for the Equinoctial VOP class.
     */
    ~EquinoctialVop() = default;

    /**
     * @brief Computes the partial derivatives of the orbital elements using the Equinoctial VOP method.
     *
     * @param state The current orbital elements of the vehicle.
     * @param vehicle The vehicle for which the equations of motion are being computed.
     * @return OrbitalElementPartials The computed partial derivatives of the orbital elements.
     */
    OrbitalElementPartials operator()(const OrbitalElements& state, const Vehicle& vehicle) const override;

    /**
     * @brief Returns the expected set of orbital elements for this equations of motion class.
     *
     * @return std::size_t The expected set id of orbital elements.
     */
    constexpr std::size_t get_expected_set_id() const override { return OrbitalElements::get_set_id<Equinoctial>(); };

  private:
    mutable bool checkflag                     = false;                 //!< Flag to check for degenerate conditions.
    mp_units::quantity<mp_units::one> checkTol = 1e-10 * mp_units::one; //!< Tolerance for checking conditions.

    const ForceModel* forces; //!< The force model used in the equations of motion.

    GravParam mu; //!< Gravitational parameter of the central body.
};

} // namespace astro
} // namespace astrea