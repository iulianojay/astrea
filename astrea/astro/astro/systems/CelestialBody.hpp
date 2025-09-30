/**
 * @file CelestialBody.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the CelestialBody class, which represents a celestial body in an astrodynamics system.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>

#include <math/chebyshev_util.hpp>
#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

/**
 * @brief CelestialBody class represents a celestial body in an astrodynamics system.
 */
class CelestialBody {

  public:
    /**
     * @brief Default constructor for CelestialBody.
     */
    CelestialBody() = default;

    /**
     * @brief Default destructor for CelestialBody.
     */
    virtual ~CelestialBody() = default;

    /**
     * @brief Constructs a CelestialBody from individual parameters.
     *
     * @param name Name of the celestial body.
     * @param parent Reference to the parent planetary body.
     * @param type Type of the celestial body.
     * @param referenceDate Reference date for the celestial body data.
     * @param mu Gravitational parameter (mu) of the celestial body.
     * @param mass Mass of the celestial body.
     * @param equitorialRadius Equatorial radius of the celestial body.
     * @param polarRadius Polar radius of the celestial body.
     * @param crashRadius Crash radius of the celestial body.
     * @param sphereOfInfluence Crash radius of the celestial body.
     * @param j2 J2 gravitational coefficient of the celestial body.
     * @param j3 J3 gravitational coefficient of the celestial body.
     * @param axialTilt Axial tilt of the celestial body.
     * @param rotationRate Rotation rate of the celestial body.
     * @param siderealPeriod Sidereal period of the celestial body.
     * @param semimajorAxis Semimajor axis.
     * @param eccentricity Eccentricity.
     * @param inclination Inclination.
     * @param rightAscension Right ascension.
     * @param longitudeOfPerigee Longitude of perigee.
     * @param meanLongitude Mean longitude.
     * @param semimajorAxisRate Rate of change of the semimajor axis.
     * @param eccentricityRate Rate of change of the eccentricity.
     * @param inclinationRate Rate of change of the inclination.
     * @param rightAscensionRate Rate of change of the right ascension.
     * @param longitudeOfPerigeeRate Rate of change of the longitude of perigee.
     * @param meanLongitudeRate Rate of change of the mean longitude.
     */
    constexpr CelestialBody(
        const std::string& name,
        const CelestialBodyId& parent,
        const CelestialBodyType& type,
        const Date& referenceDate,
        const GravParam& mu,
        const Mass& mass,
        const Distance& equitorialRadius,
        const Distance& polarRadius,
        const Distance& crashRadius,
        const Distance& sphereOfInfluence,
        const Unitless& j2,
        const Unitless& j3,
        const Angle& axialTilt,
        const AngularRate& rotationRate,
        const Time& siderealPeriod,
        const Distance& semimajorAxis,
        const Unitless& eccentricity,
        const Angle& inclination,
        const Angle& rightAscension,
        const Angle& longitudeOfPerigee,
        const Angle& meanLongitude,
        const BodyVelocity& semimajorAxisRate,
        const BodyUnitlessPerTime& eccentricityRate,
        const BodyAngularRate& inclinationRate,
        const BodyAngularRate& rightAscensionRate,
        const BodyAngularRate& longitudeOfPerigeeRate,
        const BodyAngularRate& meanLongitudeRate
    ) :
        _name(name),
        _parent(parent),
        _type(type),
        _referenceDate(referenceDate),
        _mu(mu),
        _mass(mass),
        _equitorialRadius(equitorialRadius),
        _polarRadius(polarRadius),
        _crashRadius(crashRadius),
        _sphereOfInfluence(sphereOfInfluence),
        _j2(j2),
        _j3(j3),
        _axialTilt(axialTilt),
        _rotationRate(rotationRate),
        _siderealPeriod(siderealPeriod),
        _semimajorAxis(semimajorAxis),
        _eccentricity(eccentricity),
        _inclination(inclination),
        _rightAscension(rightAscension),
        _longitudeOfPerigee(longitudeOfPerigee),
        _meanLongitude(meanLongitude),
        _meanAnomaly(wrap_angle(_meanLongitude - _longitudeOfPerigee)),
        _semimajorAxisRate(semimajorAxisRate),
        _eccentricityRate(eccentricityRate),
        _inclinationRate(inclinationRate),
        _rightAscensionRate(rightAscensionRate),
        _longitudeOfPerigeeRate(longitudeOfPerigeeRate),
        _meanLongitudeRate(meanLongitudeRate)
    {
    }

