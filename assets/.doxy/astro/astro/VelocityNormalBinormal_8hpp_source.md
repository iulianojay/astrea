

# File VelocityNormalBinormal.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**dynamic\_frames**](dir_212f82f17a8a6ae9a0307bd639427aed.md) **>** [**VelocityNormalBinormal.hpp**](VelocityNormalBinormal_8hpp.md)

[Go to the documentation of this file](VelocityNormalBinormal_8hpp.md)


```C++

#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/DynamicFrame.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace frames {

template <IsFrame auto _parent_>
struct VnbTag final : Frame<"Velocity-Normal-Binormal", DynamicOrigin{}, DynamicAxis{}, _parent_> {
    VelocityNormalBinormal<_parent_> instantaneous(const RadiusVector<_parent_>& r, const VelocityVector<_parent_>& v) const
    {
        return VelocityNormalBinormal<_parent_>(r, v);
    }
};

template <IsFrame auto _parent_>
inline constexpr VnbTag<_parent_> vnb_tag{};

template <IsFrame auto _parent_>
struct VelocityNormalBinormal : public DynamicFrame<VelocityNormalBinormal<_parent_>, _parent_, vnb_tag<_parent_>> {

    using tag_type = VnbTag<_parent_>;       
    static inline constexpr tag_type tag{};  
    static constexpr auto parent = _parent_; 

    VelocityNormalBinormal(const RadiusVector<parent>& position, const VelocityVector<parent>& velocity) :
        DynamicFrame<VelocityNormalBinormal<_parent_>, parent, vnb_tag<_parent_>>(position, velocity)
    {
    }

    VelocityNormalBinormal() = delete; 

    DirectionCosineMatrix<parent, tag> get_dcm(const Date& date) const
    {
        const auto r        = this->get_position(date).direction();
        const auto v        = this->get_velocity(date).direction();
        const auto h        = r.cross(v).direction();
        const auto binormal = (v.cross(h)).direction();
        return DirectionCosineMatrix<parent, tag>::from_vectors(v, h, binormal);
    }
};


} // namespace frames
} // namespace astro
} // namespace astrea
```


