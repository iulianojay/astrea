#pragma once

#include <string>
#include <vector>

#include <astro/platforms/space/Plane.hpp>
#include <astro/propagation/numerical/Integrator.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/orbital_elements/Keplerian.hpp>
#include <astro/units/units.hpp>

namespace astro {

template <class Spacecraft_T = Spacecraft>
class Shell {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Shells must be built of Spacecraft or Derived classes.");

    friend class Constellation<Spacecraft_T>;

  public:
    Shell() = default;
    Shell(std::vector<Plane<Spacecraft_T>> planes);
    Shell(std::vector<Spacecraft_T> satellites);
    Shell(
        const Distance& semimajor,
        const Angle& inclination,
        const std::size_t& T,
        const std::size_t& P,
        const double& F,
        const Angle& anchorRAAN    = 0.0 * mp_units::angular::unit_symbols::rad,
        const Angle& anchorAnomaly = 0.0 * mp_units::angular::unit_symbols::rad
    );
    ~Shell() = default;

    const std::size_t size() const;
    const std::size_t n_planes() const;

    void add_plane(const Plane<Spacecraft_T>& plane);
    void add_spacecraft(const Spacecraft_T& spacecraft, const std::size_t& planeId);
    void add_spacecraft(const Spacecraft_T& spacecraft);

    const std::vector<Plane<Spacecraft_T>>& get_all_planes() const;
    const std::vector<Spacecraft_T> get_all_spacecraft() const;

    const Plane<Spacecraft_T>& get_plane(const std::size_t& planeId) const;
    const Spacecraft_T& get_spacecraft(const std::size_t& spacecraftId) const;

    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);


    using iterator       = std::vector<Plane<Spacecraft_T>>::iterator;
    using const_iterator = std::vector<Plane<Spacecraft_T>>::const_iterator;

    iterator begin() { return planes.begin(); }
    iterator end() { return planes.end(); }
    const_iterator begin() const { return planes.begin(); }
    const_iterator end() const { return planes.end(); }
    const_iterator cbegin() const { return planes.cbegin(); }
    const_iterator cend() const { return planes.cend(); }

    class sat_iterator;

    sat_iterator sat_begin() { return sat_iterator(planes.begin(), planes.begin()->begin()); }
    sat_iterator sat_end() { return sat_iterator(planes.end(), planes.end()->end()); }

    class sat_iterator {
      private:
        iterator iterPlane;
        Plane<Spacecraft_T>::iterator iterSat;

      public:
        sat_iterator(iterator _iterPlane, Plane<Spacecraft_T>::iterator _iterSat) :
            iterPlane(_iterPlane),
            iterSat(_iterSat)
        {
        } // TODO: Sanitize inputs

        sat_iterator& operator++()
        {
            ++iterSat;
            if (iterSat == iterPlane->end()) {
                ++iterPlane;
                iterSat = iterPlane->begin();
            }
            return *this;
        }
        sat_iterator operator++(int)
        {
            sat_iterator retval = *this;
            ++(*this);
            return retval;
        }

        sat_iterator& operator--()
        {
            --iterSat;
            if (iterSat < iterPlane->begin()) {
                --iterPlane;
                iterSat = iterPlane->end();
            }
            return *this;
        }
        sat_iterator operator--(int)
        {
            sat_iterator retval = *this;
            --(*this);
            return retval;
        }

        bool operator==(const sat_iterator& other) const
        {
            return iterPlane == other.iterPlane && iterSat == other.iterSat;
        }
        bool operator!=(const sat_iterator& other) const { return !(*this == other); }
        bool operator<(const sat_iterator& other) const
        {
            return iterPlane < other.iterPlane || (iterPlane == other.iterPlane && iterSat < other.iterSat);
        }
        bool operator>(const sat_iterator& other) const
        {
            return iterPlane > other.iterPlane || (iterPlane == other.iterPlane && iterSat > other.iterSat);
        }
        bool operator<=(const sat_iterator& other) const
        {
            return iterPlane < other.iterPlane || (iterPlane == other.iterPlane && iterSat <= other.iterSat);
        }
        bool operator>=(const sat_iterator& other) const
        {
            return iterPlane > other.iterPlane || (iterPlane == other.iterPlane && iterSat >= other.iterSat);
        }
        Spacecraft_T operator*() { return *iterSat; }

        // iterator traits
        using difference_type   = Plane<Spacecraft_T>::iterator;
        using value_type        = Plane<Spacecraft_T>::iterator;
        using pointer           = const Plane<Spacecraft_T>::iterator*;
        using reference         = const Plane<Spacecraft_T>::iterator&;
        using iterator_category = std::forward_iterator_tag;
    };

    const std::size_t get_id() const { return id; }

  private:
    std::size_t id;
    std::string name;
    std::vector<Plane<Spacecraft_T>> planes;

    void generate_id_hash();
};

} // namespace astro

#include <astro/platforms/space/Shell.ipp>