    /**
     * @brief Copy constructor for CelestialBody.
     *
     * @param other The CelestialBody to copy from.
     */
    CelestialBody(const CelestialBody& other) = default;

    /**
     * @brief Equality operator for CelestialBody.
     *
     * @param other The CelestialBody to compare with.
     * @return true if the celestial bodies are equal, false otherwise.
     */
    constexpr bool operator==(const CelestialBody& other) const { return _mu == other._mu; } // Probably good enough

    /**
     * @brief Get the parent celestial body.
     *
     * @return const std::string& Reference to the name of the parent celestial body.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::UNSET; };

    /**
     * @brief Get the name of the celestial body.
     *
     * @return const std::string& Reference to the name of the celestial body.
     */
    constexpr const std::string& get_name() const { return _name; };

    /**
     * @brief Get the parent celestial body.
     *
     * @return const std::string& Reference to the name of the parent celestial body.
     */
    constexpr const CelestialBodyId& get_parent() const { return _parent; };

    /**
     * @brief Get the type of the celestial body.
     *
     * @return const CelestialBodyType& Reference to the type of the celestial body.
     */
    constexpr const CelestialBodyType& get_type() const { return _type; };

    /**
     * @brief Get the gravitational parameter (mu) of the celestial body.
     *
     * @return const GravParam& Reference to the gravitational parameter of the celestial body.
     */
    constexpr const GravParam& get_mu() const { return _mu; };

    /**
     * @brief Get the mass of the celestial body.
     *
     * @return const Mass& Reference to the mass of the celestial body.
     */
    constexpr const Mass& get_mass() const { return _mass; };

    /**
     * @brief Get the equatorial radius of the celestial body.
     *
     * @return const Distance& Reference to the equatorial radius of the celestial body.
     */
    constexpr const Distance& get_equitorial_radius() const { return _equitorialRadius; };

    /**
     * @brief Get the polar radius of the celestial body.
     *
     * @return const Distance& Reference to the polar radius of the celestial body.
     */
    constexpr const Distance& get_polar_radius() const { return _polarRadius; };

    /**
     * @brief Get the crash radius of the celestial body.
     *
     * @return const Distance& Reference to the crash radius of the celestial body.
     */
    constexpr const Distance& get_crash_radius() const { return _crashRadius; };

    /**
     * @brief Get the sphere of influence of the celestial body.
     *
     * @return const Distance& Reference to the sphere of influence of the celestial body.
     */
    constexpr const Distance& get_sphere_of_influence() const { return _sphereOfInfluence; };

    /**
     * @brief Get the J2 gravitational coefficient of the celestial body.
     *
     * @return const Unitless& Reference to the J2 coefficient of the celestial body.
     */
    constexpr const Unitless& get_j2() const { return _j2; };

    /**
     * @brief Get the J3 gravitational coefficient of the celestial body.
     *
     * @return const Unitless& Reference to the J3 coefficient of the celestial body.
     */
    constexpr const Unitless& get_j3() const { return _j3; };

    /**
     * @brief Get the axial tilt of the celestial body.
     *
     * @return const Angle& Reference to the axial tilt of the celestial body.
     */
    constexpr const Angle& get_axial_tilt() const { return _axialTilt; };

    /**
     * @brief Get the rotation rate of the celestial body.
     *
     * @return const AngularRate& Reference to the rotation rate of the celestial body.
     */
    constexpr const AngularRate& get_rotation_rate() const { return _rotationRate; };

    /**
     * @brief Get the sidereal period of the celestial body.
     *
     * @return const Time& Reference to the sidereal period of the celestial body.
     */
    constexpr const Time& get_sidereal_period() const { return _siderealPeriod; };

