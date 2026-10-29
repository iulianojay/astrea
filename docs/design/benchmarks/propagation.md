---
title: "Propagation Benchmarks"
description: "Runtime benchmarks for the Astrea propagation suite"
---

# Propagation Benchmarks

*Report generated on October 29, 2026 at 21:31:29*

*Run on **DESKTOP-CK5675I** — 16 CPUs @ 3800 MHz — 2026-10-29T21:27:39+02:00*

This report presents the propagation benchmark results for Astrea's orbital propagation suite.
Benchmarks are run using [Google Benchmark](https://github.com/google/benchmark) and cover all
supported equations of motion (EOM) types across a range of force model configurations and
propagation durations. Results are generated automatically by `scripts/run_benchmarks.sh`.

Propagation times benchmarked: **97 min** (~1 orbit), **1440 min** (1 day), **10080 min** (1 week).

## Summary

| Propagator | Configurations | Fastest (ms) | Slowest (ms) |
|---|---|---|---|
| TwoBody | 2 | 0.4195 | 6.2537 |
| J2MeanVop | 2 | 0.0332 | 0.0408 |
| KeplerianVop | 30 | 3.0444 | 12324.4392 |
| EquinoctialVop | 30 | 1.8763 | 1944.9118 |
| CowellsMethod | 30 | 134.7266 | 6948.5209 |

## Results

### TwoBody

!!! info "Notes"
    Keplerian two-body propagator. No force model — analytically exact for unperturbed orbits. Runtime scales with propagation duration due to step count.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.4195 | 0.3959 | 1,805 |
| 1440 | 6.2537 | 5.8996 | 119 |

### J2MeanVop

!!! info "Notes"
    Closed-form secular J2 propagator using mean variation of parameters. Extremely fast as it requires no numerical integration — runtime is essentially constant regardless of propagation duration.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.0332 | 0.0313 | 22,351 |
| 1440 | 0.0408 | 0.0385 | 18,110 |

### KeplerianVop

!!! info "Notes"
    Numerical VOP propagator in Keplerian elements. Supports full force model. Sensitive to gravity model degree/order and atmospheric drag — high-degree gravity with drag can result in very long run times.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 3.0444 | 2.8673 | 241 |
| 97 | 2 | Drag | 525.0479 | 496.8326 | 2 |
| 97 | 2 | N-Body | 175.7392 | 165.6497 | 4 |
| 97 | 2 | SRP | 202.8320 | 191.0753 | 4 |
| 97 | 2 | Drag, N-Body, SRP | 658.3731 | 619.7926 | 1 |
| 97 | 20 | None | 475.2459 | 446.0343 | 2 |
| 97 | 20 | Drag | 1264.5097 | 1187.5126 | 1 |
| 97 | 20 | N-Body | 484.2012 | 456.1477 | 2 |
| 97 | 20 | SRP | 488.5413 | 460.9034 | 2 |
| 97 | 20 | Drag, N-Body, SRP | 1305.2611 | 1230.7354 | 1 |
| 97 | 70 | None | 646.5078 | 609.2064 | 1 |
| 97 | 70 | Drag | 1554.7118 | 1465.2386 | 1 |
| 97 | 70 | N-Body | 633.5596 | 595.8509 | 1 |
| 97 | 70 | SRP | 661.7894 | 621.9390 | 1 |
| 97 | 70 | Drag, N-Body, SRP | 1599.9273 | 1508.1515 | 1 |
| 1440 | 2 | None | 3.6435 | 3.4252 | 203 |
| 1440 | 2 | Drag | 3288.4317 | 3086.9867 | 1 |
| 1440 | 2 | N-Body | 1418.3332 | 1336.9474 | 1 |
| 1440 | 2 | SRP | 1950.9163 | 1836.2915 | 1 |
| 1440 | 2 | Drag, N-Body, SRP | 6381.9891 | 6019.5431 | 1 |
| 1440 | 20 | None | 3469.2232 | 3254.9558 | 1 |
| 1440 | 20 | Drag | 9215.8825 | 8672.9104 | 1 |
| 1440 | 20 | N-Body | 3453.8936 | 3253.0408 | 1 |
| 1440 | 20 | SRP | 3572.8440 | 3366.1240 | 1 |
| 1440 | 20 | Drag, N-Body, SRP | 9281.5468 | 8744.4008 | 1 |
| 1440 | 70 | None | 5035.1925 | 4741.8243 | 1 |
| 1440 | 70 | Drag | 12324.4392 | 11615.3216 | 1 |
| 1440 | 70 | N-Body | 4999.1089 | 4699.5605 | 1 |
| 1440 | 70 | SRP | 5122.9092 | 4812.4585 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 12316.7300 | 11608.6215 | 1 |

### EquinoctialVop

!!! info "Notes"
    Numerical VOP propagator in equinoctial elements. Generally more efficient than KeplerianVop for perturbed orbits due to better conditioning of the element set near circular orbits.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 1.8763 | 1.7671 | 373 |
| 97 | 2 | Drag | 11.4187 | 10.8133 | 65 |
| 97 | 2 | N-Body | 7.2307 | 6.8161 | 103 |
| 97 | 2 | SRP | 1.8998 | 1.7896 | 388 |
| 97 | 2 | Drag, N-Body, SRP | 19.4862 | 18.3796 | 38 |
| 97 | 20 | None | 34.2808 | 32.1758 | 22 |
| 97 | 20 | Drag | 91.8144 | 86.2208 | 8 |
| 97 | 20 | N-Body | 34.4440 | 32.4497 | 22 |
| 97 | 20 | SRP | 34.3891 | 32.4431 | 22 |
| 97 | 20 | Drag, N-Body, SRP | 92.2525 | 86.8874 | 8 |
| 97 | 70 | None | 53.9468 | 50.8359 | 14 |
| 97 | 70 | Drag | 133.6686 | 126.0388 | 6 |
| 97 | 70 | N-Body | 53.4459 | 50.2659 | 14 |
| 97 | 70 | SRP | 52.7791 | 49.6039 | 14 |
| 97 | 70 | Drag, N-Body, SRP | 130.2951 | 122.8195 | 6 |
| 1440 | 2 | None | 2.4501 | 2.3076 | 302 |
| 1440 | 2 | Drag | 66.3020 | 62.1600 | 11 |
| 1440 | 2 | N-Body | 56.6193 | 53.3671 | 13 |
| 1440 | 2 | SRP | 18.8808 | 17.7922 | 39 |
| 1440 | 2 | Drag, N-Body, SRP | 152.8655 | 144.1739 | 5 |
| 1440 | 20 | None | 491.2421 | 461.2401 | 2 |
| 1440 | 20 | Drag | 1286.9009 | 1213.7959 | 1 |
| 1440 | 20 | N-Body | 492.1930 | 463.6843 | 2 |
| 1440 | 20 | SRP | 488.7774 | 459.3514 | 2 |
| 1440 | 20 | Drag, N-Body, SRP | 1290.3963 | 1216.1415 | 1 |
| 1440 | 70 | None | 777.8871 | 736.1485 | 1 |
| 1440 | 70 | Drag | 1932.2250 | 1820.9007 | 1 |
| 1440 | 70 | N-Body | 785.8262 | 740.2393 | 1 |
| 1440 | 70 | SRP | 783.4872 | 735.9221 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 1944.9118 | 1831.8559 | 1 |

### CowellsMethod

!!! info "Notes"
    Direct Cartesian numerical integration. Force model evaluation cost dominates — runtime scales linearly with force model complexity and propagation duration.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 134.7266 | 126.8788 | 6 |
| 97 | 2 | Drag | 364.3074 | 345.0032 | 2 |
| 97 | 2 | N-Body | 136.2106 | 128.3952 | 5 |
| 97 | 2 | SRP | 137.1494 | 129.1986 | 5 |
| 97 | 2 | Drag, N-Body, SRP | 367.9987 | 347.0941 | 2 |
| 97 | 20 | None | 148.4300 | 139.3069 | 5 |
| 97 | 20 | Drag | 398.2326 | 373.5880 | 2 |
| 97 | 20 | N-Body | 148.9783 | 140.3539 | 5 |
| 97 | 20 | SRP | 145.2172 | 137.0064 | 5 |
| 97 | 20 | Drag, N-Body, SRP | 390.5247 | 368.1076 | 2 |
| 97 | 70 | None | 198.9235 | 187.2428 | 4 |
| 97 | 70 | Drag | 488.7503 | 460.8520 | 2 |
| 97 | 70 | N-Body | 195.7211 | 184.0736 | 4 |
| 97 | 70 | SRP | 204.2928 | 191.9842 | 4 |
| 97 | 70 | Drag, N-Body, SRP | 493.6377 | 465.3500 | 2 |
| 1440 | 2 | None | 2069.0810 | 1947.6384 | 1 |
| 1440 | 2 | Drag | 5615.1896 | 5264.9047 | 1 |
| 1440 | 2 | N-Body | 2084.8724 | 1965.2857 | 1 |
| 1440 | 2 | SRP | 2089.3767 | 1970.3598 | 1 |
| 1440 | 2 | Drag, N-Body, SRP | 5617.6855 | 5296.0031 | 1 |
| 1440 | 20 | None | 2173.7825 | 2048.2711 | 1 |
| 1440 | 20 | Drag | 5714.0378 | 5388.7496 | 1 |
| 1440 | 20 | N-Body | 2156.7108 | 2028.3877 | 1 |
| 1440 | 20 | SRP | 2423.0482 | 2273.4433 | 1 |
| 1440 | 20 | Drag, N-Body, SRP | 5685.6553 | 5358.6906 | 1 |
| 1440 | 70 | None | 2816.4254 | 2665.9453 | 1 |
| 1440 | 70 | Drag | 6944.5416 | 6545.1803 | 1 |
| 1440 | 70 | N-Body | 2812.8275 | 2649.6767 | 1 |
| 1440 | 70 | SRP | 2845.7281 | 2672.9717 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 6948.5209 | 6541.9393 | 1 |

