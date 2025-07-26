#include <snapshot/database/Database.hpp>

namespace waveguide {
namespace snapshot {

template <class T>
const T& DatabaseUtilityWrapper<T>::get_database() const
{
    return _database;
}

template <class T>
template <typename... Args>
std::vector<SpaceTrackGP> DatabaseUtilityWrapper<T>::get_all(Args&&... args) const
{
    return _database.template get_all<SpaceTrackGP>(args...);
}

template <class T>
SpaceTrackGP DatabaseUtilityWrapper<T>::get_sat_from_norad_id(const unsigned& id) const
{
    using namespace sqlite_orm;
    const std::vector<SpaceTrackGP> result =
        _database.template get_all<SpaceTrackGP>(where(c(&SpaceTrackGP::NORAD_CAT_ID) == id));
    if (result.empty()) { throw std::runtime_error("No object found with NORAD_CAT_ID " + std::to_string(id) + "."); }
    else if (result.size() > 1) {
        throw std::runtime_error("Database corruption: Multiple objects found with NORAD_CAT_ID " + std::to_string(id) + ".");
    }
    return result[0];
}

template <class T>
std::vector<SpaceTrackGP> DatabaseUtilityWrapper<T>::get_sats_by_name(const std::string& name) const
{
    using namespace sqlite_orm;
    return _database.template get_all<SpaceTrackGP>(where(like(&SpaceTrackGP::OBJECT_NAME, name)));
}

template <class T>
std::vector<SpaceTrackGP> DatabaseUtilityWrapper<T>::get_sats_in_range(const Distance& minPeriapsis, const Distance& maxApoapsis) const
{
    using namespace sqlite_orm;
    using mp_units::si::unit_symbols::km;
    return _database.template get_all<SpaceTrackGP>(where(
        c(&SpaceTrackGP::APOAPSIS) <= maxApoapsis.numerical_value_in(km) and
        c(&SpaceTrackGP::PERIAPSIS) >= minPeriapsis.numerical_value_in(km)
    ));
}

} // namespace snapshot
} // namespace waveguide