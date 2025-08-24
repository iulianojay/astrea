/**
 * @file Constellation.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>
#include <vector>

#include <astro/platforms/space/Shell.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <units/units.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A Constellation is a collection of Spacecraft, organized into Shells and/or Planes.
 *
 * @tparam Spacecraft_T The type of Spacecraft that this Constellation will contain. Must be derived from Spacecraft.
 * * @note: Defaults to Spacecraft, but can be any class that inherits from Spacecraft.
 */
template <class Spacecraft_T = Spacecraft>
class Constellation {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Constellations must be built of Spacecraft or Derived classes.");

  public:
    /**
     * @brief Default constructor for Constellation.
     */
    Constellation() = default;

    /**
     * @brief Construct a Constellation from a vector of Shells.
     *
     * @param shells A vector of Shells to initialize the Constellation.
     */
    Constellation(std::vector<Shell<Spacecraft_T>> shells);

    /**
     * @brief Construct a Constellation from a vector of Planes.
     *
     * @param planes A vector of Planes to initialize the Constellation.
     */
    Constellation(std::vector<Plane<Spacecraft_T>> planes);

    /**
     * @brief Construct a Constellation from a vector of Spacecraft.
     *
     * @param satellites A vector of Spacecraft to initialize the Constellation.
     */
    Constellation(std::vector<Spacecraft_T> satellites);

    /**
     * @brief Construct a Constellation from a vector of SpaceTrackGP objects.
     *
     * @param gp A vector of snapshot::SpaceTrackGP objects to initialize the Constellation.
     * @param system The AstrodynamicsSystem to use for the Constellation.
     */
    Constellation(const std::vector<snapshot::SpaceTrackGP>& gp, const AstrodynamicsSystem& system);

    /**
     * @brief Construct a Constellation with a specific configuration.
     *
     * @param sys The AstrodynamicsSystem to use for the Constellation.
     * @param epoch The epoch of the Constellation.
     * @param semimajor The semimajor axis of the orbit.
     * @param inclination The inclination of the orbit.
     * @param T The number of shells in the Constellation.
     * @param P The number of planes in each shell.
     * @param F The number of spacecraft in each plane.
     * @param anchorRAAN The right ascension of ascending node (RAAN) for the first shell.
     * @param anchorAnomaly The argument of perigee for the first shell.
     */
    Constellation(
        const AstrodynamicsSystem& sys,
        const Date& epoch,
        const Distance& semimajor,
        const Angle& inclination,
        const std::size_t& T,
        const std::size_t& P,
        const double& F,
        const Angle& anchorRAAN    = 0.0 * mp_units::angular::unit_symbols::rad,
        const Angle& anchorAnomaly = 0.0 * mp_units::angular::unit_symbols::rad
    );

    /**
     * @brief Default destructor for Constellation.
     */
    ~Constellation() = default;

    /**
     * @brief Get the size of the Constellation.
     *
     * @return const std::size_t The number of Spacecraft in the Constellation.
     */
    const std::size_t size() const;

    /**
     * @brief Get the number of shells in the Constellation.
     *
     * @return const std::size_t The number of shells in the Constellation.
     */
    const std::size_t n_shells() const;

    /**
     * @brief Get the number of planes in the Constellation.
     *
     * @return const std::size_t The number of planes in the Constellation.
     */
    const std::size_t n_planes() const;

    // TODO: Add + overloads that accomplish similar things to these methods

    /**
     * @brief Add a Shell to the Constellation.
     *
     * @param shell The Shell to add to the Constellation.
     */
    void add_shell(const Shell<Spacecraft_T>& shell);

    /**
     * @brief Add a Plane to the Constellation with a specific shell ID.
     *
     * @param plane The Plane to add to the Constellation.
     * @param shellId The ID of the shell to which the Plane belongs.
     */
    void add_plane(const Plane<Spacecraft_T>& plane, const std::size_t& shellId);

    /**
     * @brief Add a Plane to the Constellation without specifying a shell ID.
     *
     * @param plane The Plane to add to the Constellation.
     */
    void add_plane(const Plane<Spacecraft_T>& plane);

