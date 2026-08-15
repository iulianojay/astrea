

# File default\_property\_getters.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**default\_property\_getters.hpp**](default__property__getters_8hpp.md)

[Go to the documentation of this file](default__property__getters_8hpp.md)


```C++

#pragma once

#include <astro/frames/framework/frame_utilities.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/systems/property_getters.hpp>

namespace astrea {
namespace astro {

template <auto _body_>
inline constexpr Keplerian<get_parent_frame(_body_, axes::icrf)> get_keplerian_elements_at(Date date)
{
    using namespace mp_units;
    using namespace mp_units::si;
    using astrea::units::unit_symbols::jc;

    const Distance a   = get_semimajor<_body_>(date);
    const Unitless ecc = get_eccentricity<_body_>(date);
    const Angle inc    = get_inclination<_body_>(date);
    const Angle raan   = get_right_ascension<_body_>(date);
    const Angle w      = get_longitude_of_perigee<_body_>(date);
    const Angle L      = get_mean_longitude<_body_>(date);

    const mp_units::quantity<jc> T = get_time_since_reference_epoch<_body_>(date);
    const auto [B, C, S, F]        = get_linear_expansion_coefficients<_body_>();
    const Angle Me                 = wrap_angle(L - w + B * T * T + C * cos(F * T) + S * sin(F * T));
    const Angle argPer             = wrap_angle(w - raan);

    const Angle thetat = convert_mean_anomaly_to_true_anomaly(Me, ecc);
    return Keplerian<get_parent_frame(_body_, axes::icrf)>(a, ecc, inc, raan, argPer, thetat);
}

template <auto _body_>
inline constexpr CartesianVector<Distance, get_parent_frame(_body_, axes::icrf)> get_position_at(const Date& date)
{
    constexpr auto frame        = get_parent_frame(_body_, axes::icrf);
    const Keplerian<frame> coes = get_keplerian_elements_at<_body_>(date);
    constexpr auto parent       = get_parent(_body_);
    const GravParam mu          = get_mu<parent>();
    return Cartesian<frame>(coes, mu).get_position();
}

template <auto _body_>
inline constexpr CartesianVector<Velocity, get_parent_frame(_body_, axes::icrf)> get_velocity_at(const Date& date)
{
    constexpr auto frame        = get_parent_frame(_body_, axes::icrf);
    const Keplerian<frame> coes = get_keplerian_elements_at<_body_>(date);
    constexpr auto parent       = get_parent(_body_);
    const GravParam mu          = get_mu<parent>();
    return Cartesian<frame>(coes, mu).get_velocity();
}

template <auto _body_>
inline constexpr CartesianVector<Acceleration, get_parent_frame(_body_, axes::icrf)> get_acceleration_at(const Date& date)
{
    constexpr auto frame                     = get_parent_frame(_body_, axes::icrf);
    const Keplerian<frame> coes              = get_keplerian_elements_at<_body_>(date);
    constexpr auto parent                    = get_parent(_body_);
    const GravParam mu                       = get_mu<parent>();
    const CartesianVector<Distance, frame> r = Cartesian<frame>(coes, mu).get_position();
    return -mu * r / pow<3>(r.norm());
}

} // namespace astro
} // namespace astrea
```


