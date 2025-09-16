/**
 * @file Thruster.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Thruster class definition for astrea access platform
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/platforms/Payload.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class for storing and managing thruster parameters.
 */
class ThrusterParameters : public PayloadParameters {
  public:
    /**
     * @brief Constructor for ThrusterParameters
     *
     * @param boresight Boresight direction in RIC coordinates (default is Nadir).
     * @param attachmentPoint Attachment point in RIC coordinates (default is Center).
     */
    ThrusterParameters(
        const Thrust& thrust,
        const CartesianVector<Distance, RadialInTrackCrossTrack>& boresight       = NADIR_RIC,
        const CartesianVector<Distance, RadialInTrackCrossTrack>& attachmentPoint = CENTER
    ) :
        PayloadParameters(boresight, attachmentPoint),
        _thrust(thrust)
    {
    }

    /**
     * @brief Default destructor for ThrusterParameters
     */
    virtual ~ThrusterParameters() = default;

    /**
     * @brief Get the thrust magnitude.
     *
     * @return Thrust magnitude.
     */
    Thrust get_thrust() const { return _thrust; }

  protected:
    Thrust _thrust; //!< Thrust magnitude
};

/**
 * @brief Thruster class representing a thruster on a platform
 *
 * This class inherits from AccessObject and provides functionality for thrusters,
 * including field of view and access management.
 */
class Thruster : public Payload<Thruster, ThrusterParameters> {

  public:
    /**
     * @brief Constructor for Thruster
     *
     * @param parent Parent frame reference.
     * @param parameters Thruster parameters.
     */
    template <typename Parent_T>
        requires(std::is_base_of_v<FrameReference, Parent_T>)
    Thruster(const Parent_T& parent, const ThrusterParameters& parameters) :
        Payload<Thruster, ThrusterParameters>(parent, parameters, generate_id_hash())
    {
    }

    /**
     * @brief Default destructor for Thruster
     */
    virtual ~Thruster() = default;

    /**
     * @brief Get the ID of the sensor.
     *
     * @return std::size_t ID of the sensor.
     */
    std::size_t get_id() const;

    /**
     * @brief Get the impulsive delta-v provided by the thruster.
     *
     * @return Velocity The impulsive delta-v.
     */
    Velocity get_impulsive_delta_v() const;

  private:
    /**
     * @brief Generate a hash for the thruster ID.
     */
    std::size_t generate_id_hash();
};

/**
 * @brief Thruster platform type definition.
 */
using ThrusterPlatform = PayloadPlatform<Thruster>;

} // namespace astro
} // namespace astrea