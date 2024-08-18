#pragma once

#ifndef SWIG
    #include <array>
#else

%ignore element_array;
class element_array {};

#endif

using element_array = std::array<double, 6>;
using basis_array = std::array<double, 3>;
using basis = std::array<basis_array, 3>;