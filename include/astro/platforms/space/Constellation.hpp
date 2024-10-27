#pragma once

#ifndef SWIG
    #include <vector>
    #include <string>
#endif

#include "Shell.hpp"
#include "Integrator.hpp"

class Constellation {
public:

    Constellation() = default;
    Constellation(std::vector<Shell> shells);
    Constellation(std::vector<Plane> planes);
    Constellation(std::vector<Spacecraft> satellites);

    ~Constellation() = default;

    const size_t size() const;
    const size_t n_shells() const;
    const size_t n_planes() const;

    //TODO: Add + overloads that accomplish similar things to these methods
    void add_shell(const Shell& shell);
    void add_plane(const Plane& plane, const int& shellId);
    void add_plane(const Plane& plane);
    void add_spacecraft(const Spacecraft& spacecraft, const int& planeId);
    void add_spacecraft(const Spacecraft& spacecraft);

    const std::vector<Shell>& get_all_shells() const;
    const std::vector<Plane> get_all_planes() const;
    const std::vector<Spacecraft> get_all_spacecraft() const;

    const Shell& get_shell(const int& shellId) const;
    const Plane& get_plane(const int& planeId) const;
    const Spacecraft& get_spacecraft(const int& spacecraftId) const;

    void propagate(const Interval& interval = Integrator::defaultInterval);
    void propagate(const AstrodynamicsSystem& sys, const Interval& interval = Integrator::defaultInterval);
    void propagate(EquationsOfMotion& eom, const Interval& interval = Integrator::defaultInterval);
    void propagate(Integrator& integrator, const Interval& interval = Integrator::defaultInterval);
    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);


    using iterator = std::vector<Shell>::iterator;

    class sat_iterator {
    private:

        iterator iterShell;
        Shell::iterator iterPlane;
        Plane::iterator iterSat;

    public:

        sat_iterator(iterator _iterShell, Shell::iterator _iterPlane, Plane::iterator _iterSat) :
            iterShell(_iterShell), iterPlane(_iterPlane), iterSat(_iterSat) {} // TODO: Sanitize inputs

        sat_iterator& operator++() {
            ++iterSat;
            if (iterSat == (*iterPlane).end()) {
                ++iterPlane;
                iterSat = (*iterPlane).begin();

                if (iterPlane == (*iterShell).end()) {
                    ++iterShell;
                    iterPlane = (*iterShell).begin();
                }
            }
            return *this;
        }
        sat_iterator operator++(int) {
            sat_iterator retval = *this; ++(*this);
            return retval;
        }

        sat_iterator& operator--() {
            --iterSat;
            if (iterSat < (*iterPlane).begin()) {
                --iterPlane;
                iterSat = (*iterPlane).end();

                if (iterPlane < (*iterShell).begin()) {
                    --iterShell;
                    iterPlane = (*iterShell).begin();
                }
            }
            return *this;
        }
        sat_iterator operator--(int) {
            sat_iterator retval = *this; --(*this);
            return retval;
        }

        bool operator==(sat_iterator other) const { return iterShell == other.iterShell && iterPlane == other.iterPlane && iterSat == other.iterSat; }
        bool operator!=(sat_iterator other) const { return !(*this == other); }
        Spacecraft operator*() { return *iterSat; }

        // iterator traits
        using difference_type = Shell::iterator;
        using value_type = Shell::iterator;
        using pointer = const Shell::iterator*;
        using reference = const Shell::iterator&;
        using iterator_category = std::forward_iterator_tag;
    };

    iterator begin() { return shells.begin(); }
    iterator end() { return shells.end(); }

    sat_iterator sat_begin() { return sat_iterator(shells.begin(), (*shells.begin()).begin(), (*(*shells.begin()).begin()).begin()); }
    sat_iterator sat_end() { return sat_iterator(shells.end(), (*shells.begin()).begin(), (*(*shells.begin()).begin()).end()); }

private:

    size_t id;
    std::string name;
    std::vector<Shell> shells;

    void generate_id_hash();
};