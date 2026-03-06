

# File Cylindrical.hpp

[**File List**](files.md) **>** [**angular\_elements**](dir_8f2f7499654791f4fc4240f01fb9baf6.md) **>** [**instances**](dir_1a50007be9f0149ab221abcea88ff37f.md) **>** [**Cylindrical.hpp**](Cylindrical_8hpp.md)

[Go to the documentation of this file](Cylindrical_8hpp.md)


```C++

#pragma once

#include <iosfwd>

// units
#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class Cylindrical {

    friend std::ostream& operator<<(std::ostream&, Cylindrical const&);

  public:
    Cylindrical(Unitless scale = 0.0 * astrea::detail::unitless) :
        _range(scale * astrea::detail::distance_unit),
        _azimuth(scale * astrea::detail::angle_unit),
        _elevation(scale * astrea::detail::distance_unit)
    {
    }

    Cylindrical(const Distance& range, const Angle& azimuth, const Distance& elevation) :
        _range(range),
        _azimuth(azimuth),
        _elevation(elevation)
    {
    }

    Cylindrical(const RadiusVector<frames::earth::icrf>& r, const Date& date, const CelestialBody* parent);

    Cylindrical(const RadiusVector<frames::earth::earth_fixed>& r, const CelestialBody* parent);

    template <IsOrbitalElements T>
    Cylindrical(const T& elements, const AstrodynamicsSystem& sys, const Date& date)
    {
        *this = Cylindrical(
            Cartesian(elements, sys.get_mu()).get_position().template in_frame<frames::earth::earth_fixed>(date),
            sys.get_central_body().get()
        );
    }

    Cylindrical(const Cylindrical&);

    Cylindrical(Cylindrical&&) noexcept;

    Cylindrical& operator=(Cylindrical&&) noexcept;

    Cylindrical& operator=(const Cylindrical&);

    ~Cylindrical() = default;

    bool operator==(const Cylindrical& other) const;

    bool operator!=(const Cylindrical& other) const;

    Cylindrical operator+(const Cylindrical& other) const;

    Cylindrical& operator+=(const Cylindrical& other);

    Cylindrical operator-(const Cylindrical& other) const;

    Cylindrical& operator-=(const Cylindrical& other);

    Cylindrical operator*(const Unitless& multiplier) const;

    Cylindrical& operator*=(const Unitless& multiplier);

    std::vector<Unitless> operator/(const Cylindrical& other) const;

    Cylindrical operator/(const Unitless& divisor) const;

    Cylindrical& operator/=(const Unitless& divisor);

    RadiusVector<frames::earth::earth_fixed> get_position(const CelestialBody* parent) const;

    RadiusVector<frames::earth::icrf> get_position(const Date& date, const CelestialBody* parent) const;

    const Angle& get_azimuth() const { return _azimuth; }

    const Distance& get_elevation() const { return _elevation; }

    const Distance& get_range() const { return _range; }

    Cylindrical interpolate(const Time& thisTime, const Time& otherTime, const Cylindrical& other, const Time& targetTime) const;

  private:
    Distance _range;     
    Angle _azimuth;      
    Distance _elevation; 
};


std::tuple<Distance, Angle, Distance> convert_earth_fixed_to_cylindrical(const RadiusVector<frames::earth::earth_fixed>& rEcef);


RadiusVector<frames::earth::earth_fixed>
    convert_cylindrical_to_earth_fixed(const Distance& range, const Angle& azimuth, const Distance& elevation);

} // namespace astro
} // namespace astrea
```


