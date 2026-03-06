

# File LocalHorizontalLocalVertical.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**instances**](dir_a85615e9ad779999123e94bfb15c8545.md) **>** [**LocalHorizontalLocalVertical.hpp**](LocalHorizontalLocalVertical_8hpp.md)

[Go to the documentation of this file](LocalHorizontalLocalVertical_8hpp.md)


```C++

#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/DynamicFrame.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace frames {

class LocalHorizontalLocalVertical : public DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH> {

    friend DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH>;

  public:
    LocalHorizontalLocalVertical() = delete; 

    LocalHorizontalLocalVertical(const FrameReference* parent) :
        DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH>(parent)
    {
    }

    ~LocalHorizontalLocalVertical() = default;

    DirectionCosineMatrix<frames::earth::icrf, LocalHorizontalLocalVertical> get_dcm(const Date& date) const
    {
        const auto r               = get_inertial_position(date).unit();
        const auto v               = get_inertial_velocity(date).unit();
        const auto h               = r.cross(v).unit();
        const auto localHorizontal = ((-h).cross(-r)).unit();
        return DirectionCosineMatrix<frames::earth::icrf, LocalHorizontalLocalVertical>::from_vectors(localHorizontal, -h, -r);
    }

  private:
    LocalHorizontalLocalVertical(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity) :
        DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH>(position, velocity)
    {
    }
};

namespace dynamic {
using lvlh = LocalHorizontalLocalVertical;
} // namespace dynamic

} // namespace frames
} // namespace astro
} // namespace astrea
```


