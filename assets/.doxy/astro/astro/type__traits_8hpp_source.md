

# File type\_traits.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**types**](dir_81b398d2ba04cf47420d9ac22d356bcf.md) **>** [**type\_traits.hpp**](type__traits_8hpp.md)

[Go to the documentation of this file](type__traits_8hpp.md)


```C++

#pragma once

#include <type_traits>

namespace astrea {
namespace astro {

template <typename T>
using remove_cv_ref = std::remove_cv_t<std::remove_reference_t<T>>;

} // namespace astro
} // namespace astrea
```


