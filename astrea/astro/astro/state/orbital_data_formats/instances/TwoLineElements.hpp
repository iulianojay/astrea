#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <variant>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

using MeanMotion           = mp_units::quantity<mp_units::one / mp_units::non_si::day>;
using MeanMotion1stDer     = mp_units::quantity<mp_units::one / mp_units::pow<2>(mp_units::non_si::day)>;
using MeanMotion2ndDer     = mp_units::quantity<mp_units::one / mp_units::pow<3>(mp_units::non_si::day)>;
using BallisticCoefficient = mp_units::quantity<mp_units::one / EarthRadii>;

class TwoLineElements {

    friend std::ostream& operator<<(std::ostream&, TwoLineElements const&);
    friend TwoLineElementsPartial;

  public:
    TwoLineElements() = default;
    TwoLineElements(const std::array<std::string, 3> rawTle, const AstrodynamicsSystem& sys);
    TwoLineElements(const std::array<std::string, 2> rawTle, const AstrodynamicsSystem& sys);

    // Copy constructor
    TwoLineElements(const TwoLineElements&);

    // Move constructor
    TwoLineElements(TwoLineElements&&) noexcept;

    // Move assignment operator
    TwoLineElements& operator=(TwoLineElements&&) noexcept;

    // Copy assignment operator
    TwoLineElements& operator=(const TwoLineElements&);

    ~TwoLineElements() = default;

    // Comparitors operators
    bool operator==(const TwoLineElements& other) const;
    bool operator!=(const TwoLineElements& other) const;

    // Element access
    std::array<std::string, 2> get_raw_tle() const { return _rawTLE; }
    std::string get_1st_line() const { return _rawTLE[0]; }
    std::string get_2nd_line() const { return _rawTLE[1]; }

    std::string get_name() const { return _name; }
    unsigned get_catalogue_number() const { return _catalogueNumber; }
    std::string get_classification() const { return _classification; }
    std::string get_launch_year() const { return _launchYear; }
    std::string get_launch_number() const { return _launchNumber; }
    std::string get_launch_piece() const { return _launchPiece; }

    Date get_epoch() const { return _epoch; }

    MeanMotion1stDer get_mean_motion_1st_derivative() const { return _meanMotion1st; }
    MeanMotion2ndDer get_mean_motion_2nd_derivative() const { return _meanMotion2nd; }

    BallisticCoefficient get_ballistic_coefficient() const { return _ballisticCoefficient; }

    std::size_t get_ephemeris_type() const { return _ephemerisType; }
    std::size_t get_element_set_number() const { return _elementSetNo; }
    std::size_t get_check_sum1() const { return _checkSum1; }

    Distance get_semimajor() const { return _elements.get_semimajor(); }
    Unitless get_eccentricity() const { return _elements.get_eccentricity(); }
    Angle get_inclination() const { return _elements.get_inclination(); }
    Angle get_right_ascension() const { return _elements.get_right_ascension(); }
    Angle get_argument_of_perigee() const { return _elements.get_argument_of_perigee(); }
    Angle get_true_anomaly() const { return _elements.get_true_anomaly(); }

    MeanMotion get_mean_motion() const { return _meanMotion; }

    unsigned get_rev_number() const { return _revNumber; }
    std::size_t get_check_sum2() const { return _checkSum2; }

  private:
    // Input data
    std::array<std::string, 2> _rawTLE;

    // TLE-specific inputs
    std::string _name;
    unsigned _catalogueNumber;
    std::string _classification;
    std::string _launchYear;
    std::string _launchNumber;
    std::string _launchPiece;

    Date _epoch;

    MeanMotion _meanMotion;
    MeanMotion1stDer _meanMotion1st;
    MeanMotion2ndDer _meanMotion2nd;

    BallisticCoefficient _ballisticCoefficient;

    size_t _ephemerisType;
    size_t _elementSetNo;
    size_t _checkSum1;
    unsigned _revNumber;
    size_t _checkSum2;

    // Bundle elements into Keplerian set
    Keplerian _elements;

    void ctor_impl(const std::array<std::string, 2> rawTle, const AstrodynamicsSystem& sys);
};

} // namespace astro
} // namespace astrea
