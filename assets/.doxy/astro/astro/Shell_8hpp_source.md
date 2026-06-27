

# File Shell.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**space**](dir_4e8e97ad8c5ab106f4208fffe0057899.md) **>** [**Shell.hpp**](Shell_8hpp.md)

[Go to the documentation of this file](Shell_8hpp.md)


```C++

#pragma once

#include <string>
#include <vector>

#include <units/units.hpp>
#include <utilities/IdProvider.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/platforms/space/Plane.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>

namespace astrea {
namespace astro {

template <class Spacecraft_T = Spacecraft>
class Shell {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Shells must be built of Spacecraft or Derived classes.");

    friend class Constellation<Spacecraft_T>;

  public:
    Shell() = default;

    Shell(std::vector<Plane<Spacecraft_T>> planes);

    Shell(std::vector<Spacecraft_T> satellites);

    Shell(
        const Date& epoch,
        const Distance& semimajor,
        const Angle& inclination,
        const std::size_t& T,
        const std::size_t& P,
        const Unitless& F,
        const Angle& anchorRAAN    = 0.0 * mp_units::angular::unit_symbols::rad,
        const Angle& anchorAnomaly = 0.0 * mp_units::angular::unit_symbols::rad
    );

    ~Shell() { id = utilities::IdProvider::get_next_id<"Shell">(); };

    const std::size_t size() const;

    const std::size_t n_planes() const;

    void add_plane(const Plane<Spacecraft_T>& plane);

    void add_spacecraft(const Spacecraft_T& spacecraft, const std::size_t& planeId);

    void add_spacecraft(const Spacecraft_T& spacecraft);

    std::vector<Plane<Spacecraft_T>>& get_planes();

    const std::vector<Plane<Spacecraft_T>>& get_planes() const;

    const std::vector<Spacecraft_T> get_all_spacecraft() const;

    const Plane<Spacecraft_T>& get_plane(const std::size_t& planeId) const;

    const Spacecraft_T& get_spacecraft(const std::size_t& spacecraftId) const;

    void propagate(const Time& propTime, Integrator& integrator);

    void propagate(const Date& endEpoch, Integrator& integrator);


    // using iterator       = std::vector<Plane<Spacecraft_T>>::iterator;
    // using const_iterator = std::vector<Plane<Spacecraft_T>>::const_iterator;

    // iterator begin() { return planes.begin(); }
    // iterator end() { return planes.end(); }
    // const_iterator begin() const { return planes.begin(); }
    // const_iterator end() const { return planes.end(); }
    // const_iterator cbegin() const { return planes.cbegin(); }
    // const_iterator cend() const { return planes.cend(); }

    class sat_iterator; // Forward declaration of the iterator class for iterating over spacecraft in the shell

    using iterator = sat_iterator;

    using const_iterator = const sat_iterator;

    iterator begin() { return sat_iterator(planes.begin(), planes.begin()->begin()); }

    iterator end() { return sat_iterator(planes.end(), planes.end()->end()); }

    const_iterator begin() const { return sat_iterator(planes.begin(), planes.begin()->begin()); }

    const_iterator end() const { return sat_iterator(planes.end(), planes.end()->end()); }

    const_iterator cbegin() const { return sat_iterator(planes.cbegin(), planes.cbegin()->cbegin()); }

    const_iterator cend() const { return sat_iterator(planes.cend(), planes.cend()->cend()); }

    class sat_iterator {
      private:
        std::vector<Plane<Spacecraft_T>>::iterator iterPlane; // Iterator for the vector of planes
        Plane<Spacecraft_T>::iterator iterSat;                // Iterator for the current plane's spacecraft

      public:
        sat_iterator(std::vector<Plane<Spacecraft_T>>::iterator _iterPlane, Plane<Spacecraft_T>::iterator _iterSat) :
            iterPlane(_iterPlane),
            iterSat(_iterSat)
        {
        } // TODO: Sanitize inputs

        sat_iterator& operator++()
        {
            ++iterSat;
            if (iterSat == iterPlane->end()) {
                ++iterPlane;
                iterSat = iterPlane->begin();
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
            if (iterSat < iterPlane->begin()) {
                --iterPlane;
                iterSat = iterPlane->end();
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
            return iterPlane == other.iterPlane && iterSat == other.iterSat;
        }

        bool operator!=(const sat_iterator& other) const { return !(*this == other); }

        bool operator<(const sat_iterator& other) const
        {
            return iterPlane < other.iterPlane || (iterPlane == other.iterPlane && iterSat < other.iterSat);
        }

        bool operator>(const sat_iterator& other) const
        {
            return iterPlane > other.iterPlane || (iterPlane == other.iterPlane && iterSat > other.iterSat);
        }

        bool operator<=(const sat_iterator& other) const
        {
            return iterPlane < other.iterPlane || (iterPlane == other.iterPlane && iterSat <= other.iterSat);
        }

        bool operator>=(const sat_iterator& other) const
        {
            return iterPlane > other.iterPlane || (iterPlane == other.iterPlane && iterSat >= other.iterSat);
        }

        Spacecraft_T operator*() { return *iterSat; }

        // iterator traits
        using difference_type = Plane<Spacecraft_T>::iterator;  // Use the iterator type of Plane as the difference type
        using value_type      = Plane<Spacecraft_T>::iterator;  // Use the iterator type of Plane as the value type
        using pointer   = const Plane<Spacecraft_T>::iterator*; // Use the iterator type of Plane as the pointer type
        using reference = const Plane<Spacecraft_T>::iterator&; // Use the iterator type of Plane as the reference type
        using iterator_category = std::forward_iterator_tag;    // Use forward iterator tag for the iterator category
    };

    const std::size_t get_id() const { return id; }

  private:
    std::size_t id;
    std::string name;
    std::vector<Plane<Spacecraft_T>> planes;
};

} // namespace astro
} // namespace astrea

#include <astro/platforms/space/Shell.ipp>
```


