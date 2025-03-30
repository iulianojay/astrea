#pragma once

#ifndef SWIG
#include <vector>
#endif

#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/Integrator.hpp>

#include <astro/astro.fwd.hpp>

template <class Spacecraft_T = Spacecraft>
class Plane {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Planes must be built of Spacecraft or Derived classes.");

    friend class Shell<Spacecraft_T>;
    friend class Constellation<Spacecraft_T>;

  public:
    Plane() = default;
    Plane(std::vector<Spacecraft_T> satellites);
    ~Plane() = default;

    void add_spacecraft(const Spacecraft_T& spacecraft);

    const std::vector<Spacecraft_T>& get_all_spacecraft() const;

    const Spacecraft_T& get_spacecraft(const size_t& spacecraftId) const;

    const size_t size() const;

    void propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);

    using iterator = std::vector<Spacecraft_T>::iterator;
    iterator begin() { return satellites.begin(); }
    iterator end() { return satellites.end(); }

    const size_t get_id() const { return id; }

  private:
    size_t id;
    OrbitalElements elements;
    std::vector<Spacecraft_T> satellites;

    bool strict;

    void generate_id_hash();
};


#include <astro/platforms/space/Plane.ipp>


#ifdef SWIG

%template(PlaneVector) std::vector<Plane>;

#endif