    /**
     * @brief Add a Spacecraft to a specific Plane in the Constellation.
     *
     * @param spacecraft The Spacecraft to add to the Constellation.
     * @param planeId The ID of the Plane to which the Spacecraft belongs.
     */
    void add_spacecraft(const Spacecraft_T& spacecraft, const std::size_t& planeId);

    /**
     * @brief Add a Spacecraft to the Constellation without specifying a Plane ID.
     *
     * @param spacecraft The Spacecraft to add to the Constellation.
     */
    void add_spacecraft(const Spacecraft_T& spacecraft);

    /**
     * @brief Get all Shells in the Constellation.
     *
     * @return std::vector<Shell<Spacecraft_T>>& A reference to the vector of Shells in the Constellation.
     */
    std::vector<Shell<Spacecraft_T>>& get_shells();

    /**
     * @brief Get all Shells in the Constellation.
     *
     * @return const std::vector<Shell<Spacecraft_T>>& A const reference to the vector of Shells in the Constellation.
     */
    const std::vector<Shell<Spacecraft_T>>& get_shells() const;

    /**
     * @brief Get all Planes in the Constellation.
     *
     * @return std::vector<Plane<Spacecraft_T>>& A reference to the vector of Planes in the Constellation.
     */
    const std::vector<Plane<Spacecraft_T>> get_planes() const;

    /**
     * @brief Get all Spacecraft in the Constellation.
     *
     * @return std::vector<Spacecraft_T> A vector of all Spacecraft in the Constellation.
     */
    const std::vector<Spacecraft_T> get_all_spacecraft() const;

    /**
     * @brief Get a specific Shell by its ID.
     *
     * @param shellId The ID of the Shell to retrieve.
     * @return const Shell<Spacecraft_T>& A const reference to the Shell with the specified ID.
     */
    const Shell<Spacecraft_T>& get_shell(const std::size_t& shellId) const;

    /**
     * @brief Get a specific Plane by its ID.
     *
     * @param planeId The ID of the Plane to retrieve.
     * @return const Plane<Spacecraft_T>& A const reference to the Plane with the specified ID.
     */
    const Plane<Spacecraft_T>& get_plane(const std::size_t& planeId) const;

    /**
     * @brief Get a specific Spacecraft by its ID.
     *
     * @param spacecraftId The ID of the Spacecraft to retrieve.
     * @return const Spacecraft_T& A const reference to the Spacecraft with the specified ID.
     */
    const Spacecraft_T& get_spacecraft(const std::size_t& spacecraftId) const;

    /**
     * @brief Propagate the Constellation using the provided epoch and Equations of Motion.
     *
     * @param epoch The epoch at which to propagate the Constellation.
     * @param eom The Equations of Motion to use for propagation.
     * @param interval The time interval for propagation, defaults to Integrator::defaultInterval.
     */
    void propagate(const Date& epoch, EquationsOfMotion& eom, const Interval& interval = Integrator::defaultInterval);

    /**
     * @brief Propagate the Constellation using the provided epoch, Equations of Motion, and Integrator.
     *
     * @param epoch The epoch at which to propagate the Constellation.
     * @param eom The Equations of Motion to use for propagation.
     * @param integrator The Integrator to use for propagation.
     * @param interval The time interval for propagation, defaults to Integrator::defaultInterval.
     */
    void propagate(const Date& epoch, EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);


    // using iterator       = std::vector<Shell<Spacecraft_T>>::iterator;
    // using const_iterator = std::vector<Shell<Spacecraft_T>>::const_iterator;

    // iterator begin() { return shells.begin(); }
    // iterator end() { return shells.end(); }
    // const_iterator begin() const { return shells.begin(); }
    // const_iterator end() const { return shells.end(); }
    // const_iterator cbegin() const { return shells.cbegin(); }
    // const_iterator cend() const { return shells.cend(); }

    /**
     * @brief Access the Spacecraft at a specific index in the Constellation.
     *
     * @param idx The index of the Spacecraft to access.
     * @return Spacecraft_T& A reference to the Spacecraft at the specified index.
     */
    Spacecraft_T& operator[](const std::size_t idx);