    /**
     * @brief Get the semimajor axis of the celestial body.
     *
     * @return const InterplanetaryDistance& Reference to the semimajor axis of the celestial body.
     */
    constexpr const InterplanetaryDistance& get_semimajor() const { return _semimajorAxis; };

    /**
     * @brief Get the eccentricity of the celestial body.
     *
     * @return const Unitless& Reference to the eccentricity of the celestial body.
     */
    constexpr const Unitless& get_eccentricity() const { return _eccentricity; };

    /**
     * @brief Get the inclination of the celestial body.
     *
     * @return const Angle& Reference to the inclination of the celestial body.
     */
    constexpr const Angle& get_inclination() const { return _inclination; };

    /**
     * @brief Get the right ascension of the celestial body.
     *
     * @return const Angle& Reference to the right ascension of the celestial body.
     */
    constexpr const Angle& get_right_ascension() const { return _rightAscension; };

    /**
     * @brief Get the longitude of perigee of the celestial body.
     *
     * @return const Angle& Reference to the longitude of perigee of the celestial body.
     */
    constexpr const Angle& get_longitude_of_perigee() const { return _longitudeOfPerigee; };

    /**
     * @brief Get the mean longitude of the celestial body.
     *
     * @return const Angle& Reference to the mean longitude of the celestial body.
     */
    constexpr const Angle& get_mean_longitude() const { return _meanLongitude; };

    /**
     * @brief Get the true anomaly of the celestial body.
     *
     * @return const Angle& Reference to the true anomaly of the celestial body.
     */
    Angle get_true_anomaly() const
    {
        return wrap_angle(convert_mean_anomaly_to_true_anomaly(_meanAnomaly, _eccentricity));
    };

    /**
     * @brief Get the mean anomaly of the celestial body.
     *
     * @return const Angle& Reference to the mean anomaly of the celestial body.
     */
    constexpr const Angle& get_mean_anomaly() const { return _meanAnomaly; };

    /**
     * @brief Get the semimajor axis rate of the celestial body.
     *
     * @return const BodyVelocity& Reference to the semimajor axis rate of the celestial body.
     */
    constexpr const BodyVelocity& get_semimajor_rate() const { return _semimajorAxisRate; };

    /**
     * @brief Get the eccentricity rate of the celestial body.
     *
     * @return const BodyUnitlessPerTime& Reference to the eccentricity rate of the celestial body.
     */
    constexpr const BodyUnitlessPerTime& get_eccentricity_rate() const { return _eccentricityRate; };

    /**
     * @brief Get the inclination rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the inclination rate of the celestial body.
     */
    constexpr const BodyAngularRate& get_inclination_rate() const { return _inclinationRate; };

    /**
     * @brief Get the right ascension rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the right ascension rate of the celestial body.
     */
    constexpr const BodyAngularRate& get_right_ascension_rate() const { return _rightAscensionRate; };

    /**
     * @brief Get the longitude of perigee rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the longitude of perigee rate of the celestial body.
     */
    constexpr const BodyAngularRate& get_longitude_of_perigee_rate() const { return _longitudeOfPerigeeRate; };

    /**
     * @brief Get the mean longitude rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the mean longitude rate of the celestial body.
     */
    constexpr const BodyAngularRate& get_mean_longitude_rate() const { return _meanLongitudeRate; };

    /**
     * @brief Finds the atmospheric density at a given date and state.
     *
     * @param date The date at which to find the atmospheric density.
     * @param state The Cartesian state vector at which to find the atmospheric density.
     * @return Density The atmospheric density at the specified date and state.
     *
     * @note Assume that most bodies have no significant atmosphere. Assume that
     * the atmosphere of the gas giants is defined by their radii, e.g.
     * outside of their equitorial radius, they have no noticible atmosphere
     * and inside that radius, the object will crash.
     */
    virtual Density find_atmospheric_density(const Date& date, const Distance& altitude) const;

    /**
     * @brief Get the keplerian elements of the celestial body at a specific date using a linear approximation.
     *
     * @param date The date at which to get the state of the celestial body.
     * @return Keplerian The approximate Keplerian elements of the celestial body at the specified date.
     */
    Keplerian get_keplerian_elements_at(const Date& date) const;

