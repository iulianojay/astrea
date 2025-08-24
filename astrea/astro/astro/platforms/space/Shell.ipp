#include <stdexcept>

namespace astrea {
namespace astro {

template <class Spacecraft_T>
Shell<Spacecraft_T>::Shell(std::vector<Plane<Spacecraft_T>> _planes) :
    planes(_planes)
{
    generate_id_hash();
}


template <class Spacecraft_T>
Shell<Spacecraft_T>::Shell(std::vector<Spacecraft_T> satellites)
{
    Plane<Spacecraft_T> noPlane(satellites);

    planes.push_back(noPlane);

    generate_id_hash();
}

template <class Spacecraft_T>
Shell<Spacecraft_T>::Shell(
    const AstrodynamicsSystem& sys,
    const Date& epoch,
    const Distance& semimajor,
    const Angle& inclination,
    const size_t& T,
    const size_t& P,
    const double& F,
    const Angle& anchorRAAN,
    const Angle& anchorAnomaly
)
{

    if (T % P) {
        throw std::runtime_error(
            "The Walker constructor requires the total number planes is a multiple of the total "
            "number of of satellites."
        );
    }

    const size_t satsPerPlane = T / P;
    const Angle deltaRAAN     = 360.0 / (static_cast<double>(P)) * mp_units::angular::unit_symbols::deg;
    const Angle deltaAnomaly  = F * 360.0 / (static_cast<double>(T)) * mp_units::angular::unit_symbols::deg;

    planes.resize(P);
    Unitless iAnom  = 0;
    Unitless iPlane = 0;
    for (auto& plane : planes) {
        plane.satellites.resize(satsPerPlane);
        for (auto& sat : plane.satellites) {
            sat = Spacecraft_T(
                { OrbitalElements(
                      Keplerian{ semimajor,
                                 0.0 * mp_units::one,
                                 inclination,
                                 (anchorRAAN + deltaRAAN * iPlane),
                                 0.0 * mp_units::angular::unit_symbols::rad,
                                 (anchorAnomaly + deltaAnomaly * iAnom) }
                  ),
                  epoch,
                  sys }
            );
            ++iAnom;
        }
        plane.generate_id_hash();
    }
    generate_id_hash();
}


template <class Spacecraft_T>
const size_t Shell<Spacecraft_T>::size() const
{
    size_t size = 0;
    for (const auto& plane : planes) {
        size += plane.size();
    }
    return size;
}


template <class Spacecraft_T>
const size_t Shell<Spacecraft_T>::n_planes() const
{
    return planes.size();
}


template <class Spacecraft_T>
void Shell<Spacecraft_T>::add_plane(const Plane<Spacecraft_T>& plane)
{
    planes.push_back(plane);
}


template <class Spacecraft_T>
void Shell<Spacecraft_T>::add_spacecraft(const Spacecraft_T& spacecraft, const size_t& planeId)
{
    for (auto& plane : planes) {
        if (plane.id == planeId) { plane.add_spacecraft(spacecraft); }
    }
    throw std::runtime_error("No plane found with matching id: " + std::to_string(planeId) + "\n");
}

template <class Spacecraft_T>
void Shell<Spacecraft_T>::add_spacecraft(const Spacecraft_T& spacecraft)
{
    Plane<Spacecraft_T> noPlane(std::vector<Spacecraft_T>{ spacecraft });
    planes.push_back(noPlane);
}


template <class Spacecraft_T>
const std::vector<Plane<Spacecraft_T>>& Shell<Spacecraft_T>::get_planes() const
{
    return planes;
}

template <class Spacecraft_T>
std::vector<Plane<Spacecraft_T>>& Shell<Spacecraft_T>::get_planes()
{
    return planes;
}

template <class Spacecraft_T>
const std::vector<Spacecraft_T> Shell<Spacecraft_T>::get_all_spacecraft() const
{
    std::vector<Spacecraft_T> allSpacecraft_T;
    for (auto& plane : planes) {
        const auto& shellSpacecraft_T = plane.get_all_spacecraft();
        allSpacecraft_T.insert(allSpacecraft_T.end(), shellSpacecraft_T.begin(), shellSpacecraft_T.end());
    }
    return allSpacecraft_T;
}


template <class Spacecraft_T>
const Plane<Spacecraft_T>& Shell<Spacecraft_T>::get_plane(const size_t& planeId) const
{
    for (const auto& plane : planes) {
        if (plane.id == planeId) { return plane; }
    }
    throw std::runtime_error("No plane found with matching id: " + std::to_string(planeId) + "\n");
}


template <class Spacecraft_T>
const Spacecraft_T& Shell<Spacecraft_T>::get_spacecraft(const size_t& spacecraftId) const
{
    for (const auto& plane : planes) {
        for (const auto& sat : plane.satellites) {
            if (sat.get_id() == spacecraftId) { return sat; }
        }
    }
    throw std::runtime_error("No spacecraft found with matching id: " + std::to_string(spacecraftId) + "\n");
}


template <class Spacecraft_T>
void Shell<Spacecraft_T>::generate_id_hash()
{
    id = std::hash<size_t>()(planes[0].id);
    for (size_t ii = 1; ii < planes.size(); ii++) {
        id ^= std::hash<size_t>()(planes[ii].id);
    }
}


template <class Spacecraft_T>
void Shell<Spacecraft_T>::propagate(const Date& epoch, EquationsOfMotion& eom, Integrator& integrator, const Interval& interval)
{
    for (auto& plane : planes) {
        plane.propagate(epoch, eom, integrator, interval);
    }
}

} // namespace astro
} // namespace astrea