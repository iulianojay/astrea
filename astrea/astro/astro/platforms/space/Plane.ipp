#include <astro/utilities/conversions.hpp>

#include <utilities/ProgressBar.hpp>

namespace astrea {
namespace astro {

template <class Spacecraft_T>
Plane<Spacecraft_T>::Plane(std::vector<Spacecraft_T> _satellites) :
    satellites(_satellites)
{

    // Assume Earth-system for now. TODO: Fix this
    AstrodynamicsSystem sys;

    // Grab first element set as plane set
    elements = satellites[0].get_initial_state().get_elements().template in_element_set<Keplerian>(sys.get_mu());

    // Check if other satellites are actually in-plane
    strict = true;
    for (const auto& sat : satellites) {
        OrbitalElements satElements = sat.get_initial_state().get_elements().template in_element_set<Keplerian>(sys.get_mu());
        if (!nearly_equal(elements, satElements, true)) {
            strict = false;
            break;
        }
    }

    id = utilities::IdProvider::get_next_id<"Plane">();
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
std::vector<Spacecraft_T>& Plane<Spacecraft_T>::get_all_spacecraft()
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
void Plane<Spacecraft_T>::propagate(const Time& propTime, const EquationsOfMotion& eom, Integrator& integrator)
{
    // std::cout << std::endl;
    // utilities::ProgressBar progressBar(satellites.size(), "\tPropagating Plane " + std::to_string(id));
    for (auto& sat : satellites) {
        Vehicle vehicle{ sat };
        const StateHistory& satHistory = sat.get_state_history();
        if (satHistory.size() == 0) {
            throw std::runtime_error(
                "Cannot propagate spacecraft with no initial state. Spacecraft id: " + std::to_string(sat.get_id()) + "\n"
            );
        }
        State state0            = satHistory.first();
        const auto stateHistory = integrator.propagate(state0, propTime, eom, vehicle, true);

        sat.set_state_history(stateHistory);

        // progressBar();
    }
}


template <class Spacecraft_T>
void Plane<Spacecraft_T>::propagate(const Date& endEpoch, const EquationsOfMotion& eom, Integrator& integrator)
{
    // std::cout << std::endl;
    // utilities::ProgressBar progressBar(satellites.size(), "\tPropagating Plane " + std::to_string(id));
    for (auto& sat : satellites) {
        Vehicle vehicle{ sat };
        const StateHistory& satHistory = sat.get_state_history();
        if (satHistory.size() == 0) {
            throw std::runtime_error(
                "Cannot propagate spacecraft with no initial state. Spacecraft id: " + std::to_string(sat.get_id()) + "\n"
            );
        }
        State state0            = satHistory.first();
        const auto stateHistory = integrator.propagate(state0, endEpoch, eom, vehicle, true);

        sat.set_state_history(stateHistory);

        // progressBar();
    }
}

} // namespace astro
} // namespace astrea