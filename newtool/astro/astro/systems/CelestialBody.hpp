#pragma once

#include <cfloat>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// mp-units
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

// Astro
#include <astro/constants/astronomical_constants.h>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace astro {

class CelestialBody {

  public:
    // Constructor/destructor
    CelestialBody()  = default;
    ~CelestialBody() = default;

    CelestialBody(const std::string& file);
    CelestialBody(const CelestialBody& other) = default;

    // Operators
    bool operator==(const CelestialBody& other) const { return _mu == other._mu; } // Probably good enough
    bool operator!=(const CelestialBody& other) const { return !(*this == other); }

    // Property assignment
    void propagate(const Date& epoch, const Time& propTime, const GravParam& parentMu);
    void propagate(const Date& epoch, const Date& endEpoch, const GravParam& parentMu);

    // Property getters
    const std::string& get_name() const { return _name; };
    const std::string& get_parent() const { return _parent; };
    const std::string& get_type() const { return _type; };

    const GravParam& get_mu() const { return _mu; };
    const Mass& get_mass() const { return _mass; };
    const Distance& get_equitorial_radius() const { return _equitorialRadius; };
    const Distance& get_polar_radius() const { return _polarRadius; };
    const Distance& get_crash_radius() const { return _crashRadius; };
    const Distance& get_sphere_of_influence() const { return _sphereOfInfluence; };

    const Unitless& get_j2() const { return _j2; };
    const Unitless& get_j3() const { return _j3; };

    const Angle& get_axial_tilt() const { return _axialTilt; };
    const AngularRate& get_rotation_rate() const { return _rotationRate; };
    const Time& get_siderial_period() const { return _siderialPeroid; };

    const Distance& get_semimajor() const { return _semimajorAxis; };
    const Unitless& get_eccentricity() const { return _eccentricity; };
    const Angle& get_inclination() const { return _inclination; };
    const Angle& get_right_ascension() const { return _rightAscension; };
    const Angle& get_argument_of_perigee() const { return _argumentOfPerigee; };
    const Angle& get_true_latitude() const { return _trueLatitude; };
    const Angle& get_true_anomaly() const { return _trueAnomaly; };
    const Angle& get_mean_anomaly() const { return _meanAnomaly; };

    const Velocity& get_semimajor_rate() const { return _semimajorAxisRate; };
    const UnitlessPerTime& get_eccentricity_rate() const { return _eccentricityRate; };
    const AngularRate& get_inclination_rate() const { return _inclinationRate; };
    const AngularRate& get_right_ascension_rate() const { return _rightAscensionRate; };
    const AngularRate& get_argument_of_perigee_rate() const { return _argumentOfPerigeeRate; };
    const AngularRate& get_true_latitude_rate() const { return _trueLatitudeRate; };

    std::vector<State>& get_states() { return _states; };
    const State& get_closest_state(const Time& time) const;


  private:
    // Properties
    std::string _name, _parent, _type;
    Date _referenceDate;
    GravParam _mu;
    Mass _mass;
    Distance _equitorialRadius;
    Distance _polarRadius;
    Distance _crashRadius;
    Distance _sphereOfInfluence;

    Unitless _j2;
    Unitless _j3;
    Angle _axialTilt;
    AngularRate _rotationRate;
    Time _siderialPeroid;

    Distance _semimajorAxis;
    Unitless _eccentricity;
    Angle _inclination;
    Angle _rightAscension;
    Angle _argumentOfPerigee;
    Angle _trueLatitude;
    Angle _trueAnomaly;
    Angle _meanAnomaly;

    Velocity _semimajorAxisRate;
    UnitlessPerTime _eccentricityRate;
    AngularRate _inclinationRate;
    AngularRate _rightAscensionRate;
    AngularRate _argumentOfPerigeeRate;
    AngularRate _trueLatitudeRate;

    std::vector<State> _states;

    void _propagate(const Date& epoch, const Date& endEpoch, const GravParam& parentMu);
};

} // namespace astro

template <>
struct std::hash<astro::CelestialBody> {
    std::size_t operator()(astro::CelestialBody const& body) const noexcept
    {

        size_t h = std::hash<double>{}(body.get_mu().numerical_value_in(
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