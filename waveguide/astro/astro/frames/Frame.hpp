#pragma once

#include <string>

#include <units/typedefs.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Base class for all frames.
 */
class Frame {

  protected:
    /**
     * @brief Default constructor for Frame.
     *
     * Initializes the frame with default values.
     */
    Frame() = default;

    /**
     * @brief Constructor for Frame with name and origin.
     *
     * @param name The name of the frame.
     * @param origin The origin of the frame.
     */
    Frame(const std::string& name, const std::string& origin) :
        name(name),
        origin(origin)
    {
    }

    /**
     * @brief Default destructor for Frame.
     */
    virtual ~Frame() = default;

  protected:
    std::string name;   //<! Name of the frame.
    std::string origin; //<! Origin of the frame, typically a celestial body or reference point.
};


} // namespace astro
} // namespace waveguide