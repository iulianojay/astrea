#pragma once

#include <string>
#include <vector>

#include <astro/platforms/space/Shell.hpp>
#include <astro/propagation/Integrator.hpp>

namespace astro {

template <class Spacecraft_T = Spacecraft>
class Constellation {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Constellations must be built of Spacecraft or Derived classes.");

  public:
    Constellation() = default;
    Constellation(std::vector<Shell<Spacecraft_T>> shells);
    Constellation(std::vector<Plane<Spacecraft_T>> planes);
    Constellation(std::vector<Spacecraft_T> satellites);
    Constellation(
        const double& semimajor,
        const double& inclination,
        const size_t& T,
        const size_t& P,
        const double& F,
        const double& anchorRAAN    = 0.0,
        const double& anchorAnomaly = 0.0
    );

    ~Constellation() = default;

    const size_t size() const;
    const size_t n_shells() const;
    const size_t n_planes() const;

    // TODO: Add + overloads that accomplish similar things to these methods
    void add_shell(const Shell<Spacecraft_T>& shell);
    void add_plane(const Plane<Spacecraft_T>& plane, const size_t& shellId);
    void add_plane(const Plane<Spacecraft_T>& plane);
    void add_spacecraft(const Spacecraft_T& spacecraft, const size_t& planeId);
    void add_spacecraft(const Spacecraft_T& spacecraft);

    const std::vector<Shell<Spacecraft_T>>& get_all_shells() const;
    const std::vector<Plane<Spacecraft_T>> get_all_planes() const;
    const std::vector<Spacecraft_T> get_all_spacecraft() const;

    const Shell<Spacecraft_T>& get_shell(const size_t& shellId) const;
    const Plane<Spacecraft_T>& get_plane(const size_t& planeId) const;
    const Spacecraft_T& get_spacecraft(const size_t& spacecraftId) const;

    void propagate(EquationsOfMotion& eom, const Interval& interval = Integrator::defaultInterval);
    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);


    using iterator = std::vector<Shell<Spacecraft_T>>::iterator;

    iterator begin() { return shells.begin(); }
    iterator end() { return shells.end(); }

    class sat_iterator;

    sat_iterator sat_begin() { return sat_iterator(shells.begin(), shells.begin()->sat_begin()); }
    sat_iterator sat_end() { return sat_iterator(shells.end(), shells.end()->sat_end()); }

    class sat_iterator {
      private:
        iterator iterShell;
        Shell<Spacecraft_T>::sat_iterator iterSat;

      public:
        sat_iterator(iterator _iterShell, Shell<Spacecraft_T>::sat_iterator _iterSat) :
            iterShell(_iterShell),
            iterSat(_iterSat)
        {
        } // TODO: Sanitize inputs

        sat_iterator& operator++()
        {
            ++iterSat;
            if (iterSat == iterShell->sat_end()) {
                ++iterShell;
                iterSat = iterShell->sat_begin();
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
            if (iterSat < iterShell->sat_begin()) {
                --iterShell;
                iterSat = iterShell->sat_end();
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
            return iterShell == other.iterShell && iterSat == other.iterSat;
        }
        bool operator!=(const sat_iterator& other) const { return !(*this == other); }
        bool operator<(const sat_iterator& other) const
        {
            return iterShell < other.iterShell || (iterShell == other.iterShell && iterSat < other.iterSat);
        }
        bool operator>(const sat_iterator& other) const
        {
            return iterShell > other.iterShell || (iterShell == other.iterShell && iterSat > other.iterSat);
        }
        bool operator<=(const sat_iterator& other) const
        {
            return iterShell < other.iterShell || (iterShell == other.iterShell && iterSat <= other.iterSat);
        }
        bool operator>=(const sat_iterator& other) const
        {
            return iterShell > other.iterShell || (iterShell == other.iterShell && iterSat >= other.iterSat);
        }
        Spacecraft_T operator*() { return *iterSat; }

      private:
        // iterator traits
        using difference_type   = Plane<Spacecraft_T>::iterator;
        using value_type        = Plane<Spacecraft_T>::iterator;
        using pointer           = const Plane<Spacecraft_T>::iterator*;
        using reference         = const Plane<Spacecraft_T>::iterator&;
        using iterator_category = std::forward_iterator_tag;
    };

  private:
    size_t id;
    std::string name;
    std::vector<Shell<Spacecraft_T>> shells;

    void generate_id_hash();
};

} // namespace astro

#include <astro/platforms/space/Constellation.ipp>
