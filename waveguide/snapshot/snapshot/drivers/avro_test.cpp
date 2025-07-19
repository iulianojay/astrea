#include <fstream>
#include <memory>

#include <avro/Compiler.hh>
#include <avro/DataFile.hh>
#include <avro/Decoder.hh>
#include <avro/Encoder.hh>
#include <avro/Generic.hh>
#include <avro/Specific.hh>
#include <avro/Stream.hh>
#include <avro/ValidSchema.hh>

#include <astro/astro.hpp>

using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

void ex1();
void ex2();
void ex3();

int main()
{
    ex1();
    ex2();
    // ex3(); // Does not work

    return 0;
}

void ex1()
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
    avro::InputStreamPtr inStream = avro::memoryInputStream(*outStream);
    avro::DecoderPtr decoder      = avro::binaryDecoder();
    decoder->init(*inStream);

    // Decode into new structure
    Cartesian c2;
    avro::decode(*decoder, c2);

    // Print
    std::cout << c2 << std::endl;
}


void ex2()
{
    std::ifstream infileStream("/home/jay/projects/waveguide/waveguide/snapshot/database/cartesian.json");

    avro::ValidSchema cartesianSchema;
    avro::compileJsonSchema(infileStream, cartesianSchema);

    // Build an output stream and an encoder
    avro::OutputStreamPtr outStream = avro::memoryOutputStream();
    avro::EncoderPtr encoder        = avro::validatingEncoder(cartesianSchema, avro::binaryEncoder());
    encoder->init(*outStream);

    // Build out structure
    Cartesian c1(10000 * km, 0.0 * km, 0.0 * km, 10.0 * km / s, 0.0 * km / s, 0.0 * km / s);

    // Encode
    avro::encode(*encoder, c1);

    // Build an input stream and a decoder
    avro::InputStreamPtr inStream = avro::memoryInputStream(*outStream);
    avro::DecoderPtr decoder      = avro::validatingDecoder(cartesianSchema, avro::binaryDecoder());
    decoder->init(*inStream);

    // Decode into new structure
    Cartesian c2;
    avro::decode(*decoder, c2);

    // Print
    std::cout << c2 << std::endl;
}

avro::ValidSchema loadSchema(const std::string& filename);

avro::ValidSchema loadSchema(const std::string& filename)
{
    std::ifstream ifs(filename);
    avro::ValidSchema result;
    avro::compileJsonSchema(ifs, result);
    return result;
}

void ex3()
{
    // Load schema
    std::string schemaFile = "./waveguide/snapshot/database/cartesian.json";
    std::string outFile    = "./waveguide/snapshot/database/cartesian.avro";

    avro::ValidSchema cartesianSchema = loadSchema(schemaFile);

    // Write to file
    avro::DataFileWriter<Cartesian> dataFileWriter(outFile.c_str(), cartesianSchema);
    Cartesian c1;
    for (double i = 0.0; i < 100.0; i++) {
        c1 = Cartesian((10000.0 + i) * km, i * km, i * km, (1.0 + i / 100.0) * km / s, i / 100.0 * km / s, i / 100.0 * km / s);
        dataFileWriter.write(c1);
    }
    dataFileWriter.close();

    // Read from file
    avro::DataFileReader<Cartesian> dataFileReader(outFile.c_str(), cartesianSchema);
    Cartesian c2;
    while (dataFileReader.read(c2)) {
        std::cout << c2 << std::endl;
    }
}