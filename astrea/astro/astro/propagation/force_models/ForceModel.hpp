/**
 * @file ForceModel.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the ForceModel class, which manages multiple force models and computes the total force on a vehicle.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>

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
     * @brief Copy constructor for ForceModel.
     *
     * @param other The ForceModel object to copy from.
     */
    ForceModel(const ForceModel& other);

    /**
     * @brief Move constructor for ForceModel.
     *
     * @param other The ForceModel object to move from.
     */
    ForceModel(ForceModel&&) noexcept = default;

    /**
     * @brief Copy assignment operator for ForceModel.
     *
     * @param other The ForceModel object to copy from.
     * @return ForceModel& Reference to the assigned ForceModel object.
     */
    ForceModel& operator=(const ForceModel& other);

    /**
     * @brief Move assignment operator for ForceModel.
     *
     * @param other The ForceModel object to move from.
     * @return ForceModel& Reference to the assigned ForceModel object.
     */
    ForceModel& operator=(ForceModel&&) noexcept = default;

    /**
     * @brief Returns the number of forces added to the ForceModel.
     *
     * @return std::size_t Number of forces.
     */
    std::size_t size() const { return forces.size(); }

    /**
     * @brief Adds a force model of type T with the given constructor arguments.
     *
     * @tparam T Type of the force model to add (no template parameters)
     * @tparam Args Types of the constructor arguments
     * @param args Arguments to pass to the constructor of T
     * @return const std::unique_ptr<PerturbingForce>& Reference to the added force model
     */
    template <typename T, typename... Args>
    const std::unique_ptr<PerturbingForce>& add(Args&&... args)
    {
        static const std::string name = typeid(T).name();
        if (forces.count(name) == 0) { forces.emplace(name, std::make_unique<T>(std::forward<Args>(args)...)); }
        return forces.at(name);
    }

    /**
     * @brief Adds a force model of the form Force<Params...> with the given constructor arguments.
     *
     * Enables the syntax: model.add<Pert, param1, param2>(ctor_arg1, ctor_arg2)
     * which constructs Pert<param1, param2>(ctor_arg1, ctor_arg2).
     *
     * @tparam Pert Template template parameter taking auto... NTTPs
     * @tparam Params Non-type template arguments forwarded to Pert
     * @tparam Args Types of the constructor arguments
     * @param args Arguments to pass to the constructor of Pert<Params...>
     * @return const std::unique_ptr<PerturbingForce>& Reference to the added force model
     */
    template <template <auto...> class Pert, auto... Params, typename... Args>
    const std::unique_ptr<PerturbingForce>& add(Args&&... args)
    {
        using T                       = Pert<Params...>;
        static const std::string name = typeid(T).name();
        if (forces.count(name) == 0) { forces.emplace(name, std::make_unique<T>(std::forward<Args>(args)...)); }
        return forces.at(name);
    }

    /**
     * @brief Computes the total force on a vehicle by summing the forces from all added force models.
     *
     * @param state Cartesian<frames::primary> state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @return Perturbation The total computed perturbation from all force models.
     */
    Perturbation compute_perturbations(const State& state, const Vehicle& vehicle) const;

    /**
     * @brief Retrieves a force model by name.
     *
     * @param name Name of the force model to retrieve
     * @return const std::unique_ptr<PerturbingForce>& Reference to the force model with the given name.
     */
    const std::unique_ptr<PerturbingForce>& at(const std::string& name) const;

    /**
     * @brief Retrieves a force model by type.
     *
     * @tparam T Type of the force model to retrieve
     * @return const std::unique_ptr<PerturbingForce>& Reference to the force model of type T.
     */
    template <typename T>
    const std::unique_ptr<PerturbingForce>& get() const
    {
        static const std::string name = typeid(T).name();
        return forces.at(name);
    }

  private:
    std::unordered_map<std::string, std::unique_ptr<PerturbingForce>> forces; //!< Map of force models by name
};

} // namespace astro
} // namespace astrea