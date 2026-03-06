

# File hash.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**units**](dir_69ee7df8d286dff8402d348058eb58eb.md) **>** [**units**](dir_8ace873b55bc88b2d1a73a241bbdd96b.md) **>** [**hash.hpp**](hash_8hpp.md)

[Go to the documentation of this file](hash_8hpp.md)


```C++

#pragma once

#include <functional>

#include <units/typedefs.hpp>

template <auto R, typename Rep>
struct std::hash<mp_units::quantity<R, Rep>> {
    std::size_t operator()(const mp_units::quantity<R, Rep>& q) const
    {
        return (std::hash<Rep>()(q.numerical_value_ref_in(q.unit)));
    }
};
```


