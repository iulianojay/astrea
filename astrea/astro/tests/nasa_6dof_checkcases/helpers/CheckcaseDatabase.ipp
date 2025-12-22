
namespace astrea {
namespace astro {
namespace tests {

template <class T>
const T& CheckcaseDatabaseUtilityWrapper<T>::get_database() const
{
    return _database;
}

template <class T>
template <typename... Args>
std::vector<AtmosphericCheckcaseRow> CheckcaseDatabaseUtilityWrapper<T>::get_all(Args&&... args) const
{
    return _database.template get_all<AtmosphericCheckcaseRow>(args...);
}

template <class T>
template <typename... Args>
std::vector<OrbitalCheckcaseRow> CheckcaseDatabaseUtilityWrapper<T>::get_all(Args&&... args) const
{
    return _database.template get_all<OrbitalCheckcaseRow>(args...);
}

} // namespace tests
} // namespace astro
} // namespace astrea