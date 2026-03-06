

# File RadialInTrackCrossTrack.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**instances**](dir_a85615e9ad779999123e94bfb15c8545.md) **>** [**RadialInTrackCrossTrack.hpp**](RadialInTrackCrossTrack_8hpp.md)

[Go to the documentation of this file](RadialInTrackCrossTrack_8hpp.md)


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

class RadialInTrackCrossTrack : public DynamicFrame<RadialInTrackCrossTrack, FrameAxis::RIC> {

    friend DynamicFrame<RadialInTrackCrossTrack, FrameAxis::RIC>;

  public:
    RadialInTrackCrossTrack() = delete; 

    RadialInTrackCrossTrack(const FrameReference* parent) :
        DynamicFrame<RadialInTrackCrossTrack, FrameAxis::RIC>(parent)
    {
    }

    ~RadialInTrackCrossTrack() = default;

    DirectionCosineMatrix<frames::earth::icrf, RadialInTrackCrossTrack> get_dcm(const Date& date) const
    {
        const auto r       = get_inertial_position(date).unit();
        const auto v       = get_inertial_velocity(date).unit();
        const auto h       = r.cross(v).unit();
        const auto inTrack = (-r.cross(h)).unit();
        return DirectionCosineMatrix<frames::earth::icrf, RadialInTrackCrossTrack>::from_vectors(r, inTrack, h);
    }

  private:
    RadialInTrackCrossTrack(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity) :
        DynamicFrame<RadialInTrackCrossTrack, FrameAxis::RIC>(position, velocity)
    {
    }
};

namespace dynamic {
using ric = RadialInTrackCrossTrack;
} // namespace dynamic

} // namespace frames
} // namespace astro
} // namespace astrea
```