    /**
     * @brief Get the position of the celestial body at a specific date in the ICRF frame.
     *
     * @param date The date at which to get the position of the celestial body.
     * @return CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf> The position of the celestial body at the specified date.
     */
    virtual CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

  protected:
    std::string _name;           //!< Name of the celestial body
    CelestialBodyId _parent;     //!< Parent celestial body
    CelestialBodyType _type;     //!< Type of the celestial body
    Date _referenceDate;         //!< Reference date for the celestial body data
    GravParam _mu;               //!< Gravitational parameter (mu) of the celestial body
    GravParam _parentMu;         //!< Gravitational parameter of the parent celestial body, if any
    Mass _mass;                  //!< Mass of the celestial body
    Distance _equitorialRadius;  //!< Equatorial radius of the celestial body
    Distance _polarRadius;       //!< Polar radius of the celestial body
    Distance _crashRadius;       //!< Crash radius of the celestial body
    Distance _sphereOfInfluence; //!< Crash radius of the celestial body

    Unitless _j2;              //!< J2 gravitational coefficient of the celestial body
    Unitless _j3;              //!< J3 gravitational coefficient of the celestial body
    Angle _axialTilt;          //!< Axial tilt of the celestial body
    AngularRate _rotationRate; //!< Rotation rate of the celestial body
    Time _siderealPeriod;      //!< Sidereal period of the celestial body

    InterplanetaryDistance _semimajorAxis; //!< Semimajor axis
    Unitless _eccentricity;                //!< Eccentricity
    Angle _inclination;                    //!< Inclination
    Angle _rightAscension;                 //!< Right ascension
    Angle _longitudeOfPerigee;             //!< Argument of perigee
    Angle _meanLongitude;                  //!< Mean longitude
    Angle _trueAnomaly;                    //!< True anomaly
    Angle _meanAnomaly;                    //!< Mean anomaly

    // These rates need to stay in rate/JC to avoid numerical issues
    BodyVelocity _semimajorAxisRate;         //!< Rate of change of the semimajor axis
    BodyUnitlessPerTime _eccentricityRate;   //!< Rate of change of the eccentricity
    BodyAngularRate _inclinationRate;        //!< Rate of change of the inclination
    BodyAngularRate _rightAscensionRate;     //!< Rate of change of the right ascension
    BodyAngularRate _longitudeOfPerigeeRate; //!< Rate of change of the longitude of perigee
    BodyAngularRate _meanLongitudeRate;      //!< Rate of change of the mean longitude

    static constexpr double _COEFF_ZERO_FACTOR = 1.0;

    template <typename Table_T, typename Frame_T>
    CartesianVector<InterplanetaryDistance, Frame_T> get_position_at_impl(const Date& date) const
    {
        using mp_units::si::unit_symbols::km;

        // Evaluate Chebyshev polynomials
        const auto [xInterp, yInterp, zInterp] = get_chebyshev_table_coefficients<Table_T>(date);
        const double mjd                       = (date.mjd() - Date(J2000).mjd()).count();

        InterplanetaryDistance x = math::evaluate_chebyshev_polynomial(mjd, xInterp, _COEFF_ZERO_FACTOR) * km;
        InterplanetaryDistance y = math::evaluate_chebyshev_polynomial(mjd, yInterp, _COEFF_ZERO_FACTOR) * km;
        InterplanetaryDistance z = math::evaluate_chebyshev_polynomial(mjd, zInterp, _COEFF_ZERO_FACTOR) * km;

        return CartesianVector<InterplanetaryDistance, Frame_T>(x, y, z);
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
        //! Number of days covered by each set of polynomial coefficients
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

/**
 * @brief Unique pointer type for CelestialBody.
 */
using CelestialBodyUniquePtr = std::unique_ptr<CelestialBody>;

} // namespace astro
} // namespace astrea

/**
 * @brief Hash function for CelestialBody.
 */
template <>
struct std::hash<astrea::astro::CelestialBody> {
    /**
     * @brief Computes a hash value for a CelestialBody object.
     *
     * @param body The CelestialBody object to hash.
     * @return std::size_t The computed hash value.
     */
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