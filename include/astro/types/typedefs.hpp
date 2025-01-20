#pragma once

#ifndef SWIG
    #include <array>
    #include <cstdint>
#else

%ignore element_array;
%ignore basis_array;

#endif

#include <mp-units/systems/si.h>

using element_array = std::array<double, 6>;
using basis_array = std::array<double, 3>;
using basis = std::array<basis_array, 3>;


using RadiusVector = std::array<
    mp_units::quantity<
        mp_units::si::unit_symbols::km
    >,
3>;

using VelocityVector = std::array<
    mp_units::quantity<
        mp_units::si::unit_symbols::km / mp_units::si::unit_symbols::s
    >,
3>;

using AccelerationVector = std::array<
    mp_units::quantity<
        mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s)
    >,
3>;

using EnumType = uint32_t;

#ifdef SWIG

%template(element_array) std::array<double, 6>;
%template(basis_array) std::array<double, 3>;

#endif