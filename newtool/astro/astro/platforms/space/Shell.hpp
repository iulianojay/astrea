#pragma once

#ifndef SWIG
#include <string>
#include <vector>
#endif

#include <astro/platforms/space/Plane.hpp>
#include <astro/propagation/Integrator.hpp>

#include <astro/astro.fwd.hpp>

template <class Spacecraft_T = Spacecraft>
class Shell {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Shells must be built of Spacecraft or Derived classes.");

    friend class Constellation<Spacecraft_T>;

  public:
    Shell() = default;
    Shell(std::vector<Plane<Spacecraft_T>> planes);
    Shell(std::vector<Spacecraft_T> satellites);
    Shell(
        const double& semimajor,
        const double& inclination,
        const size_t& T,
        const size_t& P,
        const double& F,
        const double& anchorRAAN    = 0.0,
        const double& anchorAnomaly = 0.0
    );
    ~Shell() = default;

    const size_t size() const;
    const size_t n_planes() const;

    void add_plane(const Plane<Spacecraft_T>& plane);
    void add_spacecraft(const Spacecraft_T& spacecraft, const size_t& planeId);
    void add_spacecraft(const Spacecraft_T& spacecraft);

    const std::vector<Plane<Spacecraft_T>>& get_all_planes() const;
    const std::vector<Spacecraft_T> get_all_spacecraft() const;

    const Plane<Spacecraft_T>& get_plane(const size_t& planeId) const;
    const Spacecraft_T& get_spacecraft(const size_t& spacecraftId) const;

    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);


    using iterator = std::vector<Plane<Spacecraft_T>>::iterator;

    iterator begin() { return planes.begin(); }
    iterator end() { return planes.end(); }

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

    const size_t get_id() const { return id; }

  private:
    size_t id;
    std::string name;
    std::vector<Plane<Spacecraft_T>> planes;

    void generate_id_hash();
};

#include <astro/platforms/space/Shell.ipp>

#ifdef SWIG

%template(ShellVector) std::vector<Shell>;

#endif