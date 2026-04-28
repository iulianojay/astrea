/**
 * @file StepWatcher.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Step watcher for numerical integrator in orbital mechanics propagation
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <functional>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Function wrapper class for watching the state of the integrator at each step. This can be used for plotting or logging the state during propagation.
 */
struct StepWatcher {
  public:
    /**
     * @brief Default constructor for StepWatcher.
     */
    StepWatcher() = default;

    /**
     * @brief Constructor for StepWatcher that takes a function to be called at each step of the integration.
     *
     * @param func The function to be called at each step of the integration.
     */
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

    /**
     * @brief Call the stored function with the given time, state, and vehicle.
     *
     * @param time The current time of the integration step.
     * @param state The current state of the vehicle at this integration step.
     * @param vehicle The vehicle being propagated.
     */
    void operator()(const Time& time, const State& state, const Vehicle& vehicle) const
    {
        if (_func) { _func(time, state, vehicle); }
    }

  private:
    std::function<void(const Time&, const State&, const Vehicle&)> _func; //!< Function to be called at each step of the integration
};

} // namespace astro
} // namespace astrea