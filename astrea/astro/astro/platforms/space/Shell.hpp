/**
 * @file Shell.hpp
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/platforms/space/Plane.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A Shell is a collection of planes, each containing a set of Spacecraft.
 * It is used to represent sub-constellations of satellites in orbit.
 *
 * @tparam Spacecraft_T The type of spacecraft contained in the shell, must derive from Spacecraft.
 * * @note This class is templated to allow for different types of spacecraft, but it must be derived from the Spacecraft base class.
 */
template <class Spacecraft_T = Spacecraft>
class Shell {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Shells must be built of Spacecraft or Derived classes.");

    friend class Constellation<Spacecraft_T>;

  public:
    /**
     * @brief Default constructor for Shell.
     * Initializes an empty shell with no planes or spacecraft.
     */
    Shell() = default;

    /**
     * @brief Constructor for Shell with a vector of planes.
     * @param planes A vector of Plane objects containing Spacecraft_T.
     */
    Shell(std::vector<Plane<Spacecraft_T>> planes);

    /**
     * @brief Constructor for Shell with a vector of satellites.
     * @param satellites A vector of Spacecraft_T objects to be added to the shell.
     */
    Shell(std::vector<Spacecraft_T> satellites);

    /**
     * @brief Constructor for Shell with a Walker parameters.
     * @param sys The astrodynamics system to which the shell belongs.
     * @param epoch The epoch date for the shell's orbit.
     * @param semimajor The semimajor axis of the shell's orbit.
     * @param inclination The inclination of the shell's orbit.
     * @param T The number of planes in the shell.
     * @param P The number of spacecraft per plane.
     * @param F The spacing factor between spacecraft in the same plane.
     * @param anchorRAAN The right ascension of ascending node for the shell's orbit (default is 0).
     * @param anchorAnomaly The argument of perigee for the shell's orbit (default is 0).
     */
    Shell(
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
     * @brief Destructor for Shell.
     * Cleans up the shell and its planes.
     */
    ~Shell() = default;

    /**
     * @brief Returns the size of the shell, which is the number of spacecraft it contains.
     *
     * @return const std::size_t The number of spacecraft in the shell.
     */
    const std::size_t size() const;

    /**
     * @brief Returns the number of planes in the shell.
     *
     * @return const std::size_t The number of planes in the shell.
     */
    const std::size_t n_planes() const;

    /**
     * @brief Adds a plane to the shell.
     *
     * @param plane The Plane object to be added to the shell.
     */
    void add_plane(const Plane<Spacecraft_T>& plane);

    /**
     * @brief Adds a spacecraft to a specific plane in the shell.
     *
     * @param spacecraft The Spacecraft_T object to be added.
     * @param planeId The ID of the plane to which the spacecraft will be added.
     */
    void add_spacecraft(const Spacecraft_T& spacecraft, const std::size_t& planeId);

    /**
     * @brief Adds a spacecraft to the shell.
     *
     * @param spacecraft The Spacecraft_T object to be added.
     */
    void add_spacecraft(const Spacecraft_T& spacecraft);

    /**
     * @brief Returns a reference to the vector of planes in the shell.
     *
     * @return std::vector<Plane<Spacecraft_T>>& A reference to the vector of planes in the shell.
     */
    std::vector<Plane<Spacecraft_T>>& get_planes();

    /**
     * @brief Returns a constant reference to the vector of planes in the shell.
     *
     * @return const std::vector<Plane<Spacecraft_T>>& A constant reference to the vector of planes in the shell.
     */
    const std::vector<Plane<Spacecraft_T>>& get_planes() const;

    /**
     * @brief Returns a vector of all spacecraft in the shell.
     *
     * @return const std::vector<Spacecraft_T> A vector containing all spacecraft in the shell.
     */
    const std::vector<Spacecraft_T> get_all_spacecraft() const;

    /**
     * @brief Returns a reference to a specific plane in the shell by its ID.
     *
     * @param planeId The ID of the plane to retrieve.
     * @return const Plane<Spacecraft_T>& A constant reference to the specified plane.
     */
    const Plane<Spacecraft_T>& get_plane(const std::size_t& planeId) const;

    /**
     * @brief Returns a reference to a specific spacecraft in the shell by its ID.
     *
     * @param spacecraftId The ID of the spacecraft to retrieve.
     * @return const Spacecraft_T& A constant reference to the specified spacecraft.
     */
    const Spacecraft_T& get_spacecraft(const std::size_t& spacecraftId) const;

    /**
     * @brief Propagates the shell's spacecraft using the provided equations of motion and integrator.
     *
     * @param epoch The epoch date for the propagation.
     * @param eom The equations of motion to be used for propagation.
     * @param integrator The integrator to be used for numerical integration.
     * @param interval The time interval for propagation (default is Integrator::defaultInterval).
     */
    void propagate(const Date& epoch, EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);


    // using iterator       = std::vector<Plane<Spacecraft_T>>::iterator;
    // using const_iterator = std::vector<Plane<Spacecraft_T>>::const_iterator;

    // iterator begin() { return planes.begin(); }
    // iterator end() { return planes.end(); }
    // const_iterator begin() const { return planes.begin(); }
    // const_iterator end() const { return planes.end(); }
    // const_iterator cbegin() const { return planes.cbegin(); }
    // const_iterator cend() const { return planes.cend(); }

    class sat_iterator; // Forward declaration of the iterator class for iterating over spacecraft in the shell

    /**
     * @brief Iterator for iterating over all Planes in the Shell.
     */
    using iterator = sat_iterator;

    /**
     * @brief Const iterator for iterating over all Planes in the Shell.
     */
    using const_iterator = const sat_iterator;

    /**
     * @brief Get an iterator to the beginning of the Shell.
     * @return iterator An iterator pointing to the first Plane in the Shell.
     */
    iterator begin() { return sat_iterator(planes.begin(), planes.begin()->begin()); }

    /**
     * @brief Get an iterator to the end of the Shell.
     * @return iterator An iterator pointing to one past the last Plane in the Shell.
     */
    iterator end() { return sat_iterator(planes.end(), planes.end()->end()); }

    /**
     * @brief Get a const iterator to the beginning of the Shell.
     * @return const_iterator A const iterator pointing to the first Plane in the Shell.
     */
    const_iterator begin() const { return sat_iterator(planes.begin(), planes.begin()->begin()); }

    /**
     * @brief Get a const iterator to the end of the Shell.
     * @return const_iterator A const iterator pointing to one past the last Plane in the Shell.
     */
    const_iterator end() const { return sat_iterator(planes.end(), planes.end()->end()); }

    /**
     * @brief Get a const iterator to the beginning of the Shell.
     * @return const_iterator A const iterator pointing to the first Plane in the Shell.
     */
    const_iterator cbegin() const { return sat_iterator(planes.cbegin(), planes.cbegin()->cbegin()); }

    /**
     * @brief Get a const iterator to the end of the Shell.
     * @return const_iterator A const iterator pointing to one past the last Plane in the Shell.
     */
    const_iterator cend() const { return sat_iterator(planes.cend(), planes.cend()->cend()); }

    /**
     * @brief Iterator for iterating over all Spacecraft in the Shell.
     */
    class sat_iterator {
      private:
        std::vector<Plane<Spacecraft_T>>::iterator iterPlane; // Iterator for the vector of planes
        Plane<Spacecraft_T>::iterator iterSat;                // Iterator for the current plane's spacecraft

      public:
        /**
         * @brief Default constructor for sat_iterator.
         * Initializes the iterator to the beginning of the first plane's spacecraft.
         */
        sat_iterator(std::vector<Plane<Spacecraft_T>>::iterator _iterPlane, Plane<Spacecraft_T>::iterator _iterSat) :
            iterPlane(_iterPlane),
            iterSat(_iterSat)
        {
        } // TODO: Sanitize inputs

        /**
         * @brief Increment operator for the sat_iterator.
         *
         * @return sat_iterator& A reference to the incremented iterator.
         */
        sat_iterator& operator++()
        {
            ++iterSat;
            if (iterSat == iterPlane->end()) {
                ++iterPlane;
                iterSat = iterPlane->begin();
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
         * @brief Decrement operator for the sat_iterator.
         *
         * @return sat_iterator& A reference to the decremented iterator.
         */
        sat_iterator& operator--()
        {
            --iterSat;
            if (iterSat < iterPlane->begin()) {
                --iterPlane;
                iterSat = iterPlane->end();
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
         * @brief Comparison operators for the sat_iterator.
         *
         * @param other The other iterator to compare against.
         * @return bool True if the iterators are equal, false otherwise.
         */
        bool operator==(const sat_iterator& other) const
        {
            return iterPlane == other.iterPlane && iterSat == other.iterSat;
        }

        /**
         * @brief Inequality operator for the sat_iterator.
         *
         * @param other The other iterator to compare against.
         * @return bool True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const sat_iterator& other) const { return !(*this == other); }

        /**
         * @brief Less than operator for the sat_iterator.
         *
         * @param other The other iterator to compare against.
         * @return true if this iterator is less than the other, false otherwise.
         * @return false if this iterator is not less than the other.
         */
        bool operator<(const sat_iterator& other) const
        {
            return iterPlane < other.iterPlane || (iterPlane == other.iterPlane && iterSat < other.iterSat);
        }

        /**
         * @brief Greater than operator for the sat_iterator.
         *
         * @param other The other iterator to compare against.
         * @return true if this iterator is greater than the other, false otherwise.
         * @return false if this iterator is not greater than the other.
         */
        bool operator>(const sat_iterator& other) const
        {
            return iterPlane > other.iterPlane || (iterPlane == other.iterPlane && iterSat > other.iterSat);
        }

        /**
         * @brief Less than or equal to operator for the sat_iterator.
         *
         * @param other The other iterator to compare against.
         * @return true if this iterator is less than or equal to the other, false otherwise.
         * @return false if this iterator is not less than or equal to the other.
         */
        bool operator<=(const sat_iterator& other) const
        {
            return iterPlane < other.iterPlane || (iterPlane == other.iterPlane && iterSat <= other.iterSat);
        }

        /**
         * @brief Greater than or equal to operator for the sat_iterator.
         *
         * @param other The other iterator to compare against.
         * @return true if this iterator is greater than or equal to the other, false otherwise.
         * @return false if this iterator is not greater than or equal to the other.
         */
        bool operator>=(const sat_iterator& other) const
        {
            return iterPlane > other.iterPlane || (iterPlane == other.iterPlane && iterSat >= other.iterSat);
        }

        /**
         * @brief Dereference operator for the sat_iterator.
         *
         * @return Spacecraft_T& A reference to the spacecraft at the current iterator position.
         */
        Spacecraft_T operator*() { return *iterSat; }

        // iterator traits
        using difference_type = Plane<Spacecraft_T>::iterator;  // Use the iterator type of Plane as the difference type
        using value_type      = Plane<Spacecraft_T>::iterator;  // Use the iterator type of Plane as the value type
        using pointer   = const Plane<Spacecraft_T>::iterator*; // Use the iterator type of Plane as the pointer type
        using reference = const Plane<Spacecraft_T>::iterator&; // Use the iterator type of Plane as the reference type
        using iterator_category = std::forward_iterator_tag;    // Use forward iterator tag for the iterator category
    };

    const std::size_t get_id() const { return id; }

  private:
    std::size_t id;
    std::string name;
    std::vector<Plane<Spacecraft_T>> planes;

    void generate_id_hash();
};

} // namespace astro
} // namespace astrea

#include <astro/platforms/space/Shell.ipp>
