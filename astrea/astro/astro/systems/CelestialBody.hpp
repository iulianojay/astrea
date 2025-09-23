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
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
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
     * @param argumentOfPerigee Argument of perigee.
     * @param trueLatitude True latitude.
     * @param semimajorAxisRate Rate of change of the semimajor axis.
     * @param eccentricityRate Rate of change of the eccentricity.
     * @param inclinationRate Rate of change of the inclination.
     * @param rightAscensionRate Rate of change of the right ascension.
     * @param argumentOfPerigeeRate Rate of change of the argument of perigee.
     * @param trueLatitudeRate Rate of change of the true latitude.
     */
    constexpr CelestialBody(
        const std::string& name,
        const PlanetaryBody& parent,
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
        const Angle& argumentOfPerigee,
        const Angle& trueLatitude,
        const BodyVelocity& semimajorAxisRate,
        const BodyUnitlessPerTime& eccentricityRate,
        const BodyAngularRate& inclinationRate,
        const BodyAngularRate& rightAscensionRate,
        const BodyAngularRate& argumentOfPerigeeRate,
        const BodyAngularRate& trueLatitudeRate
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
        _argumentOfPerigee(argumentOfPerigee),
        _trueLatitude(trueLatitude),
        _meanAnomaly(wrap_angle(_trueLatitude - _argumentOfPerigee)),
        _semimajorAxisRate(semimajorAxisRate),
        _eccentricityRate(eccentricityRate),
        _inclinationRate(inclinationRate),
        _rightAscensionRate(rightAscensionRate),
        _argumentOfPerigeeRate(argumentOfPerigeeRate),
        _trueLatitudeRate(trueLatitudeRate)
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
    static constexpr PlanetaryBody get_id() { return PlanetaryBody::UNSET; };

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
    constexpr const PlanetaryBody& get_parent() const { return _parent; };

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
     * @return const Distance& Reference to the semimajor axis of the celestial body.
     */
    constexpr const Distance& get_semimajor() const { return _semimajorAxis; };

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
     * @brief Get the argument of perigee of the celestial body.
     *
     * @return const Angle& Reference to the argument of perigee of the celestial body.
     */
    constexpr const Angle& get_argument_of_perigee() const { return _argumentOfPerigee; };

    /**
     * @brief Get the true latitude of the celestial body.
     *
     * @return const Angle& Reference to the true latitude of the celestial body.
     */
    constexpr const Angle& get_true_latitude() const { return _trueLatitude; };

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
     * @brief Get the argument of perigee rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the argument of perigee rate of the celestial body.
     */
    constexpr const BodyAngularRate& get_argument_of_perigee_rate() const { return _argumentOfPerigeeRate; };

    /**
     * @brief Get the true latitude rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the true latitude rate of the celestial body.
     */
    constexpr const BodyAngularRate& get_true_latitude_rate() const { return _trueLatitudeRate; };

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
     * @brief Get the state of the celestial body at a specific date.
     *
     * @param date The date at which to get the state of the celestial body.
     * @return State The state of the celestial body at the specified date.
     */
    virtual OrbitalElements get_elements_at(const Date& date) const;

  protected:
    template <typename Table_T>
    Cartesian get_elements_at_impl(const Date& date) const
    {
        using mp_units::non_si::day;
        using mp_units::si::unit_symbols::km;

        //! Number of days covered by each set of polynomial coefficients
        static constexpr Time timePerCoefficient = Table_T::TIME_PER_COEFFICIENT;

        // Extract components
        const std::size_t ind = Table_T::get_index(date, timePerCoefficient);
        const auto& xInterp   = Table_T::X_INTERP[ind];
        const auto& yInterp   = Table_T::Y_INTERP[ind];
        const auto& zInterp   = Table_T::Z_INTERP[ind];

        // Evaluate Chebyshev polynomials
        const double mjd = (date.mjd() - Date(J2000).mjd()).count();

        Distance x = math::evaluate_chebyshev_polynomial(mjd, xInterp, _COEFF_ZERO_FACTOR) * km;
        Distance y = math::evaluate_chebyshev_polynomial(mjd, yInterp, _COEFF_ZERO_FACTOR) * km;
        Distance z = math::evaluate_chebyshev_polynomial(mjd, zInterp, _COEFF_ZERO_FACTOR) * km;

        Velocity vx = math::evaluate_chebyshev_derivative(mjd, xInterp, _COEFF_ZERO_FACTOR) * km / day;
        Velocity vy = math::evaluate_chebyshev_derivative(mjd, yInterp, _COEFF_ZERO_FACTOR) * km / day;
        Velocity vz = math::evaluate_chebyshev_derivative(mjd, zInterp, _COEFF_ZERO_FACTOR) * km / day;

        return Cartesian{ x, y, z, vx, vy, vz };
    }

  private:
    // Properties
    std::string _name;           //!< Name of the celestial body
    PlanetaryBody _parent;       //!< Parent celestial body
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

    Distance _semimajorAxis;  //!< Semimajor axis
    Unitless _eccentricity;   //!< Eccentricity
    Angle _inclination;       //!< Inclination
    Angle _rightAscension;    //!< Right ascension
    Angle _argumentOfPerigee; //!< Argument of perigee
    Angle _trueLatitude;      //!< True latitude
    Angle _trueAnomaly;       //!< True anomaly
    Angle _meanAnomaly;       //!< Mean anomaly

    // These rates need to stay in rate/JC to avoid numerical issues
    BodyVelocity _semimajorAxisRate;        //!< Rate of change of the semimajor axis
    BodyUnitlessPerTime _eccentricityRate;  //!< Rate of change of the eccentricity
    BodyAngularRate _inclinationRate;       //!< Rate of change of the inclination
    BodyAngularRate _rightAscensionRate;    //!< Rate of change of the right ascension
    BodyAngularRate _argumentOfPerigeeRate; //!< Rate of change of the argument of perigee
    BodyAngularRate _trueLatitudeRate;      //!< Rate of change of the true latitude

    static constexpr double _COEFF_ZERO_FACTOR = 1.0;
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
        h ^= (std::hash<double>{}(body.get_argument_of_perigee()) << 1);
        h ^= (std::hash<double>{}(body.get_true_latitude()) << 1);
        */

        return h;
    }
};