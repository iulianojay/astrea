#pragma once

#ifndef SWIG
    #include <vector>
#endif

#include "Spacecraft.hpp"
#include "Integrator.hpp"

#include "Constellation.fwd.hpp"
#include "Shell.fwd.hpp"

class Plane {

    friend class Shell;
    friend class Constellation;

public:

    Plane() = default;
    Plane(std::vector<Spacecraft> satellites);
    ~Plane() = default;

    void add_spacecraft(const Spacecraft& spacecraft);

    const std::vector<Spacecraft>& get_all_spacecraft() const;

    const Spacecraft& get_spacecraft(const int& spacecraftId) const;

    const size_t size() const;

    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);

    using iterator = std::vector<Spacecraft>::iterator;
    iterator begin() { return satellites.begin(); }
    iterator end() { return satellites.end(); }

private:

    size_t id;
    OrbitalElements elements;
    std::vector<Spacecraft> satellites;

    bool strict;

    void generate_id_hash();

};


#ifdef SWIG

%template(PlaneVector) std::vector<Plane>;

#endif