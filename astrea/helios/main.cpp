/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <omp.h>

#include <webui.hpp>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace {

struct Point3 {
    double x;
    double y;
    double z;
};

struct PropagationResult {
    std::vector<std::vector<Point3>> frames; // frames[frameIdx][objectIdx]
    std::size_t numFrames = 0;
    double elapsedMs      = 0.0;
    double maxRadiusKm    = 0.0;
};

PropagationResult propagate_many_objects(const std::size_t objectCount, const Time& propTime, const Time& stepTime)
{
    struct SimpleVehicle {
        Mass get_mass() const { return 1000.0 * kg; }
    };

    const std::size_t numExpectedFrames =
        static_cast<std::size_t>(propTime.numerical_value_in(s) / stepTime.numerical_value_in(s)) + 1;

    PropagationResult result;
    result.numFrames = numExpectedFrames;
    result.frames.assign(numExpectedFrames, std::vector<Point3>(objectCount, { 0.0, 0.0, 0.0 }));

    const double earthRadiusKm = get_celestial_body_parameters<planets::Earth>().equitorialRadius.numerical_value_in(km);
    const Date epoch{};

    const auto start = std::chrono::steady_clock::now();

    double maxRadius = 0.0;

#pragma omp parallel reduction(max : maxRadius)
    {
        Integrator integrator;
        integrator.set_abs_tol(1.0e-10);
        integrator.set_rel_tol(1.0e-10);
        integrator.switch_fixed_timestep(true, stepTime);

        Vehicle vehicle{ SimpleVehicle{} };

        std::mt19937_64 rng(42ULL + static_cast<uint64_t>(omp_get_thread_num()));
        std::uniform_real_distribution<double> altKm(250.0, 36000.0);
        std::uniform_real_distribution<double> ecc(0.0, 0.08);
        std::uniform_real_distribution<double> incDeg(0.0, 110.0);
        std::uniform_real_distribution<double> angleDeg(0.0, 360.0);

#pragma omp for schedule(dynamic, 64)
        for (std::size_t i = 0; i < objectCount; ++i) {
            const double aKm = earthRadiusKm + altKm(rng);

            const Keplerian<frames::earth::icrf> elements(
                aKm * km, ecc(rng) * one, incDeg(rng) * deg, angleDeg(rng) * deg, angleDeg(rng) * deg, angleDeg(rng) * deg
            );

            const State state0{ elements, epoch };
            const StateHistory history = integrator.propagate(state0, propTime, vehicle);

            std::size_t frameIdx = 0;
            for (const auto& state : history) {
                if (frameIdx >= numExpectedFrames) break;
                const auto r               = state.get_position();
                const double x             = r.get_x().numerical_value_in(km);
                const double y             = r.get_y().numerical_value_in(km);
                const double z             = r.get_z().numerical_value_in(km);
                result.frames[frameIdx][i] = { x, y, z };
                maxRadius                  = std::max(maxRadius, std::sqrt(x * x + y * y + z * z));
                ++frameIdx;
            }
            // Pad any remaining slots with the last known position.
            for (; frameIdx > 0 && frameIdx < numExpectedFrames; ++frameIdx) {
                result.frames[frameIdx][i] = result.frames[frameIdx - 1][i];
            }
        }
    }

    const auto end     = std::chrono::steady_clock::now();
    result.elapsedMs   = std::chrono::duration<double, std::milli>(end - start).count();
    result.maxRadiusKm = maxRadius;

    return result;
}

std::string build_frames_js(const std::vector<std::vector<Point3>>& frames)
{
    std::ostringstream os;
    os << std::fixed << std::setprecision(3);
    os << "[";
    for (std::size_t f = 0; f < frames.size(); ++f) {
        if (f > 0) { os << ","; }
        os << "[";
        for (std::size_t i = 0; i < frames[f].size(); ++i) {
            if (i > 0) { os << ","; }
            os << "[" << frames[f][i].x << "," << frames[f][i].y << "," << frames[f][i].z << "]";
        }
        os << "]";
    }
    os << "]";
    return os.str();
}

std::string replace_all(std::string text, const std::string& from, const std::string& to)
{
    std::size_t pos = 0;
    while ((pos = text.find(from, pos)) != std::string::npos) {
        text.replace(pos, from.size(), to);
        pos += to.size();
    }
    return text;
}

