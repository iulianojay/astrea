#pragma once

#include <array>

// avro
#include <avro/Decoder.hh>
#include <avro/Encoder.hh>
#include <avro/Specific.hh>

// mp-units
#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

namespace astro {

namespace detail {

inline constexpr auto time_unit           = mp_units::si::unit_symbols::s;
inline constexpr auto distance_unit       = mp_units::si::unit_symbols::km;
inline constexpr auto minor_distance_unit = mp_units::si::unit_symbols::m;
inline constexpr auto angle_unit          = mp_units::angular::unit_symbols::rad;
inline constexpr auto mass_unit           = mp_units::si::unit_symbols::kg;
inline constexpr auto unitless            = mp_units::one;

} // namespace detail

inline constexpr struct JulianCentury final : mp_units::named_unit<"JulianCentury", mp_units::mag<36525> * mp_units::non_si::day> {
} JulianCentury;

} // namespace astro

namespace avro {

template <auto R, typename Rep>
struct codec_traits<mp_units::quantity<R, Rep>> {
    static void encode(Encoder& encoder, const mp_units::quantity<R, Rep>& quantity)
    {
        const Rep& value = quantity.numerical_value_ref_in(quantity.unit);
        avro::encode(encoder, value);
    }
    static void decode(Decoder& decoder, mp_units::quantity<R, Rep>& quantity)
    {
        Rep value{};
        avro::decode(decoder, value);
        quantity = mp_units::quantity<R, Rep>({ static_cast<Rep>(value), R });
    }
};

} // namespace avro