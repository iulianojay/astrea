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

#include <memory>

#include <astro/platforms/Payload.hpp>
#include <astro/state/CartesianVector.hpp>
#include <astro/state/frames/FrameReference.hpp>
#include <astro/state/frames/frames.hpp>
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
     * @param fov Field of View for the thruster.
     * @param boresight Boresight direction in RIC coordinates (default is Nadir).
     * @param attachmentPoint Attachment point in RIC coordinates (default is Center).
     */
    ThrusterParameters(const astro::RadiusVector<astro::RIC>& boresight = NADIR_RIC, const astro::RadiusVector<astro::RIC>& attachmentPoint = CENTER) :
        PayloadParameters(boresight, attachmentPoint)
    {
    }

    /**
     * @brief Default destructor for ThrusterParameters
     */
    virtual ~ThrusterParameters() = default;
};

/**
 * @brief Thruster class representing a thruster on a platform
 *
 * This class inherits from AccessObject and provides functionality for thrusters,
 * including field of view and access management.
 */
class Thruster : public Payload<ThrusterParameters> {

  public:
    /**
     * @brief Constructs a Thruster from a FieldOfView object.
     *
     * @param parent The parent platform to which the thruster is attached.
     * @param fov Field of view object defining the thruster's coverage area.
     * @param boresight The boresight vector of the thruster.
     * @param attachmentPoint The point on the platform where the thruster is attached.
     */
    template <typename Parent_T>
        requires(std::is_base_of_v<FrameReference, Parent_T>)
    Thruster(const Parent_T& parent, const ThrusterParameters& parameters) :
        Payload<ThrusterParameters>(&parent, parameters)
    {
    }

    /**
     * @brief Default destructor for Thruster
     */
    virtual ~Thruster() = default;

  private:
    /**
     * @brief Generate a hash for the thruster ID.
     */
    void generate_id_hash();
};

} // namespace astro
} // namespace astrea