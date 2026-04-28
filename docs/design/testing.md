# Testing

Astrea's testing strategy ensures reliability, accuracy, and performance through comprehensive validation against established benchmarks, real-world data, and theoretical expectations. This document outlines the testing philosophy, methodologies, and infrastructure.

## Testing Philosophy

### 1. Correctness First
All algorithms must be validated against known analytical solutions, published benchmarks, and reference implementations before being integrated.

### 2. Multi-Level Validation
Testing occurs at multiple levels: unit tests for individual components, integration tests for component interaction, and system tests for end-to-end workflows.

### 3. Real-World Validation
Benchmark data includes actual mission data, NASA published test cases, and comparison with operational aerospace software.

### 4. Continuous Validation
Automated testing prevents regression and ensures new features don't break existing functionality.

## Test Categories 

### Unit Tests

```cpp
// Example: Testing coordinate frame transformations
class FrameTransformationTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_epoch_ = time::EpochTT{1000.0 * units::julian_day};
        icrf_position_ = Position<frames::ICRF>{
            Vector3{6778136.3, 0.0, 0.0} * units::metre
        };
    }
    
    time::EpochTT test_epoch_;
    Position<frames::ICRF> icrf_position_;
};

TEST_F(FrameTransformationTest, ICRFtoITRFTransformation) {
    auto itrf_position = transform_position<frames::ICRF, frames::ITRF>(
        icrf_position_, test_epoch_
    );
    
    // Verify transformation using known reference values
    auto expected_itrf = Vector3{6778136.3, 0.0, 0.0} * units::metre;
    auto tolerance = 1.0 * units::metre;
    
    EXPECT_NEAR(itrf_position.vector().x().value(), 
                expected_itrf.x().value(), tolerance.value());
}
```

### Integration Tests

```cpp
// Testing propagation with multiple force models
class PropagationIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        initial_state_ = state::CartesianState<>{
            Position<frames::ICRF>{Vector3{7000.0, 0.0, 0.0} * units::km},
            Velocity<frames::ICRF>{Vector3{0.0, 7.546, 0.0} * units::km_per_s},
            time::EpochTT{0.0 * units::second}
        };
        
        force_models_.push_back(std::make_unique<forces::CentralGravity>());
        force_models_.push_back(std::make_unique<forces::J2Perturbation>());
    }
    
    state::CartesianState<> initial_state_;
    std::vector<std::unique_ptr<ForceModel>> force_models_;
};
```

### Benchmark Validation Tests

None yet, but they're currently being designed. A future release will ship with runtime performance guarantees.


## NASA 6DOF Checkcases

An automatically generate report can be found [here](nasa_6dof_report/nasa_6dof_report.md)