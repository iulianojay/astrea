

# File EulerAngles.ipp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**attitude**](dir_d187d1a6cf435d7a067093cc1f3d7926.md) **>** [**EulerAngles.ipp**](EulerAngles_8ipp.md)

[Go to the documentation of this file](EulerAngles_8ipp.md)


```C++

#pragma once

#include <astro/state/attitude/Quaternion.hpp>

namespace astrea {
namespace astro {

template <RotationSequence sequence, RotationType rotation_type, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
template <RotationSequence sequence_u, RotationType rotation_type_u>
    requires(!IsCompatibleEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_, _out_frame_>)
EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>::EulerAngles(const EulerAngles<sequence_u, rotation_type_u, _in_frame_, _out_frame_>& other)
{
    *this = Quaternion<_in_frame_, _out_frame_>(other).template to_euler_angles<sequence, rotation_type>();
}

} // namespace astro
} // namespace astrea
```


