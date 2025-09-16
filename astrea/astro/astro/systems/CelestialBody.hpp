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

// Astro
#include <astro/astro.fwd.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

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
    ~CelestialBody() = default;

    /**
     * @brief Constructs a CelestialBody from a file.
     *
     * @param file Path to the file containing celestial body data.
     * @param system Reference to the AstrodynamicsSystem this body belongs to.
     */
    CelestialBody(const std::string& file, const AstrodynamicsSystem& system);

    /**
     * @brief Copy constructor for CelestialBody.
     *
     * @param other The CelestialBody to copy from.
     */
    CelestialBody(const CelestialBody& other) = default;

    /**
     * @brief Assigns the system pointer to this celestial body.
     *
     * @param systemPtr Reference to the AstrodynamicsSystem this body belongs to.
     */
    void assign_system(const AstrodynamicsSystem& system) { _systemPtr = &system; }

    /**
     * @brief Equality operator for CelestialBody.
     *
     * @param other The CelestialBody to compare with.
     * @return true if the celestial bodies are equal, false otherwise.
     */
    bool operator==(const CelestialBody& other) const { return _mu == other._mu; } // Probably good enough

    /**
     * @brief Get the name of the celestial body.
     *
     * @return const std::string& Reference to the name of the celestial body.
     */
    const std::string& get_name() const { return _name; };

    /**
     * @brief Get the parent celestial body.
     *
     * @return const std::string& Reference to the name of the parent celestial body.
     */
    const std::string& get_parent() const { return _parent; };

    /**
     * @brief Get the type of the celestial body.
     *
     * @return const std::string& Reference to the type of the celestial body.
     */
    const std::string& get_type() const { return _type; };

    /**
     * @brief Get the gravitational parameter (mu) of the celestial body.
     *
     * @return const GravParam& Reference to the gravitational parameter of the celestial body.
     */
    const GravParam& get_mu() const { return _mu; };

    /**
     * @brief Get the mass of the celestial body.
     *
     * @return const Mass& Reference to the mass of the celestial body.
     */
    const Mass& get_mass() const { return _mass; };

    /**
     * @brief Get the equatorial radius of the celestial body.
     *
     * @return const Distance& Reference to the equatorial radius of the celestial body.
     */
    const Distance& get_equitorial_radius() const { return _equitorialRadius; };

    /**
     * @brief Get the polar radius of the celestial body.
     *
     * @return const Distance& Reference to the polar radius of the celestial body.
     */
    const Distance& get_polar_radius() const { return _polarRadius; };

    /**
     * @brief Get the crash radius of the celestial body.
     *
     * @return const Distance& Reference to the crash radius of the celestial body.
     */
    const Distance& get_crash_radius() const { return _crashRadius; };

    /**
     * @brief Get the sphere of influence of the celestial body.
     *
     * @return const Distance& Reference to the sphere of influence of the celestial body.
     */
    const Distance& get_sphere_of_influence() const { return _sphereOfInfluence; };

    /**
     * @brief Get the J2 gravitational coefficient of the celestial body.
     *
     * @return const Unitless& Reference to the J2 coefficient of the celestial body.
     */
    const Unitless& get_j2() const { return _j2; };

    /**
     * @brief Get the J3 gravitational coefficient of the celestial body.
     *
     * @return const Unitless& Reference to the J3 coefficient of the celestial body.
     */
    const Unitless& get_j3() const { return _j3; };

    /**
     * @brief Get the axial tilt of the celestial body.
     *
     * @return const Angle& Reference to the axial tilt of the celestial body.
     */
    const Angle& get_axial_tilt() const { return _axialTilt; };

    /**
     * @brief Get the rotation rate of the celestial body.
     *
     * @return const AngularRate& Reference to the rotation rate of the celestial body.
     */
    const AngularRate& get_rotation_rate() const { return _rotationRate; };

    /**
     * @brief Get the sidereal period of the celestial body.
     *
     * @return const Time& Reference to the sidereal period of the celestial body.
     */
    const Time& get_siderial_period() const { return _siderialPeroid; };

    /**
     * @brief Get the semimajor axis of the celestial body.
     *
     * @return const Distance& Reference to the semimajor axis of the celestial body.
     */
    const Distance& get_semimajor() const { return _semimajorAxis; };

    /**
     * @brief Get the eccentricity of the celestial body.
     *
     * @return const Unitless& Reference to the eccentricity of the celestial body.
     */
    const Unitless& get_eccentricity() const { return _eccentricity; };

    /**
     * @brief Get the inclination of the celestial body.
     *
     * @return const Angle& Reference to the inclination of the celestial body.
     */
    const Angle& get_inclination() const { return _inclination; };

    /**
     * @brief Get the right ascension of the celestial body.
     *
     * @return const Angle& Reference to the right ascension of the celestial body.
     */
    const Angle& get_right_ascension() const { return _rightAscension; };

    /**
     * @brief Get the argument of perigee of the celestial body.
     *
     * @return const Angle& Reference to the argument of perigee of the celestial body.
     */
    const Angle& get_argument_of_perigee() const { return _argumentOfPerigee; };

    /**
     * @brief Get the true latitude of the celestial body.
     *
     * @return const Angle& Reference to the true latitude of the celestial body.
     */
    const Angle& get_true_latitude() const { return _trueLatitude; };

    /**
     * @brief Get the true anomaly of the celestial body.
     *
     * @return const Angle& Reference to the true anomaly of the celestial body.
     */
    const Angle& get_true_anomaly() const { return _trueAnomaly; };

    /**
     * @brief Get the mean anomaly of the celestial body.
     *
     * @return const Angle& Reference to the mean anomaly of the celestial body.
     */
    const Angle& get_mean_anomaly() const { return _meanAnomaly; };

    /**
     * @brief Get the semimajor axis rate of the celestial body.
     *
     * @return const BodyVelocity& Reference to the semimajor axis rate of the celestial body.
     */
    const BodyVelocity& get_semimajor_rate() const { return _semimajorAxisRate; };

    /**
     * @brief Get the eccentricity rate of the celestial body.
     *
     * @return const BodyUnitlessPerTime& Reference to the eccentricity rate of the celestial body.
     */
    const BodyUnitlessPerTime& get_eccentricity_rate() const { return _eccentricityRate; };

    /**
     * @brief Get the inclination rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the inclination rate of the celestial body.
     */
    const BodyAngularRate& get_inclination_rate() const { return _inclinationRate; };

    /**
     * @brief Get the right ascension rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the right ascension rate of the celestial body.
     */
    const BodyAngularRate& get_right_ascension_rate() const { return _rightAscensionRate; };

    /**
     * @brief Get the argument of perigee rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the argument of perigee rate of the celestial body.
     */
    const BodyAngularRate& get_argument_of_perigee_rate() const { return _argumentOfPerigeeRate; };

    /**
     * @brief Get the true latitude rate of the celestial body.
     *
     * @return const BodyAngularRate& Reference to the true latitude rate of the celestial body.
     */
    const BodyAngularRate& get_true_latitude_rate() const { return _trueLatitudeRate; };

    /**
     * @brief Get the state of the celestial body at a specific date.
     *
     * @param date The date at which to get the state of the celestial body.
     * @return State The state of the celestial body at the specified date.
     */
    State get_state_at(const Date& date) const;

  private:
    // Properties
    std::string _name;          //!< Name of the celestial body
    std::string _parent;        //!< Name of the parent celestial body, if any
    std::string _type;          //!< Type of the celestial body (e.g., planet, moon)
    Date _referenceDate;        //!< Reference date for the celestial body data
    GravParam _mu;              //!< Gravitational parameter (mu) of the celestial body
    GravParam _parentMu;        //!< Gravitational parameter of the parent celestial body, if any
    Mass _mass;                 //!< Mass of the celestial body
    Distance _equitorialRadius; //!< Equatorial radius of the celestial body
    Distance _polarRadius;      //!< Polar radius of the celestial body
    Distance _crashRadius;      //!< Crash radius of the celestial body, used for collision detection
    Distance _sphereOfInfluence; //!< Sphere of influence of the celestial body, used for gravitational influence calculations

    Unitless _j2;              //!< J2 gravitational coefficient of the celestial body
    Unitless _j3;              //!< J3 gravitational coefficient of the celestial body
    Angle _axialTilt;          //!< Axial tilt of the celestial body, used for rotation calculations
    AngularRate _rotationRate; //!< Rotation rate of the celestial body, used for calculating rotation effects
    Time _siderialPeroid;      //!< Sidereal period of the celestial body, used for calculating rotation effects

    Distance _semimajorAxis; //!< Semimajor axis of the celestial body's orbit
    Unitless _eccentricity;  //!< Eccentricity of the celestial body's orbit, used for calculating orbital shape
    Angle _inclination;      //!< Inclination of the celestial body's orbit, used for calculating orbital tilt
    Angle _rightAscension;   //!< Right ascension of the celestial body's orbit, used for calculating orbital position
    Angle _argumentOfPerigee; //!< Argument of perigee of the celestial body's orbit, used for calculating orbital position
    Angle _trueLatitude;      //!< True latitude of the celestial body's orbit, used for calculating orbital position
    Angle _trueAnomaly;       //!< True anomaly of the celestial body's orbit, used for calculating orbital position
    Angle _meanAnomaly;       //!< Mean anomaly of the celestial body's orbit, used for calculating orbital position

    // These rates need to stay in rate/JC to avoid numerical issues
    BodyVelocity _semimajorAxisRate; //!< Rate of change of the semimajor axis, used for calculating orbital evolution
    BodyUnitlessPerTime _eccentricityRate; //!< Rate of change of the eccentricity, used for calculating orbital evolution
    BodyAngularRate _inclinationRate;    //!< Rate of change of the inclination, used for calculating orbital evolution
    BodyAngularRate _rightAscensionRate; //!< Rate of change of the right ascension, used for calculating orbital evolution
    BodyAngularRate _argumentOfPerigeeRate; //!< Rate of change of the argument of perigee, used for calculating orbital evolution
    BodyAngularRate _trueLatitudeRate; //!< Rate of change of the true latitude, used for calculating orbital evolution

    /**
     * @brief Propagates the state of the celestial body from a given epoch to an end epoch.
     *
     * @param epoch The starting date for propagation.
     * @param endEpoch The ending date for propagation.
     * @param parentMu The gravitational parameter of the parent celestial body, if any.
     * @return StateHistory The history of states propagated from the epoch to the end epoch.
     */
    StateHistory _propagate(const Date& epoch, const Date& endEpoch, const GravParam& parentMu);

    const AstrodynamicsSystem* _systemPtr; //!< Pointer to the AstrodynamicsSystem this celestial body belongs to
};

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
        h ^= (std::hash<double>{}(body.get_mass().numerical_value_in(mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)) << 1);
        /* // These are probably overkill
        h ^= (std::hash<double>{}(body.get_equitorial_radius()) << 1);
        h ^= (std::hash<double>{}(body.get_polar_radius()) << 1);
        h ^= (std::hash<double>{}(body.get_crash_radius()) << 1);
        h ^= (std::hash<double>{}(body.get_sphere_of_influence()) << 1);
        h ^= (std::hash<double>{}(body.get_j2()) << 1);
        h ^= (std::hash<double>{}(body.get_j3()) << 1);
        h ^= (std::hash<double>{}(body.get_axial_tilt()) << 1);
        h ^= (std::hash<double>{}(body.get_rotation_rate()) << 1);
        h ^= (std::hash<double>{}(body.get_siderial_period()) << 1);
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