/**
 * @file Plane.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/numerical/Integrator.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A Plane is a collection of Spacecraft that share the same orbital elements.
 *
 * @tparam Spacecraft_T The type of Spacecraft that this Plane will contain. Must be derived from Spacecraft.
 * * @note This class is templated to allow for different types of Spacecraft, but it is expected that the type will be derived from Spacecraft.
 */
template <class Spacecraft_T = Spacecraft>
class Plane {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Planes must be built of Spacecraft or Derived classes.");

    friend class Shell<Spacecraft_T>;
    friend class Constellation<Spacecraft_T>;

  public:
    /**
     * @brief Default constructor for Plane.
     */
    Plane() = default;

    /**
     * @brief Construct a Plane from a vector of Spacecraft.
     *
     * @param satellites A vector of Spacecraft to initialize the Plane.
     */
    Plane(std::vector<Spacecraft_T> satellites);

    /**
     * @brief Destructor for Plane.
     */
    ~Plane() = default;

    /**
     * @brief Add a Spacecraft to the Plane.
     *
     * @param spacecraft The Spacecraft to add to the Plane.
     */
    void add_spacecraft(const Spacecraft_T& spacecraft);

    /**
     * @brief Get all Spacecraft in the Plane.
     *
     * @return std::vector<Spacecraft_T>& A reference to the vector of Spacecraft in the Plane.
     */
    std::vector<Spacecraft_T>& get_all_spacecraft();

    /**
     * @brief Get all Spacecraft in the Plane.
     *
     * @return const std::vector<Spacecraft_T>& A const reference to the vector of Spacecraft in the Plane.
     */
    const std::vector<Spacecraft_T>& get_all_spacecraft() const;

    /**
     * @brief Get a Spacecraft by its ID.
     *
     * @param spacecraftId The ID of the Spacecraft to retrieve.
     * @return Spacecraft_T& A reference to the Spacecraft with the specified ID.
     */
    const Spacecraft_T& get_spacecraft(const std::size_t& spacecraftId) const;

    /**
     * @brief Get the number of Spacecraft in the Plane.
     *
     * @return std::size_t The number of Spacecraft in the Plane.
     */
    const std::size_t size() const;

    /**
     * @brief Propagate the Plane using the provided epoch and Equations of Motion.
     *
     * @param epoch The epoch at which to propagate the Plane.
     * @param eom The Equations of Motion to use for propagation.
     * @param interval The time interval for propagation, defaults to Integrator::defaultInterval.
     */
    void propagate(const Date& epoch, EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);

    /**
     * @brief Iterator for iterating over all Spacecraft in the Plane.
     */
    using iterator = std::vector<Spacecraft_T>::iterator;

    /**
     * @brief Const iterator for iterating over all Spacecraft in the Plane.
     */
    using const_iterator = std::vector<Spacecraft_T>::const_iterator;

    /**
     * @brief Get an iterator to the beginning of the Plane.
     *
     * @return iterator An iterator pointing to the first Spacecraft in the Plane.
     */
    iterator begin() { return satellites.begin(); }

    /**
     * @brief Get an iterator to the end of the Plane.
     *
     * @return iterator An iterator pointing to one past the last Spacecraft in the Plane.
     */
    iterator end() { return satellites.end(); }

    /**
     * @brief Get a const iterator to the beginning of the Plane.
     *
     * @return const_iterator A const iterator pointing to the first Spacecraft in the Plane.
     */
    const_iterator begin() const { return satellites.begin(); }

    /**
     * @brief Get a const iterator to the end of the Plane.
     *
     * @return const_iterator A const iterator pointing to one past the last Spacecraft in the Plane.
     */
    const_iterator end() const { return satellites.end(); }

    /**
     * @brief Get a const iterator to the beginning of the Plane.
     *
     * @return const_iterator A const iterator pointing to the first Spacecraft in the Plane.
     */
    const_iterator cbegin() const { return satellites.cbegin(); }

    /**
     * @brief Get a const iterator to the end of the Plane.
     *
     * @return const_iterator A const iterator pointing to one past the last Spacecraft in the Plane.
     */
    const_iterator cend() const { return satellites.cend(); }

    /**
     * @brief Get the ID of the Plane.
     *
     * @return const std::size_t The unique identifier for the Plane.
     */
    const std::size_t get_id() const { return id; }

  private:
    std::size_t id;                       // Unique identifier for the Plane
    OrbitalElements elements;             // Orbital elements shared by all Spacecraft in the Plane
    std::vector<Spacecraft_T> satellites; // Vector of Spacecraft in the Plane

    bool strict; // Flag to indicate if the Plane is strict (all Spacecraft must have the same orbital elements)

    /**
     * @brief Generate a unique ID hash for the Plane.
     *
     * This function generates a unique ID hash for the Plane based on its contents.
     */
    void generate_id_hash();
};

} // namespace astro
} // namespace astrea

#include <astro/platforms/space/Plane.ipp>
