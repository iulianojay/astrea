#pragma once

#include <vector>

#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/numerical/Integrator.hpp>

#include <astro/astro.fwd.hpp>

namespace astro {

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

    const Spacecraft_T& get_spacecraft(const std::size_t& spacecraftId) const;

    const std::size_t size() const;

    void propagate(const Date& epoch, EquationsOfMotion& eom, Integrator& integrator, const Interval& interval = Integrator::defaultInterval);

    using iterator       = std::vector<Spacecraft_T>::iterator;
    using const_iterator = std::vector<Spacecraft_T>::const_iterator;

    iterator begin() { return satellites.begin(); }
    iterator end() { return satellites.end(); }
    const_iterator begin() const { return satellites.begin(); }
    const_iterator end() const { return satellites.end(); }
    const_iterator cbegin() const { return satellites.cbegin(); }
    const_iterator cend() const { return satellites.cend(); }

    const std::size_t get_id() const { return id; }

  private:
    std::size_t id;
    OrbitalElements elements;
    std::vector<Spacecraft_T> satellites;

    bool strict;

    void generate_id_hash();
};

} // namespace astro

#include <astro/platforms/space/Plane.ipp>