    /**
     * @brief Access the Spacecraft at a specific index in the Constellation.
     *
     * @param idx The index of the Spacecraft to access.
     * @return const Spacecraft_T& A const reference to the Spacecraft at the specified index.
     */
    const Spacecraft_T& operator[](const std::size_t idx) const;

    class sat_iterator; // Forward declaration of the iterator class

    /**
     * @brief Iterator for iterating over all Spacecraft in the Constellation.
     *
     * This iterator allows iteration over all Spacecraft in the Constellation, regardless of their Shell or Plane.
     */
    using iterator = sat_iterator;

    /**
     * @brief Const iterator for iterating over all Spacecraft in the Constellation.
     *
     * This const iterator allows iteration over all Spacecraft in the Constellation, regardless of their Shell or Plane.
     */
    using const_iterator = const sat_iterator;

    /**
     * @brief Get an iterator to the beginning of the Constellation.
     *
     * @return iterator An iterator pointing to the first Spacecraft in the Constellation.
     */
    iterator begin() { return sat_iterator(shells.begin(), shells.begin()->begin()); }

    /**
     * @brief Get an iterator to the end of the Constellation.
     *
     * @return iterator An iterator pointing to one past the last Spacecraft in the Constellation.
     */
    iterator end() { return sat_iterator(shells.end(), shells.end()->end()); }

    /**
     * @brief Get a const iterator to the beginning of the Constellation.
     *
     * @return const_iterator A const iterator pointing to the first Spacecraft in the Constellation.
     */
    const_iterator begin() const { return sat_iterator(shells.begin(), shells.begin()->begin()); }

    /**
     * @brief Get a const iterator to the end of the Constellation.
     *
     * @return const_iterator A const iterator pointing to one past the last Spacecraft in the Constellation.
     */
    const_iterator end() const { return sat_iterator(shells.end(), shells.end()->end()); }

    /**
     * @brief Get a const iterator to the beginning of the Constellation.
     *
     * @return const_iterator A const iterator pointing to the first Spacecraft in the Constellation.
     */
    const_iterator cbegin() const { return sat_iterator(shells.cbegin(), shells.cbegin()->cbegin()); }

    /**
     * @brief Get a const iterator to the end of the Constellation.
     *
     * @return const_iterator A const iterator pointing to one past the last Spacecraft in the Constellation.
     */
    const_iterator cend() const { return sat_iterator(shells.cend(), shells.cend()->cend()); }

    /**
     * @brief Iterator class for iterating over all Spacecraft in the Constellation.
     */
    class sat_iterator {
      private:
        std::vector<Shell<Spacecraft_T>>::iterator iterShell; // Iterator for the Shells in the Constellation
        Shell<Spacecraft_T>::sat_iterator iterSat;            // Iterator for the Spacecraft within the current Shell

      public:
        /**
         * @brief Construct a sat_iterator from a Shell iterator and a Spacecraft iterator.
         *
         * @param _iterShell The iterator for the Shells in the Constellation.
         * @param _iterSat The iterator for the Spacecraft within the current Shell.
         */
        sat_iterator(std::vector<Shell<Spacecraft_T>>::iterator _iterShell, Shell<Spacecraft_T>::sat_iterator _iterSat) :
            iterShell(_iterShell),
            iterSat(_iterSat)
        {
        } // TODO: Sanitize inputs

        /**
         * @brief Pre-increment operator for the sat_iterator.
         *
         * @return sat_iterator& A reference to the incremented iterator.
         */
        sat_iterator& operator++()
        {
            ++iterSat;
            if (iterSat == iterShell->end()) {
                ++iterShell;
                iterSat = iterShell->begin();
            }
            return *this;
        }

        /**
         * @brief Post-increment operator for the sat_iterator.
         *
         * @return sat_iterator A copy of the iterator before incrementing.
         */
        sat_iterator operator++(int)
        {
            sat_iterator retval = *this;
            ++(*this);
            return retval;
        }

