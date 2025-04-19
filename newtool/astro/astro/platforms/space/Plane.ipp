template <class Spacecraft_T>
Plane<Spacecraft_T>::Plane(std::vector<Spacecraft_T> _satellites) :
    satellites(_satellites)
{

    // Assume Earth-system for now. TODO: Fix this
    AstrodynamicsSystem sys;

    // Grab first element set as plane set
    elements = Keplerian(satellites[0].get_initial_state().elements, sys);

    // Check if other satellites are actually in-plane
    strict = true;
    for (const auto& sat : satellites) {
        Keplerian satElements(sat.get_initial_state().elements, sys);
        if (!elements.nearly_equal(satElements, true)) {
            strict = false;
            break;
        }
    }

    generate_id_hash();
}


template <class Spacecraft_T>
const size_t Plane<Spacecraft_T>::size() const
{
    return satellites.size();
}


template <class Spacecraft_T>
void Plane<Spacecraft_T>::add_spacecraft(const Spacecraft_T& spacecraft)
{
    satellites.push_back(spacecraft);
}


template <class Spacecraft_T>
const std::vector<Spacecraft_T>& Plane<Spacecraft_T>::get_all_spacecraft() const
{
    return satellites;
}


template <class Spacecraft_T>
const Spacecraft_T& Plane<Spacecraft_T>::get_spacecraft(const size_t& spacecraftId) const
{
    for (const auto& sat : satellites) {
        if (sat.get_id() == spacecraftId) { return sat; }
    }
    throw std::runtime_error("No spacecraft found with matching id: " + std::to_string(spacecraftId) + "\n");
}


template <class Spacecraft_T>
void Plane<Spacecraft_T>::generate_id_hash()
{
    id = std::hash<size_t>()(satellites[0].get_id());
    for (size_t ii = 1; ii < satellites.size(); ii++) {
        id ^= std::hash<size_t>()(satellites[ii].get_id());
    }
}


template <class Spacecraft_T>
void Plane<Spacecraft_T>::propagate(EquationsOfMotion& eom, Integrator& integrator, const Interval& interval)
{
    for (auto& sat : satellites) {
        Vehicle vehicle{ sat };
        integrator.propagate(interval, eom, vehicle);
        sat = *vehicle.extract<Spacecraft_T>();
    }
}