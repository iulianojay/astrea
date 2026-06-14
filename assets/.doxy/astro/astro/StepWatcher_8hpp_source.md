

# File StepWatcher.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**numerical**](dir_89452d20321c19f5539a283cd906a79c.md) **>** [**StepWatcher.hpp**](StepWatcher_8hpp.md)

[Go to the documentation of this file](StepWatcher_8hpp.md)


```C++

#pragma once

#include <functional>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

struct StepWatcher {
  public:
    StepWatcher() = default;

    template <typename T>
    StepWatcher(T&& func)
    {
        if constexpr (std::is_invocable_v<T, const Time&, const State&, const Vehicle&>) {
            _func = std::forward<T>(func);
        }
        else if constexpr (std::is_invocable_v<T, const Time&, const State&>) {
            _func = [f = std::forward<T>(func)](const Time& t, const State& s, const Vehicle&) { f(t, s); };
        }
        else if constexpr (std::is_invocable_v<T, const Time&, const Vehicle&>) {
            _func = [f = std::forward<T>(func)](const Time& t, const State&, const Vehicle& v) { f(t, v); };
        }
        else if constexpr (std::is_invocable_v<T, const State&, const Vehicle&>) {
            _func = [f = std::forward<T>(func)](const Time&, const State& s, const Vehicle& v) { f(s, v); };
        }
        else if constexpr (std::is_invocable_v<T, const Time&>) {
            _func = [f = std::forward<T>(func)](const Time& t, const State&, const Vehicle&) { f(t); };
        }
        else if constexpr (std::is_invocable_v<T, const State&>) {
            _func = [f = std::forward<T>(func)](const Time&, const State& s, const Vehicle&) { f(s); };
        }
        else if constexpr (std::is_invocable_v<T, const Vehicle&>) {
            _func = [f = std::forward<T>(func)](const Time&, const State&, const Vehicle& v) { f(v); };
        }
        else if constexpr (std::is_invocable_v<T>) {
            _func = [f = std::forward<T>(func)](const Time&, const State&, const Vehicle&) { f(); };
        }
        else {
            static_assert(false, "Unsupported StepWatcher function signature");
        }
    }

    void operator()(const Time& time, const State& state, const Vehicle& vehicle) const
    {
        if (_func) { _func(time, state, vehicle); }
    }

  private:
    std::function<void(const Time&, const State&, const Vehicle&)> _func; 
};

} // namespace astro
} // namespace astrea
```


