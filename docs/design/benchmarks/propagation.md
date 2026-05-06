---
title: "Propagation Benchmarks"
description: "Runtime benchmarks for the Astrea propagation suite"
---

# Propagation Benchmarks

*Report generated on May 04, 2026 at 12:26:57*

*Run on **DESKTOP-CK5675I** — 16 CPUs @ 3800 MHz — 2026-05-03T16:57:20+03:00*

This report presents the propagation benchmark results for Astrea's orbital propagation suite.
Benchmarks are run using [Google Benchmark](https://github.com/google/benchmark) and cover all
supported equations of motion (EOM) types across a range of force model configurations and
propagation durations. Results are generated automatically by `scripts/run_benchmarks.sh`.

Propagation times benchmarked: **97 min** (~1 orbit), **1440 min** (1 day), **10080 min** (1 week).

## Summary

| Propagator | Configurations | Fastest (ms) | Slowest (ms) |
|---|---|---|---|
| TwoBody | 4 | 0.3040 | 4.9535 |
| J2MeanVop | 4 | 0.0070 | 0.0105 |
| KeplerianVop | 60 | 2.5223 | 420435.4953 |
| EquinoctialVop | 60 | 0.0075 | 364834.8390 |
| CowellsMethod | 60 | 0.7558 | 421723.8894 |

## Results

### TwoBody

!!! info "Notes"
    Keplerian two-body propagator. No force model — analytically exact for unperturbed orbits. Runtime scales with propagation duration due to step count.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.3259 | 0.2981 | 2,204 |
| 97 | 0.3040 | 0.3094 | 2,253 |
| 1440 | 4.9535 | 4.5308 | 154 |
| 1440 | 4.6496 | 4.7318 | 148 |

### J2MeanVop

!!! info "Notes"
    Closed-form secular J2 propagator using mean variation of parameters. Extremely fast as it requires no numerical integration — runtime is essentially constant regardless of propagation duration.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.0079 | 0.0072 | 97,646 |
| 97 | 0.0070 | 0.0071 | 98,280 |
| 1440 | 0.0105 | 0.0096 | 72,709 |
| 1440 | 0.0094 | 0.0096 | 73,624 |

### KeplerianVop

!!! info "Notes"
    Numerical VOP propagator in Keplerian elements. Supports full force model. Sensitive to gravity model degree/order and atmospheric drag — high-degree gravity with drag can result in very long run times.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 2.7896 | 2.5517 | 275 |
| 97 | 2 | None | 2.5581 | 2.6033 | 262 |
| 97 | 2 | Drag | 2.8920 | 2.6291 | 268 |
| 97 | 2 | Drag | 2.5223 | 2.5651 | 274 |
| 97 | 2 | N-Body | 3.7007 | 3.3641 | 208 |
| 97 | 2 | N-Body | 3.2594 | 3.3248 | 210 |
| 97 | 2 | SRP | 3.6931 | 3.3573 | 210 |
| 97 | 2 | SRP | 3.2280 | 3.3030 | 210 |
| 97 | 2 | Drag, N-Body, SRP | 5.9863 | 5.4460 | 111 |
| 97 | 2 | Drag, N-Body, SRP | 5.2728 | 5.3762 | 130 |
| 97 | 20 | None | 25.2509 | 22.9554 | 29 |
| 97 | 20 | None | 21.1536 | 21.5163 | 33 |
| 97 | 20 | Drag | 26.7022 | 24.2732 | 28 |
| 97 | 20 | Drag | 23.3750 | 23.7737 | 29 |
| 97 | 20 | N-Body | 26.8251 | 24.3955 | 29 |
| 97 | 20 | N-Body | 23.1235 | 23.5382 | 30 |
| 97 | 20 | SRP | 18.5527 | 16.8649 | 53 |
| 97 | 20 | SRP | 12.7546 | 13.0334 | 44 |
| 97 | 20 | Drag, N-Body, SRP | 20.7171 | 18.8342 | 38 |
| 97 | 20 | Drag, N-Body, SRP | 17.6660 | 18.1730 | 38 |
| 97 | 70 | None | 219.8266 | 199.8382 | 4 |
| 97 | 70 | None | 186.3314 | 189.4980 | 4 |
| 97 | 70 | Drag | 228.6777 | 207.9378 | 4 |
| 97 | 70 | Drag | 193.0659 | 196.4336 | 4 |
| 97 | 70 | N-Body | 221.6225 | 201.5576 | 4 |
| 97 | 70 | N-Body | 187.9428 | 191.3123 | 4 |
| 97 | 70 | SRP | 118.0834 | 107.3477 | 7 |
| 97 | 70 | SRP | 100.3773 | 102.4934 | 7 |
| 97 | 70 | Drag, N-Body, SRP | 146.1980 | 132.9040 | 5 |
| 97 | 70 | Drag, N-Body, SRP | 125.1406 | 129.2177 | 5 |
| 1440 | 2 | None | 28.4030 | 25.9789 | 27 |
| 1440 | 2 | None | 24.5504 | 24.9844 | 28 |
| 1440 | 2 | Drag | 15325.8733 | 13992.5144 | 1 |
| 1440 | 2 | Drag | 13532.9113 | 13768.4817 | 1 |
| 1440 | 2 | N-Body | 36.8923 | 33.5367 | 21 |
| 1440 | 2 | N-Body | 32.4654 | 33.1161 | 21 |
| 1440 | 2 | SRP | 16.7049 | 15.1861 | 46 |
| 1440 | 2 | SRP | 14.8747 | 15.1995 | 46 |
| 1440 | 2 | Drag, N-Body, SRP | 23466.5122 | 21354.7583 | 1 |
| 1440 | 2 | Drag, N-Body, SRP | 20611.6428 | 20978.1253 | 1 |
| 1440 | 20 | None | 152.4496 | 138.5875 | 5 |
| 1440 | 20 | None | 132.4651 | 134.7151 | 5 |
| 1440 | 20 | Drag | 57547.2747 | 52476.9518 | 1 |
| 1440 | 20 | Drag | 49500.7295 | 50396.2989 | 1 |
| 1440 | 20 | N-Body | 167.3029 | 152.1495 | 5 |
| 1440 | 20 | N-Body | 149.4308 | 152.1118 | 5 |
| 1440 | 20 | SRP | 67.7640 | 61.5994 | 11 |
| 1440 | 20 | SRP | 58.7016 | 59.9853 | 12 |
| 1440 | 20 | Drag, N-Body, SRP | 65397.9888 | 59482.6611 | 1 |
| 1440 | 20 | Drag, N-Body, SRP | 56514.8288 | 57552.8783 | 1 |
| 1440 | 70 | None | 1573.9572 | 1430.7887 | 1 |
| 1440 | 70 | None | 1354.0742 | 1377.0423 | 1 |
| 1440 | 70 | Drag | 420435.4953 | 382787.6509 | 1 |
| 1440 | 70 | Drag | 358153.9112 | 365148.7698 | 1 |
| 1440 | 70 | N-Body | 1604.0714 | 1458.3865 | 1 |
| 1440 | 70 | N-Body | 1364.1591 | 1395.8520 | 1 |
| 1440 | 70 | SRP | 631.2354 | 573.8417 | 1 |
| 1440 | 70 | SRP | 539.9934 | 550.6022 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 420281.3267 | 382613.0571 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 364976.8567 | 372505.9423 | 1 |

### EquinoctialVop

!!! info "Notes"
    Numerical VOP propagator in equinoctial elements. Generally more efficient than KeplerianVop for perturbed orbits due to better conditioning of the element set near circular orbits.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 0.0075 | 0.0069 | 101,726 |
| 97 | 2 | None | 0.1286 | 0.1309 | 5,322 |
| 97 | 2 | Drag | 0.0077 | 0.0070 | 101,108 |
| 97 | 2 | Drag | 0.3771 | 0.3835 | 1,820 |
| 97 | 2 | N-Body | 0.0076 | 0.0069 | 100,970 |
| 97 | 2 | N-Body | 0.1804 | 0.1840 | 3,792 |
| 97 | 2 | SRP | 0.0076 | 0.0069 | 100,205 |
| 97 | 2 | SRP | 0.8296 | 0.8489 | 3,607 |
| 97 | 2 | Drag, N-Body, SRP | 0.0076 | 0.0069 | 100,520 |
| 97 | 2 | Drag, N-Body, SRP | 0.6778 | 0.6911 | 1,015 |
| 97 | 20 | None | 0.0076 | 0.0069 | 100,076 |
| 97 | 20 | None | 1.2944 | 1.3164 | 535 |
| 97 | 20 | Drag | 0.0076 | 0.0069 | 101,769 |
| 97 | 20 | Drag | 2.7772 | 2.8249 | 247 |
| 97 | 20 | N-Body | 0.0077 | 0.0070 | 99,889 |
| 97 | 20 | N-Body | 1.4249 | 1.4505 | 481 |
| 97 | 20 | SRP | 0.0076 | 0.0069 | 101,350 |
| 97 | 20 | SRP | 1.3681 | 1.3980 | 499 |
| 97 | 20 | Drag, N-Body, SRP | 0.0077 | 0.0070 | 100,684 |
| 97 | 20 | Drag, N-Body, SRP | 3.4725 | 3.5721 | 197 |
| 97 | 70 | None | 0.0080 | 0.0073 | 100,000 |
| 97 | 70 | None | 14.2275 | 14.4693 | 48 |
| 97 | 70 | Drag | 0.0079 | 0.0072 | 86,293 |
| 97 | 70 | Drag | 20.1921 | 20.5440 | 34 |
| 97 | 70 | N-Body | 0.0076 | 0.0069 | 101,152 |
| 97 | 70 | N-Body | 14.5021 | 14.7622 | 48 |
| 97 | 70 | SRP | 0.0076 | 0.0069 | 100,989 |
| 97 | 70 | SRP | 14.6769 | 14.9653 | 47 |
| 97 | 70 | Drag, N-Body, SRP | 0.0076 | 0.0069 | 100,938 |
| 97 | 70 | Drag, N-Body, SRP | 18.9300 | 19.3571 | 36 |
| 1440 | 2 | None | 0.0107 | 0.0097 | 74,527 |
| 1440 | 2 | None | 1.6016 | 1.6299 | 429 |
| 1440 | 2 | Drag | 0.0102 | 0.0094 | 75,246 |
| 1440 | 2 | Drag | 11431.1169 | 11628.0280 | 1 |
| 1440 | 2 | N-Body | 0.0102 | 0.0093 | 75,218 |
| 1440 | 2 | N-Body | 2.2236 | 2.2682 | 308 |
| 1440 | 2 | SRP | 0.0102 | 0.0093 | 75,460 |
| 1440 | 2 | SRP | 2.3603 | 2.4120 | 284 |
| 1440 | 2 | Drag, N-Body, SRP | 0.0103 | 0.0093 | 75,064 |
| 1440 | 2 | Drag, N-Body, SRP | 17889.7998 | 18212.4678 | 1 |
| 1440 | 20 | None | 0.0104 | 0.0094 | 75,543 |
| 1440 | 20 | None | 18.2281 | 18.5374 | 38 |
| 1440 | 20 | Drag | 0.0102 | 0.0093 | 75,565 |
| 1440 | 20 | Drag | 47421.5479 | 48243.6493 | 1 |
| 1440 | 20 | N-Body | 0.0102 | 0.0092 | 75,650 |
| 1440 | 20 | N-Body | 20.0727 | 20.4327 | 34 |
| 1440 | 20 | SRP | 0.0102 | 0.0093 | 75,283 |
| 1440 | 20 | SRP | 20.3824 | 20.8278 | 33 |
| 1440 | 20 | Drag, N-Body, SRP | 0.0102 | 0.0093 | 75,494 |
| 1440 | 20 | Drag, N-Body, SRP | 53827.2817 | 54918.3001 | 1 |
| 1440 | 70 | None | 0.0102 | 0.0093 | 75,402 |
| 1440 | 70 | None | 209.9554 | 213.5201 | 3 |
| 1440 | 70 | Drag | 0.0102 | 0.0093 | 75,923 |
| 1440 | 70 | Drag | 355771.8750 | 363032.3877 | 1 |
| 1440 | 70 | N-Body | 0.0102 | 0.0093 | 75,355 |
| 1440 | 70 | N-Body | 210.7442 | 215.6442 | 3 |
| 1440 | 70 | SRP | 0.0102 | 0.0093 | 75,530 |
| 1440 | 70 | SRP | 220.7680 | 225.1050 | 3 |
| 1440 | 70 | Drag, N-Body, SRP | 0.0103 | 0.0094 | 75,066 |
| 1440 | 70 | Drag, N-Body, SRP | 364834.8390 | 372397.9985 | 1 |

### CowellsMethod

!!! info "Notes"
    Direct Cartesian numerical integration. Force model evaluation cost dominates — runtime scales linearly with force model complexity and propagation duration.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 0.8506 | 0.7781 | 909 |
| 97 | 2 | None | 0.7558 | 0.7692 | 907 |
| 97 | 2 | Drag | 1.1697 | 1.0634 | 654 |
| 97 | 2 | Drag | 1.0246 | 1.0420 | 671 |
| 97 | 2 | N-Body | 1.2878 | 1.1706 | 601 |
| 97 | 2 | N-Body | 1.1333 | 1.1561 | 609 |
| 97 | 2 | SRP | 1.2117 | 1.1015 | 633 |
| 97 | 2 | SRP | 1.0707 | 1.0954 | 641 |
| 97 | 2 | Drag, N-Body, SRP | 2.1868 | 1.9957 | 349 |
| 97 | 2 | Drag, N-Body, SRP | 1.9187 | 1.9563 | 358 |
| 97 | 20 | None | 5.9625 | 5.4204 | 134 |
| 97 | 20 | None | 5.0898 | 5.1763 | 134 |
| 97 | 20 | Drag | 8.4076 | 7.6430 | 88 |
| 97 | 20 | Drag | 7.2370 | 7.3704 | 95 |
| 97 | 20 | N-Body | 6.4345 | 5.8516 | 121 |
| 97 | 20 | N-Body | 5.6173 | 5.7180 | 123 |
| 97 | 20 | SRP | 6.2631 | 5.6935 | 125 |
| 97 | 20 | SRP | 5.3416 | 5.4584 | 128 |
| 97 | 20 | Drag, N-Body, SRP | 9.3793 | 8.5264 | 82 |
| 97 | 20 | Drag, N-Body, SRP | 7.9568 | 8.1841 | 85 |
| 97 | 70 | None | 59.2418 | 53.8551 | 13 |
| 97 | 70 | None | 51.5048 | 52.3797 | 13 |
| 97 | 70 | Drag | 78.5500 | 72.3409 | 9 |
| 97 | 70 | Drag | 70.2492 | 71.4575 | 10 |
| 97 | 70 | N-Body | 60.6162 | 55.1270 | 12 |
| 97 | 70 | N-Body | 52.4449 | 53.4164 | 13 |
| 97 | 70 | SRP | 56.3303 | 51.2083 | 13 |
| 97 | 70 | SRP | 48.8864 | 49.8459 | 14 |
| 97 | 70 | Drag, N-Body, SRP | 71.0568 | 64.5965 | 11 |
| 97 | 70 | Drag, N-Body, SRP | 60.3720 | 61.3939 | 11 |
| 1440 | 2 | None | 14.0008 | 12.7277 | 59 |
| 1440 | 2 | None | 11.3597 | 11.5605 | 61 |
| 1440 | 2 | Drag | 10095.4141 | 9217.3869 | 1 |
| 1440 | 2 | Drag | 8347.7896 | 8490.2473 | 1 |
| 1440 | 2 | N-Body | 19.5004 | 17.7276 | 40 |
| 1440 | 2 | N-Body | 17.1079 | 17.4272 | 40 |
| 1440 | 2 | SRP | 18.1892 | 16.5352 | 42 |
| 1440 | 2 | SRP | 16.2036 | 16.5578 | 43 |
| 1440 | 2 | Drag, N-Body, SRP | 16453.5234 | 14957.5745 | 1 |
| 1440 | 2 | Drag, N-Body, SRP | 14271.6481 | 14591.4497 | 1 |
| 1440 | 20 | None | 87.7961 | 79.8136 | 9 |
| 1440 | 20 | None | 74.3418 | 75.6026 | 9 |
| 1440 | 20 | Drag | 51378.0272 | 46744.6507 | 1 |
| 1440 | 20 | Drag | 44210.1210 | 45047.3584 | 1 |
| 1440 | 20 | N-Body | 93.0941 | 84.6646 | 8 |
| 1440 | 20 | N-Body | 82.2056 | 83.6812 | 8 |
| 1440 | 20 | SRP | 93.3337 | 84.8455 | 8 |
| 1440 | 20 | SRP | 80.5175 | 82.2782 | 8 |
| 1440 | 20 | Drag, N-Body, SRP | 58926.8909 | 53599.3851 | 1 |
| 1440 | 20 | Drag, N-Body, SRP | 50803.0436 | 52057.1440 | 1 |
| 1440 | 70 | None | 881.1355 | 800.9747 | 1 |
| 1440 | 70 | None | 751.1144 | 763.8695 | 1 |
| 1440 | 70 | Drag | 411186.8975 | 374039.0730 | 1 |
| 1440 | 70 | Drag | 353502.7339 | 360614.4577 | 1 |
| 1440 | 70 | N-Body | 876.6878 | 796.9574 | 1 |
| 1440 | 70 | N-Body | 749.2250 | 766.6452 | 1 |
| 1440 | 70 | SRP | 873.0552 | 793.6675 | 1 |
| 1440 | 70 | SRP | 742.7300 | 757.3209 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 421723.8894 | 384086.8029 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 359508.1914 | 366990.3408 | 1 |

