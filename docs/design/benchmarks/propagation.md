---
title: "Propagation Benchmarks"
description: "Runtime benchmarks for the Astrea propagation suite"
---

# Propagation Benchmarks

*Report generated on November 07, 2026 at 13:02:11*

*Run on **DESKTOP-CK5675I** — 16 CPUs @ 3800 MHz — 2026-11-07T12:58:06+02:00*

This report presents the propagation benchmark results for Astrea's orbital propagation suite.
Benchmarks are run using [Google Benchmark](https://github.com/google/benchmark) and cover all
supported equations of motion (EOM) types across a range of force model configurations and
propagation durations. Results are generated automatically by `scripts/run_benchmarks.sh`.

Propagation times benchmarked: **97 min** (~1 orbit), **1440 min** (1 day), **10080 min** (1 week).

## Summary

| Propagator | Configurations | Fastest (ms) | Slowest (ms) |
|---|---|---|---|
| TwoBody | 4 | 0.4110 | 7.0272 |
| J2MeanVop | 4 | 0.0332 | 0.0472 |
| KeplerianVop | 60 | 2.1371 | 17086.8694 |
| EquinoctialVop | 60 | 1.2711 | 2648.9369 |
| CowellsMethod | 60 | 91.4459 | 9513.1281 |

## Results

### TwoBody

!!! info "Notes"
    Keplerian two-body propagator. No force model — analytically exact for unperturbed orbits. Runtime scales with propagation duration due to step count.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.4614 | 0.4343 | 1,612 |
| 97 | 0.4110 | 0.3867 | 1,814 |
| 1440 | 7.0272 | 6.6144 | 106 |
| 1440 | 6.3783 | 6.0019 | 117 |

### J2MeanVop

!!! info "Notes"
    Closed-form secular J2 propagator using mean variation of parameters. Extremely fast as it requires no numerical integration — runtime is essentially constant regardless of propagation duration.

| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|
| 97 | 0.0332 | 0.0312 | 22,496 |
| 97 | 0.0336 | 0.0316 | 22,188 |
| 1440 | 0.0472 | 0.0445 | 15,772 |
| 1440 | 0.0416 | 0.0391 | 17,908 |

### KeplerianVop

!!! info "Notes"
    Numerical VOP propagator in Keplerian elements. Supports full force model. Sensitive to gravity model degree/order and atmospheric drag — high-degree gravity with drag can result in very long run times.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 2.3008 | 2.1656 | 323 |
| 97 | 2 | None | 2.1371 | 2.0112 | 351 |
| 97 | 2 | Drag | 698.4320 | 657.5066 | 1 |
| 97 | 2 | Drag | 466.5897 | 438.9363 | 2 |
| 97 | 2 | N-Body | 217.2980 | 204.5124 | 3 |
| 97 | 2 | N-Body | 121.9633 | 114.8230 | 6 |
| 97 | 2 | SRP | 258.1571 | 242.8620 | 3 |
| 97 | 2 | SRP | 139.2224 | 131.0167 | 5 |
| 97 | 2 | Drag, N-Body, SRP | 890.4306 | 836.4354 | 1 |
| 97 | 2 | Drag, N-Body, SRP | 565.6476 | 531.3566 | 1 |
| 97 | 20 | None | 594.9175 | 559.8461 | 1 |
| 97 | 20 | None | 329.0066 | 309.6280 | 2 |
| 97 | 20 | Drag | 1671.4972 | 1572.7467 | 1 |
| 97 | 20 | Drag | 1051.3031 | 990.0778 | 1 |
| 97 | 20 | N-Body | 596.4902 | 561.3608 | 1 |
| 97 | 20 | N-Body | 344.7473 | 324.3607 | 2 |
| 97 | 20 | SRP | 624.3861 | 587.3611 | 1 |
| 97 | 20 | SRP | 343.4172 | 322.6593 | 2 |
| 97 | 20 | Drag, N-Body, SRP | 1731.5805 | 1629.0436 | 1 |
| 97 | 20 | Drag, N-Body, SRP | 1114.7919 | 1048.0080 | 1 |
| 97 | 70 | None | 850.7279 | 800.9215 | 1 |
| 97 | 70 | None | 463.0693 | 436.6540 | 2 |
| 97 | 70 | Drag | 2108.9699 | 1983.9980 | 1 |
| 97 | 70 | Drag | 1295.0651 | 1221.6301 | 1 |
| 97 | 70 | N-Body | 856.0032 | 805.7472 | 1 |
| 97 | 70 | N-Body | 466.5116 | 438.8725 | 2 |
| 97 | 70 | SRP | 869.0257 | 817.5881 | 1 |
| 97 | 70 | SRP | 478.0976 | 450.0793 | 2 |
| 97 | 70 | Drag, N-Body, SRP | 2172.5115 | 2053.0637 | 1 |
| 97 | 70 | Drag, N-Body, SRP | 1359.3621 | 1282.0601 | 1 |
| 1440 | 2 | None | 3.0355 | 2.8566 | 245 |
| 1440 | 2 | None | 2.5356 | 2.3862 | 295 |
| 1440 | 2 | Drag | 4443.5976 | 4181.3198 | 1 |
| 1440 | 2 | Drag | 2728.1811 | 2566.0206 | 1 |
| 1440 | 2 | N-Body | 1783.6476 | 1678.6125 | 1 |
| 1440 | 2 | N-Body | 1005.2252 | 942.5667 | 1 |
| 1440 | 2 | SRP | 2496.7674 | 2343.7292 | 1 |
| 1440 | 2 | SRP | 1335.4852 | 1256.7992 | 1 |
| 1440 | 2 | Drag, N-Body, SRP | 8446.4139 | 7934.0996 | 1 |
| 1440 | 2 | Drag, N-Body, SRP | 5319.8816 | 5005.5780 | 1 |
| 1440 | 20 | None | 4340.4941 | 4085.9713 | 1 |
| 1440 | 20 | None | 2429.7301 | 2290.9542 | 1 |
| 1440 | 20 | Drag | 12341.4735 | 11614.6491 | 1 |
| 1440 | 20 | Drag | 7628.1755 | 7183.2152 | 1 |
| 1440 | 20 | N-Body | 4303.5059 | 4050.0809 | 1 |
| 1440 | 20 | N-Body | 2482.4371 | 2334.7707 | 1 |
| 1440 | 20 | SRP | 4496.3149 | 4230.0642 | 1 |
| 1440 | 20 | SRP | 2583.8282 | 2430.6139 | 1 |
| 1440 | 20 | Drag, N-Body, SRP | 12358.5325 | 11621.8265 | 1 |
| 1440 | 20 | Drag, N-Body, SRP | 7814.2239 | 7354.1330 | 1 |
| 1440 | 70 | None | 6739.3704 | 6342.0005 | 1 |
| 1440 | 70 | None | 3678.3593 | 3460.5084 | 1 |
| 1440 | 70 | Drag | 17086.8694 | 16070.7624 | 1 |
| 1440 | 70 | Drag | 10428.1226 | 9820.0220 | 1 |
| 1440 | 70 | N-Body | 6708.3392 | 6315.8986 | 1 |
| 1440 | 70 | N-Body | 3687.0688 | 3468.2431 | 1 |
| 1440 | 70 | SRP | 6902.2336 | 6502.3148 | 1 |
| 1440 | 70 | SRP | 3731.4369 | 3512.8519 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 17009.4143 | 16003.0118 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 10326.6535 | 9714.5208 | 1 |

### EquinoctialVop

!!! info "Notes"
    Numerical VOP propagator in equinoctial elements. Generally more efficient than KeplerianVop for perturbed orbits due to better conditioning of the element set near circular orbits.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 2.2663 | 2.1332 | 329 |
| 97 | 2 | None | 1.2844 | 1.2087 | 583 |
| 97 | 2 | Drag | 15.0716 | 14.1886 | 49 |
| 97 | 2 | Drag | 9.7221 | 9.1434 | 74 |
| 97 | 2 | N-Body | 8.7212 | 8.2077 | 85 |
| 97 | 2 | N-Body | 5.0614 | 4.7654 | 149 |
| 97 | 2 | SRP | 2.2815 | 2.1463 | 327 |
| 97 | 2 | SRP | 1.2711 | 1.1962 | 584 |
| 97 | 2 | Drag, N-Body, SRP | 25.7472 | 24.2110 | 29 |
| 97 | 2 | Drag, N-Body, SRP | 16.1337 | 15.1796 | 46 |
| 97 | 20 | None | 41.6570 | 39.2011 | 18 |
| 97 | 20 | None | 23.1911 | 21.8237 | 32 |
| 97 | 20 | Drag | 120.9694 | 113.8355 | 6 |
| 97 | 20 | Drag | 75.5162 | 71.1180 | 10 |
| 97 | 20 | N-Body | 41.9064 | 39.4386 | 18 |
| 97 | 20 | N-Body | 24.1552 | 22.7284 | 31 |
| 97 | 20 | SRP | 41.8380 | 39.3604 | 18 |
| 97 | 20 | SRP | 23.9768 | 22.5641 | 31 |
| 97 | 20 | Drag, N-Body, SRP | 121.7541 | 114.5367 | 6 |
| 97 | 20 | Drag, N-Body, SRP | 75.8126 | 71.3394 | 10 |
| 97 | 70 | None | 71.3306 | 67.1558 | 10 |
| 97 | 70 | None | 40.1631 | 37.8668 | 18 |
| 97 | 70 | Drag | 181.8079 | 171.0337 | 4 |
| 97 | 70 | Drag | 112.2202 | 105.8577 | 7 |
| 97 | 70 | N-Body | 71.7617 | 67.5704 | 10 |
| 97 | 70 | N-Body | 38.6539 | 36.3662 | 19 |
| 97 | 70 | SRP | 69.9852 | 65.8577 | 11 |
| 97 | 70 | SRP | 38.6554 | 36.3902 | 19 |
| 97 | 70 | Drag, N-Body, SRP | 177.9770 | 167.4150 | 4 |
| 97 | 70 | Drag, N-Body, SRP | 111.7132 | 105.3510 | 7 |
| 1440 | 2 | None | 2.9886 | 2.8125 | 249 |
| 1440 | 2 | None | 1.6828 | 1.5837 | 441 |
| 1440 | 2 | Drag | 85.2438 | 80.2067 | 9 |
| 1440 | 2 | Drag | 54.5761 | 51.3299 | 14 |
| 1440 | 2 | N-Body | 68.5564 | 64.5213 | 11 |
| 1440 | 2 | N-Body | 38.1109 | 35.8576 | 19 |
| 1440 | 2 | SRP | 24.7145 | 23.2168 | 30 |
| 1440 | 2 | SRP | 12.6413 | 11.8964 | 59 |
| 1440 | 2 | Drag, N-Body, SRP | 201.2159 | 189.0164 | 4 |
| 1440 | 2 | Drag, N-Body, SRP | 125.7246 | 118.3076 | 6 |
| 1440 | 20 | None | 599.0993 | 564.0341 | 1 |
| 1440 | 20 | None | 336.0379 | 316.8426 | 2 |
| 1440 | 20 | Drag | 1707.5891 | 1610.3170 | 1 |
| 1440 | 20 | Drag | 1061.0724 | 999.0869 | 1 |
| 1440 | 20 | N-Body | 601.6254 | 566.2200 | 1 |
| 1440 | 20 | N-Body | 365.7864 | 344.1372 | 2 |
| 1440 | 20 | SRP | 591.4483 | 556.4010 | 1 |
| 1440 | 20 | SRP | 344.1440 | 323.8645 | 2 |
| 1440 | 20 | Drag, N-Body, SRP | 1713.4483 | 1612.1044 | 1 |
| 1440 | 20 | Drag, N-Body, SRP | 1063.1238 | 1002.3685 | 1 |
| 1440 | 70 | None | 1038.7535 | 977.8328 | 1 |
| 1440 | 70 | None | 560.9592 | 527.7595 | 1 |
| 1440 | 70 | Drag | 2648.9369 | 2492.4591 | 1 |
| 1440 | 70 | Drag | 1602.6350 | 1507.9144 | 1 |
| 1440 | 70 | N-Body | 1042.7557 | 981.0002 | 1 |
| 1440 | 70 | N-Body | 564.9442 | 531.6475 | 1 |
| 1440 | 70 | SRP | 1043.5162 | 981.5273 | 1 |
| 1440 | 70 | SRP | 564.6604 | 531.5801 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 2634.2523 | 2485.2591 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 1610.3070 | 1513.8931 | 1 |

### CowellsMethod

!!! info "Notes"
    Direct Cartesian numerical integration. Force model evaluation cost dominates — runtime scales linearly with force model complexity and propagation duration.

| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |
|---|---|---|---|---|---|
| 97 | 2 | None | 162.9126 | 153.3431 | 5 |
| 97 | 2 | None | 92.6540 | 87.2008 | 8 |
| 97 | 2 | Drag | 483.4682 | 455.1288 | 2 |
| 97 | 2 | Drag | 304.5124 | 286.4116 | 2 |
| 97 | 2 | N-Body | 164.2280 | 154.5640 | 5 |
| 97 | 2 | N-Body | 92.1539 | 86.7587 | 8 |
| 97 | 2 | SRP | 164.7121 | 154.9527 | 5 |
| 97 | 2 | SRP | 91.4459 | 86.0520 | 8 |
| 97 | 2 | Drag, N-Body, SRP | 484.7636 | 455.7337 | 2 |
| 97 | 2 | Drag, N-Body, SRP | 325.3277 | 306.1116 | 2 |
| 97 | 20 | None | 180.0568 | 169.4392 | 4 |
| 97 | 20 | None | 100.1952 | 94.4370 | 7 |
| 97 | 20 | Drag | 523.8665 | 492.9452 | 2 |
| 97 | 20 | Drag | 324.6034 | 305.6965 | 2 |
| 97 | 20 | N-Body | 181.4734 | 170.7850 | 4 |
| 97 | 20 | N-Body | 103.0961 | 97.0001 | 7 |
| 97 | 20 | SRP | 176.8391 | 166.3600 | 4 |
| 97 | 20 | SRP | 99.1017 | 93.2635 | 7 |
| 97 | 20 | Drag, N-Body, SRP | 514.1928 | 483.7123 | 2 |
| 97 | 20 | Drag, N-Body, SRP | 361.1915 | 338.0015 | 2 |
| 97 | 70 | None | 262.5188 | 246.8188 | 3 |
| 97 | 70 | None | 145.7306 | 137.1749 | 5 |
| 97 | 70 | Drag | 667.0811 | 627.5688 | 1 |
| 97 | 70 | Drag | 408.7880 | 385.1706 | 2 |
| 97 | 70 | N-Body | 263.6140 | 248.2153 | 3 |
| 97 | 70 | N-Body | 145.3503 | 136.7423 | 5 |
| 97 | 70 | SRP | 263.5887 | 248.3539 | 3 |
| 97 | 70 | SRP | 146.8044 | 138.1983 | 5 |
| 97 | 70 | Drag, N-Body, SRP | 669.8507 | 630.0927 | 1 |
| 97 | 70 | Drag, N-Body, SRP | 421.5898 | 396.5960 | 2 |
| 1440 | 2 | None | 2511.5342 | 2362.5696 | 1 |
| 1440 | 2 | None | 1410.2237 | 1327.1329 | 1 |
| 1440 | 2 | Drag | 7405.6425 | 6965.1860 | 1 |
| 1440 | 2 | Drag | 4590.4790 | 4320.5073 | 1 |
| 1440 | 2 | N-Body | 2531.3771 | 2382.3541 | 1 |
| 1440 | 2 | N-Body | 1453.4666 | 1367.5694 | 1 |
| 1440 | 2 | SRP | 2535.3100 | 2384.1899 | 1 |
| 1440 | 2 | SRP | 1423.1601 | 1339.2487 | 1 |
| 1440 | 2 | Drag, N-Body, SRP | 7410.1310 | 6971.0365 | 1 |
| 1440 | 2 | Drag, N-Body, SRP | 4767.9199 | 4486.4356 | 1 |
| 1440 | 20 | None | 2622.7262 | 2469.1270 | 1 |
| 1440 | 20 | None | 1459.9602 | 1376.6397 | 1 |
| 1440 | 20 | Drag | 7547.1711 | 7113.5821 | 1 |
| 1440 | 20 | Drag | 4719.2544 | 4444.9213 | 1 |
| 1440 | 20 | N-Body | 2615.9547 | 2461.9843 | 1 |
| 1440 | 20 | N-Body | 1523.3364 | 1433.1052 | 1 |
| 1440 | 20 | SRP | 2599.3603 | 2444.6230 | 1 |
| 1440 | 20 | SRP | 1465.0141 | 1378.7318 | 1 |
| 1440 | 20 | Drag, N-Body, SRP | 7509.0051 | 7104.1804 | 1 |
| 1440 | 20 | Drag, N-Body, SRP | 4730.0395 | 4461.0126 | 1 |
| 1440 | 70 | None | 3746.1116 | 3526.5084 | 1 |
| 1440 | 70 | None | 2071.0746 | 1948.4521 | 1 |
| 1440 | 70 | Drag | 9513.1281 | 8949.7788 | 1 |
| 1440 | 70 | Drag | 5941.9963 | 5594.1342 | 1 |
| 1440 | 70 | N-Body | 3737.8952 | 3516.4727 | 1 |
| 1440 | 70 | N-Body | 2017.6289 | 1898.7210 | 1 |
| 1440 | 70 | SRP | 3757.7507 | 3533.4408 | 1 |
| 1440 | 70 | SRP | 2107.4849 | 1983.4917 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 9440.0015 | 8896.3148 | 1 |
| 1440 | 70 | Drag, N-Body, SRP | 5793.1693 | 5449.2950 | 1 |

