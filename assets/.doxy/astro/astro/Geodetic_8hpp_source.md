

# File Geodetic.hpp

[**File List**](files.md) **>** [**angular\_elements**](dir_8f2f7499654791f4fc4240f01fb9baf6.md) **>** [**Geodetic.hpp**](Geodetic_8hpp.md)

[Go to the documentation of this file](Geodetic_8hpp.md)


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
class Geodetic {

    template <IsCelestialBody auto body>
    friend std::ostream& operator<<(std::ostream&, Geodetic<body> const&);

  public:
    static constexpr auto body          = _body_; 
    static constexpr auto _icrf_frame_  = make_frame(_body_, axes::icrf); 
    static constexpr auto _fixed_frame_ = get_body_fixed_frame<_body_>(); 

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

    template <auto _frame_>
        requires(equivalent(_frame_, make_frame(_body_, axes::icrf)))
    Geodetic(const RadiusVector<_frame_>& r, const Date& date);

    Geodetic(const RadiusVector<_fixed_frame_>& r);

    template <IsOrbitalElements T>
    Geodetic(const T& elements, const Date& date)
    {
        static const GravParam mu = get_mu<_body_>();
        *this = Geodetic<_body_>(Cartesian<T::frame>(elements, mu).get_position().template in_frame<_fixed_frame_>(date));
    }

    Geodetic(const Geodetic<_body_>&);

    Geodetic(Geodetic<_body_>&&) noexcept;

    Geodetic& operator=(Geodetic<_body_>&&) noexcept;

    Geodetic& operator=(const Geodetic<_body_>&);

    ~Geodetic() = default;

    bool operator==(const Geodetic<_body_>& other) const;

    bool operator!=(const Geodetic<_body_>& other) const;

    Geodetic operator+(const Geodetic<_body_>& other) const;

    Geodetic& operator+=(const Geodetic<_body_>& other);

    Geodetic operator-(const Geodetic<_body_>& other) const;

    Geodetic& operator-=(const Geodetic<_body_>& other);

    Geodetic operator*(const Unitless& multiplier) const;

    Geodetic& operator*=(const Unitless& multiplier);

    std::vector<Unitless> operator/(const Geodetic<_body_>& other) const;

    Geodetic operator/(const Unitless& divisor) const;

    Geodetic& operator/=(const Unitless& divisor);

    RadiusVector<_fixed_frame_> get_position() const;

    RadiusVector<_icrf_frame_> get_position(const Date& date) const;

    const Angle& get_latitude() const { return _latitude; }

    const Angle& get_longitude() const { return _longitude; }

    const Distance& get_altitude() const { return _altitude; }

    Geodetic interpolate(const Time& thisTime, const Time& otherTime, const Geodetic<_body_>& other, const Time& targetTime) const;

  private:
    Angle _latitude;    
    Angle _longitude;   
    Distance _altitude; 
};


template <IsFrame auto frame>
    requires(IsBodyFixedFrame<decltype(frame)>)
inline std::tuple<Angle, Angle, Distance> convert_body_fixed_to_geodetic(const RadiusVector<frame>& rBodyFixed)
{
    using mp_units::abs;
    using mp_units::sqrt;
    using mp_units::si::atan2;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::mm;

    static const unsigned MAX_ITER  = 1e4;
    static const Distance MAX_ERROR = 1.0 * mm;

    const Distance& xEcef = rBodyFixed[0];
    const Distance& yEcef = rBodyFixed[1];
    const Distance& zEcef = rBodyFixed[2];

    static const Distance rEquitorial = get_equitorial_radius<decltype(frame)::origin>();
    static const Distance rPolar      = get_polar_radius<decltype(frame)::origin>();
    static const Unitless f           = (rEquitorial - rPolar) / rEquitorial;
    static const Unitless eSq         = (2.0 - f) * f;

    const auto xSqYSq = xEcef * xEcef + yEcef * yEcef;

    Distance dz  = eSq * zEcef;
    Distance err = 1.0 * km;
    Distance N   = 0.0 * km;
    unsigned ii  = 0;
    while (err > MAX_ERROR && ii < MAX_ITER) {
        const Unitless s = (zEcef + dz) / sqrt(xSqYSq + (zEcef + dz) * (zEcef + dz));
        N                = rEquitorial / sqrt(1 - eSq * s * s);
        err              = abs(dz - N * eSq * s);
        dz               = N * eSq * s;
        ++ii;
    }

    if (ii >= MAX_ITER - 1) { throw std::runtime_error("Conversion from ECEF to LLA failed to converge."); }

    const Angle longitude = atan2(yEcef, xEcef);
    const Angle latitude  = atan2(zEcef + dz, sqrt(xSqYSq));
    Distance altitude     = sqrt(xSqYSq + (zEcef + dz) * (zEcef + dz)) - N;
    if (altitude < 0.0 * km) { altitude = 0.0 * km; }

    return { latitude, longitude, altitude };
}


template <IsFrame auto frame>
    requires(IsBodyFixedFrame<decltype(frame)>)
inline constexpr RadiusVector<frame> convert_geodetic_to_body_fixed(const Angle& lat, const Angle& lon, const Distance& alt)
{
    using math::cos;
    using math::sin;
    using mp_units::sqrt;

    const Unitless sinLat = sin(lat);
    const Unitless cosLat = cos(lat);

    static constexpr Distance rEquitorial = get_equitorial_radius<decltype(frame)::origin>();
    static constexpr Distance rPolar      = get_polar_radius<decltype(frame)::origin>();
    static constexpr Unitless f           = (rEquitorial - rPolar) / rEquitorial;
    static constexpr Unitless eSq         = (2.0 - f) * f;

    const Distance N = rEquitorial / sqrt(1.0 - eSq * sinLat * sinLat);

    // Ecef coordinates
    return { (N + alt) * cosLat * cos(lon), (N + alt) * cosLat * sin(lon), ((1.0 - eSq) * N + alt) * sinLat };
}

} // namespace astro
} // namespace astrea

#include <astro/state/angular_elements/Geodetic.ipp>
```


