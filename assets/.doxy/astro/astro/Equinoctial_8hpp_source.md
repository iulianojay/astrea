

# File Equinoctial.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**orbital\_elements**](dir_6eb62f1e639545772a8b9a71f7b1d0b7.md) **>** [**instances**](dir_2296e922a578ce2ef4a64c83384e553c.md) **>** [**Equinoctial.hpp**](Equinoctial_8hpp.md)

[Go to the documentation of this file](Equinoctial_8hpp.md)


```C++

#pragma once

#include <iosfwd>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class Equinoctial {

    friend std::ostream& operator<<(std::ostream&, Equinoctial const&);
    friend class OrbitalElements;

  public:
    Equinoctial(Unitless scale = 0.0 * astrea::detail::unitless) :
        _semilatus(scale * astrea::detail::distance_unit),
        _f(scale * astrea::detail::unitless),
        _g(scale * astrea::detail::unitless),
        _h(scale * astrea::detail::unitless),
        _k(scale * astrea::detail::unitless),
        _trueLongitude(scale * astrea::detail::angle_unit)
    {
    }

    Equinoctial(const Distance& semilatus, const Unitless& f, const Unitless& g, const Unitless& h, const Unitless& k, const Angle& trueLongitude) :
        _semilatus(semilatus),
        _f(f),
        _g(g),
        _h(h),
        _k(k),
        _trueLongitude(trueLongitude)
    {
    }

    Equinoctial(const Equinoctial& elements, const GravParam& mu) :
        Equinoctial(elements)
    {
    }

    Equinoctial(const Keplerian& elements, const GravParam& mu);

    Equinoctial(const Cartesian& elements, const GravParam& mu);

    Equinoctial(const OrbitalElements& elements, const GravParam& mu);

    static Equinoctial LEO(const GravParam& mu);

    static Equinoctial LMEO(const GravParam& mu);

    static Equinoctial GPS(const GravParam& mu);

    static Equinoctial HMEO(const GravParam& mu);

    static Equinoctial GEO(const GravParam& mu);

    Equinoctial(const Equinoctial&);

    Equinoctial(Equinoctial&& other) noexcept;

    Equinoctial& operator=(Equinoctial&& other) noexcept;

    Equinoctial& operator=(const Equinoctial& other);

    ~Equinoctial() = default;

    bool operator==(const Equinoctial& other) const;

    bool operator!=(const Equinoctial& other) const;

    Equinoctial operator+(const Equinoctial& other) const;

    Equinoctial& operator+=(const Equinoctial& other);

    Equinoctial operator-(const Equinoctial& other) const;

    Equinoctial& operator-=(const Equinoctial& other);

    Equinoctial operator*(const Unitless& multiplier) const;

    Equinoctial& operator*=(const Unitless& multiplier);

    EquinoctialPartial operator/(const Time& time) const;

    Equinoctial operator/(const Unitless& divisor) const;

    Equinoctial& operator/=(const Unitless& divisor);

    const Distance& get_semilatus() const { return _semilatus; }

    const Unitless& get_f() const { return _f; }

    const Unitless& get_g() const { return _g; }

    const Unitless& get_h() const { return _h; }

    const Unitless& get_k() const { return _k; }

    const Angle& get_true_longitude() const { return _trueLongitude; }

    std::vector<Unitless> force_to_vector() const;

    Equinoctial interpolate(const Time& thisTime, const Time& otherTime, const Equinoctial& other, const GravParam& mu, const Time& targetTime) const;

  private:
    Distance _semilatus;  
    Unitless _f;          
    Unitless _g;          
    Unitless _h;          
    Unitless _k;          
    Angle _trueLongitude; 

    static Equinoctial from_vector(const std::vector<Unitless>& vec);
};

class EquinoctialPartial {

    friend std::ostream& operator<<(std::ostream&, EquinoctialPartial const&);

  public:
    EquinoctialPartial() = default;

    EquinoctialPartial(
        const Velocity& semilatusPartial,
        const UnitlessPerTime& fPartial,
        const UnitlessPerTime& gPartial,
        const UnitlessPerTime& hPartial,
        const UnitlessPerTime& kPartial,
        const AngularRate& trueLongitudePartial
    ) :
        _semilatusPartial(semilatusPartial),
        _fPartial(fPartial),
        _gPartial(gPartial),
        _hPartial(hPartial),
        _kPartial(kPartial),
        _trueLongitudePartial(trueLongitudePartial)
    {
    }

    Equinoctial operator*(const Time& time) const;

    std::vector<Unitless> force_to_vector() const;

  private:
    Velocity _semilatusPartial;        
    UnitlessPerTime _fPartial;         
    UnitlessPerTime _gPartial;         
    UnitlessPerTime _hPartial;         
    UnitlessPerTime _kPartial;         
    AngularRate _trueLongitudePartial; 
};

} // namespace astro
} // namespace astrea
```


