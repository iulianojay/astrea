#pragma once

// avro
#include <avro/Decoder.hh>
#include <avro/Encoder.hh>
#include <avro/Specific.hh>

// mp-units
#include <mp-units/core.h>

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