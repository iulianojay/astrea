

# File DynamicFrame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**DynamicFrame.hpp**](DynamicFrame_8hpp.md)

[Go to the documentation of this file](DynamicFrame_8hpp.md)


```C++

#pragma once

#include <string>

#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

template <typename Self, IsFrame auto _parent_, IsFrame auto _self_>
struct DynamicFrame {
  protected:
    DynamicFrame(const RadiusVector<_parent_>& position, const VelocityVector<_parent_>& velocity) :
        _position(position),
        _velocity(velocity)
    {
    }

  public:
    static constexpr auto parent = _parent_; 

    template <typename Value_T>
    CartesianVector<Value_T, _self_> rotate_into_this_frame(const CartesianVector<Value_T, parent>& vec, const Date& date) const
    {
        return this->get_dcm_impl(date) * vec;
    }

    template <typename Value_T>
    CartesianVector<Value_T, parent> rotate_out_of_this_frame(const CartesianVector<Value_T, _self_>& vec, const Date& date) const
    {
        return this->get_dcm_impl(date).transpose() * vec;
    }

    RadiusVector<_self_> transform_to_this_frame(const RadiusVector<parent>& vec, const Date& date) const
    {
        return this->get_dcm_impl(date) * (vec - get_position(date));
    }

    RadiusVector<parent> transform_from_this_frame(const RadiusVector<_self_>& vec, const Date& date) const
    {
        return this->get_dcm_impl(date).transpose() * vec + get_position(date);
    }

  private:
    DirectionCosineMatrix<parent, _self_> get_dcm_impl(const Date& date) const
    {
        return static_cast<const Self*>(this)->get_dcm(date);
    }

  protected:
    RadiusVector<parent> _position;   
    VelocityVector<parent> _velocity; 

    RadiusVector<parent> get_position(const Date& date) const { return _position; }

    VelocityVector<parent> get_velocity(const Date& date) const { return _velocity; }
};

} // namespace astro
} // namespace astrea
```


