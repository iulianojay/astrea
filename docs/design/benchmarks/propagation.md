---
title: "Propagation Benchmarks"
description: "Runtime benchmarks for the Astrea propagation suite"
---

# Propagation Benchmarks

*Report generated on June 01, 2026 at 14:02:22*

*Run on **DESKTOP-CK5675I** — 16 CPUs @ 3800 MHz — 2026-06-01T14:00:57+03:00*

This report presents the propagation benchmark results for Astrea's orbital propagation suite.
Benchmarks are run using [Google Benchmark](https://github.com/google/benchmark) and cover all
supported equations of motion (EOM) types across a range of force model configurations and
propagation durations. Results are generated automatically by `scripts/run_benchmarks.sh`.

Propagation times benchmarked: **97 min** (~1 orbit), **1440 min** (1 day), **10080 min** (1 week).

## Summary

| Propagator | Configurations | Fastest (ms) | Slowest (ms) |
|---|---|---|---|
| TwoBody | 2 | 0.4074 | 6.2042 |
| J2MeanVop | 2 | 0.0083 | 0.0111 |
| KeplerianVop | 30 | 0.0150 | 1156.3215 |
| EquinoctialVop | 30 | 0.0140 | 441.0823 |
| CowellsMethod | 30 | 0.7210 | 823.5044 |

## Results

### TwoBody

!!! info "Notes"
    Keplerian two-body propagator. No force model — analytically exact for unperturbed orbits. Runtime scales with propagation duration due to step count.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.4074 | 0.4155 | 1,666 |
| 1440 | 6.2042 | 6.3268 | 111 |

### J2MeanVop

!!! info "Notes"
    Closed-form secular J2 propagator using mean variation of parameters. Extremely fast as it requires no numerical integration — runtime is essentially constant regardless of propagation duration.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.0083 | 0.0085 | 82,707 |
| 1440 | 0.0111 | 0.0113 | 61,851 |

### KeplerianVop

!!! info "Notes"
    Numerical VOP propagator in Keplerian elements. Supports full force model. Sensitive to gravity model degree/order and atmospheric drag — high-degree gravity with drag can result in very long run times.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 0.0150 | 0.0152 | 45,990 |
| 97 | 2 | Drag | 0.0172 | 0.0175 | 39,914 |
| 97 | 2 | N-Body | 2.7965 | 2.8527 | 246 |
| 97 | 2 | SRP | 3.1265 | 3.1881 | 220 |
| 97 | 2 | Drag, N-Body, SRP | 5.2092 | 5.3139 | 132 |
| 97 | 20 | None | 17.4880 | 17.8348 | 39 |
| 97 | 20 | Drag | 18.3859 | 18.7483 | 37 |
| 97 | 20 | N-Body | 21.9288 | 22.3688 | 31 |
| 97 | 20 | SRP | 13.4834 | 13.7497 | 50 |
| 97 | 20 | Drag, N-Body, SRP | 16.2618 | 16.5886 | 42 |
| 97 | 70 | None | 155.4633 | 158.5276 | 4 |
| 97 | 70 | Drag | 155.9381 | 159.0711 | 4 |
| 97 | 70 | N-Body | 157.8314 | 160.9465 | 4 |
| 97 | 70 | SRP | 100.8068 | 102.8319 | 7 |
| 97 | 70 | Drag, N-Body, SRP | 108.5652 | 110.7092 | 6 |
| 1440 | 2 | None | 0.0198 | 0.0202 | 34,710 |
| 1440 | 2 | Drag | 0.0231 | 0.0235 | 29,287 |
| 1440 | 2 | N-Body | 22.2923 | 22.7398 | 31 |
| 1440 | 2 | SRP | 25.7948 | 26.3043 | 27 |
| 1440 | 2 | Drag, N-Body, SRP | 41.3337 | 42.1644 | 17 |
| 1440 | 20 | None | 110.3874 | 112.5809 | 6 |
| 1440 | 20 | Drag | 115.4673 | 117.7418 | 6 |
| 1440 | 20 | N-Body | 137.5194 | 140.2802 | 5 |
| 1440 | 20 | SRP | 89.3539 | 91.1179 | 8 |
| 1440 | 20 | Drag, N-Body, SRP | 111.9055 | 114.1516 | 6 |
| 1440 | 70 | None | 1122.0564 | 1144.1552 | 1 |
| 1440 | 70 | Drag | 1130.8629 | 1153.5717 | 1 |
| 1440 | 70 | N-Body | 1156.3215 | 1179.1429 | 1 |
| 1440 | 70 | SRP | 718.0900 | 732.5134 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 742.7614 | 757.4471 | 1 |

### EquinoctialVop

!!! info "Notes"
    Numerical VOP propagator in equinoctial elements. Generally more efficient than KeplerianVop for perturbed orbits due to better conditioning of the element set near circular orbits.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 0.0140 | 0.0143 | 48,954 |
| 97 | 2 | Drag | 0.0160 | 0.0163 | 43,196 |
| 97 | 2 | N-Body | 0.1074 | 0.1095 | 6,397 |
| 97 | 2 | SRP | 0.9110 | 0.9290 | 754 |
| 97 | 2 | Drag, N-Body, SRP | 1.5203 | 1.5508 | 454 |
| 97 | 20 | None | 1.0611 | 1.0822 | 650 |
| 97 | 20 | Drag | 1.1004 | 1.1221 | 618 |
| 97 | 20 | N-Body | 1.3088 | 1.3351 | 523 |
| 97 | 20 | SRP | 3.7170 | 3.7903 | 184 |
| 97 | 20 | Drag, N-Body, SRP | 4.1194 | 4.2021 | 166 |
| 97 | 70 | None | 11.6131 | 11.8417 | 59 |
| 97 | 70 | Drag | 11.7537 | 11.9895 | 58 |
| 97 | 70 | N-Body | 11.9846 | 12.2210 | 57 |
| 97 | 70 | SRP | 25.0225 | 25.5251 | 28 |
| 97 | 70 | Drag, N-Body, SRP | 26.8533 | 27.3846 | 25 |
| 1440 | 2 | None | 0.0186 | 0.0189 | 36,947 |
| 1440 | 2 | Drag | 0.0212 | 0.0216 | 32,385 |
| 1440 | 2 | N-Body | 0.8408 | 0.8577 | 816 |
| 1440 | 2 | SRP | 15.4204 | 15.7247 | 45 |
| 1440 | 2 | Drag, N-Body, SRP | 25.3089 | 25.8167 | 27 |
| 1440 | 20 | None | 14.8903 | 15.1846 | 46 |
| 1440 | 20 | Drag | 15.4193 | 15.7240 | 45 |
| 1440 | 20 | N-Body | 18.3377 | 18.7055 | 37 |
| 1440 | 20 | SRP | 54.4699 | 55.5457 | 13 |
| 1440 | 20 | Drag, N-Body, SRP | 64.3710 | 65.6639 | 11 |
| 1440 | 70 | None | 174.5429 | 177.9856 | 4 |
| 1440 | 70 | Drag | 174.2096 | 177.7100 | 4 |
| 1440 | 70 | N-Body | 178.9905 | 182.5258 | 4 |
| 1440 | 70 | SRP | 415.1505 | 423.4860 | 2 |
| 1440 | 70 | Drag, N-Body, SRP | 441.0823 | 449.7979 | 2 |

### CowellsMethod

!!! info "Notes"
    Direct Cartesian numerical integration. Force model evaluation cost dominates — runtime scales linearly with force model complexity and propagation duration.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 0.7210 | 0.7353 | 954 |
| 97 | 2 | Drag | 0.7745 | 0.7898 | 892 |
| 97 | 2 | N-Body | 1.6773 | 1.7109 | 412 |
| 97 | 2 | SRP | 2.0028 | 2.0424 | 341 |
| 97 | 2 | Drag, N-Body, SRP | 3.9472 | 4.0265 | 173 |
| 97 | 20 | None | 4.1130 | 4.1945 | 167 |
| 97 | 20 | Drag | 4.2407 | 4.3244 | 164 |
| 97 | 20 | N-Body | 5.4666 | 5.5763 | 134 |
| 97 | 20 | SRP | 6.9673 | 7.1050 | 99 |
| 97 | 20 | Drag, N-Body, SRP | 9.0633 | 9.2455 | 77 |
| 97 | 70 | None | 44.2723 | 45.1437 | 15 |
| 97 | 70 | Drag | 44.3517 | 45.2435 | 15 |
| 97 | 70 | N-Body | 45.5596 | 46.4591 | 15 |
| 97 | 70 | SRP | 54.9096 | 56.0116 | 12 |
| 97 | 70 | Drag, N-Body, SRP | 54.0352 | 55.1030 | 13 |
| 1440 | 2 | None | 10.9396 | 11.1569 | 63 |
| 1440 | 2 | Drag | 11.6635 | 11.8936 | 59 |
| 1440 | 2 | N-Body | 25.2440 | 25.7510 | 27 |
| 1440 | 2 | SRP | 31.2148 | 31.8292 | 22 |
| 1440 | 2 | Drag, N-Body, SRP | 54.8669 | 55.9678 | 13 |
| 1440 | 20 | None | 60.6079 | 61.8019 | 11 |
| 1440 | 20 | Drag | 61.5102 | 62.7458 | 11 |
| 1440 | 20 | N-Body | 74.9838 | 76.4672 | 9 |
| 1440 | 20 | SRP | 100.7089 | 102.7322 | 7 |
| 1440 | 20 | Drag, N-Body, SRP | 125.4050 | 127.8850 | 5 |
| 1440 | 70 | None | 620.2184 | 632.4517 | 1 |
| 1440 | 70 | Drag | 622.2726 | 634.7852 | 1 |
| 1440 | 70 | N-Body | 643.6696 | 656.3750 | 1 |
| 1440 | 70 | SRP | 781.8564 | 797.5363 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 823.5044 | 839.7886 | 1 |

