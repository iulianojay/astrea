/* astro.i */
%module astro
%{                      // This adds the include to the generated wrapper.
#include <string.h>

#include "astro.hpp"
%}

%include "astro.hpp"    // This *processes* the include and makes wrappers.