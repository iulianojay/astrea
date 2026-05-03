---
title: "Propagation Benchmarks"
description: "Runtime benchmarks for the Astrea propagation suite"
---

# Propagation Benchmarks

*Report generated on May 03, 2026 at 16:35:22*

*Run on **DESKTOP-CK5675I** — 16 CPUs @ 3800 MHz — 2026-05-03T15:26:40+03:00*

This report presents the propagation benchmark results for Astrea's orbital propagation suite.
Benchmarks are run using [Google Benchmark](https://github.com/google/benchmark) and cover all
supported equations of motion (EOM) types across a range of force model configurations and
propagation durations. Results are generated automatically by `scripts/run_benchmarks.sh`.

Propagation times benchmarked: **97 min** (~1 orbit), **1440 min** (1 day).

## Summary

| Propagator | Configurations | Fastest (ms) | Slowest (ms) |
|---|---|---|---|
| TwoBody | 1 | 4.934 | 4.934 |
| J2MeanVop | 1 | 0.01046 | 0.01046 |
| KeplerianVop | 15 | 16.36 | 4.124e+05 |
| EquinoctialVop | 15 | 0.009574 | 0.01019 |
| CowellsMethod | 15 | 12.97 | 4.036e+05 |

## Results

### TwoBody

!!! info "Notes"
    Keplerian two-body propagator. No force model — analytically exact for unperturbed orbits. Runtime scales with propagation duration due to step count.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 1440 | 4.934 | 4.555 | 154 |

### J2MeanVop

!!! info "Notes"
    Closed-form secular J2 propagator using mean variation of parameters. Extremely fast as it requires no numerical integration — runtime is essentially constant regardless of propagation duration.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 1440 | 0.01046 | 0.009659 | 72,578 |

### KeplerianVop

!!! info "Notes"
    Numerical VOP propagator in Keplerian elements. Supports full force model. Sensitive to gravity model degree/order and atmospheric drag — high-degree gravity with drag can result in very long run times.

| Gravity | Perturbations | Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 2 | None | 1440 | 27.24 | 25.14 | 28 |
| 2 | Drag | 1440 | 1.508e+04 | 1.397e+04 | 1 |
| 2 | N-Body | 1440 | 36.56 | 33.74 | 21 |
| 2 | SRP | 1440 | 16.36 | 15.1 | 46 |
| 2 | Drag, N-Body, SRP | 1440 | 2.369e+04 | 2.196e+04 | 1 |
| 20 | None | 1440 | 149.6 | 139.9 | 5 |
| 20 | Drag | 1440 | 5.53e+04 | 5.114e+04 | 1 |
| 20 | N-Body | 1440 | 167 | 154.1 | 5 |
| 20 | SRP | 1440 | 65.92 | 60.84 | 11 |
| 20 | Drag, N-Body, SRP | 1440 | 6.375e+04 | 5.909e+04 | 1 |
| 70 | None | 1440 | 1523 | 1406 | 1 |
| 70 | Drag | 1440 | 4.034e+05 | 3.734e+05 | 1 |
| 70 | N-Body | 1440 | 1538 | 1420 | 1 |
| 70 | SRP | 1440 | 599 | 552.9 | 1 |
| 70 | Drag, N-Body, SRP | 1440 | 4.124e+05 | 3.824e+05 | 1 |

### EquinoctialVop

!!! info "Notes"
    Numerical VOP propagator in equinoctial elements. Generally more efficient than KeplerianVop for perturbed orbits due to better conditioning of the element set near circular orbits.

| Gravity | Perturbations | Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 2 | None | 1440 | 0.01007 | 0.009299 | 74,918 |
| 2 | Drag | 1440 | 0.01004 | 0.009267 | 74,737 |
| 2 | N-Body | 1440 | 0.01005 | 0.009274 | 74,580 |
| 2 | SRP | 1440 | 0.01004 | 0.00927 | 75,667 |
| 2 | Drag, N-Body, SRP | 1440 | 0.01017 | 0.009388 | 74,859 |
| 20 | None | 1440 | 0.01019 | 0.009407 | 74,984 |
| 20 | Drag | 1440 | 0.01019 | 0.009407 | 74,617 |
| 20 | N-Body | 1440 | 0.009574 | 0.009217 | 75,863 |
| 20 | SRP | 1440 | 0.01001 | 0.009242 | 76,070 |
| 20 | Drag, N-Body, SRP | 1440 | 0.01009 | 0.009317 | 74,634 |
| 70 | None | 1440 | 0.01019 | 0.009407 | 75,035 |
| 70 | Drag | 1440 | 0.01005 | 0.009323 | 75,320 |
| 70 | N-Body | 1440 | 0.009997 | 0.009228 | 74,964 |
| 70 | SRP | 1440 | 0.01005 | 0.009278 | 75,895 |
| 70 | Drag, N-Body, SRP | 1440 | 0.01012 | 0.009342 | 74,891 |

### CowellsMethod

!!! info "Notes"
    Direct Cartesian numerical integration. Force model evaluation cost dominates — runtime scales linearly with force model complexity and propagation duration.

| Gravity | Perturbations | Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 2 | None | 1440 | 12.97 | 11.97 | 60 |
| 2 | Drag | 1440 | 9244 | 8586 | 1 |
| 2 | N-Body | 1440 | 18.92 | 17.46 | 40 |
| 2 | SRP | 1440 | 17.8 | 16.43 | 42 |
| 2 | Drag, N-Body, SRP | 1440 | 1.615e+04 | 1.491e+04 | 1 |
| 20 | None | 1440 | 84.5 | 78 | 9 |
| 20 | Drag | 1440 | 4.9e+04 | 4.573e+04 | 1 |
| 20 | N-Body | 1440 | 91.34 | 84.31 | 8 |
| 20 | SRP | 1440 | 90.59 | 83.62 | 6 |
| 20 | Drag, N-Body, SRP | 1440 | 5.808e+04 | 5.378e+04 | 1 |
| 70 | None | 1440 | 860.7 | 794.5 | 1 |
| 70 | Drag | 1440 | 3.9e+05 | 3.613e+05 | 1 |
| 70 | N-Body | 1440 | 833.8 | 769.6 | 1 |
| 70 | SRP | 1440 | 826.3 | 762.8 | 1 |
| 70 | Drag, N-Body, SRP | 1440 | 4.036e+05 | 3.741e+05 | 1 |

