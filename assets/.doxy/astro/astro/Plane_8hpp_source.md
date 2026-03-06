

# File Plane.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**space**](dir_4e8e97ad8c5ab106f4208fffe0057899.md) **>** [**Plane.hpp**](Plane_8hpp.md)

[Go to the documentation of this file](Plane_8hpp.md)


```C++

#pragma once

#include <vector>

#include <astro/astro.fwd.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/numerical/Integrator.hpp>

namespace astrea {
namespace astro {

template <class Spacecraft_T = Spacecraft>
class Plane {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Planes must be built of Spacecraft or Derived classes.");

    friend class Shell<Spacecraft_T>;
    friend class Constellation<Spacecraft_T>;

  public:
    Plane() = default;

    Plane(std::vector<Spacecraft_T> satellites);

    ~Plane() { generate_id(); };

    void add_spacecraft(const Spacecraft_T& spacecraft);

    std::vector<Spacecraft_T>& get_all_spacecraft();

    const std::vector<Spacecraft_T>& get_all_spacecraft() const;

    const Spacecraft_T& get_spacecraft(const std::size_t& spacecraftId) const;

    const std::size_t size() const;

    void propagate(const Time& propTime, const EquationsOfMotion& eom, Integrator& integrator);

    void propagate(const Date& endEpoch, const EquationsOfMotion& eom, Integrator& integrator);

    using iterator = std::vector<Spacecraft_T>::iterator;

    using const_iterator = std::vector<Spacecraft_T>::const_iterator;

    iterator begin() { return satellites.begin(); }

    iterator end() { return satellites.end(); }

    const_iterator begin() const { return satellites.begin(); }

    const_iterator end() const { return satellites.end(); }

    const_iterator cbegin() const { return satellites.cbegin(); }

    const_iterator cend() const { return satellites.cend(); }

    const std::size_t get_id() const { return id; }

  private:
    std::size_t id;                       // Unique identifier for the Plane
    OrbitalElements elements;             // Orbital elements shared by all Spacecraft in the Plane
    std::vector<Spacecraft_T> satellites; // Vector of Spacecraft in the Plane

    bool strict; // Flag to indicate if the Plane is strict (all Spacecraft must have the same orbital elements)

    void generate_id();
};

} // namespace astro
} // namespace astrea

#include <astro/platforms/space/Plane.ipp>
```