std::string build_html(
    const std::vector<std::vector<Point3>>& frames,
    const double earthRadiusKm,
    const double maxRadiusKm,
    const double elapsedMs,
    const double propMinutes,
    const double stepMinutes
)
{
    const std::size_t numObjects = frames.empty() ? 0 : frames[0].size();
    const double throughput      = elapsedMs > 0.0 ? (1000.0 * static_cast<double>(numObjects) / elapsedMs) : 0.0;

    std::ostringstream stats;
    stats << std::fixed << std::setprecision(2);
    stats << "{"
          << "\"objects\":" << numObjects << ","
          << "\"elapsedMs\":" << elapsedMs << ","
          << "\"throughput\":" << throughput << ","
          << "\"propMinutes\":" << propMinutes << ","
          << "\"stepMinutes\":" << stepMinutes << ","
          << "\"numFrames\":" << frames.size() << "}";

    std::ostringstream nums;
    nums << std::fixed << std::setprecision(3);
    nums << "{"
         << "\"earthRadiusKm\":" << earthRadiusKm << ","
         << "\"maxRadiusKm\":" << maxRadiusKm << ""
         << "}";

    const std::string htmlTemplate = R"HTML(
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <script src="/webui.js"></script>
  <title>Astrea Helios</title>
  <style>
    :root {
      --bg0: #081226;
      --bg1: #12304a;
      --ink: #e9f4ff;
      --muted: #93b6d8;
      --earth: #2e78d8;
      --earth-atmo: #5eb2ff;
      --point: #d9f1ff;
      --panel: rgba(3, 16, 33, 0.7);
      --line: rgba(141, 194, 243, 0.35);
    }

    * { box-sizing: border-box; }

    body {
      margin: 0;
      min-height: 100vh;
      color: var(--ink);
      font-family: "IBM Plex Sans", "Segoe UI", sans-serif;
      background:
        radial-gradient(1200px 700px at 15% 10%, #1f4e79 0%, rgba(31, 78, 121, 0.0) 60%),
        radial-gradient(1000px 600px at 85% 85%, #104667 0%, rgba(16, 70, 103, 0.0) 65%),
        linear-gradient(160deg, var(--bg0), var(--bg1));
      overflow: hidden;
    }

    .hud {
      position: fixed;
      top: 14px;
      left: 14px;
      z-index: 10;
      background: var(--panel);
      border: 1px solid var(--line);
      border-radius: 14px;
      padding: 12px 14px;
      backdrop-filter: blur(6px);
      box-shadow: 0 12px 24px rgba(0, 0, 0, 0.35);
      max-width: min(92vw, 420px);
    }

    .title {
      margin: 0 0 6px;
      font-size: clamp(1.0rem, 2.4vw, 1.2rem);
      letter-spacing: 0.04em;
      text-transform: uppercase;
      color: #d7ecff;
    }

    .sub {
      margin: 0 0 10px;
      color: var(--muted);
      font-size: 0.92rem;
    }

    .metrics {
      margin: 0;
      padding: 0;
      list-style: none;
      display: grid;
      gap: 4px;
      font-size: 0.95rem;
    }

    .metrics strong {
      color: #ffffff;
      font-weight: 600;
    }

    canvas {
      width: 100vw;
      height: 100vh;
      display: block;
    }
  </style>
</head>
<body>
  <section class="hud">
    <h1 class="title">Astrea Helios Propagation View</h1>
    <p class="sub">Earth sphere + one rendered point per propagated object.</p>
    <ul class="metrics" id="metrics"></ul>
  </section>
  <canvas id="scene"></canvas>

  <script>
    const stats = __STATS__;
    const numeric = __NUMERIC__;
    const frames = __FRAMES__;

    const metrics = document.getElementById("metrics");
    metrics.innerHTML = [
      `<li><strong>${stats.objects.toLocaleString()}</strong> propagated objects</li>`,
      `<li><strong>${stats.propMinutes.toFixed(1)} min</strong> propagation &nbsp;·&nbsp; <strong>${stats.stepMinutes.toFixed(1)} min</strong> steps &nbsp;·&nbsp; <strong>${stats.numFrames}</strong> frames</li>`,
      `<li><strong>${stats.elapsedMs.toFixed(1)} ms</strong> backend propagation time</li>`,
      `<li><strong>${stats.throughput.toLocaleString(undefined, {maximumFractionDigits: 0})}</strong> objects/sec</li>`,
      `<li id="simtime"><strong>T+0.0 min</strong></li>`
    ].join("");

    const canvas = document.getElementById("scene");
    const ctx = canvas.getContext("2d");

    const state = {
      t: 0,
      frameIdx: 0,
      tickCount: 0,
      pointColor: "#d9f1ff",
      earthColor: "#2e78d8",
      earthGlow: "#5eb2ff",
      earthRadiusKm: numeric.earthRadiusKm,
      maxRadiusKm: numeric.maxRadiusKm
    };

    function resize() {
      const dpr = Math.max(1, Math.min(2, window.devicePixelRatio || 1));
      canvas.width = Math.floor(window.innerWidth * dpr);
      canvas.height = Math.floor(window.innerHeight * dpr);
      ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    }

    function draw() {
      state.t += 0.004;
      state.tickCount++;
      if (frames.length > 1 && state.tickCount % 90 === 0) {
        state.frameIdx = (state.frameIdx + 1) % frames.length;
        const el = document.getElementById("simtime");
        if (el) el.innerHTML = `<strong>T+${(state.frameIdx * stats.stepMinutes).toFixed(1)} min</strong>`;
      }
      const currentFrame = frames[state.frameIdx];

      const w = window.innerWidth;
      const h = window.innerHeight;
      const cx = w * 0.5;
      const cy = h * 0.54;

      ctx.clearRect(0, 0, w, h);

      const span = Math.max(state.maxRadiusKm, state.earthRadiusKm * 1.6);
      const scale = Math.min(w, h) * 0.43 / span;
      const yaw = state.t;
      const pitch = 0.5;
      const cosY = Math.cos(yaw), sinY = Math.sin(yaw);
      const cosP = Math.cos(pitch), sinP = Math.sin(pitch);

      const project = (p) => {
        const x1 = p[0] * cosY + p[2] * sinY;
        const z1 = -p[0] * sinY + p[2] * cosY;
        const y2 = p[1] * cosP - z1 * sinP;
        const z2 = p[1] * sinP + z1 * cosP;
        const depth = 1.0 / (1.0 + z2 / (span * 2.8));
        return {
          x: cx + x1 * scale * depth,
          y: cy - y2 * scale * depth,
          z: z2,
          d: depth
        };
      };

      const earthCenter = project([0, 0, 0]);
      const earthEdge = project([state.earthRadiusKm, 0, 0]);
      const earthRadiusPx = Math.max(2, Math.abs(earthEdge.x - earthCenter.x));

      const glow = ctx.createRadialGradient(
        earthCenter.x, earthCenter.y, earthRadiusPx * 0.4,
        earthCenter.x, earthCenter.y, earthRadiusPx * 2.5
      );
      glow.addColorStop(0, "rgba(94, 178, 255, 0.30)");
      glow.addColorStop(1, "rgba(94, 178, 255, 0.0)");
      ctx.fillStyle = glow;
      ctx.beginPath();
      ctx.arc(earthCenter.x, earthCenter.y, earthRadiusPx * 2.5, 0, Math.PI * 2);
      ctx.fill();

      ctx.fillStyle = state.earthColor;
      ctx.beginPath();
      ctx.arc(earthCenter.x, earthCenter.y, earthRadiusPx, 0, Math.PI * 2);
      ctx.fill();

      ctx.strokeStyle = "rgba(208, 235, 255, 0.24)";
      ctx.lineWidth = 1;
      for (let i = -2; i <= 2; i++) {
        const y = earthCenter.y + i * earthRadiusPx * 0.32;
        const rx = earthRadiusPx * Math.sqrt(Math.max(0, 1 - Math.pow((y - earthCenter.y) / earthRadiusPx, 2)));
        ctx.beginPath();
        ctx.ellipse(earthCenter.x, y, rx, rx * 0.22, 0, 0, Math.PI * 2);
        ctx.stroke();
      }

      for (let i = 0; i < currentFrame.length; i++) {
        const p = project(currentFrame[i]);
        if (p.z < -span * 0.9) continue;
        const alpha = Math.max(0.12, Math.min(1, 0.18 + 0.85 * p.d));
        const r = Math.max(0.7, Math.min(2.3, 1.1 * p.d));
        ctx.fillStyle = `rgba(217, 241, 255, ${alpha.toFixed(3)})`;
        ctx.beginPath();
        ctx.arc(p.x, p.y, r, 0, Math.PI * 2);
        ctx.fill();
      }

      requestAnimationFrame(draw);
    }

    window.addEventListener("resize", resize);
    resize();
    draw();
  </script>
</body>
</html>
)HTML";

    std::string html = htmlTemplate;
    html             = replace_all(std::move(html), "__STATS__", stats.str());
    html             = replace_all(std::move(html), "__NUMERIC__", nums.str());
    html             = replace_all(std::move(html), "__FRAMES__", build_frames_js(frames));
    return html;
}

} // namespace

int main()
{
    constexpr std::size_t kObjectCount   = 30000;
    constexpr double kPropagationMinutes = 90.0;

    constexpr double kOutputStepMinutes = 5.0;

    const Time propagationInterval = minutes(kPropagationMinutes);
    const Time stepInterval        = minutes(kOutputStepMinutes);
    const auto result              = propagate_many_objects(kObjectCount, propagationInterval, stepInterval);

    const double earthRadiusKm = get_celestial_body_parameters<planets::Earth>().equitorialRadius.numerical_value_in(km);

    webui::window window;
    window.set_size(1280, 860);
    window.set_center();

    const std::string html =
        build_html(result.frames, earthRadiusKm, result.maxRadiusKm, result.elapsedMs, kPropagationMinutes, kOutputStepMinutes);

    window.show(html);
    webui::wait();

    return 0;
}
