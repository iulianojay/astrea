#pragma once

#ifndef SWIG
    #include <vector>
    #include <string>
#endif

#include "Plane.hpp"
#include "Integrator.hpp"

#include "Constellation.fwd.hpp"

class Shell {

    friend class Constellation;

public:

    Shell() = default;
    Shell(std::vector<Plane> planes);
    Shell(std::vector<Spacecraft> satellites);
    ~Shell() = default;

    const size_t size() const;
    const size_t n_planes() const;

    void add_plane(const Plane& plane);
    void add_spacecraft(const Spacecraft& spacecraft, const int& planeId);
    void add_spacecraft(const Spacecraft& spacecraft);

    const std::vector<Plane>& get_all_planes() const;
    const std::vector<Spacecraft> get_all_spacecraft() const;

    const Plane& get_plane(const int& planeId) const;
    const Spacecraft& get_spacecraft(const int& spacecraftId) const;

    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);

private:

    size_t id;
    std::string name;
    std::vector<Plane> planes;

    void generate_id_hash();

};


#ifdef SWIG

%template(ShellVector) std::vector<Shell>;

#endif