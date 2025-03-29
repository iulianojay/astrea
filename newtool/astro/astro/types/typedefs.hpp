#pragma once

#ifndef SWIG
#include <array>
#else

% ignore ElementArray;
% ignore BasisArray;

#endif

using ElementArray = std::array<double, 6>;
using BasisArray   = std::array<double, 3>;
using Basis        = std::array<BasisArray, 3>;


#ifdef SWIG

%template(ElementArray) std::array<double, 6>;
%template(BasisArray) std::array<double, 3>;

#endif