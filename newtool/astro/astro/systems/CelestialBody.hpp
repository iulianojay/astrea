#pragma once

#ifndef SWIG
#include <cfloat>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#endif

// Astro
#include <astro/constants/astronomical_constants.h>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>

class CelestialBody {
  public:
    // Constructor/destructor
    CelestialBody()                           = default;
    CelestialBody(const CelestialBody& other) = default;
    CelestialBody(const std::string& file);
    ~CelestialBody() = default;

    // Operators
    bool operator==(const CelestialBody& other) const { return _mu == other._mu; } // Probably good enough
    bool operator!=(const CelestialBody& other) const { return !(*this == other); }

    // Property assignment
    void propagate(const Date& epoch, const Time& propTime, const double parentMu);
    void propagate(const Date& epoch, const Date& endEpoch, const double parentMu);

    // Property getters
    const std::string& get_name() const { return _name; };
    const std::string& get_parent() const { return _parent; };
    const std::string& get_type() const { return _type; };

    const double& get_mu() const { return _mu; };
    const double& get_mass() const { return _mass; };
    const double& get_equitorial_radius() const { return _equitorialRadius; };
    const double& get_polar_radius() const { return _polarRadius; };
    const double& get_crash_radius() const { return _crashRadius; };
    const double& get_sphere_of_influence() const { return _sphereOfInfluence; };

    const double& get_j2() const { return _j2; };
    const double& get_j3() const { return _j3; };

    const double& get_axial_tilt() const { return _axialTilt; };
    const double& get_rotation_rate() const { return _rotationRate; };
    const double& get_siderial_period() const { return _siderialPeroid; };

    const double& get_semimajor() const { return _semimajorAxis; };
    const double& get_eccentricity() const { return _eccentricity; };
    const double& get_inclination() const { return _inclination; };
    const double& get_right_ascension() const { return _rightAscension; };
    const double& get_argument_of_perigee() const { return _argumentOfPerigee; };
    const double& get_true_latitude() const { return _trueLatitude; };
    const double& get_true_anomaly() const { return _trueAnomaly; };
    const double& get_mean_anomaly() const { return _meanAnomaly; };

    const double& get_semimajor_rate() const { return _semimajorAxisRate; };
    const double& get_eccentricity_rate() const { return _eccentricityRate; };
    const double& get_inclination_rate() const { return _inclinationRate; };
    const double& get_right_ascension_rate() const { return _rightAscensionRate; };
    const double& get_argument_of_perigee_rate() const { return _argumentOfPerigeeRate; };
    const double& get_true_latitude_rate() const { return _trueLatitudeRate; };

    std::vector<State>& get_states() { return _states; };
    const State& get_closest_state(const Time& time) const;

  private:
    //----------------------------------------------- Variables -----------------------------------------------//

    // Properties
    std::string _name, _parent, _type;
    Date _referenceDate;
    double _mu, _mass, _equitorialRadius, _polarRadius, _crashRadius, _sphereOfInfluence, _j2, _j3, _axialTilt,
        _rotationRate, _siderialPeroid, _semimajorAxis, _eccentricity, _inclination, _rightAscension,
        _argumentOfPerigee, _trueLatitude, _trueAnomaly, _meanAnomaly, _semimajorAxisRate, _eccentricityRate,
        _inclinationRate, _rightAscensionRate, _argumentOfPerigeeRate, _trueLatitudeRate;

    std::vector<State> _states;

    //------------------------------------------------ Methods ------------------------------------------------//
    void _propagate(const Date& epoch, const Date& endEpoch, const double parentMu);
};

template <>
struct std::hash<CelestialBody> {
    std::size_t operator()(CelestialBody const& body) const noexcept
    {

        size_t h = std::hash<double>{}(body.get_mu());
        h ^= (std::hash<double>{}(body.get_mass()) << 1);
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