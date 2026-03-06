

# File Keplerian.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**orbital\_elements**](dir_6eb62f1e639545772a8b9a71f7b1d0b7.md) **>** [**instances**](dir_2296e922a578ce2ef4a64c83384e553c.md) **>** [**Keplerian.hpp**](Keplerian_8hpp.md)

[Go to the documentation of this file](Keplerian_8hpp.md)


```C++

#pragma once

#include <iosfwd>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class Keplerian {

    friend std::ostream& operator<<(std::ostream&, Keplerian const&);
    friend class OrbitalElements;

  public:
    Keplerian(Unitless scale = 0.0 * astrea::detail::unitless) :
        _semimajor(scale * astrea::detail::distance_unit),
        _eccentricity(scale * astrea::detail::unitless),
        _inclination(scale * astrea::detail::angle_unit),
        _rightAscension(scale * astrea::detail::angle_unit),
        _argPerigee(scale * astrea::detail::angle_unit),
        _trueAnomaly(scale * astrea::detail::angle_unit)
    {
    }

    Keplerian(const Distance& semimajor, const Unitless& eccentricity, const Angle& inclination, const Angle& rightAscension, const Angle& argPerigee, const Angle& trueAnomaly) :
        _semimajor(semimajor),
        _eccentricity(eccentricity),
        _inclination(inclination),
        _rightAscension(rightAscension),
        _argPerigee(argPerigee),
        _trueAnomaly(trueAnomaly)
    {
    }

    Keplerian(const Keplerian& elements, const GravParam& mu) :
        Keplerian(elements)
    {
    }

    Keplerian(const OrbitalElements& elements, const GravParam& mu);

    Keplerian(const Cartesian& elements, const GravParam& mu);

    Keplerian(const Equinoctial& elements, const GravParam& mu);

    static Keplerian LEO();

    static Keplerian LMEO();

    static Keplerian GPS();

    static Keplerian HMEO();

    static Keplerian GEO();

    Keplerian(const Keplerian&);

    Keplerian(Keplerian&&) noexcept;

    Keplerian& operator=(Keplerian&&) noexcept;

    Keplerian& operator=(const Keplerian&);

    ~Keplerian() = default;

    bool operator==(const Keplerian& other) const;

    bool operator!=(const Keplerian& other) const;

    Keplerian operator+(const Keplerian& other) const;

    Keplerian& operator+=(const Keplerian& other);

    Keplerian operator-(const Keplerian& other) const;

    Keplerian& operator-=(const Keplerian& other);

    Keplerian operator*(const Unitless& multiplier) const;

    Keplerian& operator*=(const Unitless& multiplier);

    KeplerianPartial operator/(const Time& time) const;

    Keplerian operator/(const Unitless& divisor) const;

    Keplerian& operator/=(const Unitless& divisor);

    void set_semimajor(const Distance& semimajor) { _semimajor = semimajor; }

    void set_eccentricity(const Unitless& eccentricity) { _eccentricity = eccentricity; }

    void set_inclination(const Angle& inclination) { _inclination = inclination; }

    void set_right_ascension(const Angle& rightAscension) { _rightAscension = rightAscension; }

    void set_argument_of_perigee(const Angle& argPerigee) { _argPerigee = argPerigee; }

    void set_true_anomaly(const Angle& trueAnomaly) { _trueAnomaly = trueAnomaly; }

    const Distance& get_semimajor() const { return _semimajor; }

    const Unitless& get_eccentricity() const { return _eccentricity; }

    const Angle& get_inclination() const { return _inclination; }

    const Angle& get_right_ascension() const { return _rightAscension; }

    const Angle& get_argument_of_perigee() const { return _argPerigee; }

    const Angle& get_true_anomaly() const { return _trueAnomaly; }

    Angle get_mean_anomaly() const;

    MeanMotion get_mean_motion(const GravParam& mu) const;

    Keplerian interpolate(const Time& thisTime, const Time& otherTime, const Keplerian& other, const GravParam& mu, const Time& targetTime) const;

    std::vector<Unitless> force_to_vector() const;

  private:
    Distance _semimajor;    
    Unitless _eccentricity; 
    Angle _inclination;     
    Angle _rightAscension;  
    Angle _argPerigee;      
    Angle _trueAnomaly;     

    void wrap_angles();

    Angle interpolate_angle(const std::array<Time, 2>& times, const std::array<Angle, 2>& angles, const Time& targetTime) const;


    static Keplerian from_vector(const std::vector<Unitless>& vec);
};

class KeplerianPartial {

    friend std::ostream& operator<<(std::ostream&, KeplerianPartial const&);

  public:
    KeplerianPartial() = default;

    KeplerianPartial(
        const Velocity& semimajorPartial,
        const UnitlessPerTime& eccentricityPartial,
        const AngularRate& inclinationPartial,
        const AngularRate& rightAscensionPartial,
        const AngularRate& argPerigeePartial,
        const AngularRate& trueAnomalyPartial
    ) :
        _semimajorPartial(semimajorPartial),
        _eccentricityPartial(eccentricityPartial),
        _inclinationPartial(inclinationPartial),
        _rightAscensionPartial(rightAscensionPartial),
        _argPerigeePartial(argPerigeePartial),
        _trueAnomalyPartial(trueAnomalyPartial)
    {
    }

    Keplerian operator*(const Time& time) const;

    std::vector<Unitless> force_to_vector() const;

  private:
    Velocity _semimajorPartial;           
    UnitlessPerTime _eccentricityPartial; 
    AngularRate _inclinationPartial;      
    AngularRate _rightAscensionPartial;   
    AngularRate _argPerigeePartial;       
    AngularRate _trueAnomalyPartial;      
};

} // namespace astro
} // namespace astrea
```


