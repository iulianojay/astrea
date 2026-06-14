

# File Integrator.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**numerical**](dir_89452d20321c19f5539a283cd906a79c.md) **>** [**Integrator.hpp**](Integrator_8hpp.md)

[Go to the documentation of this file](Integrator_8hpp.md)


```C++

#pragma once

#include <optional>
#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/event_detection/Schedule.hpp>
#include <astro/propagation/numerical/StepWatcher.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Interval.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

enum class StepMethod : EnumType {
    RK45,  
    RKF45, 
    RKF78, 
    DOP45, 
    DOP78, 
};

struct IntegratorSettings {
    Unitless absTol       = 1.0e-13;                              
    Unitless relTol       = 1.0e-13;                              
    int itMax             = 10000;                                
    StepMethod stepMethod = StepMethod::RKF78;                    
    Time initialTimeStep  = 1.0 * mp_units::si::unit_symbols::s;  
    bool useFixedStep     = false;                                
    Time fixedTimeStep    = 30.0 * mp_units::si::unit_symbols::s; 
};

class Integrator {

  public:
    Integrator() = default;

    Integrator(const IntegratorSettings& settings) :
        _ABS_TOL(settings.absTol),
        _REL_TOL(settings.relTol),
        _MAX_ITER(settings.itMax),
        _timeStepInitial(settings.initialTimeStep),
        _stepMethod(settings.stepMethod),
        _useFixedStep(settings.useFixedStep),
        _fixedTimeStep(settings.fixedTimeStep)
    {
    }

    ~Integrator() = default;

    StateHistory propagate(const State& state0, const Time& propTime, Vehicle vehicle);

    StateHistory propagate(const State& state0, const Date& endEpoch, Vehicle vehicle);

    State propagate_no_storage(const State& state0, const Time& propTime, Vehicle vehicle);

    State propagate_no_storage(const State& state0, const Date& endEpoch, Vehicle vehicle);

    void set_schedule(const Schedule& schedule);

    void clear();

    void add_event(const Event& event);

    void add_events(const std::vector<Event>& events);

    void clear_events();

    template <typename T>
        requires(std::derived_from<T, EquationsOfMotion>)
    void set_equations_of_motion(const T& eom)
    {
        _eom = std::make_unique<T>(eom);
    }

    void add_step_watcher(const StepWatcher& watcher);

    void clear_watchers();

    void set_abs_tol(const Unitless& absTol);

    void set_rel_tol(const Unitless& relTol);

    void set_max_iter(const int& itMax);

    void set_step_method(const StepMethod& stepMethod);

    void set_initial_timestep(const Time& dt0);

    void switch_fixed_timestep(const bool& onOff);

    void switch_fixed_timestep(const bool& onOff, const Time& fixedTimeStep);

    void set_timestep(const Time& fixedTimeStep);

    int n_func_evals() { return _functionEvaluations; }

  private:
    // Tolerances
    Unitless _ABS_TOL = 1.0e-13; 
    Unitless _REL_TOL = 1.0e-13; 

    // Integrator constants
    const Unitless _EPSILON               = 0.8;    
    const Unitless _MIN_ERROR_TO_CATCH    = 2.0e-4; 
    const Unitless _MIN_ERROR_STEP_FACTOR = 5.0;    
    const Unitless _MIN_REL_STEP_SIZE     = 0.2;    

    // Iteration variables
    unsigned long _iteration          = 0;   
    unsigned _variableStepIteration   = 0;   
    unsigned long _MAX_ITER           = 1e8; 
    const unsigned _MAX_VAR_STEP_ITER = 1e3; 

    // Function evals
    int _functionEvaluations = 0; 

    // Time variables
    Time _timeStepPrevious; 
    Date _epoch0;           

    // Error variables
    Unitless _maxErrorPrevious; 

    // Butcher Tableau
    std::size_t _nStages{};                    
    static const std::size_t _MAX_STAGES = 13; 
    std::array<std::array<Unitless, _MAX_STAGES>, _MAX_STAGES> _a = {}; 
    std::array<Unitless, _MAX_STAGES> _b                          = {}; 
    std::array<Unitless, _MAX_STAGES> _bhat                       = {}; 
    std::array<Unitless, _MAX_STAGES> _db = {}; 
    std::array<Unitless, _MAX_STAGES> _c  = {}; 

    // ith order steps
    std::array<State, _MAX_STAGES> _kMatrix = {}; 
    StatePartial _YFinalPrevious;                 

    // Initial step size
    Time _timeStepInitial = 60.0 * astrea::detail::time_unit; 

    // Run options
    bool _printOn = false; 
    bool _store   = true;  

    StepMethod _stepMethod = StepMethod::DOP45; 
    std::unique_ptr<EquationsOfMotion> _eom; 

    // Fixed step
    bool _useFixedStep  = false;                           
    Time _fixedTimeStep = 1.0 * astrea::detail::time_unit; 

    // Events
    EventDetector _eventDetector;
    Schedule _schedule;
    std::vector<StepWatcher> _stepWatchers;

    StateHistory propagate_impl(const State& state0, const Time& propTime, Vehicle vehicle);

    StatePartial find_state_derivative(const Time& time, const State& state, Vehicle& vehicle);

    void setup();

    void setup_butcher_tableau();

    bool try_step(Time& time, Time& timeStep, State& state, Vehicle& vehicle);

    Unitless find_max_error(const State& stateNew, const State& stateError) const;

    void take_fixed_step(Time& time, Time& timeStep, State& state, Vehicle& vehicle);

    std::pair<State, State> take_step(const Time& time, const Time& timeStep, const State& state, Vehicle& vehicle);

    bool check_error(const Unitless& maxError, const State& stateNew, const State& stateError, Time& time, Time& timeStep, State& state);

    Unitless get_relative_step_size(const Unitless& maxError) const;

    void store_final_func_eval(const Time& timeStep);

    bool check_event(const Time& time, State& state, Vehicle& vehicle);

    bool validate_state_and_time(const Time& time, const State& state) const;

    void watch_step(const Time& time, const State& state, const Vehicle& vehicle) const;
};

} // namespace astro
} // namespace astrea
```


