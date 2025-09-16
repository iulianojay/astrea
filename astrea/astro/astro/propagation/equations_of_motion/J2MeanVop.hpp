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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>

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
    J2MeanVop(const AstrodynamicsSystem& system);

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
     * @return std::size_t The expected set id of orbital elements.
     */
    constexpr std::size_t get_expected_set_id() const override;

  private:
    mutable bool checkflag = false;                                        //!< Flag to check for degenerate conditions.
    Unitless eccTol        = 1e-10 * mp_units::one;                        //!< Tolerance for checking eccentricity.
    Angle incTol           = 1e-10 * mp_units::angular::unit_symbols::rad; //!< Tolerance for checking inclination.

    GravParam mu;         //!< Gravitational parameter of the central body.
    Unitless J2;          //!< J2 coefficient of the central body.
    Distance equitorialR; //!< Equatorial radius of the central body.
};

} // namespace astro
} // namespace astrea