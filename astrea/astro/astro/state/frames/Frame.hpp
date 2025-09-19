#pragma once

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all state/frames.
 */
template <typename Frame_T>
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

  public:
    /**
     * @brief Null conversion from a frame to itself.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in Frame_T coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, Frame_T> The input vector.
     */
    template <typename Value_T>
    static CartesianVector<Value_T, Frame_T> rotate_into_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
    {
        return vec;
    }

    /**
     * @brief Null conversion from a frame to itself.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in Frame_T coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, Frame_T> The input vector.
     */
    template <typename Value_T>
    static CartesianVector<Value_T, Frame_T> rotate_out_of_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
    {
        return vec;
    }

    /**
     * @brief Get the name of the frame.
     *
     * @return The name of the frame.
     */
    std::string get_name() const { return name; }

    /**
     * @brief Get the origin of the frame.
     *
     * @return The origin of the frame.
     */
    std::string get_origin() const { return origin; }

  protected:
    std::string name;   //!< Name of the frame.
    std::string origin; //!< Origin of the frame, typically a celestial body or reference point.
};


} // namespace astro
} // namespace astrea