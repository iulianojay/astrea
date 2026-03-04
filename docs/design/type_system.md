# Type System

Astrea's type system is designed to prevent common errors in aerospace calculations through compile-time checking and strong typing. The system leverages modern C++23 features to provide safety without sacrificing performance.

## Design Goals

### 1. Compile-time Safety
- **Unit Consistency**: Prevent dimensional analysis errors
- **Frame Correctness**: Eliminate coordinate frame confusion
- **Time Scale Accuracy**: Ensure proper time system handling
- **Conversion Safety**: Require explicit intent for potentially lossy operations

### 2. Zero Overhead
- **Compile-time Evaluation**: Move checks and conversions to compile-time
- **Template Optimization**: Enable aggressive compiler optimizations
- **Memory Efficiency**: No runtime overhead for type safety

### 3. Intuitive Usage
- **Natural Syntax**: Code reads like mathematical expressions
- **Clear Errors**: Helpful error messages for type mismatches
- **Familiar Concepts**: Types mirror aerospace engineering terminology

## Core Type Categories

### Physical Quantities with Units

Astrea extends [mp-units](https://github.com/mpusz/mp-units) with aerospace-specific quantities:

```cpp
namespace astrea::units {
    // Length quantities
    using length = mp_units::quantity<mp_units::isq::length[mp_units::si::metre]>;
    using distance = length;  // Alias for clarity in astrodynamics context
    
    // Time quantities
    using duration = mp_units::quantity<mp_units::isq::time[mp_units::si::second]>;
    using epoch_duration = duration;  // Time since reference epoch
    
    // Velocity quantities
    using velocity = mp_units::quantity<mp_units::isq::speed[mp_units::si::metre_per_second]>;
    
    // Angular quantities
    using angle = mp_units::quantity<mp_units::isq::plane_angle[mp_units::si::radian]>;
    using angular_velocity = mp_units::quantity<mp_units::isq::angular_velocity[mp_units::si::radian_per_second]>;
    
    // Aerospace-specific quantities
    using gravitational_parameter = mp_units::quantity<
        mp_units::isq::length.pow<3>() / mp_units::isq::time.pow<2>()
        [mp_units::si::cubic_metre_per_square_second]
    >;
}
```

#### Type-Safe Calculations

```cpp
// This compiles and produces correct results
auto orbital_velocity(units::length radius, units::gravitational_parameter mu) {
    return sqrt(mu / radius);  // Returns velocity quantity
}

// This fails to compile - unit mismatch
auto invalid_calculation(units::length radius, units::duration time) {
    return radius / time / time;  // ERROR: Cannot divide length by time squared
}
```

### Coordinate Frame Types

Strong typing prevents coordinate frame confusion:

```cpp
namespace astrea::frames {
    // Frame tag types
    struct ICRF {};     // International Celestial Reference Frame
    struct ITRF {};     // International Terrestrial Reference Frame
    struct TOD {};      // True of Date
    struct MOD {};      // Mean of Date
    struct LVLH {};     // Local Vertical Local Horizontal
    struct SEZ {};      // South-East-Zenith (topocentric)
    
    // Strongly typed position vectors
    template<typename Frame>
    class Position {
        math::Vector3<units::length> vector_;
    public:
        explicit Position(math::Vector3<units::length> vec) : vector_(vec) {}
        
        auto vector() const -> const math::Vector3<units::length>& { 
            return vector_; 
        }
        
        // Explicit conversion required
        template<typename ToFrame>
        auto transform_to() const -> Position<ToFrame>;
    };
    
    using PositionICRF = Position<ICRF>;
    using PositionITRF = Position<ITRF>;
    using PositionLVLH = Position<LVLH>;
}
```

#### Frame Transformation Safety

```cpp
// This compiles - explicit frame conversion
auto transform_example() {
    auto pos_icrf = frames::PositionICRF{/* ... */};
    auto pos_itrf = pos_icrf.transform_to<frames::ITRF>();  // Explicit conversion
    return pos_itrf;
}

// This fails to compile - implicit frame conversion not allowed
auto invalid_assignment() {
    auto pos_icrf = frames::PositionICRF{/* ... */};
    frames::PositionITRF pos_itrf = pos_icrf;  // ERROR: No implicit conversion
    return pos_itrf;
}
```

### Time System Types

Precise handling of different astronomical time scales:

```cpp
namespace astrea::time {
    // Time scale tag types
    struct UTC {};      // Coordinated Universal Time
    struct TT {};       // Terrestrial Time
    struct TAI {};      // International Atomic Time
    struct GPS {};      // GPS Time
    struct UT1 {};      // Universal Time 1
    
    // Strongly typed epochs
    template<typename TimeScale>
    class Epoch {
        units::epoch_duration since_j2000_;
    public:\n        explicit Epoch(units::epoch_duration duration) : since_j2000_(duration) {}\n        \n        auto since_j2000() const -> units::epoch_duration { \n            return since_j2000_; \n        }\n        \n        // Explicit time scale conversion\n        template<typename ToTimeScale>\n        auto convert_to() const -> Epoch<ToTimeScale>;\n        \n        // Arithmetic operations within the same time scale\n        auto operator+(units::duration dt) const -> Epoch<TimeScale> {\n            return Epoch<TimeScale>{since_j2000_ + dt};\n        }\n    };\n    \n    using EpochUTC = Epoch<UTC>;\n    using EpochTT = Epoch<TT>;\n    using EpochTAI = Epoch<TAI>;\n}\n```\n\n#### Time Scale Conversion Safety\n\n```cpp\n// Explicit time scale conversions required\nauto time_conversion_example() {\n    auto utc_epoch = time::EpochUTC{1000.0 * units::julian_day};\n    auto tt_epoch = utc_epoch.convert_to<time::TT>();  // Explicit conversion\n    return tt_epoch;\n}\n\n// Time arithmetic within same scale is allowed\nauto time_arithmetic() {\n    auto epoch1 = time::EpochUTC{1000.0 * units::julian_day};\n    auto epoch2 = epoch1 + 3600.0 * units::second;  // Same time scale\n    return epoch2;\n}\n```\n\n### State Representation Types\n\nType-safe orbital state representations:\n\n```cpp\nnamespace astrea::state {\n    // Element set tag types\n    struct Cartesian {};\n    struct Keplerian {};\n    struct Equinoctial {};\n    struct ModifiedEquinoctial {};\n    \n    // Strongly typed orbital states\n    template<typename ElementSet, typename Frame, typename TimeScale>\n    class State {\n        // Element-specific data storage\n        ElementData<ElementSet> elements_;\n        time::Epoch<TimeScale> epoch_;\n        \n    public:\n        // Type-safe accessors\n        auto elements() const -> const ElementData<ElementSet>&;\n        auto epoch() const -> time::Epoch<TimeScale>;\n        \n        // Explicit conversions\n        template<typename ToElementSet>\n        auto convert_to() const -> State<ToElementSet, Frame, TimeScale>;\n        \n        template<typename ToFrame>\n        auto transform_to() const -> State<ElementSet, ToFrame, TimeScale>;\n    };\n    \n    // Common state type aliases\n    template<typename Frame = frames::ICRF, typename TimeScale = time::TT>\n    using CartesianState = State<Cartesian, Frame, TimeScale>;\n    \n    template<typename Frame = frames::ICRF, typename TimeScale = time::TT>\n    using KeplerianState = State<Keplerian, Frame, TimeScale>;\n}\n```\n\n#### State Conversion Type Safety\n\n```cpp\n// Explicit element set conversions\nauto element_conversion() {\n    auto cartesian = state::CartesianState<>{/* ... */};\n    auto keplerian = cartesian.convert_to<state::Keplerian>();  // Explicit\n    return keplerian;\n}\n\n// Frame and time scale must match for operations\nauto compatible_states() {\n    auto state1 = state::CartesianState<frames::ICRF, time::TT>{/* ... */};\n    auto state2 = state::CartesianState<frames::ICRF, time::TT>{/* ... */};\n    // Operations allowed - same frame and time scale\n    return state1.difference_from(state2);\n}\n```\n\n## Advanced Type System Features\n\n### Concept-Based Constraints\n\n```cpp\n// C++20 concepts for type checking\ntemplate<typename T>\nconcept CoordinateFrame = requires {\n    typename T;  // Must be a complete type\n    // Additional frame-specific requirements\n};\n\ntemplate<typename T>\nconcept TimeScale = requires {\n    typename T;  // Must be a complete type\n    // Additional time scale requirements\n};\n\ntemplate<typename T>\nconcept ElementSet = requires {\n    typename T;\n    // Must have conversion methods\n};\n\n// Function templates with concept constraints\ntemplate<CoordinateFrame FromFrame, CoordinateFrame ToFrame>\nauto transform_position(\n    const frames::Position<FromFrame>& pos,\n    const time::EpochTT& epoch\n) -> frames::Position<ToFrame>;\n```\n\n### SFINAE-Based Type Selection\n\n```cpp\n// Different algorithms based on frame types\ntemplate<typename Frame>\nauto compute_gravity_gradient(const frames::Position<Frame>& pos)\n    -> math::Matrix3<units::acceleration_per_length> {\n    \n    if constexpr (std::is_same_v<Frame, frames::ICRF>) {\n        return compute_inertial_gradient(pos);\n    } else if constexpr (std::is_same_v<Frame, frames::ITRF>) {\n        return compute_earth_fixed_gradient(pos);\n    } else {\n        // Convert to ICRF and compute\n        auto icrf_pos = pos.template transform_to<frames::ICRF>();\n        return compute_inertial_gradient(icrf_pos);\n    }\n}\n```\n\n### Template Metaprogramming for Optimization\n\n```cpp\n// Compile-time selection of transformation algorithms\ntemplate<typename FromFrame, typename ToFrame>\nstruct TransformationStrategy {\n    static constexpr bool is_identity = std::is_same_v<FromFrame, ToFrame>;\n    static constexpr bool is_simple_rotation = /* ... */;\n    static constexpr bool requires_time_dependent = /* ... */;\n    \n    using type = std::conditional_t<\n        is_identity, \n        IdentityTransform,\n        std::conditional_t<\n            is_simple_rotation,\n            SimpleRotationTransform<FromFrame, ToFrame>,\n            ComplexTransform<FromFrame, ToFrame>\n        >\n    >;\n};\n```\n\n## Error Handling and Diagnostics\n\n### Compile-Time Error Messages\n\nCustom error messages for common mistakes:\n\n```cpp\n// Static assertions with helpful messages\ntemplate<typename Frame>\nvoid validate_earth_fixed_frame() {\n    static_assert(\n        std::is_same_v<Frame, frames::ITRF> || std::is_same_v<Frame, frames::TOD>,\n        \"Earth-fixed calculations require ITRF or TOD frame. \"\n        \"Consider using .transform_to<frames::ITRF>() to convert your coordinates.\"\n    );\n}\n\n// SFINAE with clear error guidance\ntemplate<typename FromFrame, typename ToFrame>\nauto invalid_direct_transform() \n    -> std::enable_if_t<\n        !is_direct_transform_supported_v<FromFrame, ToFrame>,\n        frames::Position<ToFrame>\n    > {\n    static_assert(\n        always_false_v<FromFrame>,\n        \"Direct transformation not supported between these frames. \"\n        \"Consider using an intermediate frame like ICRF.\"\n    );\n}\n```\n\n### Runtime Type Information\n\n```cpp\n// Optional runtime type information for debugging\nclass TypeInfo {\npublic:\n    template<typename Frame>\n    static auto frame_name() -> std::string_view {\n        if constexpr (std::is_same_v<Frame, frames::ICRF>) {\n            return \"ICRF\";\n        } else if constexpr (std::is_same_v<Frame, frames::ITRF>) {\n            return \"ITRF\";\n        }\n        // ... other frames\n        return \"Unknown\";\n    }\n    \n    template<typename TimeScale>\n    static auto time_scale_name() -> std::string_view {\n        if constexpr (std::is_same_v<TimeScale, time::UTC>) {\n            return \"UTC\";\n        } else if constexpr (std::is_same_v<TimeScale, time::TT>) {\n            return \"TT\";\n        }\n        // ... other time scales\n        return \"Unknown\";\n    }\n};\n```\n\n## Performance Implications\n\n### Zero-Cost Abstractions\n\n```cpp\n// All type information is compile-time only\nstatic_assert(sizeof(frames::Position<frames::ICRF>) == \n              sizeof(math::Vector3<units::length>));\n              \nstatic_assert(sizeof(time::EpochUTC) == \n              sizeof(units::epoch_duration));\n\n// No virtual function overhead\nstatic_assert(std::is_trivially_copyable_v<frames::Position<frames::ICRF>>);\nstatic_assert(std::is_standard_layout_v<time::EpochUTC>);\n```\n\n### Compile-Time Computation\n\n```cpp\n// Frame transformation matrices computed at compile-time when possible\nconstexpr auto icrf_to_j2000_matrix() {\n    // Small rotation matrix - can be computed at compile-time\n    return math::Matrix3<units::dimensionless>{\n        /* known constant values */\n    };\n}\n\n// Time scale offsets as compile-time constants\nnamespace time_constants {\n    constexpr auto tai_minus_utc = 37.0 * units::second;\n    constexpr auto tt_minus_tai = 32.184 * units::second;\n    constexpr auto tt_minus_utc = tt_minus_tai + tai_minus_utc;\n}\n```\n\n## Type System Evolution\n\n### Future Enhancements\n\n1. **Module System Integration**: Support for C++23 modules\n2. **Reflection Support**: Automatic serialization and introspection\n3. **Contracts**: Use C++ contracts when available for runtime checking\n4. **Pattern Matching**: Leverage pattern matching for type dispatch\n\n### Backward Compatibility\n\n- Strong typing maintained across versions\n- Explicit migration paths for breaking changes\n- Deprecated features clearly marked\n- Type aliases provided for common legacy patterns\n\n---\n\n*Astrea's type system demonstrates how modern C++ can provide both safety and performance for mission-critical aerospace calculations, catching errors at compile-time while maintaining zero runtime overhead.*
