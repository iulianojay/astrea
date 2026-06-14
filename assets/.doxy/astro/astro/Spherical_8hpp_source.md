

# File Spherical.hpp

[**File List**](files.md) **>** [**angular\_elements**](dir_8f2f7499654791f4fc4240f01fb9baf6.md) **>** [**Spherical.hpp**](Spherical_8hpp.md)

[Go to the documentation of this file](Spherical_8hpp.md)


```C++

#pragma once

#include <iosfwd>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

// units
#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

template <IsCelestialBody auto _body_>
class Spherical {

    template <IsCelestialBody auto body>
    friend std::ostream& operator<<(std::ostream&, Spherical<body> const&);

  public:
    static constexpr auto body          = _body_; 
    static constexpr auto _icrf_frame_  = make_frame(_body_, axes::icrf); 
    static constexpr auto _fixed_frame_ = get_body_fixed_frame<_body_>(); 

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

    template <auto _frame_>
        requires(equivalent(_frame_, make_frame(_body_, axes::icrf)))
    Spherical(const RadiusVector<_frame_>& r, const Date& date);

    Spherical(const RadiusVector<_fixed_frame_>& r);

    template <IsOrbitalElements T>
    Spherical(const T& elements, const Date& date)
    {
        static const GravParam mu = get_mu<_body_>();
        *this = Spherical<_body_>(Cartesian<T::frame>(elements, mu).get_position().template in_frame<_fixed_frame_>(date));
    }

    Spherical(const Spherical<_body_>&);

    Spherical(Spherical<_body_>&&) noexcept;

    Spherical<_body_>& operator=(Spherical<_body_>&&) noexcept;

    Spherical<_body_>& operator=(const Spherical<_body_>&);

    ~Spherical() = default;

    bool operator==(const Spherical<_body_>& other) const;
    bool operator!=(const Spherical<_body_>& other) const;

    Spherical<_body_> operator+(const Spherical<_body_>& other) const;
    Spherical<_body_>& operator+=(const Spherical<_body_>& other);
    Spherical<_body_> operator-(const Spherical<_body_>& other) const;
    Spherical<_body_>& operator-=(const Spherical<_body_>& other);
    Spherical<_body_> operator*(const Unitless& multiplier) const;
    Spherical<_body_>& operator*=(const Unitless& multiplier);
    std::vector<Unitless> operator/(const Spherical<_body_>& other) const;
    Spherical<_body_> operator/(const Unitless& divisor) const;
    Spherical<_body_>& operator/=(const Unitless& divisor);

    RadiusVector<_fixed_frame_> get_position() const;

    RadiusVector<_icrf_frame_> get_position(const Date& date) const;

    const Angle& get_azimuth() const { return _azimuth; }
    const Angle& get_inclination() const { return _inclination; }
    const Distance& get_range() const { return _range; }

    Spherical<_body_>
        interpolate(const Time& thisTime, const Time& otherTime, const Spherical<_body_>& other, const Time& targetTime) const;

  private:
    Distance _range;    
    Angle _inclination; 
    Angle _azimuth;     
};


template <IsFrame auto _frame_>
    requires(IsBodyFixedFrame<decltype(_frame_)>)
std::tuple<Distance, Angle, Angle> convert_body_fixed_to_spherical(const RadiusVector<_frame_>& rFixed)
{
    using mp_units::angular::unit_symbols::rad;
    using mp_units::si::unit_symbols::km;
    const Distance range    = rFixed.norm();
    const Angle inclination = acos(rFixed.get_z() / range);

    const Distance& x = rFixed.get_x();
    const Distance& y = rFixed.get_y();

    Angle azimuth;
    if (x == 0.0 * km && y == 0.0 * km) { azimuth = 0.0 * rad; }
    else {
        azimuth = acos(x / sqrt(x * x + y * y));
        if (y < 0.0 * km) { azimuth = -azimuth; }
    }
    return std::make_tuple(range, inclination, azimuth);
}


template <IsFrame auto _frame_>
    requires(IsBodyFixedFrame<decltype(_frame_)>)
RadiusVector<_frame_> convert_spherical_to_body_fixed(const Distance& range, const Angle& inclination, const Angle& azimuth)
{
    return RadiusVector<_frame_>(range * sin(inclination) * cos(azimuth), range * sin(inclination) * sin(azimuth), range * cos(inclination));
}

} // namespace astro
} // namespace astrea

#include <astro/state/angular_elements/Spherical.ipp>
```


