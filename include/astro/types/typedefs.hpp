#pragma once

#ifndef SWIG
    #include <array>
    #include <cstdint>
#else

%ignore element_array;
%ignore basis_array;

#endif

using element_array = std::array<double, 6>;
using basis_array = std::array<double, 3>;
using basis = std::array<basis_array, 3>;

using enum_type = uint32_t;

#ifdef SWIG

%template(element_array) std::array<double, 6>;
%template(basis_array) std::array<double, 3>;

#endif