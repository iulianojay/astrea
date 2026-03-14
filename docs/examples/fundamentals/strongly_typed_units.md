# Strongly Typed Units

Astrea relies on the mp-units library to handle units. This allows for strong typing of physical quantities, and compile-time unit checking, while also forcing developers to be explicit about units. This process helps avoid hard-to-see coversion issues, implicit units declarations, and inconsistencies in rounding and precision.

```cpp
// In general, the mp-units library is highly generalized for any united quantity, but Astrea uses simple type wrappers for consistency and convenience.
quantity<s> t = 1.0 * s; // mp-units explicit style
Time time     = 1.0 * s; // Astrea implicit style

std::cout << "Quantity Time: " << t << std::endl;
std::cout << "Astrea Time: " << time << std::endl;

// Outputs:
// Quantity Time: 1 s
// Astrea Time: 1 s
```