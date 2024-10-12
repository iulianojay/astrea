#pragma once

#ifndef SWIG
    #include <array>
#else

%ignore element_array;
%ignore basis_array;

#endif

using element_array = std::array<double, 6>;
using basis_array = std::array<double, 3>;
using basis = std::array<basis_array, 3>;


#ifdef SWIG

%template(element_array) std::array<double, 6>;
%template(basis_array) std::array<double, 3>;

#endif