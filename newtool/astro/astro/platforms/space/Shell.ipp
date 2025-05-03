#include <stdexcept>

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
Shell<Spacecraft_T>::Shell(const double& semimajor, const double& inclination, const size_t& T, const size_t& P, const double& F, const double& anchorRAAN, const double& anchorAnomaly)
{

    if (T % P) {
        throw std::runtime_error("The Walker constructor requires the total number planes is a multiple of the total "
                                 "number of of satellites.");
    }

    const size_t satsPerPlane = T / P;
    const double deltaRAAN    = 360.0 / double(P);
    const double deltaAnomaly = F * 360.0 / double(T);

    const double deg2rad = M_PI / 180.0;

    planes.resize(P);
    size_t iAnom  = 0;
    size_t iPlane = 0;
    for (auto& plane : planes) {
        plane.satellites.resize(satsPerPlane);
        for (auto& sat : plane.satellites) {
            sat = Spacecraft_T(
                OrbitalElements(
                    { semimajor, 0.0, inclination * deg2rad, (anchorRAAN + deltaRAAN * iPlane) * deg2rad, 0.0, (anchorAnomaly + deltaAnomaly * iAnom) * deg2rad },
                    ElementSet::KEPLERIAN
                ),
                Date("Jan-01-2030 00:00:00.0")
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
const std::vector<Plane<Spacecraft_T>>& Shell<Spacecraft_T>::get_all_planes() const
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
void Shell<Spacecraft_T>::propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval)
{
    for (auto& plane : planes) {
        plane.propagate(eom, integrator, interval);
    }
}

} // namespace astro