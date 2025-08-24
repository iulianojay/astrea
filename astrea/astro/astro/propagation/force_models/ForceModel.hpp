/**
 * @file ForceModel.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the ForceModel class, which manages multiple force models and computes the total force on a vehicle.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include <astro/propagation/force_models/Force.hpp>
#include <units/units.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to manage multiple force models and compute the total force on a vehicle.
 *
 * This class allows adding different force models, computing the total force on a vehicle,
 * and retrieving specific force models by name or type.
 */
class ForceModel {
  public:
    /**
     * @brief Default constructor for ForceModel.
     */
    ForceModel() = default;

    /**
     * @brief Default destructor for ForceModel.
     */
    ~ForceModel() = default;

    /**
     * @brief Adds a force model of type T with the given arguments.
     *
     * @tparam T Type of the force model to add
     * @tparam Args Types of the arguments for the constructor of T
     * @param args Arguments to pass to the constructor of T
     * @return const std::unique_ptr<Force>& Reference to the added force model
     */
    template <typename T, typename... Args>
    const std::unique_ptr<Force>& add(Args&&... args)
    {
        static const std::string name = typeid(T).name();
        if (forces.count(name) == 0) { forces.emplace(name, std::make_unique<T>(std::forward<Args>(args)...)); }
        return forces.at(name);
    }

    /**
     * @brief Computes the total force on a vehicle by summing the forces from all added force models.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @param sys Astrodynamics system containing celestial body data
     * @return AccelerationVector<ECI> The total computed acceleration vector from all force models.
     */
    AccelerationVector<ECI>
        compute_forces(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const;

    /**
     * @brief Retrieves a force model by name.
     *
     * @param name Name of the force model to retrieve
     * @return const std::unique_ptr<Force>& Reference to the force model with the given name.
     */
    const std::unique_ptr<Force>& at(const std::string& name) const;

    /**
     * @brief Retrieves a force model by type.
     *
     * @tparam T Type of the force model to retrieve
     * @return const std::unique_ptr<Force>& Reference to the force model of type T.
     */
    template <typename T>
    const std::unique_ptr<Force>& get() const
    {
        static const std::string name = typeid(T).name();
        return forces.at(name);
    }

  private:
    std::unordered_map<std::string, std::unique_ptr<Force>> forces; //!< Map of force models by name
};

} // namespace astro
} // namespace astrea