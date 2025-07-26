#include <astro/state/State.hpp>

namespace waveguide {
namespace astro {

std::ostream& operator<<(std::ostream& os, const State& state)
{
    os << state.get_epoch() << ", " << state.get_elements();
    return os;
}

} // namespace astro
} // namespace waveguide