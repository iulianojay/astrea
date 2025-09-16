/**
 * @file KeplerianVop.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Keplerian VOP equations of motion class.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class implementing the Keplerian VOP equations of motion.
 */
class KeplerianVop : public EquationsOfMotion {

  public:
    /**
     * @brief Constructor for the Keplerian VOP class.
     *
     * @param system The astrodynamics system containing the central body and its properties.
     * @param forces The force model to be used in the equations of motion.
     * @param doWarn Flag to indicate whether to warn about degenerate cases.
     */
    KeplerianVop(const AstrodynamicsSystem& system, const ForceModel& forces, const bool doWarn = true);

    /**
     * @brief Destructor for the Keplerian VOP class.
     */
    ~KeplerianVop() = default;

    /**
     * @brief Computes the partial derivatives of the orbital elements using the Keplerian VOP method.
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
    constexpr std::size_t get_expected_set_id() const override;

  private:
    Unitless checkTol = 1e-10 * mp_units::one; //!< Tolerance for checking conditions.

    const ForceModel* forces; //!< The force model used in the equations of motion.
    GravParam mu;             //!< Gravitational parameter of the central body.
    bool doWarn;              //!< Flag to indicate whether to warn about degenerate cases.

    /**
     * @brief Checks for degenerate conditions in the orbital elements.
     *
     * @param ecc The eccentricity of the orbit.
     * @param inc The inclination of the orbit.
     */
    void check_degenerate(const Unitless& ecc, const Angle& inc) const;
};

} // namespace astro
} // namespace astrea