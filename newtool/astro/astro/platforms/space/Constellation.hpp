#pragma once

#ifndef SWIG
#include <string>
#include <vector>
#endif

#include <astro/platforms/space/Shell.hpp>
#include <astro/propagation/Integrator.hpp>

class Constellation {
  public:
    Constellation() = default;
    Constellation(std::vector<Shell> shells);
    Constellation(std::vector<Plane> planes);
    Constellation(std::vector<Spacecraft> satellites);
    Constellation(
        const double& semimajor,
        const double& inclination,
        const size_t& T,
        const size_t& P,
        const double& F,
        const double& anchorRAAN    = 0.0,
        const double& anchorAnomaly = 0.0);

    ~Constellation() = default;

    const size_t size() const;
    const size_t n_shells() const;
    const size_t n_planes() const;

    // TODO: Add + overloads that accomplish similar things to these methods
    void add_shell(const Shell& shell);
    void add_plane(const Plane& plane, const size_t& shellId);
    void add_plane(const Plane& plane);
    void add_spacecraft(const Spacecraft& spacecraft, const size_t& planeId);
    void add_spacecraft(const Spacecraft& spacecraft);

    const std::vector<Shell>& get_all_shells() const;
    const std::vector<Plane> get_all_planes() const;
    const std::vector<Spacecraft> get_all_spacecraft() const;

    const Shell& get_shell(const size_t& shellId) const;
    const Plane& get_plane(const size_t& planeId) const;
    const Spacecraft& get_spacecraft(const size_t& spacecraftId) const;

    void propagate(EquationsOfMotion& eom, const Interval& interval = Integrator::defaultInterval);
    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);


    using iterator = std::vector<Shell>::iterator;

    iterator begin() { return shells.begin(); }
    iterator end() { return shells.end(); }

    class sat_iterator;

    sat_iterator sat_begin() { return sat_iterator(shells.begin(), shells.begin()->sat_begin()); }
    sat_iterator sat_end() { return sat_iterator(shells.end(), shells.end()->sat_end()); }

    class sat_iterator {
      private:
        iterator iterShell;
        Shell::sat_iterator iterSat;

      public:
        sat_iterator(iterator _iterShell, Shell::sat_iterator _iterSat) :
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
        Spacecraft operator*() { return *iterSat; }

      private:
        // iterator traits
        using difference_type   = Plane::iterator;
        using value_type        = Plane::iterator;
        using pointer           = const Plane::iterator*;
        using reference         = const Plane::iterator&;
        using iterator_category = std::forward_iterator_tag;
    };

  private:
    size_t id;
    std::string name;
    std::vector<Shell> shells;

    void generate_id_hash();
};


#ifdef SWIG

%template(ConstellationVector) std::vector<Constellation>;

#endif