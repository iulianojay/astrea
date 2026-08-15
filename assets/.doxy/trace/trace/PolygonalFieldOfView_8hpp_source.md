

# File PolygonalFieldOfView.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**sensors**](dir_4c34a36d272c54a3547c6d2c18e9dea2.md) **>** [**fov**](dir_303a66b90134ad3dff734d202c421315.md) **>** [**PolygonalFieldOfView.hpp**](PolygonalFieldOfView_8hpp.md)

[Go to the documentation of this file](PolygonalFieldOfView_8hpp.md)


```C++

#pragma once

#include <numbers>
#include <vector>

#include <gtl/phmap.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <units/units.hpp>

#include <trace/platforms/sensors/fov/FieldOfView.hpp>

namespace astrea {
namespace trace {

class PolygonalFieldOfView : public FieldOfView {
  public:
    PolygonalFieldOfView(const Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::si::unit_symbols::rad, const int& nPoints = 72);

    PolygonalFieldOfView(const Angle& halfConeWidth, const Angle& halfConeHeight, const int& nPoints = 72);

    PolygonalFieldOfView(const gtl::flat_hash_map<Angle, Angle>& points) :
        _points(points)
    {
        find_min_and_max_angles();
    }

    ~PolygonalFieldOfView() = default;

    bool contains(
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& boresight,
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& target
    ) const;

    Angle max_half_angle() const override { return _maxHalfAngle; }

  private:
    // TODO: These angle are actually defined w.r.t a frame so we need to figure out what that
    // is and how to define it meaningfully.
    // Probably will be some body-fixed frame aligned with the sensor boresight
    // The key angle is the azimuthal angle around the boresight, and the value angle is the
    // off-boresight angle at that azimuth
    gtl::flat_hash_map<Angle, Angle> _points;                    
    Angle _minHalfAngle = 0.0 * mp_units::si::unit_symbols::rad; 
    Angle _maxHalfAngle = std::numeric_limits<Angle>::infinity(); 

    void find_min_and_max_angles();

    std::vector<std::pair<Unitless, Unitless>> build_polygon() const;
};

bool point_in_polygon(const std::pair<Unitless, Unitless>& point, const std::vector<std::pair<Unitless, Unitless>>& polygon);

} // namespace trace
} // namespace astrea
```


