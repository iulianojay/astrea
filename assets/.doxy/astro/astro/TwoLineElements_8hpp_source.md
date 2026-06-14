

# File TwoLineElements.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**orbital\_data\_formats**](dir_dce17fbadb9e43f0864b0608daddb5e0.md) **>** [**TwoLineElements.hpp**](TwoLineElements_8hpp.md)

[Go to the documentation of this file](TwoLineElements_8hpp.md)


```C++

#pragma once

#include <array>
#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

class TwoLineElements {

    friend std::ostream& operator<<(std::ostream&, TwoLineElements const&);

    friend TwoLineElementsPartial;

  public:
    TwoLineElements() = default;

    TwoLineElements(const std::array<std::string, 3> rawTle);

    TwoLineElements(const std::array<std::string, 2> rawTle);

    TwoLineElements(const TwoLineElements&);

    TwoLineElements(TwoLineElements&&) noexcept;

    TwoLineElements& operator=(TwoLineElements&&) noexcept;

    TwoLineElements& operator=(const TwoLineElements&);

    ~TwoLineElements() = default;

    bool operator==(const TwoLineElements& other) const;

    bool operator!=(const TwoLineElements& other) const;

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
    Keplerian<frames::earth::icrf> _elements; 

    void ctor_impl(const std::array<std::string, 2> rawTle);
};

} // namespace astro
} // namespace astrea
```


