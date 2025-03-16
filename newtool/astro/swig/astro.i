/* astro.i */
%module astro

%{                      // This adds the include to the generated wrapper.
#include <string.h>

#include "astro.hpp"
%}

%include std_array.i
%include std_map.i
%include std_pair.i
%include std_string.i
%include std_unordered_map.i
%include std_unordered_set.i
%include std_vector.i

%include typemaps.i

%include "astro.hpp"    // This *processes* the include and makes wrappers.