        /**
         * @brief Pre-decrement operator for the sat_iterator.
         *
         * @return sat_iterator& A reference to the decremented iterator.
         */
        sat_iterator& operator--()
        {
            --iterSat;
            if (iterSat < iterShell->begin()) {
                --iterShell;
                iterSat = iterShell->end();
            }
            return *this;
        }

        /**
         * @brief Post-decrement operator for the sat_iterator.
         *
         * @return sat_iterator A copy of the iterator before decrementing.
         */
        sat_iterator operator--(int)
        {
            sat_iterator retval = *this;
            --(*this);
            return retval;
        }

        /**
         * @brief Equality operator for the sat_iterator.
         *
         * @param other The other sat_iterator to compare with.
         * @return true if both iterators point to the same Spacecraft, false otherwise.
         */
        bool operator==(const sat_iterator& other) const
        {
            return iterShell == other.iterShell && iterSat == other.iterSat;
        }

        /**
         * @brief Inequality operator for the sat_iterator.
         *
         * @param other The other sat_iterator to compare with.
         * @return true if both iterators do not point to the same Spacecraft, false otherwise.
         */
        bool operator!=(const sat_iterator& other) const { return !(*this == other); }

        /**
         * @brief Less than operator for the sat_iterator.
         *
         * @param other The other sat_iterator to compare with.
         * @return true if this iterator is less than the other, false otherwise.
         * @return false if this iterator is greater than or equal to the other.
         */
        bool operator<(const sat_iterator& other) const
        {
            return iterShell < other.iterShell || (iterShell == other.iterShell && iterSat < other.iterSat);
        }

        /**
         * @brief Greater than operator for the sat_iterator.
         *
         * @param other The other sat_iterator to compare with.
         * @return true if this iterator is greater than the other, false otherwise.
         * @return false if this iterator is less than or equal to the other.
         */
        bool operator>(const sat_iterator& other) const
        {
            return iterShell > other.iterShell || (iterShell == other.iterShell && iterSat > other.iterSat);
        }

        /**
         * @brief Less than or equal to operator for the sat_iterator.
         *
         * @param other The other sat_iterator to compare with.
         * @return true if this iterator is less than or equal to the other, false otherwise.
         * @return false if this iterator is greater than the other.
         */
        bool operator<=(const sat_iterator& other) const
        {
            return iterShell < other.iterShell || (iterShell == other.iterShell && iterSat <= other.iterSat);
        }

        /**
         * @brief Greater than or equal to operator for the sat_iterator.
         *
         * @param other The other sat_iterator to compare with.
         * @return true if this iterator is greater than or equal to the other, false otherwise.
         * @return false if this iterator is less than the other.
         */
        bool operator>=(const sat_iterator& other) const
        {
            return iterShell > other.iterShell || (iterShell == other.iterShell && iterSat >= other.iterSat);
        }

        /**
         * @brief Dereference operator for the sat_iterator.
         *
         * @return Spacecraft_T& A reference to the Spacecraft pointed to by the iterator.
         */
        Spacecraft_T operator*() { return *iterSat; }

      private:
        // iterator traits
        using difference_type = Plane<Spacecraft_T>::iterator;  // Use the iterator type of Plane as the difference type
        using value_type      = Plane<Spacecraft_T>::iterator;  // Use the iterator type of Plane as the value type
        using pointer   = const Plane<Spacecraft_T>::iterator*; // Use the iterator type of Plane as the pointer type
        using reference = const Plane<Spacecraft_T>::iterator&; // Use the iterator type of Plane as the reference type
        using iterator_category = std::forward_iterator_tag;    // Use forward iterator tag for the iterator category
    };

  private:
    std::size_t id;                          // Unique identifier for the Constellation
    std::string name;                        // Name of the Constellation
    std::vector<Shell<Spacecraft_T>> shells; // Vector of Shells in the Constellation

    /**
     * @brief Generate a unique ID hash for the Constellation.
     */
    void generate_id_hash();
};

} // namespace astro
} // namespace astrea

#include <astro/platforms/space/Constellation.ipp>
