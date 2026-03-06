

# File DynamicFrame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**types**](dir_6f58486cdc039e35eca8cf5d1aadadc3.md) **>** [**DynamicFrame.hpp**](DynamicFrame_8hpp.md)

[Go to the documentation of this file](DynamicFrame_8hpp.md)


```C++

#pragma once

#include <string>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/frames/frames.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

template <class Frame_T, FrameAxis axis>
    requires(axis != FrameAxis::ICRF && axis != FrameAxis::J2000 && axis != FrameAxis::BODY_FIXED)
struct DynamicFrame : public Frame<CelestialBodyId::CUSTOM, axis> {
  protected:
    DynamicFrame(const FrameReference* parent) :
        _parent(parent),
        _isInstantaneous(false)
    {
        if (parent == nullptr) {
            throw std::invalid_argument(
                "Parent of a dynamic frame cannot be null. Use Frame_T::instantaneous(r, v) "
                "for instantaneous dynamic state/frames."
            );
        }
    }

    DynamicFrame(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity) :
        _position(position),
        _velocity(velocity),
        _isInstantaneous(true)
    {
    }

  public:
    static constexpr CelestialBodyId get_origin() { return Frame<CelestialBodyId::CUSTOM, axis>::get_origin(); }

    static constexpr FrameAxis get_axis() { return Frame<CelestialBodyId::CUSTOM, axis>::get_axis(); }

    static Frame_T instantaneous(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity)
    {
        return Frame_T(position, velocity);
    }

    template <typename Value_T>
    CartesianVector<Value_T, Frame_T>
        rotate_into_this_frame(const CartesianVector<Value_T, frames::earth::icrf>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * vec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, frames::earth::icrf>
        rotate_out_of_this_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec;
    }

    RadiusVector<Frame_T> convert_to_this_frame(const RadiusVector<frames::earth::icrf>& vec, const Date& date) const
    {
        return get_dcm_impl(date) * (vec - get_inertial_position(date));
    }

    RadiusVector<frames::earth::icrf> convert_from_this_frame(const RadiusVector<Frame_T>& vec, const Date& date) const
    {
        return get_dcm_impl(date).transpose() * vec + get_inertial_position(date);
    }

  private:
    DCM<frames::earth::icrf, Frame_T> get_dcm_impl(const Date& date) const
    {
        return static_cast<const Frame_T*>(this)->get_dcm(date);
    }

    RadiusVector<frames::earth::icrf> get_center_offset(const Date& date) const { return get_inertial_position(date); }

  protected:
    const FrameReference* _parent;                 
    RadiusVector<frames::earth::icrf> _position;   
    VelocityVector<frames::earth::icrf> _velocity; 
    bool _isInstantaneous;                         

    RadiusVector<frames::earth::icrf> get_inertial_position(const Date& date) const
    {
        return _isInstantaneous ? _position : _parent->get_inertial_position(date); // TODO: maybe store date for instantaneous and throw here if it doesn't match
    }

    VelocityVector<frames::earth::icrf> get_inertial_velocity(const Date& date) const
    {
        return _isInstantaneous ? _velocity : _parent->get_inertial_velocity(date);
    }
};

} // namespace astro
} // namespace astrea
```


