#include "State.hpp"

bool state_time_comparitor(State s, Time time ) { 
    return s.time < time; 
} 

std::ostream &operator<<(std::ostream& os, const State& state) { 
    return os << "(" << state.time << ") = " << state.elements << "\n";
}