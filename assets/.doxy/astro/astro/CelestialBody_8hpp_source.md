

# File CelestialBody.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**CelestialBody.hpp**](CelestialBody_8hpp.md)

[Go to the documentation of this file](CelestialBody_8hpp.md)


```C++

#pragma once

#include <string>

#include <math/chebyshev_util.hpp>
#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frames.hpp>
#include <astro/systems/CelestialBodyParameters.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

class CelestialBody {

  public:
    CelestialBody() = default;

    virtual ~CelestialBody() = default;

    constexpr CelestialBody(const CelestialBodyParameters& data) :
        _name(data.name),
        _parent(data.parent),
        _type(data.type),
        _referenceDate(data.referenceDate),
        _mu(data.mu),
        _mass(data.mass),
        _equitorialRadius(data.equitorialRadius),
        _polarRadius(data.polarRadius),
        _crashRadius(data.crashRadius),
        _sphereOfInfluence(data.sphereOfInfluence),
        _j2(data.j2),
        _j3(data.j3),
        _axialTilt(data.axialTilt),
        _rotationRate(data.rotationRate),
        _siderealPeriod(data.siderealPeriod),
        _semimajorAxis(data.semimajorAxis),
        _eccentricity(data.eccentricity),
        _inclination(data.inclination),
        _rightAscension(data.rightAscension),
        _longitudeOfPerigee(data.longitudeOfPerigee),
        _meanLongitude(data.meanLongitude),
        _meanAnomaly(wrap_angle(_meanLongitude - _longitudeOfPerigee)),
        _semimajorAxisRate(data.semimajorAxisRate),
        _eccentricityRate(data.eccentricityRate),
        _inclinationRate(data.inclinationRate),
        _rightAscensionRate(data.rightAscensionRate),
        _longitudeOfPerigeeRate(data.longitudeOfPerigeeRate),
        _meanLongitudeRate(data.meanLongitudeRate)
    {
    }

    CelestialBody(const CelestialBody& other) = default;

    constexpr bool operator==(const CelestialBody& other) const { return _mu == other._mu; } // Probably good enough

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::UNSET; };

    constexpr const std::string& get_name() const { return _name; };

    constexpr const CelestialBodyId& get_parent() const { return _parent; };

    constexpr const CelestialBodyType& get_type() const { return _type; };

    constexpr const GravParam& get_mu() const { return _mu; };

    constexpr const Mass& get_mass() const { return _mass; };

    constexpr const Distance& get_equitorial_radius() const { return _equitorialRadius; };

    constexpr const Distance& get_polar_radius() const { return _polarRadius; };

    constexpr const Distance& get_crash_radius() const { return _crashRadius; };

    constexpr const Distance& get_sphere_of_influence() const { return _sphereOfInfluence; };

    constexpr const Unitless& get_j2() const { return _j2; };

    constexpr const Unitless& get_j3() const { return _j3; };

    constexpr const Angle& get_axial_tilt() const { return _axialTilt; };

    constexpr const AngularRate& get_rotation_rate() const { return _rotationRate; };

    constexpr const Time& get_sidereal_period() const { return _siderealPeriod; };

    constexpr const Distance& get_semimajor() const { return _semimajorAxis; };

    constexpr const Unitless& get_eccentricity() const { return _eccentricity; };

    constexpr const Angle& get_inclination() const { return _inclination; };

    constexpr const Angle& get_right_ascension() const { return _rightAscension; };

    constexpr const Angle& get_longitude_of_perigee() const { return _longitudeOfPerigee; };

    constexpr const Angle& get_mean_longitude() const { return _meanLongitude; };

    Angle get_true_anomaly() const
    {
        return wrap_angle(convert_mean_anomaly_to_true_anomaly(_meanAnomaly, _eccentricity));
    };

    constexpr const Angle& get_mean_anomaly() const { return _meanAnomaly; };

    constexpr const InterplanetaryVelocity& get_semimajor_rate() const { return _semimajorAxisRate; };

    constexpr const BodyUnitlessPerTime& get_eccentricity_rate() const { return _eccentricityRate; };

    constexpr const BodyAngularRate& get_inclination_rate() const { return _inclinationRate; };

    constexpr const BodyAngularRate& get_right_ascension_rate() const { return _rightAscensionRate; };

    constexpr const BodyAngularRate& get_longitude_of_perigee_rate() const { return _longitudeOfPerigeeRate; };

    constexpr const BodyAngularRate& get_mean_longitude_rate() const { return _meanLongitudeRate; };

    virtual Density find_atmospheric_density(const Date& date, const Distance& altitude) const;

    Keplerian get_keplerian_elements_at(const Date& date) const;

    virtual CartesianVector<Distance, frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

  protected:
    std::string _name;           
    CelestialBodyId _parent;     
    CelestialBodyType _type;     
    Date _referenceDate;         
    GravParam _mu;               
    GravParam _parentMu;         
    Mass _mass;                  
    Distance _equitorialRadius;  
    Distance _polarRadius;       
    Distance _crashRadius;       
    Distance _sphereOfInfluence; 

    Unitless _j2;              
    Unitless _j3;              
    Angle _axialTilt;          
    AngularRate _rotationRate; 
    Time _siderealPeriod;      

    Distance _semimajorAxis;   
    Unitless _eccentricity;    
    Angle _inclination;        
    Angle _rightAscension;     
    Angle _longitudeOfPerigee; 
    Angle _meanLongitude;      
    Angle _trueAnomaly;        
    Angle _meanAnomaly;        

    // These rates need to stay in rate/JC to avoid numerical issues
    InterplanetaryVelocity _semimajorAxisRate; 
    BodyUnitlessPerTime _eccentricityRate;     
    BodyAngularRate _inclinationRate;          
    BodyAngularRate _rightAscensionRate;       
    BodyAngularRate _longitudeOfPerigeeRate;   
    BodyAngularRate _meanLongitudeRate;        

    static constexpr double _COEFF_ZERO_FACTOR = 1.0;

    template <typename Table_T, typename Frame_T>
    CartesianVector<Distance, Frame_T> get_position_at_impl(const Date& date) const
    {
        using mp_units::si::unit_symbols::km;

        // Evaluate Chebyshev polynomials
        const auto [xInterp, yInterp, zInterp] = get_chebyshev_table_coefficients<Table_T>(date);
        const double mjd                       = (date.mjd() - Date(J2000).mjd()).count();

        Distance x = math::evaluate_chebyshev_polynomial(mjd, xInterp, _COEFF_ZERO_FACTOR) * km;
        Distance y = math::evaluate_chebyshev_polynomial(mjd, yInterp, _COEFF_ZERO_FACTOR) * km;
        Distance z = math::evaluate_chebyshev_polynomial(mjd, zInterp, _COEFF_ZERO_FACTOR) * km;

        return CartesianVector<Distance, Frame_T>(x, y, z);
    }

    template <typename Table_T, typename Frame_T>
    CartesianVector<Velocity, Frame_T> get_velocity_at_impl(const Date& date) const
    {
        using mp_units::non_si::day;
        using mp_units::si::unit_symbols::km;

        // Evaluate Chebyshev polynomials
        const auto [xInterp, yInterp, zInterp] = get_chebyshev_table_coefficients<Table_T>(date);
        const double mjd                       = (date.mjd() - Date(J2000).mjd()).count();

        Velocity vx = math::evaluate_chebyshev_derivative(mjd, xInterp, _COEFF_ZERO_FACTOR) * km / day;
        Velocity vy = math::evaluate_chebyshev_derivative(mjd, yInterp, _COEFF_ZERO_FACTOR) * km / day;
        Velocity vz = math::evaluate_chebyshev_derivative(mjd, zInterp, _COEFF_ZERO_FACTOR) * km / day;

        return CartesianVector<Velocity, Frame_T>(vx, vy, vz);
    }

    template <typename Table_T>
    const auto get_chebyshev_table_coefficients(const Date& date) const
    {
        static constexpr Time timePerCoefficient = Table_T::TIME_PER_COEFFICIENT;

        // Extract components
        const std::size_t ind = Table_T::get_index(date, timePerCoefficient);
        const auto& xInterp   = Table_T::X_INTERP[ind];
        const auto& yInterp   = Table_T::Y_INTERP[ind];
        const auto& zInterp   = Table_T::Z_INTERP[ind];

        return std::make_tuple(xInterp, yInterp, zInterp);
    }

    using CoefficientPack = std::tuple<
        mp_units::quantity<mp_units::angular::unit_symbols::rad / (JulianCentury * JulianCentury)>,
        mp_units::quantity<mp_units::angular::unit_symbols::rad>,
        mp_units::quantity<mp_units::angular::unit_symbols::rad>,
        mp_units::quantity<mp_units::angular::unit_symbols::rad / JulianCentury>>;

    virtual constexpr CoefficientPack get_linear_expansion_coefficients() const
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(0.0 * rad / (JulianCentury * JulianCentury), 0.0 * rad, 0.0 * rad, 0.0 * rad / JulianCentury);
    }
};

using CelestialBodyUniquePtr = std::unique_ptr<CelestialBody>;

} // namespace astro
} // namespace astrea

template <>
struct std::hash<astrea::astro::CelestialBody> {
    std::size_t operator()(astrea::astro::CelestialBody const& body) const noexcept
    {

        std::size_t h = std::hash<double>{}(body.get_mu().numerical_value_in(
            mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)
        ));
        h ^= (std::hash<double>{}(body.get_mass().numerical_value_in((mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg))) << 1);
        /* // These are probably overkill
        h ^= (std::hash<double>{}(body.get_equitorial_radius()) << 1);
        h ^= (std::hash<double>{}(body.get_polar_radius()) << 1);
        h ^= (std::hash<double>{}(body.get_crash_radius()) << 1);
        h ^= (std::hash<double>{}(body.get_sphere_of_influence()) << 1);
        h ^= (std::hash<double>{}(body.get_j2()) << 1);
        h ^= (std::hash<double>{}(body.get_j3()) << 1);
        h ^= (std::hash<double>{}(body.get_axial_tilt()) << 1);
        h ^= (std::hash<double>{}(body.get_rotation_rate()) << 1);
        h ^= (std::hash<double>{}(body.get_sidereal_period()) << 1);
        h ^= (std::hash<double>{}(body.get_semimajor()) << 1);
        h ^= (std::hash<double>{}(body.get_eccentricity()) << 1);
        h ^= (std::hash<double>{}(body.get_inclination()) << 1);
        h ^= (std::hash<double>{}(body.get_right_ascension()) << 1);
        h ^= (std::hash<double>{}(body.get_longitude_of_perigee()) << 1);
        h ^= (std::hash<double>{}(body.get_mean_longitude()) << 1);
        */

        return h;
    }
};
```


