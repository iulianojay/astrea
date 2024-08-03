#include "Time.hpp"

std::ostream &operator<<(std::ostream& os, Time const& time) { 
    return os << time.time;
}