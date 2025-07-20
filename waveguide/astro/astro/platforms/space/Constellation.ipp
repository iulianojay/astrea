namespace waveguide {
namespace astro {

static const size_t DEFAULT_SHELL_ID = SIZE_MAX;

template <class Spacecraft_T>
Constellation<Spacecraft_T>::Constellation(std::vector<Shell<Spacecraft_T>> _shells)
{
    shells = _shells;
    generate_id_hash();
}


template <class Spacecraft_T>
Constellation<Spacecraft_T>::Constellation(std::vector<Plane<Spacecraft_T>> planes)
{
    Shell<Spacecraft_T> noShell(planes);
    noShell.name = "DEFAULT";
    noShell.id   = DEFAULT_SHELL_ID;

    shells.push_back(noShell);

    generate_id_hash();
}


template <class Spacecraft_T>
Constellation<Spacecraft_T>::Constellation(std::vector<Spacecraft_T> satellites)
{
    Plane<Spacecraft_T> noPlane(satellites);
    Shell<Spacecraft_T> noShell(std::vector<Plane<Spacecraft_T>>{ noPlane });
    noShell.name = "DEFAULT";

    shells.push_back(noShell);

    generate_id_hash();
}

template <class Spacecraft_T>
Constellation<Spacecraft_T>::Constellation(const std::vector<snapshot::SpaceTrackGP>& gps, const AstrodynamicsSystem& system)
{
    std::vector<Spacecraft_T> satellites;
    for (const auto gp : gps) {
        satellites.push_back(Spacecraft_T(gp, system));
    }
    *this = Constellation(satellites);
}


template <class Spacecraft_T>
Constellation<Spacecraft_T>::Constellation(
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

    shells.emplace_back(Shell<Spacecraft_T>(sys, epoch, semimajor, inclination, T, P, F, anchorRAAN, anchorAnomaly));

    generate_id_hash();
}


template <class Spacecraft_T>
const size_t Constellation<Spacecraft_T>::size() const
{
    size_t size = 0;
    for (const auto& shell : shells) {
        size += shell.size();
    }
    return size;
}


template <class Spacecraft_T>
const size_t Constellation<Spacecraft_T>::n_shells() const
{
    return shells.size();
}


template <class Spacecraft_T>
const size_t Constellation<Spacecraft_T>::n_planes() const
{
    size_t nPlane = 0;
    for (const auto& shell : shells) {
        nPlane += shell.n_planes();
    }
    return nPlane;
}


template <class Spacecraft_T>
void Constellation<Spacecraft_T>::add_shell(const Shell<Spacecraft_T>& shell)
{
    shells.push_back(shell);
}


template <class Spacecraft_T>
void Constellation<Spacecraft_T>::add_plane(const Plane<Spacecraft_T>& plane, const size_t& shellId)
{
    for (auto& shell : shells) {
        if (shell.id == shellId) { shell.add_plane(plane); }
    }
    throw std::runtime_error("No shell found with matching id: " + std::to_string(shellId) + "\n");
}


template <class Spacecraft_T>
void Constellation<Spacecraft_T>::add_plane(const Plane<Spacecraft_T>& plane)
{
    for (auto& shell : shells) {
        if (shell.id == DEFAULT_SHELL_ID) {
            shell.add_plane(plane);
            return;
        }
    }

    Shell<Spacecraft_T> noShell(std::vector<Plane<Spacecraft_T>>{ plane });
    noShell.name = "DEFAULT";
    noShell.id   = DEFAULT_SHELL_ID;

    shells.push_back(noShell);
}


template <class Spacecraft_T>
void Constellation<Spacecraft_T>::add_spacecraft(const Spacecraft_T& spacecraft, const size_t& planeId)
{
    for (auto& shell : shells) {
        for (auto& plane : shell.planes) {
            if (plane.id == planeId) { plane.add_spacecraft(spacecraft); }
        }
    }
    throw std::runtime_error("No plane found with matching id: " + std::to_string(planeId) + "\n");
}


template <class Spacecraft_T>
void Constellation<Spacecraft_T>::add_spacecraft(const Spacecraft_T& spacecraft)
{
    for (auto& shell : shells) {
        if (shell.id == DEFAULT_SHELL_ID) {
            shell.add_spacecraft(spacecraft);
            return;
        }
    }

    Shell<Spacecraft_T> noShell(std::vector<Plane<Spacecraft_T>>{ std::vector<Spacecraft_T>{ spacecraft } });
    noShell.name = "DEFAULT";
    noShell.id   = DEFAULT_SHELL_ID;

    shells.push_back(noShell);
}


template <class Spacecraft_T>
const std::vector<Shell<Spacecraft_T>>& Constellation<Spacecraft_T>::get_all_shells() const
{
    return shells;
}


template <class Spacecraft_T>
const std::vector<Plane<Spacecraft_T>> Constellation<Spacecraft_T>::get_all_planes() const
{
    std::vector<Plane<Spacecraft_T>> allPlanes;
    for (auto& shell : shells) {
        const auto& shellPlanes = shell.get_all_planes();
        allPlanes.insert(allPlanes.end(), shellPlanes.begin(), shellPlanes.end());
    }
    return allPlanes;
}


template <class Spacecraft_T>
const std::vector<Spacecraft_T> Constellation<Spacecraft_T>::get_all_spacecraft() const
{
    std::vector<Spacecraft_T> allSpacecraft;
    for (auto& shell : shells) {
        const auto shellSpacecraft = shell.get_all_spacecraft();
        allSpacecraft.insert(allSpacecraft.end(), shellSpacecraft.begin(), shellSpacecraft.end());
    }
    return allSpacecraft;
}


template <class Spacecraft_T>
const Shell<Spacecraft_T>& Constellation<Spacecraft_T>::get_shell(const size_t& shellId) const
{
    for (const auto& shell : shells) {
        if (shell.id == shellId) { return shell; }
    }
    throw std::runtime_error("No shell found with matching id: " + std::to_string(shellId) + "\n");
}


template <class Spacecraft_T>
const Plane<Spacecraft_T>& Constellation<Spacecraft_T>::get_plane(const size_t& planeId) const
{
    for (const auto& shell : shells) {
        for (const auto& plane : shell.planes) {
            if (plane.id == planeId) { return plane; }
        }
    }
    throw std::runtime_error("No plane found with matching id: " + std::to_string(planeId) + "\n");
}


template <class Spacecraft_T>
const Spacecraft_T& Constellation<Spacecraft_T>::get_spacecraft(const size_t& spacecraftId) const
{
    for (const auto& shell : shells) {
        for (const auto& plane : shell.planes) {
            for (const auto& sat : plane.satellites) {
                if (sat.get_id() == spacecraftId) { return sat; }
            }
        }
    }
    throw std::runtime_error("No spacecraft found with matching id: " + std::to_string(spacecraftId) + "\n");
}


template <class Spacecraft_T>
void Constellation<Spacecraft_T>::generate_id_hash()
{
    id = std::hash<size_t>()(shells[0].id);
    for (size_t ii = 1; ii < shells.size(); ii++) {
        id ^= std::hash<size_t>()(shells[ii].id);
    }
}


template <class Spacecraft_T>
void Constellation<Spacecraft_T>::propagate(const Date& epoch, EquationsOfMotion& eom, const Interval& interval)
{
    Integrator integrator;
    propagate(epoch, eom, integrator, interval);
}


template <class Spacecraft_T>
void Constellation<Spacecraft_T>::propagate(const Date& epoch, EquationsOfMotion& eom, Integrator& integrator, const Interval& interval)
{
    for (auto& shell : shells) {
        shell.propagate(epoch, eom, integrator, interval);
    }
}

} // namespace astro
} // namespace waveguide