#pragma once

#ifndef SWIG
    #include <vector>
    #include <string>
#endif

#include <astro/platforms/space/Plane.hpp>
#include <astro/propagation/Integrator.hpp>

#include <astro/astro.fwd.hpp>

class Shell {

    friend class Constellation;

public:

    Shell() = default;
    Shell(std::vector<Plane> planes);
    Shell(std::vector<Spacecraft> satellites);
    Shell(const double& semimajor, const double& inclination, const size_t& T, const size_t& P, const double& F,
        const double& anchorRAAN = 0.0, const double& anchorAnomaly = 0.0);
    ~Shell() = default;

    const size_t size() const;
    const size_t n_planes() const;

    void add_plane(const Plane& plane);
    void add_spacecraft(const Spacecraft& spacecraft, const size_t& planeId);
    void add_spacecraft(const Spacecraft& spacecraft);

    const std::vector<Plane>& get_all_planes() const;
    const std::vector<Spacecraft> get_all_spacecraft() const;

    const Plane& get_plane(const size_t& planeId) const;
    const Spacecraft& get_spacecraft(const size_t& spacecraftId) const;

    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);


    using iterator = std::vector<Plane>::iterator;

    iterator begin() { return planes.begin(); }
    iterator end() { return planes.end(); }

    class sat_iterator;

    sat_iterator sat_begin() { return sat_iterator(planes.begin(), planes.begin()->begin()); }
    sat_iterator sat_end() { return sat_iterator(planes.end(), planes.end()->end()); }

    class sat_iterator {
    private:

        iterator iterPlane;
        Plane::iterator iterSat;

    public:

        sat_iterator(iterator _iterPlane, Plane::iterator _iterSat) :
            iterPlane(_iterPlane), iterSat(_iterSat) {} // TODO: Sanitize inputs

        sat_iterator& operator++() {
            ++iterSat;
            if (iterSat == iterPlane->end()) {
                ++iterPlane;
                iterSat = iterPlane->begin();
            }
            return *this;
        }
        sat_iterator operator++(int) {
            sat_iterator retval = *this; ++(*this);
            return retval;
        }

        sat_iterator& operator--() {
            --iterSat;
            if (iterSat < iterPlane->begin()) {
                --iterPlane;
                iterSat = iterPlane->end();
            }
            return *this;
        }
        sat_iterator operator--(int) {
            sat_iterator retval = *this; --(*this);
            return retval;
        }

        bool operator==(const sat_iterator& other) const { return iterPlane == other.iterPlane && iterSat == other.iterSat; }
        bool operator!=(const sat_iterator& other) const { return !(*this == other); }
        bool operator<(const sat_iterator& other) const { return iterPlane < other.iterPlane || (iterPlane == other.iterPlane && iterSat < other.iterSat); }
        bool operator>(const sat_iterator& other) const { return iterPlane > other.iterPlane || (iterPlane == other.iterPlane && iterSat > other.iterSat); }
        bool operator<=(const sat_iterator& other) const { return iterPlane < other.iterPlane || (iterPlane == other.iterPlane && iterSat <= other.iterSat); }
        bool operator>=(const sat_iterator& other) const { return iterPlane > other.iterPlane || (iterPlane == other.iterPlane && iterSat >= other.iterSat); }
        Spacecraft operator*() { return *iterSat; }

        // iterator traits
        using difference_type = Plane::iterator;
        using value_type = Plane::iterator;
        using pointer = const Plane::iterator*;
        using reference = const Plane::iterator&;
        using iterator_category = std::forward_iterator_tag;
    };

    const size_t get_id() const { return id; }

private:

    size_t id;
    std::string name;
    std::vector<Plane> planes;

    void generate_id_hash();

};


#ifdef SWIG

%template(ShellVector) std::vector<Shell>;

#endif