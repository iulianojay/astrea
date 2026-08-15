

# File Cylindrical.hpp

[**File List**](files.md) **>** [**angular\_elements**](dir_8f2f7499654791f4fc4240f01fb9baf6.md) **>** [**Cylindrical.hpp**](Cylindrical_8hpp.md)

[Go to the documentation of this file](Cylindrical_8hpp.md)


```C++

#pragma once

#include <iosfwd>

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>

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
class Cylindrical {

    template <IsCelestialBody auto body>
    friend std::ostream& operator<<(std::ostream&, Cylindrical<body> const&);

  public:
    static constexpr auto body          = _body_; 
    static constexpr auto _icrf_frame_  = make_frame(_body_, axes::icrf); 
    static constexpr auto _fixed_frame_ = get_body_fixed_frame<_body_>(); 

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

    template <auto _frame_>
        requires(equivalent(_frame_, make_frame(_body_, axes::icrf)))
    Cylindrical(const RadiusVector<_frame_>& r, const Date& date);

    Cylindrical(const RadiusVector<_fixed_frame_>& r);

    template <IsOrbitalElements T>
    Cylindrical(const T& elements, const Date& date)
    {
        static const GravParam mu = get_mu<_body_>();
        *this = Cylindrical<_body_>(Cartesian<T::frame>(elements, mu).get_position().template in_frame<_fixed_frame_>(date));
    }

    Cylindrical(const Cylindrical<_body_>&);

    Cylindrical(Cylindrical<_body_>&&) noexcept;

    Cylindrical<_body_>& operator=(Cylindrical<_body_>&&) noexcept;

    Cylindrical<_body_>& operator=(const Cylindrical<_body_>&);

    ~Cylindrical() = default;

    bool operator==(const Cylindrical<_body_>& other) const;
    bool operator!=(const Cylindrical<_body_>& other) const;

    Cylindrical<_body_> operator+(const Cylindrical<_body_>& other) const;
    Cylindrical<_body_>& operator+=(const Cylindrical<_body_>& other);
    Cylindrical<_body_> operator-(const Cylindrical<_body_>& other) const;
    Cylindrical<_body_>& operator-=(const Cylindrical<_body_>& other);
    Cylindrical<_body_> operator*(const Unitless& multiplier) const;
    Cylindrical<_body_>& operator*=(const Unitless& multiplier);
    std::vector<Unitless> operator/(const Cylindrical<_body_>& other) const;
    Cylindrical<_body_> operator/(const Unitless& divisor) const;
    Cylindrical<_body_>& operator/=(const Unitless& divisor);

    RadiusVector<_fixed_frame_> get_position() const;

    RadiusVector<_icrf_frame_> get_position(const Date& date) const;

    const Angle& get_azimuth() const { return _azimuth; }
    const Distance& get_elevation() const { return _elevation; }
    const Distance& get_range() const { return _range; }

    Cylindrical<_body_>
        interpolate(const Time& thisTime, const Time& otherTime, const Cylindrical<_body_>& other, const Time& targetTime) const;

  private:
    Distance _range;     
    Angle _azimuth;      
    Distance _elevation; 
};


template <IsFrame auto _frame_>
    requires(IsBodyFixedFrame<decltype(_frame_)>)
std::tuple<Distance, Angle, Distance> convert_body_fixed_to_cylindrical(const RadiusVector<_frame_>& rFixed)
{
    using mp_units::si::acos;
    using mp_units::si::unit_symbols::km;

    const Distance range     = rFixed.norm();
    const Distance elevation = rFixed.get_z();
    Angle azimuth = acos(rFixed.get_x() / sqrt(rFixed.get_x() * rFixed.get_x() + rFixed.get_y() * rFixed.get_y()));
    if (rFixed.get_y() < 0.0 * km) { azimuth = -azimuth; }
    return { range, azimuth, elevation };
}


template <IsFrame auto _frame_>
    requires(IsBodyFixedFrame<decltype(_frame_)>)
RadiusVector<_frame_> convert_cylindrical_to_body_fixed(const Distance& range, const Angle& azimuth, const Distance& elevation)
{
    using mp_units::si::cos;
    using mp_units::si::sin;

    return RadiusVector<_frame_>(range * cos(azimuth), range * sin(azimuth), elevation);
}

} // namespace astro
} // namespace astrea


#include <astro/state/angular_elements/Cylindrical.ipp>
```


