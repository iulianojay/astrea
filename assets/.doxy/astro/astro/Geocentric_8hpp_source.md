

# File Geocentric.hpp

[**File List**](files.md) **>** [**angular\_elements**](dir_8f2f7499654791f4fc4240f01fb9baf6.md) **>** [**Geocentric.hpp**](Geocentric_8hpp.md)

[Go to the documentation of this file](Geocentric_8hpp.md)


```C++

#pragma once

#include <iosfwd>

// units
#include <math/trig.hpp>
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
class Geocentric {

    template <IsCelestialBody auto body>
    friend std::ostream& operator<<(std::ostream&, Geocentric<body> const&);

  public:
    static constexpr auto body          = _body_; 
    static constexpr auto _icrf_frame_  = make_frame(_body_, axes::icrf); 
    static constexpr auto _fixed_frame_ = get_body_fixed_frame<_body_>(); 

    Geocentric(Unitless scale = 0.0 * astrea::detail::unitless) :
        _latitude(scale * astrea::detail::angle_unit),
        _longitude(scale * astrea::detail::angle_unit),
        _altitude(scale * astrea::detail::distance_unit)
    {
    }

    Geocentric(const Angle& latitude, const Angle& longitude, const Distance& altitude) :
        _latitude(latitude),
        _longitude(longitude),
        _altitude(altitude)
    {
    }

    template <auto _frame_>
        requires(equivalent(_frame_, make_frame(_body_, axes::icrf)))
    Geocentric(const RadiusVector<_frame_>& r, const Date& date);

    Geocentric(const RadiusVector<_fixed_frame_>& r);

    template <IsOrbitalElements T>
    Geocentric(const T& elements, const Date& date)
    {
        static const GravParam mu = get_mu<_body_>();
        *this = Geocentric<_body_>(Cartesian<T::frame>(elements, mu).get_position().template in_frame<_fixed_frame_>(date));
    }

    Geocentric(const Geocentric<_body_>&);

    Geocentric(Geocentric<_body_>&&) noexcept;

    Geocentric<_body_>& operator=(Geocentric<_body_>&&) noexcept;

    Geocentric<_body_>& operator=(const Geocentric<_body_>&);

    ~Geocentric() = default;

    bool operator==(const Geocentric<_body_>& other) const;

    bool operator!=(const Geocentric<_body_>& other) const;

    Geocentric<_body_> operator+(const Geocentric<_body_>& other) const;

    Geocentric<_body_>& operator+=(const Geocentric<_body_>& other);

    Geocentric<_body_> operator-(const Geocentric<_body_>& other) const;

    Geocentric<_body_>& operator-=(const Geocentric<_body_>& other);

    Geocentric<_body_> operator*(const Unitless& multiplier) const;

    Geocentric<_body_>& operator*=(const Unitless& multiplier);

    std::vector<Unitless> operator/(const Geocentric<_body_>& other) const;

    Geocentric<_body_> operator/(const Unitless& divisor) const;

    Geocentric<_body_>& operator/=(const Unitless& divisor);

    RadiusVector<_fixed_frame_> get_position() const;

    RadiusVector<_icrf_frame_> get_position(const Date& date) const;

    const Angle& get_latitude() const { return _latitude; }

    const Angle& get_longitude() const { return _longitude; }

    const Distance& get_altitude() const { return _altitude; }

    Geocentric<_body_>
        interpolate(const Time& thisTime, const Time& otherTime, const Geocentric<_body_>& other, const Time& targetTime) const;

  private:
    Angle _latitude;    
    Angle _longitude;   
    Distance _altitude; 
};

template <IsCelestialBody auto body>
inline constexpr Distance calculate_geocentric_radius(const Angle& lat)
{
    using math::cos;
    using math::sin;
    using mp_units::pow;

    static constexpr Distance a = get_equitorial_radius<body>();
    static constexpr Distance b = get_polar_radius<body>();
    const Unitless cosLatSq     = pow<2>(cos(lat));
    const Unitless sinLatSq     = pow<2>(sin(lat));
    return sqrt((pow<4>(a) * cosLatSq + pow<4>(b) * sinLatSq) / (pow<2>(a) * cosLatSq + pow<2>(b) * sinLatSq));
}

template <IsFrame auto frame>
    requires(IsBodyFixedFrame<decltype(frame)>)
inline constexpr std::tuple<Angle, Angle, Distance> convert_body_fixed_to_geocentric(const RadiusVector<frame>& rEcef)
{
    using math::atan2;
    using mp_units::sqrt;

    const Distance& x = rEcef[0];
    const Distance& y = rEcef[1];
    const Distance& z = rEcef[2];
    const Distance R  = rEcef.norm();

    const Distance rho = sqrt(x * x + y * y);

    const Angle longitude = atan2(y, x);
    const Angle latitude  = atan2(z, rho);

    const Distance rGeocentric = calculate_geocentric_radius<decltype(frame)::origin>(latitude);
    const Distance altitude    = R - rGeocentric;

    return { latitude, longitude, altitude };
}


template <IsFrame auto _frame_>
    requires(IsBodyFixedFrame<decltype(_frame_)>)
inline constexpr RadiusVector<_frame_> convert_geocentric_to_body_fixed(const Angle& lat, const Angle& lon, const Distance& alt)
{
    using math::cos;
    using math::sin;

    const Distance rGeocentric = calculate_geocentric_radius<decltype(_frame_)::origin>(lat);
    const Distance R           = rGeocentric + alt;

    // Ecef coordinates
    return { R * cos(lat) * cos(lon), R * cos(lat) * sin(lon), R * sin(lat) };
}

} // namespace astro
} // namespace astrea

#include <astro/state/angular_elements/Geocentric.ipp>
```


