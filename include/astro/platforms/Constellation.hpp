#pragma once

#ifndef SWIG
    #include <vector>
    #include <string>
#endif

#include "Shell.hpp"
#include "Integrator.hpp"

class Constellation {

public:

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
    void add_spacecraft(const Spacecraft& spacecraft, const int& planeId);

    void propagate(const Interval& interval = Integrator::defaultInterval);
    void propagate(const AstrodynamicsSystem& sys, const Interval& interval = Integrator::defaultInterval);
    void propagate(EquationsOfMotion& eom, const Interval& interval = Integrator::defaultInterval);
    void propagate(Integrator& integrator, const Interval& interval = Integrator::defaultInterval);
    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);

private:

    int id;
    std::string name;
    std::vector<Shell> shells;

    void generate_id_hash();
};