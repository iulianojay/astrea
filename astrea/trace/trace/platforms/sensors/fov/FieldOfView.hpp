/**
 * @file FieldOfView.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Field of View (FoV) classes for representing different types of sensor fields of view.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <numbers>
#include <unordered_map>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Computes the angle between two radius vectors.
 *
 * @param vector1 The first radius vector.
 * @param vector2 The second radius vector.
 * @return Angle The angle between the two vectors.
 */
Angle calculate_angle_between_vectors(
    const astro::CartesianVector<Distance, astro::frames::earth::icrf>& vector1,
    const astro::CartesianVector<Distance, astro::frames::earth::icrf>& vector2
);

/**
 * @brief Base class for Field of View (FoV) representations.
 *
 * This class defines the interface for different types of fields of view.
 */
class FieldOfView {
  public:
    /**
     * @brief Default constructor for FieldOfView.
     */
    FieldOfView() = default;

    /**
     * @brief Virtual destructor for FieldOfView.
     *
     * Ensures proper cleanup of derived classes.
     */
    ~FieldOfView() = default;

    /**
     * @brief Checks if a target is within the field of view.
     *
     * @param boresight The boresight vector of the sensor.
     * @param target The target vector to check.
     * @return true If the target is within the field of view.
     * @return false If the target is outside the field of view.
     */
    virtual bool contains(
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& boresight,
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& target
    ) const = 0;
};

/**
 * @brief Circular field of view implementation.
 *
 * This class represents a circular field of view defined by a half-cone angle.
 */
class CircularFieldOfView : public FieldOfView {
  public:
    /**
     * @brief Constructor for CircularFieldOfView.
     *
     * @param halfConeAngle The half-cone angle defining the field of view.
     */
    CircularFieldOfView(const Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::angular::unit_symbols::rad) :
        _halfConeAngle(halfConeAngle)
    {
    }

    /**
     * @brief Default destructor for CircularFieldOfView.
     */
    ~CircularFieldOfView() = default;

    /**
     * @brief Checks if a target is within the circular field of view.
     *
     * @param boresight The boresight vector of the sensor.
     * @param target The target vector to check.
     * @return true If the target is within the circular field of view.
     * @return false If the target is outside the circular field of view.
     */
    bool contains(
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& boresight,
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& target
    ) const;

  private:
    Angle _halfConeAngle; // Half-cone angle defining the circular field of view
};

/**
 * @brief Polygonal field of view implementation.
 *
 * This class represents a polygonal field of view defined by a set of points.
 */
class PolygonalFieldOfView : public FieldOfView {
  public:
    /**
     * @brief Constructor for PolygonalFieldOfView.
     *
     * @param halfConeAngle The half-cone angle defining the field of view.
     * @param nPoints The number of points defining the polygon.
     */
    PolygonalFieldOfView(const Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::angular::unit_symbols::rad, const int& nPoints = 72);

    /**
     * @brief Constructor for PolygonalFieldOfView with specified half-cone width and height.
     *
     * @param halfConeWidth The half-cone width angle.
     * @param halfConeHeight The half-cone height angle.
     * @param nPoints The number of points defining the polygon.
     */
    PolygonalFieldOfView(const Angle& halfConeWidth, const Angle& halfConeHeight, const int& nPoints = 72);

    /**
     * @brief Constructor for PolygonalFieldOfView with a set of points.
     *
     * @param points A map of angles defining the polygonal field of view.
     */
    PolygonalFieldOfView(const std::unordered_map<Angle, Angle>& points) :
        _points(points)
    {
    }

    /**
     * @brief Default destructor for PolygonalFieldOfView.
     */
    ~PolygonalFieldOfView() = default;

    /**
     * @brief Checks if a target is within the polygonal field of view.
     *
     * @param boresight The boresight vector of the sensor.
     * @param target The target vector to check.
     * @return true If the target is within the polygonal field of view.
     * @return false If the target is outside the polygonal field of view.
     */
    bool contains(
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& boresight,
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& target
    ) const
    {
        return false;
    };

  private:
    std::unordered_map<Angle, Angle> _points; // Map of angles defining the polygonal field of view
};

} // namespace trace
} // namespace astrea