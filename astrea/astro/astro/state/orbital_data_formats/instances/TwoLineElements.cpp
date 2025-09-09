#include <astro/state/orbital_data_formats/instances/TwoLineElements.hpp>

#include <cmath>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <math/interpolation.hpp>
#include <utilities/string_util.hpp>

#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astrea {
namespace astro {

TwoLineElements::TwoLineElements(const std::array<std::string, 3> rawTle, const AstrodynamicsSystem& sys) :
    _rawTLE({ rawTle[1], rawTle[2] })
{
    ctor_impl({ rawTle[1], rawTle[2] }, sys);
    _name = utilities::trim(rawTle[0]);
}

TwoLineElements::TwoLineElements(const std::array<std::string, 2> rawTle, const AstrodynamicsSystem& sys) :
    _rawTLE(rawTle)
{
    ctor_impl(rawTle, sys);
    _name = "Unnamed";
}

void TwoLineElements::ctor_impl(const std::array<std::string, 2> rawTle, const AstrodynamicsSystem& sys)
{
    // Parse the TLE lines
    if (rawTle[0].size() != 69) {
        throw std::invalid_argument(
            "TLE lines must be exactly 69 characters long. First line was " + std::to_string(rawTle[0].size()) + " characters."
        );
    }
    else if (rawTle[1].size() != 69) {
        throw std::invalid_argument(
            "TLE lines must be exactly 69 characters long. Second line was " + std::to_string(rawTle[1].size()) + " characters."
        );
    }

    // Line 1
    _catalogueNumber = std::stoi(rawTle[0].substr(2, 5));
    _classification  = utilities::trim(rawTle[0].substr(7, 1));
    _launchYear      = utilities::trim(rawTle[0].substr(9, 2));
    _launchNumber    = utilities::trim(rawTle[0].substr(11, 3));
    _launchPiece     = utilities::trim(rawTle[0].substr(14, 3));

    const unsigned yearInt      = std::stoi(rawTle[0].substr(18, 2));
    const std::string epochYear = yearInt < 50 ? "20" + rawTle[0].substr(18, 2) : "19" + rawTle[0].substr(18, 2);
    const double epochDay       = std::stod(rawTle[0].substr(20, 12));
    const double epochHour      = (epochDay - std::floor(epochDay)) * 24.0;
    const double epochMinute    = (epochHour - std::floor(epochHour)) * 60.0;
    const double epochSecond    = (epochMinute - std::floor(epochMinute)) * 60.0;
    const std::string epochStr  = epochYear + "-" + std::to_string(static_cast<int>(std::floor(epochDay))) + " " +
                                 std::to_string(static_cast<int>(std::floor(epochHour))) + ":" +
                                 std::to_string(static_cast<int>(std::floor(epochMinute))) + ":" +
                                 std::to_string(static_cast<int>(std::floor(epochSecond)));
    _epoch = Date(epochStr, "%Y-%j %H:%M:%S");

    _meanMotion1st = std::stod(rawTle[0].substr(33, 10)) * one / pow<2>(si::day);

    std::string meanMotion2ndStr = rawTle[0].substr(44, 8);
    int nDecimalPlaces           = std::stoi(meanMotion2ndStr.substr(6)) - 5;
    _meanMotion2nd               = std::stod(meanMotion2ndStr) * std::pow(10.0, nDecimalPlaces) * one / pow<3>(si::day);

    const std::string ballisticCoefficientStr = rawTle[0].substr(53, 8);
    nDecimalPlaces                            = std::stoi(ballisticCoefficientStr.substr(6)) - 5;
    _ballisticCoefficient = std::stod(ballisticCoefficientStr.substr(0, 6)) * std::pow(10.0, nDecimalPlaces) * one / EarthRadii;

    _ephemerisType = std::stoi(rawTle[0].substr(62, 1));
    _elementSetNo  = std::stoi(rawTle[0].substr(64, 4));
    _checkSum1     = std::stoi(rawTle[0].substr(68, 1));

    // Line 2
    _meanMotion = std::stod(rawTle[1].substr(52, 11)) * one / si::day;
    _revNumber  = std::stoi(rawTle[1].substr(63, 5));
    _checkSum2  = std::stoi(rawTle[1].substr(68, 1));

    const Distance semimajor = pow<1, 3>(sys.get_center()->get_mu() / (_meanMotion.in(one / s) * _meanMotion.in(one / s)));
    const Angle inclination       = std::stod(rawTle[1].substr(8, 8)) * deg;
    const Angle rightAscension    = std::stod(rawTle[1].substr(17, 8)) * deg;
    const Unitless eccentricity   = std::stod("." + rawTle[1].substr(26, 7)) * one;
    const Angle argumentOfPerigee = std::stod(rawTle[1].substr(34, 8)) * deg;
    const Angle meanAnomaly       = std::stod(rawTle[1].substr(43, 8)) * deg;

    const Angle trueAnomaly = convert_mean_anomaly_to_true_anomaly(meanAnomaly, eccentricity);

    _elements = Keplerian(semimajor, eccentricity, inclination, rightAscension, argumentOfPerigee, trueAnomaly);
}

// Copy constructor
TwoLineElements::TwoLineElements(const TwoLineElements& other) :
    _rawTLE(other._rawTLE),
    _catalogueNumber(other._catalogueNumber),
    _classification(other._classification),
    _launchYear(other._launchYear),
    _launchNumber(other._launchNumber),
    _launchPiece(other._launchPiece),
    _epoch(other._epoch),
    _meanMotion(other._meanMotion),
    _meanMotion1st(other._meanMotion1st),
    _meanMotion2nd(other._meanMotion2nd),
    _ballisticCoefficient(other._ballisticCoefficient),
    _ephemerisType(other._ephemerisType),
    _checkSum1(other._checkSum1),
    _revNumber(other._revNumber),
    _checkSum2(other._checkSum2),
    _elements(other._elements)
{
}

// Move constructor
TwoLineElements::TwoLineElements(TwoLineElements&& other) noexcept :
    _rawTLE(std::move(other._rawTLE)),
    _catalogueNumber(std::move(other._catalogueNumber)),
    _classification(std::move(other._classification)),
    _launchYear(std::move(other._launchYear)),
    _launchNumber(std::move(other._launchNumber)),
    _launchPiece(std::move(other._launchPiece)),
    _epoch(std::move(other._epoch)),
    _meanMotion(std::move(other._meanMotion)),
    _meanMotion1st(std::move(other._meanMotion1st)),
    _meanMotion2nd(std::move(other._meanMotion2nd)),
    _ballisticCoefficient(std::move(other._ballisticCoefficient)),
    _ephemerisType(std::move(other._ephemerisType)),
    _checkSum1(std::move(other._checkSum1)),
    _revNumber(std::move(other._revNumber)),
    _checkSum2(std::move(other._checkSum2)),
    _elements(std::move(other._elements))
{
}

// Move assignment operator
TwoLineElements& TwoLineElements::operator=(TwoLineElements&& other) noexcept
{
    if (this != &other) {
        _rawTLE               = std::move(other._rawTLE);
        _catalogueNumber      = std::move(other._catalogueNumber);
        _classification       = std::move(other._classification);
        _launchYear           = std::move(other._launchYear);
        _launchNumber         = std::move(other._launchNumber);
        _launchPiece          = std::move(other._launchPiece);
        _epoch                = std::move(other._epoch);
        _meanMotion           = std::move(other._meanMotion);
        _meanMotion1st        = std::move(other._meanMotion1st);
        _meanMotion2nd        = std::move(other._meanMotion2nd);
        _ballisticCoefficient = std::move(other._ballisticCoefficient);
        _ephemerisType        = std::move(other._ephemerisType);
        _checkSum1            = std::move(other._checkSum1);
        _revNumber            = std::move(other._revNumber);
        _checkSum2            = std::move(other._checkSum2);
        _elements             = std::move(other._elements);
    }
    return *this;
}

// Copy assignment operator
TwoLineElements& TwoLineElements::operator=(const TwoLineElements& other) { return *this = TwoLineElements(other); }

// Comparitors operators
bool TwoLineElements::operator==(const TwoLineElements& other) const
{
    return _catalogueNumber == other._catalogueNumber && _classification == other._classification &&
           _launchYear == other._launchYear && _launchNumber == other._launchNumber && _launchPiece == other._launchPiece &&
           _epoch == other._epoch && _meanMotion == other._meanMotion && _meanMotion1st == other._meanMotion1st &&
           _meanMotion2nd == other._meanMotion2nd && _ballisticCoefficient == other._ballisticCoefficient &&
           _ephemerisType == other._ephemerisType && _checkSum1 == other._checkSum1 && _revNumber == other._revNumber &&
           _checkSum2 == other._checkSum2 && _elements == other._elements;
}

bool TwoLineElements::operator!=(const TwoLineElements& other) const { return !(*this == other); }


std::ostream& operator<<(std::ostream& os, TwoLineElements const& elements)
{
    os << "[";
    os << elements.get_1st_line() << std::endl;
    os << " " << elements.get_2nd_line();
    os << "] (Tle)";
    return os;
}

} // namespace astro
} // namespace astrea