#include <astro/utilities/conversions.hpp>

#include <math/operations.hpp>
#include <utilities/ProgressBar.hpp>

namespace astrea {
namespace astro {


inline bool planes_are_nearly_equal(const OrbitalElements& elem1, const OrbitalElements& elem2, const Unitless& relTol)
{
    const auto blob1 = elem1.force_to_vector();
    const auto blob2 = elem2.force_to_vector();
    return math::nearly_equal(blob1[0], blob2[0], relTol) && math::nearly_equal(blob1[1], blob2[1], relTol) &&
           math::nearly_equal(blob1[2], blob2[2], relTol) && math::nearly_equal(blob1[3], blob2[3], relTol) &&
           math::nearly_equal(blob1[4], blob2[4], relTol);
}

template <class Spacecraft_T>
Plane<Spacecraft_T>::Plane(std::vector<Spacecraft_T> _satellites) :
    satellites(_satellites)
{
    // Grab first element set as plane set
    const GravParam mu = get_mu<frames::earth::icrf.origin>();
    elements = satellites[0].get_initial_state().get_elements().template in_element_set<Keplerian<frames::earth::icrf>>(mu);

    // Check if other satellites are actually in-plane
    strict = true;
    for (const auto& sat : satellites) {
        const OrbitalElements satElements =
            sat.get_initial_state().get_elements().template in_element_set<Keplerian<frames::earth::icrf>>(mu);
        if (!planes_are_nearly_equal(elements, satElements, 1.0e-6 * mp_units::one)) {
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
void Plane<Spacecraft_T>::propagate(const Time& propTime, Integrator& integrator)
{
    for (auto& sat : satellites) {
        Vehicle vehicle{ sat };
        const StateHistory& satHistory = sat.get_state_history();
        if (satHistory.size() == 0) {
            throw std::runtime_error(
                "Cannot propagate spacecraft with no initial state. Spacecraft id: " + std::to_string(sat.get_id()) + "\n"
            );
        }
        State state0            = satHistory.first();
        const auto stateHistory = integrator.propagate(state0, propTime, vehicle);

        sat.set_state_history(stateHistory);
    }
}


template <class Spacecraft_T>
void Plane<Spacecraft_T>::propagate(const Date& endEpoch, Integrator& integrator)
{
    for (auto& sat : satellites) {
        Vehicle vehicle{ sat };
        const StateHistory& satHistory = sat.get_state_history();
        if (satHistory.size() == 0) {
            throw std::runtime_error(
                "Cannot propagate spacecraft with no initial state. Spacecraft id: " + std::to_string(sat.get_id()) + "\n"
            );
        }
        State state0            = satHistory.first();
        const auto stateHistory = integrator.propagate(state0, endEpoch, vehicle);

        sat.set_state_history(stateHistory);
    }
}

} // namespace astro
} // namespace astrea