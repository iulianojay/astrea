#include <stdexcept>

namespace astrea {
namespace astro {

template <class Spacecraft_T>
Shell<Spacecraft_T>::Shell(std::vector<Plane<Spacecraft_T>> _planes) :
    planes(_planes)
{
    id = utilities::IdProvider::get_next_id<"Shell">();
}


template <class Spacecraft_T>
Shell<Spacecraft_T>::Shell(std::vector<Spacecraft_T> satellites)
{
    Plane<Spacecraft_T> noPlane(satellites);

    planes.push_back(noPlane);

    id = utilities::IdProvider::get_next_id<"Shell">();
}

template <class Spacecraft_T>
Shell<Spacecraft_T>::Shell(
    const Date& epoch,
    const Distance& semimajor,
    const Angle& inclination,
    const size_t& T,
    const size_t& P,
    const Unitless& F,
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
    if (T == 0) { throw std::runtime_error("Constellation must have at least one satellite, and one plane."); }
    if (mp_units::leq_zero(F)) { throw std::runtime_error("Constellation phasing parameter must be non-negative."); }

    const size_t satsPerPlane = T / P;
    const Angle deltaRAAN     = 360.0 / (static_cast<double>(P)) * deg;
    const Angle deltaAnomaly  = F * 360.0 / (static_cast<double>(T)) * deg;

    planes.resize(P);
    Unitless iAnom  = 0;
    Unitless iPlane = 0;
    for (auto& plane : planes) {
        plane.satellites.resize(satsPerPlane);

        const Keplerian<frames::primary> planeElements{ semimajor,     Unitless::zero(),
                                                        inclination,   (anchorRAAN + deltaRAAN * iPlane),
                                                        Angle::zero(), Angle::zero() };
        plane.elements = OrbitalElements(planeElements);

        for (auto& sat : plane.satellites) {
            auto satElements = planeElements;
            satElements.set_true_anomaly(anchorAnomaly + deltaAnomaly * iAnom);

            const State state(OrbitalElements(satElements), epoch);
            sat.store_state(state);
            ++iAnom;
        }
        ++iPlane;
    }
    id = utilities::IdProvider::get_next_id<"Shell">();
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
        if (plane.id == planeId) {
            plane.add_spacecraft(spacecraft);
            return;
        }
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
void Shell<Spacecraft_T>::propagate(const Time& propTime, Integrator& integrator)
{
    for (auto& plane : planes) {
        plane.propagate(propTime, integrator);
    }
}


template <class Spacecraft_T>
void Shell<Spacecraft_T>::propagate(const Date& endEpoch, Integrator& integrator)
{
    for (auto& plane : planes) {
        plane.propagate(endEpoch, integrator);
    }
}

} // namespace astro
} // namespace astrea