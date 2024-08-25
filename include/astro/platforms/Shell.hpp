#pragma once

#ifndef SWIG
    #include <vector>
    #include <string>
#endif

#include "Plane.hpp"
#include "Integrator.hpp"

class Constellation;

class Shell {

    friend class Constellation;

public:

    Shell(std::vector<Plane> planes);
    Shell(std::vector<Spacecraft> satellites);
    ~Shell() = default;
    
    const size_t size() const;
    const size_t n_planes() const;

    void add_plane(const Plane& plane);
    void add_spacecraft(const Spacecraft& spacecraft, const int& planeId);
    
    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);

private:

    int id;
    std::string name;
    std::vector<Plane> planes;

    void generate_id_hash();

};