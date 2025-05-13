// #include <fstream>
#include <memory>

#include <avro/Decoder.hh>
#include <avro/Encoder.hh>
#include <avro/Specific.hh>

// #include <avro/Compiler.hh>
// #include <avro/ValidSchema.hh>

#include <astro/astro.hpp>

namespace c {

struct cpx {
    double re;
    double im;
};

} // namespace c

namespace avro {
template <>
struct codec_traits<c::cpx> {
    static void encode(Encoder& e, const c::cpx& v)
    {
        avro::encode(e, v.re);
        avro::encode(e, v.im);
    }
    static void decode(Decoder& d, c::cpx& v)
    {
        avro::decode(d, v.re);
        avro::decode(d, v.im);
    }
};

} // namespace avro

using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

int main()
{
    // Build an output stream and an encoder
    avro::OutputStreamPtr outStream = avro::memoryOutputStream();
    avro::EncoderPtr encoder        = avro::binaryEncoder();
    encoder->init(*outStream);

    // Build out structure
    Cartesian c1(10000 * km, 0.0 * km, 0.0 * km, 10.0 * km / s, 0.0 * km / s, 0.0 * km / s);

    // Encode
    avro::encode(*encoder, c1);

    // Build an input stream and a decoder
    avro::InputStreamPtr in  = avro::memoryInputStream(*outStream);
    avro::DecoderPtr decoder = avro::binaryDecoder();
    decoder->init(*in);

    // Decode into new structure
    Cartesian c2;
    avro::decode(*decoder, c2);

    // Print
    std::cout << c2 << std::endl;

    return 0;
}