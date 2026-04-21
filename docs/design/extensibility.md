# Extensibility

Astrea is designed to be highly extensible, allowing users to add custom force models, coordinate frames, propagators, and analysis tools without modifying the core library. This document outlines the extensibility patterns and interfaces that enable customization.

## Extensibility Principles

### 1. Open/Closed Principle
Astrea is open for extension but closed for modification. New functionality can be added through well-defined interfaces without changing existing code.

### 2. Plugin Architecture
Extensions are implemented as plugins that register themselves with the appropriate systems at startup or compile-time.

### 3. Type Safety
Extensions maintain the same compile-time type safety guarantees as the core library.

### 4. Performance Preservation
Extension mechanisms introduce zero runtime overhead when not used and minimal overhead when active.

## Extension Points

### Custom Force Models

```cpp
// Abstract base class for force models
class ForceModel {
public:
    Force() = default;
    virtual ~Force() = default;
    virtual Perturbation compute_perturbation(const State state, const Vehicle& vehicle) const = 0;

// Example: Custom atmospheric drag model
class CustomDragModel : public PerturbingForce {
    Unitless _dragCoefficient;
    Area _crossSectionalArea;
    units::mass _spacecraftMass;
    
public:
    auto compute_perturbation(const State state, const Vehicle& vehicle
    ) const -> CartesianVector<Acceleration, frames::earth::icrf> override {
        // Implementation details...
        return dragAcceleration;
    }
    
    auto name() const -> std::string_view override { return "CustomDrag"; }
};
```

### Custom Analysis Tools

```cpp
namespace astrea::trace {
    class AnalysisTool {
    public:
        virtual ~AnalysisTool() = default;
        
        virtual auto analyze(
            const std::vector<Platform>& platforms,
            const TimeInterval& analysis_period
        ) const -> AnalysisResults = 0;
        
        virtual auto name() const -> std::string_view = 0;
    };
}
```

---

*Astrea's extensibility architecture enables users to customize every aspect of the library while maintaining type safety, performance, and the consistent API design that makes Astrea reliable for mission-critical applications.*