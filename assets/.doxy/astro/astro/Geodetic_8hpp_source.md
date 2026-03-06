

# File Geodetic.hpp

[**File List**](files.md) **>** [**angular\_elements**](dir_8f2f7499654791f4fc4240f01fb9baf6.md) **>** [**instances**](dir_1a50007be9f0149ab221abcea88ff37f.md) **>** [**Geodetic.hpp**](Geodetic_8hpp.md)

[Go to the documentation of this file](Geodetic_8hpp.md)


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

class Geodetic {

    friend std::ostream& operator<<(std::ostream&, Geodetic const&);

  public:
    Geodetic(Unitless scale = 0.0 * astrea::detail::unitless) :
        _latitude(scale * astrea::detail::angle_unit),
        _longitude(scale * astrea::detail::angle_unit),
        _altitude(scale * astrea::detail::distance_unit)
    {
    }

    Geodetic(const Angle& latitude, const Angle& longitude, const Distance& altitude) :
        _latitude(latitude),
        _longitude(longitude),
        _altitude(altitude)
    {
    }

    Geodetic(const RadiusVector<frames::earth::icrf>& r, const Date& date, const CelestialBody* parent);

    Geodetic(const RadiusVector<frames::earth::earth_fixed>& r, const CelestialBody* parent);

    template <IsOrbitalElements T>
    Geodetic(const T& elements, const AstrodynamicsSystem& sys, const Date& date)
    {
        *this = Geodetic(
            Cartesian(elements, sys.get_mu()).get_position().template in_frame<frames::earth::earth_fixed>(date),
            sys.get_central_body().get()
        );
    }

    Geodetic(const Geodetic&);

    Geodetic(Geodetic&&) noexcept;

    Geodetic& operator=(Geodetic&&) noexcept;

    Geodetic& operator=(const Geodetic&);

    ~Geodetic() = default;

    bool operator==(const Geodetic& other) const;

    bool operator!=(const Geodetic& other) const;

    Geodetic operator+(const Geodetic& other) const;

    Geodetic& operator+=(const Geodetic& other);

    Geodetic operator-(const Geodetic& other) const;

    Geodetic& operator-=(const Geodetic& other);

    Geodetic operator*(const Unitless& multiplier) const;

    Geodetic& operator*=(const Unitless& multiplier);

    std::vector<Unitless> operator/(const Geodetic& other) const;

    Geodetic operator/(const Unitless& divisor) const;

    Geodetic& operator/=(const Unitless& divisor);

    RadiusVector<frames::earth::earth_fixed> get_position(const CelestialBody* parent) const;

    RadiusVector<frames::earth::icrf> get_position(const Date& date, const CelestialBody* parent) const;

    const Angle& get_latitude() const { return _latitude; }

    const Angle& get_longitude() const { return _longitude; }

    const Distance& get_altitude() const { return _altitude; }

    Geodetic interpolate(const Time& thisTime, const Time& otherTime, const Geodetic& other, const Time& targetTime) const;

  private:
    Angle _latitude;    
    Angle _longitude;   
    Distance _altitude; 
};


std::tuple<Angle, Angle, Distance>
    convert_earth_fixed_to_geodetic(const RadiusVector<frames::earth::earth_fixed>& rEcef, const Distance& rEquitorial, const Distance& rPolar);


RadiusVector<frames::earth::earth_fixed>
    convert_geodetic_to_earth_fixed(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& rEquitorial, const Distance& rPolar);

} // namespace astro
} // namespace astrea
```


