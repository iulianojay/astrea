---
title: "Propagation Benchmarks"
description: "Runtime benchmarks for the Astrea propagation suite"
---

# Propagation Benchmarks

*Report generated on May 31, 2026 at 11:20:18*

*Run on **DESKTOP-CK5675I** — 16 CPUs @ 3800 MHz — 2026-05-31T11:18:54+03:00*

This report presents the propagation benchmark results for Astrea's orbital propagation suite.
Benchmarks are run using [Google Benchmark](https://github.com/google/benchmark) and cover all
supported equations of motion (EOM) types across a range of force model configurations and
propagation durations. Results are generated automatically by `scripts/run_benchmarks.sh`.

Propagation times benchmarked: **97 min** (~1 orbit), **1440 min** (1 day), **10080 min** (1 week).

## Summary

| Propagator | Configurations | Fastest (ms) | Slowest (ms) |
|---|---|---|---|
| TwoBody | 2 | 0.4174 | 6.3565 |
| J2MeanVop | 2 | 0.0083 | 0.0111 |
| KeplerianVop | 30 | 0.0152 | 1156.7478 |
| EquinoctialVop | 30 | 0.0144 | 447.5944 |
| CowellsMethod | 30 | 0.7349 | 835.9460 |

## Results

### TwoBody

!!! info "Notes"
    Keplerian two-body propagator. No force model — analytically exact for unperturbed orbits. Runtime scales with propagation duration due to step count.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.4174 | 0.4219 | 1,649 |
| 1440 | 6.3565 | 6.4274 | 108 |

### J2MeanVop

!!! info "Notes"
    Closed-form secular J2 propagator using mean variation of parameters. Extremely fast as it requires no numerical integration — runtime is essentially constant regardless of propagation duration.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.0083 | 0.0084 | 83,348 |
| 1440 | 0.0111 | 0.0112 | 62,288 |

### KeplerianVop

!!! info "Notes"
    Numerical VOP propagator in Keplerian elements. Supports full force model. Sensitive to gravity model degree/order and atmospheric drag — high-degree gravity with drag can result in very long run times.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 0.0152 | 0.0148 | 47,258 |
| 97 | 2 | Drag | 0.0172 | 0.0173 | 40,365 |
| 97 | 2 | N-Body | 2.8348 | 2.8691 | 242 |
| 97 | 2 | SRP | 3.2291 | 3.2682 | 214 |
| 97 | 2 | Drag, N-Body, SRP | 5.4137 | 5.4791 | 126 |
| 97 | 20 | None | 17.9492 | 17.7097 | 39 |
| 97 | 20 | Drag | 19.9461 | 20.1391 | 35 |
| 97 | 20 | N-Body | 22.0270 | 22.2920 | 31 |
| 97 | 20 | SRP | 13.5509 | 13.7149 | 51 |
| 97 | 20 | Drag, N-Body, SRP | 16.9902 | 16.7686 | 42 |
| 97 | 70 | None | 157.2809 | 157.1104 | 4 |
| 97 | 70 | Drag | 155.5284 | 157.1714 | 4 |
| 97 | 70 | N-Body | 157.6299 | 159.5401 | 4 |
| 97 | 70 | SRP | 101.4103 | 102.6361 | 7 |
| 97 | 70 | Drag, N-Body, SRP | 110.2694 | 110.1646 | 6 |
| 1440 | 2 | None | 0.0202 | 0.0197 | 35,603 |
| 1440 | 2 | Drag | 0.0229 | 0.0231 | 30,174 |
| 1440 | 2 | N-Body | 22.4702 | 22.7407 | 31 |
| 1440 | 2 | SRP | 26.6281 | 26.9510 | 26 |
| 1440 | 2 | Drag, N-Body, SRP | 44.5400 | 43.4766 | 16 |
| 1440 | 20 | None | 112.0873 | 111.4939 | 6 |
| 1440 | 20 | Drag | 116.1748 | 117.4148 | 6 |
| 1440 | 20 | N-Body | 138.4686 | 140.1363 | 5 |
| 1440 | 20 | SRP | 90.9528 | 92.0565 | 8 |
| 1440 | 20 | Drag, N-Body, SRP | 115.3626 | 114.7846 | 6 |
| 1440 | 70 | None | 1129.6694 | 1133.4196 | 1 |
| 1440 | 70 | Drag | 1125.4953 | 1137.9544 | 1 |
| 1440 | 70 | N-Body | 1156.7478 | 1170.7373 | 1 |
| 1440 | 70 | SRP | 723.4069 | 732.1373 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 752.3821 | 754.5595 | 1 |

### EquinoctialVop

!!! info "Notes"
    Numerical VOP propagator in equinoctial elements. Generally more efficient than KeplerianVop for perturbed orbits due to better conditioning of the element set near circular orbits.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 0.0144 | 0.0139 | 50,390 |
| 97 | 2 | Drag | 0.0158 | 0.0159 | 43,900 |
| 97 | 2 | N-Body | 0.1093 | 0.1107 | 6,366 |
| 97 | 2 | SRP | 0.9453 | 0.9567 | 732 |
| 97 | 2 | Drag, N-Body, SRP | 1.6569 | 1.5980 | 438 |
| 97 | 20 | None | 1.0860 | 1.0747 | 654 |
| 97 | 20 | Drag | 1.1445 | 1.1560 | 565 |
| 97 | 20 | N-Body | 1.3203 | 1.3362 | 523 |
| 97 | 20 | SRP | 3.7756 | 3.8214 | 182 |
| 97 | 20 | Drag, N-Body, SRP | 4.2759 | 4.2339 | 165 |
| 97 | 70 | None | 11.8389 | 11.8450 | 54 |
| 97 | 70 | Drag | 11.7223 | 11.8481 | 59 |
| 97 | 70 | N-Body | 11.9934 | 12.1385 | 58 |
| 97 | 70 | SRP | 25.1332 | 25.4365 | 28 |
| 97 | 70 | Drag, N-Body, SRP | 28.4668 | 28.3270 | 25 |
| 1440 | 2 | None | 0.0188 | 0.0185 | 37,971 |
| 1440 | 2 | Drag | 0.0219 | 0.0221 | 33,026 |
| 1440 | 2 | N-Body | 0.8520 | 0.8623 | 813 |
| 1440 | 2 | SRP | 16.0191 | 16.2131 | 42 |
| 1440 | 2 | Drag, N-Body, SRP | 27.4501 | 26.9164 | 26 |
| 1440 | 20 | None | 15.2751 | 15.2189 | 46 |
| 1440 | 20 | Drag | 15.7006 | 15.8713 | 45 |
| 1440 | 20 | N-Body | 18.5173 | 18.7403 | 37 |
| 1440 | 20 | SRP | 55.3098 | 55.9801 | 12 |
| 1440 | 20 | Drag, N-Body, SRP | 66.5730 | 66.3328 | 11 |
| 1440 | 70 | None | 176.2505 | 175.9956 | 4 |
| 1440 | 70 | Drag | 174.2598 | 176.2102 | 4 |
| 1440 | 70 | N-Body | 178.5533 | 180.7171 | 4 |
| 1440 | 70 | SRP | 419.0181 | 424.0914 | 2 |
| 1440 | 70 | Drag, N-Body, SRP | 447.5944 | 449.5271 | 2 |

### CowellsMethod

!!! info "Notes"
    Direct Cartesian numerical integration. Force model evaluation cost dominates — runtime scales linearly with force model complexity and propagation duration.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 0.7349 | 0.7138 | 969 |
| 97 | 2 | Drag | 0.7676 | 0.7733 | 904 |
| 97 | 2 | N-Body | 1.6913 | 1.7116 | 407 |
| 97 | 2 | SRP | 2.0984 | 2.1238 | 330 |
| 97 | 2 | Drag, N-Body, SRP | 4.3327 | 4.2029 | 167 |
| 97 | 20 | None | 4.2152 | 4.1834 | 167 |
| 97 | 20 | Drag | 4.6107 | 4.6585 | 160 |
| 97 | 20 | N-Body | 5.1622 | 5.2243 | 131 |
| 97 | 20 | SRP | 7.0872 | 7.1731 | 98 |
| 97 | 20 | Drag, N-Body, SRP | 9.2858 | 9.2180 | 76 |
| 97 | 70 | None | 44.6941 | 44.7815 | 16 |
| 97 | 70 | Drag | 44.2018 | 44.6843 | 16 |
| 97 | 70 | N-Body | 45.3538 | 45.9021 | 15 |
| 97 | 70 | SRP | 55.4392 | 56.1098 | 13 |
| 97 | 70 | Drag, N-Body, SRP | 55.1496 | 55.2639 | 12 |
| 1440 | 2 | None | 10.9664 | 10.7815 | 65 |
| 1440 | 2 | Drag | 11.9095 | 12.0194 | 59 |
| 1440 | 2 | N-Body | 25.6013 | 25.9096 | 27 |
| 1440 | 2 | SRP | 32.2137 | 32.6042 | 21 |
| 1440 | 2 | Drag, N-Body, SRP | 59.3288 | 58.3494 | 12 |
| 1440 | 20 | None | 61.5663 | 61.4226 | 11 |
| 1440 | 20 | Drag | 62.0308 | 62.6838 | 11 |
| 1440 | 20 | N-Body | 75.6896 | 76.6036 | 9 |
| 1440 | 20 | SRP | 102.5457 | 103.7837 | 7 |
| 1440 | 20 | Drag, N-Body, SRP | 130.2243 | 129.9403 | 5 |
| 1440 | 70 | None | 629.6226 | 632.9174 | 1 |
| 1440 | 70 | Drag | 623.3129 | 630.3522 | 1 |
| 1440 | 70 | N-Body | 641.4477 | 649.1970 | 1 |
| 1440 | 70 | SRP | 790.2493 | 799.7934 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 835.9460 | 840.2586 | 1 |

