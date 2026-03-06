

# File OblatenessForce.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**OblatenessForce.hpp**](OblatenessForce_8hpp.md)

[Go to the documentation of this file](OblatenessForce_8hpp.md)


```C++

#pragma once

#include <array>
#include <memory>
#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/Force.hpp>

namespace astrea {
namespace astro {

class LegendreCache {
  public:
    LegendreCache() = default;

    ~LegendreCache() = default;

    LegendreCache(const AstrodynamicsSystem& sys, const std::size_t& degree, const std::size_t& order);

    Unitless get_cosine_coefficient(const std::size_t& n, const std::size_t& m) const;

    Unitless get_sine_coefficient(const std::size_t& n, const std::size_t& m) const;

    // /**
    //  * @brief Computes the Legendre polynomial coefficients for the oblateness force.
    //  *
    //  * @param x Value at which to evaluate the Legendre polynomial
    //  * @param degree Degree of the spherical harmonics
    //  * @param order Order of the spherical harmonics
    //  */
    // std::vector<std::vector<Unitless>>
    //     get_legendre_coefficients(const std::size_t& degree, const std::size_t& order, const Unitless& x) const;

    Unitless get_normalizing_coefficient(const std::size_t& n, const std::size_t& m) const;

  private:
    std::vector<std::vector<Unitless>> _normalizingCoefficients{}; 
    std::vector<std::vector<Unitless>> _C{};                       
    std::vector<std::vector<Unitless>> _S{};                       

    void size_vectors(const std::size_t& degree, const std::size_t& order);

    void ingest_legendre_coefficient_file(const AstrodynamicsSystem& sys, const std::size_t& degree, const std::size_t& order);
};

class OblatenessForce : public Force {
  public:
    ~OblatenessForce() = default;

    OblatenessForce(const AstrodynamicsSystem& sys, const std::size_t& N = 2, const std::size_t& M = 0);

    CartesianVector<Acceleration, frames::earth::icrf> compute_force(const State& state, const Vehicle& vehicle) const;

  private:
    const std::size_t _degree;          
    const std::size_t _order;           
    const AstrodynamicsSystem* _sys;    
    const LegendreCache _legendreCache; 
};

} // namespace astro
} // namespace astrea
```


