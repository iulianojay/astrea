

# File Database.ipp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**snapshot**](dir_ad01b7a66bf2103e1e551598d7ba094a.md) **>** [**snapshot**](dir_d7d302d432d8a6ab561803ec6eec1eed.md) **>** [**database**](dir_51ef3faf157d043087a4594bebbd2397.md) **>** [**Database.ipp**](Database_8ipp.md)

[Go to the documentation of this file](Database_8ipp.md)


```C++
#include <snapshot/database/Database.hpp>

namespace astrea {
namespace snapshot {

using astro::GeneralPerturbations;

template <class T>
const T& DatabaseUtilityWrapper<T>::get_database() const
{
    return _database;
}

template <class T>
template <typename... Args>
std::vector<GeneralPerturbations> DatabaseUtilityWrapper<T>::get_all(Args&&... args) const
{
    return _database.template get_all<GeneralPerturbations>(args...);
}

template <class T>
GeneralPerturbations DatabaseUtilityWrapper<T>::get_sat_from_norad_id(const unsigned& id) const
{
    using namespace sqlite_orm;
    const std::vector<GeneralPerturbations> result =
        _database.template get_all<GeneralPerturbations>(where(c(&GeneralPerturbations::NORAD_CAT_ID) == id));
    if (result.empty()) { throw std::runtime_error("No object found with NORAD_CAT_ID " + std::to_string(id) + "."); }
    else if (result.size() > 1) {
        throw std::runtime_error("Database corruption: Multiple objects found with NORAD_CAT_ID " + std::to_string(id) + ".");
    }
    return result[0];
}

template <class T>
std::vector<GeneralPerturbations> DatabaseUtilityWrapper<T>::get_sats_by_name(const std::string& name) const
{
    using namespace sqlite_orm;
    return _database.template get_all<GeneralPerturbations>(where(like(&GeneralPerturbations::OBJECT_NAME, name)));
}

template <class T>
std::vector<GeneralPerturbations>
    DatabaseUtilityWrapper<T>::get_sats_in_range(const Distance& minPeriapsis, const Distance& maxApoapsis) const
{
    using namespace sqlite_orm;
    using mp_units::si::unit_symbols::km;
    return _database.template get_all<GeneralPerturbations>(where(
        c(&GeneralPerturbations::APOAPSIS) <= maxApoapsis.numerical_value_in(km) and
        c(&GeneralPerturbations::PERIAPSIS) >= minPeriapsis.numerical_value_in(km)
    ));
}

} // namespace snapshot
} // namespace astrea
```


