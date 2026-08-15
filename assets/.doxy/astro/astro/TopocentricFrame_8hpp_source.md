

# File TopocentricFrame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**TopocentricFrame.hpp**](TopocentricFrame_8hpp.md)

[Go to the documentation of this file](TopocentricFrame_8hpp.md)


```C++

#pragma once

#include <type_traits>

#include <mp-units/core.h>
#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/frames/framework/BodyFixedFrame.hpp>
#include <astro/frames/framework/FixedOffsetFrame.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

// There has to be a better way to do this

template <IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
inline consteval auto get_x_offset_from_lla()
{
    return convert_geodetic_to_body_fixed<_parent_>(_lat_, _lon_, _alt_)[0];
}

template <IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
inline consteval auto get_y_offset_from_lla()
{
    return convert_geodetic_to_body_fixed<_parent_>(_lat_, _lon_, _alt_)[1];
}

template <IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
inline consteval auto get_z_offset_from_lla()
{
    return convert_geodetic_to_body_fixed<_parent_>(_lat_, _lon_, _alt_)[2];
}

template <mp_units::symbol_text _name_, IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
struct TopocentricFrame : FixedOffsetFrame<
                              _name_,
                              _parent_,
                              get_x_offset_from_lla<_parent_, _lat_, _lon_, _alt_>(),
                              get_y_offset_from_lla<_parent_, _lat_, _lon_, _alt_>(),
                              get_z_offset_from_lla<_parent_, _lat_, _lon_, _alt_>(),
                              Angle(90.0 * mp_units::si::degree), // rotation z by longitude,
                              _lat_,                              // rotation y by latitude,
                              _lon_,                   // rotation x by 90 degrees (to align with local vertical)
                              RotationSequence::ZYX> { // This gives the NWU frame

    static constexpr auto lat  = _lat_; 
    static constexpr auto lon  = _lon_; 
    static constexpr auto alt  = _alt_; 
    static constexpr auto body = _parent_.origin; 
};

} // namespace astro
} // namespace astrea
```


