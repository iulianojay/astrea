

# File Constellation.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**space**](dir_4e8e97ad8c5ab106f4208fffe0057899.md) **>** [**Constellation.hpp**](Constellation_8hpp.md)

[Go to the documentation of this file](Constellation_8hpp.md)


```C++

#pragma once

#include <string>
#include <vector>

#include <units/units.hpp>

#include <astro/platforms/space/Shell.hpp>
#include <astro/propagation/numerical/Integrator.hpp>

namespace astrea {
namespace astro {

template <class Spacecraft_T = Spacecraft>
class Constellation {

    static_assert(std::is_base_of<Spacecraft, Spacecraft_T>::value, "Constellations must be built of Spacecraft or Derived classes.");

  public:
    Constellation() { generate_id(); };

    Constellation(std::vector<Shell<Spacecraft_T>> shells);

    Constellation(std::vector<Plane<Spacecraft_T>> planes);

    Constellation(std::vector<Spacecraft_T> satellites);

    Constellation(const std::vector<GeneralPerturbations>& gp, const AstrodynamicsSystem& system);

    Constellation(
        const AstrodynamicsSystem& sys,
        const Date& epoch,
        const Distance& semimajor,
        const Angle& inclination,
        const std::size_t& T,
        const std::size_t& P,
        const double& F,
        const Angle& anchorRAAN    = 0.0 * mp_units::angular::unit_symbols::rad,
        const Angle& anchorAnomaly = 0.0 * mp_units::angular::unit_symbols::rad
    );

    ~Constellation() = default;

    const std::size_t size() const;

    const std::size_t n_shells() const;

    const std::size_t n_planes() const;

    // TODO: Add + overloads that accomplish similar things to these methods

    void add_shell(const Shell<Spacecraft_T>& shell);

    void add_plane(const Plane<Spacecraft_T>& plane, const std::size_t& shellId);

    void add_plane(const Plane<Spacecraft_T>& plane);

    void add_spacecraft(const Spacecraft_T& spacecraft, const std::size_t& planeId);

    void add_spacecraft(const Spacecraft_T& spacecraft);

    std::vector<Shell<Spacecraft_T>>& get_shells();

    const std::vector<Shell<Spacecraft_T>>& get_shells() const;

    const std::vector<Plane<Spacecraft_T>> get_planes() const;

    const std::vector<Spacecraft_T> get_all_spacecraft() const;

    const Shell<Spacecraft_T>& get_shell(const std::size_t& shellId) const;

    const Plane<Spacecraft_T>& get_plane(const std::size_t& planeId) const;

    const Spacecraft_T& get_spacecraft(const std::size_t& spacecraftId) const;

    void propagate(const Time& propTime, const EquationsOfMotion& eom, Integrator& integrator);

    void propagate(const Date& endEpoch, const EquationsOfMotion& eom, Integrator& integrator);


    // using iterator       = std::vector<Shell<Spacecraft_T>>::iterator;
    // using const_iterator = std::vector<Shell<Spacecraft_T>>::const_iterator;

    // iterator begin() { return shells.begin(); }
    // iterator end() { return shells.end(); }
    // const_iterator begin() const { return shells.begin(); }
    // const_iterator end() const { return shells.end(); }
    // const_iterator cbegin() const { return shells.cbegin(); }
    // const_iterator cend() const { return shells.cend(); }

    Spacecraft_T& operator[](const std::size_t idx);

    const Spacecraft_T& operator[](const std::size_t idx) const;

    class sat_iterator; // Forward declaration of the iterator class

    using iterator = sat_iterator;

    using const_iterator = const sat_iterator;

    iterator begin() { return sat_iterator(shells.begin(), shells.begin()->begin()); }

    iterator end() { return sat_iterator(shells.end(), shells.end()->end()); }

    const_iterator begin() const { return sat_iterator(shells.begin(), shells.begin()->begin()); }

    const_iterator end() const { return sat_iterator(shells.end(), shells.end()->end()); }

    const_iterator cbegin() const { return sat_iterator(shells.cbegin(), shells.cbegin()->cbegin()); }

    const_iterator cend() const { return sat_iterator(shells.cend(), shells.cend()->cend()); }

    class sat_iterator {
      private:
        std::vector<Shell<Spacecraft_T>>::iterator iterShell; // Iterator for the Shells in the Constellation
        Shell<Spacecraft_T>::sat_iterator iterSat;            // Iterator for the Spacecraft within the current Shell

      public:
        sat_iterator(std::vector<Shell<Spacecraft_T>>::iterator _iterShell, Shell<Spacecraft_T>::sat_iterator _iterSat) :
            iterShell(_iterShell),
            iterSat(_iterSat)
        {
        } // TODO: Sanitize inputs

        sat_iterator& operator++()
        {
            ++iterSat;
            if (iterSat == iterShell->end()) {
                ++iterShell;
                iterSat = iterShell->begin();
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
            if (iterSat < iterShell->begin()) {
                --iterShell;
                iterSat = iterShell->end();
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
            return iterShell == other.iterShell && iterSat == other.iterSat;
        }

        bool operator!=(const sat_iterator& other) const { return !(*this == other); }

        bool operator<(const sat_iterator& other) const
        {
            return iterShell < other.iterShell || (iterShell == other.iterShell && iterSat < other.iterSat);
        }

        bool operator>(const sat_iterator& other) const
        {
            return iterShell > other.iterShell || (iterShell == other.iterShell && iterSat > other.iterSat);
        }

        bool operator<=(const sat_iterator& other) const
        {
            return iterShell < other.iterShell || (iterShell == other.iterShell && iterSat <= other.iterSat);
        }

        bool operator>=(const sat_iterator& other) const
        {
            return iterShell > other.iterShell || (iterShell == other.iterShell && iterSat >= other.iterSat);
        }

        Spacecraft_T operator*() { return *iterSat; }

      private:
        // iterator traits
        using difference_type = Plane<Spacecraft_T>::iterator;  // Use the iterator type of Plane as the difference type
        using value_type      = Plane<Spacecraft_T>::iterator;  // Use the iterator type of Plane as the value type
        using pointer   = const Plane<Spacecraft_T>::iterator*; // Use the iterator type of Plane as the pointer type
        using reference = const Plane<Spacecraft_T>::iterator&; // Use the iterator type of Plane as the reference type
        using iterator_category = std::forward_iterator_tag;    // Use forward iterator tag for the iterator category
    };

  private:
    std::size_t id;                          // Unique identifier for the Constellation
    std::string name;                        // Name of the Constellation
    std::vector<Shell<Spacecraft_T>> shells; // Vector of Shells in the Constellation

    void generate_id();
};

} // namespace astro
} // namespace astrea

#include <astro/platforms/space/Constellation.ipp>
```


