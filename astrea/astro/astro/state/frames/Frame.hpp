#pragma once

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/// Frame types ///
template <typename Frame_T>
concept IsInertialFrame = requires {
    { Frame_T::get_axis() == FrameAxis::ICRF || Frame_T::get_axis() == FrameAxis::J2000 };
    { Frame_T::get_origin() != CelestialBodyId::UNSET && Frame_T::get_origin() != CelestialBodyId::CUSTOM };
};

template <typename Frame_T>
concept IsBodyFixedFrame = requires {
    { Frame_T::get_axis() == FrameAxis::BODY_FIXED };
    { Frame_T::get_origin() != CelestialBodyId::UNSET && Frame_T::get_origin() != CelestialBodyId::CUSTOM };
};

/// Frame comparitors ///
template <typename Frame_T, typename Frame_U>
concept IsSameFrame = requires {
    { Frame_T::get_axis() == Frame_U::get_axis() };
    { Frame_T::get_origin() == Frame_U::get_origin() };
};

template <typename Frame_T, typename Frame_U>
concept HasSameOrigin = requires {
    { Frame_T::get_origin() == Frame_U::get_origin() };
};

template <typename Frame_T, typename Frame_U>
concept HasSameAxis = requires {
    { Frame_T::get_axis() == Frame_U::get_axis() };
};

/// Conversion types ///
template <typename Frame_T, typename Frame_U>
concept IsFixedOffsetConversion = requires {
    requires !IsSameFrame<Frame_T, Frame_U>;
    requires !HasSameOrigin<Frame_T, Frame_U>;
    requires HasSameAxis<Frame_T, Frame_U>;
};

/**
 * @brief Base class for all state/frames.
 */
template <typename Frame_T, CelestialBodyId origin, FrameAxis axis>
struct Frame {

  protected:
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
    template <typename Value_T, typename Frame_U>
        requires(HasSameAxis<Frame_T, Frame_U>)
    static constexpr CartesianVector<Value_T, Frame_T>
        rotate_into_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
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
    template <typename Value_T, typename Frame_U>
        requires(HasSameAxis<Frame_T, Frame_U>)
    static constexpr CartesianVector<Value_T, Frame_T>
        rotate_out_of_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
    {
        return vec;
    }

    /**
     * @brief Converts a CartesianVector from Frame_T coordinates to itself - null conversion.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in Frame_T coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, Frame_T> The converted CartesianVector in Frame_T coordinates.
     */
    template <typename Value_T>
    static constexpr CartesianVector<Value_T, Frame_T>
        convert_to_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
    {
        return vec;
    }

    /**
     * @brief Converts a CartesianVector from Frame_T coordinates to itself - null conversion.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector in Frame_T coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, Frame_T> The converted CartesianVector in Frame_T coordinates.
     */
    template <typename Value_T>
    static constexpr CartesianVector<Value_T, Frame_T>
        convert_from_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
    {
        return vec;
    }

    /**
     * @brief Get the origin of the frame.
     *
     * @return The origin of the frame.
     */
    static constexpr CelestialBodyId get_origin() { return _origin; }

    /**
     * @brief Get the origin of the frame.
     *
     * @return The origin of the frame.
     */
    static constexpr FrameAxis get_axis() { return _axis; }

  protected:
    static constexpr CelestialBodyId _origin = origin; //!< The central body associated with the inertial frame.
    static constexpr FrameAxis _axis         = axis;   //!< The axis type of the inertial frame.
};


} // namespace astro
} // namespace astrea