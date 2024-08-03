#include "Time.hpp"

std::ostream &operator<<(std::ostream& os, Time const& time) { 
    using namespace std::chrono;
    return os << duration_cast<minutes>(time.time).count() << " min";
}