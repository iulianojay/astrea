

# File Spherical.hpp

[**File List**](files.md) **>** [**angular\_elements**](dir_8f2f7499654791f4fc4240f01fb9baf6.md) **>** [**instances**](dir_1a50007be9f0149ab221abcea88ff37f.md) **>** [**Spherical.hpp**](Spherical_8hpp.md)

[Go to the documentation of this file](Spherical_8hpp.md)


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

class Spherical {

    friend std::ostream& operator<<(std::ostream&, Spherical const&);

  public:
    Spherical(Unitless scale = 0.0 * astrea::detail::unitless) :
        _range(scale * astrea::detail::distance_unit),
        _inclination(scale * astrea::detail::angle_unit),
        _azimuth(scale * astrea::detail::angle_unit)
    {
    }

    Spherical(const Distance& range, const Angle& inclination, const Angle& azimuth) :
        _range(range),
        _inclination(inclination),
        _azimuth(azimuth)
    {
    }

    Spherical(const RadiusVector<frames::earth::icrf>& r, const Date& date, const CelestialBody* parent);

    Spherical(const RadiusVector<frames::earth::earth_fixed>& r, const CelestialBody* parent);

    template <IsOrbitalElements T>
    Spherical(const T& elements, const AstrodynamicsSystem& sys, const Date& date)
    {
        *this = Spherical(
            Cartesian(elements, sys.get_mu()).get_position().template in_frame<frames::earth::earth_fixed>(date),
            sys.get_central_body().get()
        );
    }

    Spherical(const Spherical&);

    Spherical(Spherical&&) noexcept;

    Spherical& operator=(Spherical&&) noexcept;

    Spherical& operator=(const Spherical&);

    ~Spherical() = default;

    bool operator==(const Spherical& other) const;

    bool operator!=(const Spherical& other) const;

    Spherical operator+(const Spherical& other) const;

    Spherical& operator+=(const Spherical& other);

    Spherical operator-(const Spherical& other) const;

    Spherical& operator-=(const Spherical& other);

    Spherical operator*(const Unitless& multiplier) const;

    Spherical& operator*=(const Unitless& multiplier);

    std::vector<Unitless> operator/(const Spherical& other) const;

    Spherical operator/(const Unitless& divisor) const;

    Spherical& operator/=(const Unitless& divisor);

    RadiusVector<frames::earth::earth_fixed> get_position(const CelestialBody* parent) const;

    RadiusVector<frames::earth::icrf> get_position(const Date& date, const CelestialBody* parent) const;

    const Angle& get_azimuth() const { return _azimuth; }

    const Angle& get_inclination() const { return _inclination; }

    const Distance& get_range() const { return _range; }

    Spherical interpolate(const Time& thisTime, const Time& otherTime, const Spherical& other, const Time& targetTime) const;

  private:
    Distance _range;    
    Angle _inclination; 
    Angle _azimuth;     
};


std::tuple<Distance, Angle, Angle> convert_earth_fixed_to_spherical(const RadiusVector<frames::earth::earth_fixed>& rEcef);


RadiusVector<frames::earth::earth_fixed>
    convert_spherical_to_earth_fixed(const Distance& range, const Angle& inclination, const Angle& azimuth);

} // namespace astro
} // namespace astrea
```


