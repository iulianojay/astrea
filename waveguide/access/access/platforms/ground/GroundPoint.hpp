/**
 * @file GroundPoint.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the GroundPoint class.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <astro/systems/CelestialBody.hpp>

#include <access/platforms/sensors/SensorPlatform.hpp>
#include <access/types/typedefs.hpp>


namespace waveguide {
namespace accesslib {

/**
 * @brief Represents a point on the ground with latitude, longitude, and altitude.
 *
 * This class is used to define a ground point in terms of its geographic coordinates
 * and altitude above sea level. It can be extended to include additional properties
 * or methods as needed for specific applications.
 */
class GroundPoint : virtual public AccessObject {
  public:
    /**
     * @brief Constructs a GroundPoint with specified latitude, longitude, and altitude.
     *
     * @param latitutde The latitude of the ground point (default is 0 degrees).
     * @param longitude The longitude of the ground point (default is 0 degrees).
     * @param altitude The altitude of the ground point above sea level (default is 0 kilometers).
     */
    GroundPoint(
        const astro::CelestialBody* parent = nullptr,
        const Angle& latitutde             = 0.0 * mp_units::angular::unit_symbols::deg,
        const Angle& longitude             = 0.0 * mp_units::angular::unit_symbols::deg,
        const Distance& altitude           = 0.0 * mp_units::si::unit_symbols::km
    ) :
        AccessObject(),
        _parent(parent),
        _latitude(latitutde),
        _longitude(longitude),
        _altitude(altitude)
    {
        generate_id_hash();
    }

    /**
     * @brief Destructor for the GroundPoint class.
     */
    virtual ~GroundPoint() = default;

    /**
     * @brief Gets the latitude of the ground point.
     *
     * @return Angle The latitude of the ground point.
     */
    Angle get_latitude() const { return _latitude; }

    /**
     * @brief Gets the longitude of the ground point.
     *
     * @return Angle The longitude of the ground point.
     */
    Angle get_longitude() const { return _longitude; }

    /**
     * @brief Gets the altitude of the ground point above sea level.
     *
     * @return Distance The altitude of the ground point.
     */
    Distance get_altitude() const { return _altitude; }

    /**
     * @brief Get the unique identifier for the ground station.
     *
     * @return std::size_t The unique identifier for the ground station.
     */
    std::size_t get_id() const { return _id; }

  protected:
    std::size_t _id;                     //!< Unique identifier for the ground station, generated from its properties.
    const astro::CelestialBody* _parent; //!< Pointer to the parent celestial body
    Angle _latitude;                     //!< Latitude of the ground point
    Angle _longitude;                    //!< Longitude of the ground point
    Distance _altitude;                  //!< Altitude of the ground point above sea level

    /**
     * @brief Generates a unique identifier for the ground station based on its properties.
     * This method is called in the constructor to ensure that each ground station has a unique ID.
     */
    void generate_id_hash()
    {
        _id = std::hash<Angle>()(_latitude) ^ std::hash<Angle>()(_longitude) ^ std::hash<Distance>()(_altitude);
    }
};

} // namespace accesslib
} // namespace waveguide