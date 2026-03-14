---
title: "Comparison to NASA 6DoF Checkcases"
description: "Validation report comparing ASTREA orbital propagation results against NASA 6DoF reference checkcases"
---

# Comparison to NASA 6DoF Checkcases

This report presents a comprehensive comparison of ASTREA's orbital propagation capabilities against NASA's 6 Degree of Freedom (6DoF) reference checkcases. The validation demonstrates ASTREA's accuracy and reliability for astrodynamics computations by comparing trajectory propagation results across multiple orbital scenarios and numerical integration methods.

*Report generated on March 06, 2026 at 18:50:03*

## Executive Summary

This validation study encompasses **13 orbital test cases** with **52 total checkcases**, evaluating **4 distinct propagation methods**. The tests validate ASTREA's orbital mechanics implementation against established NASA reference solutions.

!!! info "Test Coverage"
    - **13** Orbit Tests
    - **52** Total Checkcases  
    - **4** Propagation Methods

### Tested Propagation Methods

The following numerical integration methods were evaluated:

- ** Cowells_Method**
- ** Equinoctial_VOP**
- ** Keplerian_VOP**
- ** Two_Body**

### Available Orbit Tests

- **Orbit_02** - 5 checkcases
- **Orbit_03A** - 4 checkcases
- **Orbit_03B** - 4 checkcases
- **Orbit_04** - 4 checkcases
- **Orbit_05A** - 4 checkcases
- **Orbit_05B** - 4 checkcases
- **Orbit_05C** - 4 checkcases
- **Orbit_06A** - 3 checkcases
- **Orbit_06B** - 4 checkcases
- **Orbit_07A** - 4 checkcases
- **Orbit_07B** - 4 checkcases
- **Orbit_07C** - 4 checkcases
- **Orbit_07D** - 4 checkcases


## Orbit_02

### Test Notes

This test validates the basic orbital propagation with no perturbations.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 3 | Two_Body        | 1.15263e-06 m         | 8.21942e-07 m            | 2.63415e-06 m        | 1.36897e-09 m        | 1.2929e-07 cm/s       | 9.18349e-08 cm/s         | 2.9089e-07 cm/s      | 1.22699e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 2.12151e-06 m         | 1.94208e-06 m            | 7.03431e-06 m        | 1.36897e-09 m        | 2.40918e-07 cm/s      | 2.19114e-07 cm/s         | 7.60277e-07 cm/s     | 1.22699e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 7.37598e-06 m         | 4.39303e-06 m            | 1.3458e-05 m         | 1.36897e-09 m        | 8.36633e-07 cm/s      | 4.98106e-07 cm/s         | 1.55116e-06 cm/s     | 1.22699e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 7.25852e-06 m         | 4.38224e-06 m            | 1.32574e-05 m        | 2.44889e-09 m        | 8.22222e-07 cm/s      | 4.98586e-07 cm/s         | 1.5283e-06 cm/s      | 2.71753e-10 cm/s     |
| Checkcase 2 | Two_Body        | 0.00046621 m          | 0.000269897 m            | 0.000901377 m        | 2.514e-09 m          | 5.27707e-05 cm/s      | 3.0641e-05 cm/s          | 0.000103065 cm/s     | 1.94453e-10 cm/s     |
| Checkcase 2 | Cowells_Method  | 0.00046524 m          | 0.000268874 m            | 0.000898553 m        | 2.514e-09 m          | 5.2659e-05 cm/s       | 3.05215e-05 cm/s         | 0.000102507 cm/s     | 1.94453e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 0.00047467 m          | 0.000274874 m            | 0.00091567 m         | 2.514e-09 m          | 5.37312e-05 cm/s      | 3.12067e-05 cm/s         | 0.000104818 cm/s     | 1.94453e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 0.000474556 m         | 0.000274846 m            | 0.000915469 m        | 2.72848e-09 m        | 5.37163e-05 cm/s      | 3.12069e-05 cm/s         | 0.000104795 cm/s     | 4.0817e-10 cm/s      |
| Checkcase 1 | Two_Body        | 1.02193e-05 m         | 7.2058e-06 m             | 2.15217e-05 m        | 1.42072e-08 m        | 1.15885e-06 cm/s      | 8.17376e-07 cm/s         | 2.44369e-06 cm/s     | 8.21565e-10 cm/s     |
| Checkcase 1 | Cowells_Method  | 1.11912e-05 m         | 8.26797e-06 m            | 2.67394e-05 m        | 1.42072e-08 m        | 1.27077e-06 cm/s      | 9.39121e-07 cm/s         | 3.00132e-06 cm/s     | 8.21565e-10 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 2.01895e-06 m         | 2.20995e-06 m            | 8.28424e-06 m        | 1.22529e-08 m        | 2.27702e-07 cm/s      | 2.5171e-07 cm/s          | 9.27576e-07 cm/s     | 1.06419e-09 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 2.06585e-06 m         | 2.28541e-06 m            | 8.48528e-06 m        | 6.98596e-09 m        | 2.32684e-07 cm/s      | 2.60632e-07 cm/s         | 9.50369e-07 cm/s     | 5.99931e-10 cm/s     |
| Checkcase 0 | Two_Body        | 0.000439215 m         | 0.000155127 m            | 0.00084044 m         | 1.36897e-09 m        | 4.49567e-05 cm/s      | 1.46666e-05 cm/s         | 7.8551e-05 cm/s      | 1.22699e-10 cm/s     |
| Checkcase 0 | Cowells_Method  | 0.000439171 m         | 0.00015509 m             | 0.000840672 m        | 1.36897e-09 m        | 4.49577e-05 cm/s      | 1.46646e-05 cm/s         | 7.85466e-05 cm/s     | 1.22699e-10 cm/s     |
| Checkcase 0 | Keplerian_VOP   | 0.000439414 m         | 0.000155347 m            | 0.000838366 m        | 1.36897e-09 m        | 4.49559e-05 cm/s      | 1.46747e-05 cm/s         | 7.82507e-05 cm/s     | 1.22699e-10 cm/s     |
| Checkcase 0 | Equinoctial_VOP | 0.000439418 m         | 0.000155346 m            | 0.000838373 m        | 2.44889e-09 m        | 4.49559e-05 cm/s      | 1.46743e-05 cm/s         | 7.82622e-05 cm/s     | 2.71753e-10 cm/s     |
| Checkcase 4 | Two_Body        | 1.51338e-05 m         | 8.73725e-06 m            | 3.47038e-05 m        | 1.36897e-09 m        | 1.69645e-06 cm/s      | 9.97869e-07 cm/s         | 3.74112e-06 cm/s     | 1.22699e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 1.60912e-05 m         | 9.77548e-06 m            | 3.92947e-05 m        | 1.36897e-09 m        | 1.8071e-06 cm/s       | 1.11825e-06 cm/s         | 4.27058e-06 cm/s     | 1.22699e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 7.52488e-06 m         | 4.02404e-06 m            | 2.09249e-05 m        | 1.36897e-09 m        | 8.22723e-07 cm/s      | 4.52808e-07 cm/s         | 2.18895e-06 cm/s     | 1.22699e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 7.6014e-06 m          | 4.06972e-06 m            | 2.11237e-05 m        | 2.44889e-09 m        | 8.3104e-07 cm/s       | 4.58881e-07 cm/s         | 2.21134e-06 cm/s     | 2.71753e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Two_Body, Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Two_Body, Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Two_Body, Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Two_Body, Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/Checkcase 2/orbital_elements_comparison.png)

#### Checkcase 0

**Propagation Methods:** Two_Body, Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 0 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/Checkcase 0/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/Checkcase 0/orbital_elements_comparison.png)


## Orbit_03A

### Test Notes

This test validates 4x4 oblateness models in propagation.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 1 | Cowells_Method  | 545.056 m             | 313.808 m                | 1053.07 m            | 1.42072e-08 m        | 61.8738 cm/s          | 35.4779 cm/s             | 121.743 cm/s         | 1.06594e-09 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 545.056 m             | 313.808 m                | 1053.07 m            | 1.42072e-08 m        | 61.8738 cm/s          | 35.4779 cm/s             | 121.743 cm/s         | 1.06594e-09 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 556.977 m             | 318.512 m                | 1079.98 m            | 1.46104e-08 m        | 63.4099 cm/s          | 36.0639 cm/s             | 123.251 cm/s         | 1.1128e-09 cm/s      |
| Checkcase 3 | Cowells_Method  | 549.629 m             | 316.673 m                | 1061.35 m            | 1.36897e-09 m        | 62.3923 cm/s          | 35.8016 cm/s             | 122.725 cm/s         | 1.22699e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 549.629 m             | 316.673 m                | 1061.35 m            | 1.36897e-09 m        | 62.3923 cm/s          | 35.8016 cm/s             | 122.725 cm/s         | 1.22699e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 561.586 m             | 321.318 m                | 1088.87 m            | 2.44889e-09 m        | 63.9318 cm/s          | 36.3827 cm/s             | 124.233 cm/s         | 2.71753e-10 cm/s     |
| Checkcase 2 | Cowells_Method  | 548.637 m             | 316.133 m                | 1059.62 m            | 2.514e-09 m          | 62.2798 cm/s          | 35.7407 cm/s             | 122.526 cm/s         | 1.94453e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 548.637 m             | 316.133 m                | 1059.62 m            | 2.514e-09 m          | 62.2798 cm/s          | 35.7407 cm/s             | 122.526 cm/s         | 1.94453e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 560.594 m             | 320.783 m                | 1087.16 m            | 2.72848e-09 m        | 63.8193 cm/s          | 36.3219 cm/s             | 124.034 cm/s         | 4.0817e-10 cm/s      |
| Checkcase 4 | Cowells_Method  | 548.669 m             | 316.205 m                | 1059.82 m            | 1.36897e-09 m        | 62.2835 cm/s          | 35.7489 cm/s             | 122.55 cm/s          | 1.22699e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 548.669 m             | 316.205 m                | 1059.82 m            | 1.36897e-09 m        | 62.2835 cm/s          | 35.7489 cm/s             | 122.55 cm/s          | 1.22699e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 560.626 m             | 320.856 m                | 1087.35 m            | 2.44889e-09 m        | 63.823 cm/s           | 36.3302 cm/s             | 124.057 cm/s         | 2.71753e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03A/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03A/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03A/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03A/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03A/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03A/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03A/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03A/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03A/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03A/Checkcase 2/orbital_elements_comparison.png)


## Orbit_03B

### Test Notes

This test validates 8x8 oblateness models in propagation.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 2 | Cowells_Method  | 901.093 m             | 655.72 m                 | 2110.89 m            | 2.514e-09 m          | 102.837 cm/s          | 73.7641 cm/s             | 218.886 cm/s         | 1.94453e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 901.093 m             | 655.72 m                 | 2110.89 m            | 2.514e-09 m          | 102.837 cm/s          | 73.7641 cm/s             | 218.886 cm/s         | 1.94453e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 912.918 m             | 668.701 m                | 2222.95 m            | 2.72848e-09 m        | 104.354 cm/s          | 74.7598 cm/s             | 226.561 cm/s         | 4.0817e-10 cm/s      |
| Checkcase 3 | Cowells_Method  | 902.071 m             | 656.256 m                | 2112.55 m            | 1.36897e-09 m        | 102.948 cm/s          | 73.8258 cm/s             | 219.074 cm/s         | 1.22699e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 902.071 m             | 656.256 m                | 2112.55 m            | 1.36897e-09 m        | 102.948 cm/s          | 73.8258 cm/s             | 219.074 cm/s         | 1.22699e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 913.925 m             | 669.193 m                | 2224.6 m             | 2.44889e-09 m        | 104.47 cm/s           | 74.814 cm/s              | 226.748 cm/s         | 2.71753e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 901.126 m             | 655.793 m                | 2111.08 m            | 1.36897e-09 m        | 102.841 cm/s          | 73.7723 cm/s             | 218.906 cm/s         | 1.22699e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 901.126 m             | 655.793 m                | 2111.08 m            | 1.36897e-09 m        | 102.841 cm/s          | 73.7723 cm/s             | 218.906 cm/s         | 1.22699e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 912.951 m             | 668.774 m                | 2223.13 m            | 2.44889e-09 m        | 104.358 cm/s          | 74.7681 cm/s             | 226.581 cm/s         | 2.71753e-10 cm/s     |
| Checkcase 1 | Cowells_Method  | 897.525 m             | 653.399 m                | 2103.91 m            | 1.42072e-08 m        | 102.433 cm/s          | 73.4989 cm/s             | 218.118 cm/s         | 1.06594e-09 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 897.525 m             | 653.399 m                | 2103.91 m            | 1.42072e-08 m        | 102.433 cm/s          | 73.4989 cm/s             | 218.118 cm/s         | 1.06594e-09 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 909.349 m             | 666.41 m                 | 2216 m               | 1.46104e-08 m        | 103.949 cm/s          | 74.4962 cm/s             | 225.796 cm/s         | 1.1128e-09 cm/s      |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03B/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03B/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03B/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03B/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03B/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03B/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03B/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03B/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03B/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03B/Checkcase 2/orbital_elements_comparison.png)


## Orbit_04

### Test Notes

This test validates n-body perturbations from the Sun.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 2 | Cowells_Method  | 0.0481298 m           | 0.0354889 m              | 0.137391 m           | 2.514e-09 m          | 0.00541631 cm/s       | 0.00402624 cm/s          | 0.0162371 cm/s       | 1.94453e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 0.0481263 m           | 0.0354884 m              | 0.137386 m           | 2.514e-09 m          | 0.0054159 cm/s        | 0.00402619 cm/s          | 0.0162365 cm/s       | 1.94453e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 0.0481017 m           | 0.0355054 m              | 0.135265 m           | 2.72848e-09 m        | 0.00540742 cm/s       | 0.00403285 cm/s          | 0.0162401 cm/s       | 4.0817e-10 cm/s      |
| Checkcase 3 | Cowells_Method  | 0.048403 m            | 0.0355277 m              | 0.137726 m           | 1.36897e-09 m        | 0.00545023 cm/s       | 0.00403027 cm/s          | 0.0162825 cm/s       | 1.22699e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 0.0483993 m           | 0.0355271 m              | 0.137721 m           | 1.36897e-09 m        | 0.0054498 cm/s        | 0.00403021 cm/s          | 0.0162819 cm/s       | 1.22699e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 0.0483668 m           | 0.0355276 m              | 0.135393 m           | 2.44889e-09 m        | 0.00544077 cm/s       | 0.00403609 cm/s          | 0.016282 cm/s        | 2.71753e-10 cm/s     |
| Checkcase 1 | Cowells_Method  | 0.048302 m            | 0.0355199 m              | 0.137628 m           | 1.42072e-08 m        | 0.00543689 cm/s       | 0.00402898 cm/s          | 0.0162646 cm/s       | 1.06594e-09 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 0.0482984 m           | 0.0355193 m              | 0.137623 m           | 1.42072e-08 m        | 0.00543646 cm/s       | 0.00402892 cm/s          | 0.016264 cm/s        | 1.06594e-09 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 0.0482684 m           | 0.0355266 m              | 0.13538 m            | 1.46104e-08 m        | 0.00542761 cm/s       | 0.00403514 cm/s          | 0.0162656 cm/s       | 1.1128e-09 cm/s      |
| Checkcase 4 | Cowells_Method  | 0.0465731 m           | 0.0356209 m              | 0.135783 m           | 1.36897e-09 m        | 0.00522873 cm/s       | 0.00404743 cm/s          | 0.0160368 cm/s       | 1.22699e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 0.0465722 m           | 0.0356212 m              | 0.135782 m           | 1.36897e-09 m        | 0.00522861 cm/s       | 0.00404748 cm/s          | 0.0160368 cm/s       | 1.22699e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 0.0466945 m           | 0.0358514 m              | 0.13659 m            | 2.44889e-09 m        | 0.00524185 cm/s       | 0.00404941 cm/s          | 0.016088 cm/s        | 2.71753e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_04/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_04/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_04/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_04/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_04/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_04/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_04/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_04/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_04/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_04/Checkcase 2/orbital_elements_comparison.png)


## Orbit_05A

### Test Notes

This test validates srp perturbations at solar min.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 1 | Cowells_Method  | 2.51003 m             | 1.56377 m                | 5.87057 m            | 1.38399e-08 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 1.72605e-08 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 2.51003 m             | 1.56377 m                | 5.87056 m            | 1.38399e-08 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 1.72605e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 2.51063 m             | 1.5648 m                 | 5.87873 m            | 1.32858e-08 m        | 0.2822 cm/s           | 0.169024 cm/s            | 0.667844 cm/s        | 1.72498e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 2.51039 m             | 1.56395 m                | 5.87112 m            | 2.16005e-09 m        | 0.282163 cm/s         | 0.168945 cm/s            | 0.667695 cm/s        | 3.58907e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 2.51039 m             | 1.56394 m                | 5.87111 m            | 2.16005e-09 m        | 0.282162 cm/s         | 0.168944 cm/s            | 0.667695 cm/s        | 3.58907e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 2.51099 m             | 1.56497 m                | 5.87928 m            | 2.44889e-09 m        | 0.282241 cm/s         | 0.169044 cm/s            | 0.667911 cm/s        | 3.39663e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 2.51003 m             | 1.56377 m                | 5.87057 m            | 2.23937e-09 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667629 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 2.51003 m             | 1.56377 m                | 5.87057 m            | 2.23937e-09 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 2.51063 m             | 1.5648 m                 | 5.87873 m            | 2.82392e-09 m        | 0.2822 cm/s           | 0.169024 cm/s            | 0.667844 cm/s        | 2.47508e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 2.51003 m             | 1.56377 m                | 5.87056 m            | 2.23937e-09 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 2.51003 m             | 1.56377 m                | 5.87055 m            | 2.23937e-09 m        | 0.28212 cm/s          | 0.168925 cm/s            | 0.667627 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 2.51063 m             | 1.5648 m                 | 5.87872 m            | 2.82392e-09 m        | 0.282199 cm/s         | 0.169024 cm/s            | 0.667843 cm/s        | 2.47508e-10 cm/s     |

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/Checkcase 2/orbital_elements_comparison.png)


## Orbit_05B

### Test Notes

This test validates srp perturbations at solar mean.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 2 | Cowells_Method  | 2.51039 m             | 1.56395 m                | 5.87112 m            | 2.16005e-09 m        | 0.282163 cm/s         | 0.168945 cm/s            | 0.667695 cm/s        | 3.58907e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 2.51039 m             | 1.56394 m                | 5.87111 m            | 2.16005e-09 m        | 0.282162 cm/s         | 0.168944 cm/s            | 0.667695 cm/s        | 3.58907e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 2.51099 m             | 1.56497 m                | 5.87928 m            | 2.44889e-09 m        | 0.282241 cm/s         | 0.169044 cm/s            | 0.667911 cm/s        | 3.39663e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 2.51003 m             | 1.56377 m                | 5.87056 m            | 2.23937e-09 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 2.51003 m             | 1.56377 m                | 5.87055 m            | 2.23937e-09 m        | 0.28212 cm/s          | 0.168925 cm/s            | 0.667627 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 2.51063 m             | 1.5648 m                 | 5.87872 m            | 2.82392e-09 m        | 0.282199 cm/s         | 0.169024 cm/s            | 0.667843 cm/s        | 2.47508e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 2.51003 m             | 1.56377 m                | 5.87057 m            | 2.23937e-09 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667629 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 2.51003 m             | 1.56377 m                | 5.87057 m            | 2.23937e-09 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 2.51063 m             | 1.5648 m                 | 5.87873 m            | 2.82392e-09 m        | 0.2822 cm/s           | 0.169024 cm/s            | 0.667844 cm/s        | 2.47508e-10 cm/s     |
| Checkcase 1 | Cowells_Method  | 2.51003 m             | 1.56377 m                | 5.87057 m            | 1.38399e-08 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 1.72605e-08 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 2.51003 m             | 1.56377 m                | 5.87056 m            | 1.38399e-08 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 1.72605e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 2.51063 m             | 1.5648 m                 | 5.87873 m            | 1.32858e-08 m        | 0.2822 cm/s           | 0.169024 cm/s            | 0.667844 cm/s        | 1.72498e-08 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/Checkcase 2/orbital_elements_comparison.png)


## Orbit_05C

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 4 | Cowells_Method  | 2.51003 m             | 1.56377 m                | 5.87056 m            | 2.23937e-09 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 2.51003 m             | 1.56377 m                | 5.87055 m            | 2.23937e-09 m        | 0.28212 cm/s          | 0.168925 cm/s            | 0.667627 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 2.51063 m             | 1.5648 m                 | 5.87872 m            | 2.82392e-09 m        | 0.282199 cm/s         | 0.169024 cm/s            | 0.667843 cm/s        | 2.47508e-10 cm/s     |
| Checkcase 2 | Cowells_Method  | 2.51039 m             | 1.56395 m                | 5.87112 m            | 2.16005e-09 m        | 0.282163 cm/s         | 0.168945 cm/s            | 0.667695 cm/s        | 3.58907e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 2.51039 m             | 1.56394 m                | 5.87111 m            | 2.16005e-09 m        | 0.282162 cm/s         | 0.168944 cm/s            | 0.667695 cm/s        | 3.58907e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 2.51099 m             | 1.56497 m                | 5.87928 m            | 2.44889e-09 m        | 0.282241 cm/s         | 0.169044 cm/s            | 0.667911 cm/s        | 3.39663e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 2.51003 m             | 1.56377 m                | 5.87057 m            | 2.23937e-09 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667629 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 2.51003 m             | 1.56377 m                | 5.87057 m            | 2.23937e-09 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 2.62154e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 2.51063 m             | 1.5648 m                 | 5.87873 m            | 2.82392e-09 m        | 0.2822 cm/s           | 0.169024 cm/s            | 0.667844 cm/s        | 2.47508e-10 cm/s     |
| Checkcase 1 | Cowells_Method  | 2.51003 m             | 1.56377 m                | 5.87057 m            | 1.38399e-08 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 1.72605e-08 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 2.51003 m             | 1.56377 m                | 5.87056 m            | 1.38399e-08 m        | 0.282121 cm/s         | 0.168925 cm/s            | 0.667628 cm/s        | 1.72605e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 2.51063 m             | 1.5648 m                 | 5.87873 m            | 1.32858e-08 m        | 0.2822 cm/s           | 0.169024 cm/s            | 0.667844 cm/s        | 1.72498e-08 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05C/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05C/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05C/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05C/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05C/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05C/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05C/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05C/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05C/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05C/Checkcase 2/orbital_elements_comparison.png)


## Orbit_06A

### Test Notes

This test validates atmospheric perturbations with a fixed sphere.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 4 | Cowells_Method  | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 4 | Keplerian_VOP   | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 4 | Equinoctial_VOP | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 2 | Cowells_Method  | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 2 | Keplerian_VOP   | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 2 | Equinoctial_VOP | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 3 | Cowells_Method  | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 3 | Keplerian_VOP   | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 3 | Equinoctial_VOP | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06A/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06A/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06A/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06A/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06A/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06A/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06A/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06A/Checkcase 2/orbital_elements_comparison.png)


## Orbit_06B

### Test Notes

This test validates atmospheric perturbations with a dynamic sphere.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 3 | Cowells_Method  | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 3 | Keplerian_VOP   | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 3 | Equinoctial_VOP | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 1 | Cowells_Method  | 5.98314e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 1 | Keplerian_VOP   | 5.98314e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 1 | Equinoctial_VOP | 5.98314e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 2 | Cowells_Method  | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 2 | Keplerian_VOP   | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 2 | Equinoctial_VOP | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 4 | Cowells_Method  | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 4 | Keplerian_VOP   | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |
| Checkcase 4 | Equinoctial_VOP | 5.98313e+07 m         | 3.08855e+07 m            | 1.11201e+08 m        | 33023.3 m            | 804865 cm/s           | 302766 cm/s              | 1.34714e+06 cm/s     | 1083.52 cm/s         |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06B/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06B/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06B/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06B/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06B/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06B/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06B/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06B/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06B/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06B/Checkcase 2/orbital_elements_comparison.png)


## Orbit_07A

### Test Notes

This test validates 4x4 oblateness and n-body effects simultaneously.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 4 | Cowells_Method  | 539.61 m              | 310.743 m                | 1042.77 m            | 2.23937e-09 m        | 61.2097 cm/s          | 35.0723 cm/s             | 120.95 cm/s          | 2.62154e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 539.61 m              | 310.743 m                | 1042.77 m            | 2.23937e-09 m        | 61.2097 cm/s          | 35.0723 cm/s             | 120.95 cm/s          | 2.62154e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 679.26 m              | 544.627 m                | 2173.96 m            | 2.82392e-09 m        | 64.3842 cm/s          | 46.3605 cm/s             | 171.999 cm/s         | 2.47508e-10 cm/s     |
| Checkcase 2 | Cowells_Method  | 539.614 m             | 310.746 m                | 1042.79 m            | 2.16005e-09 m        | 61.2101 cm/s          | 35.0727 cm/s             | 120.951 cm/s         | 3.58907e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 539.614 m             | 310.746 m                | 1042.79 m            | 2.16005e-09 m        | 61.2101 cm/s          | 35.0727 cm/s             | 120.951 cm/s         | 3.58907e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 679.261 m             | 544.63 m                 | 2173.97 m            | 2.44889e-09 m        | 64.3845 cm/s          | 46.3607 cm/s             | 172 cm/s             | 3.39663e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 540.596 m             | 311.28 m                 | 1044.49 m            | 2.23937e-09 m        | 61.3214 cm/s          | 35.1329 cm/s             | 121.148 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 540.596 m             | 311.28 m                 | 1044.49 m            | 2.23937e-09 m        | 61.3214 cm/s          | 35.1329 cm/s             | 121.148 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 679.586 m             | 545.235 m                | 2175.6 m             | 2.82392e-09 m        | 64.4739 cm/s          | 46.4014 cm/s             | 172.185 cm/s         | 2.47508e-10 cm/s     |
| Checkcase 1 | Cowells_Method  | 539.129 m             | 310.205 m                | 1042.21 m            | 1.38399e-08 m        | 61.1557 cm/s          | 35.0116 cm/s             | 120.856 cm/s         | 1.72605e-08 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 539.129 m             | 310.205 m                | 1042.21 m            | 1.38399e-08 m        | 61.1557 cm/s          | 35.0116 cm/s             | 120.856 cm/s         | 1.72605e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 679.036 m             | 544.13 m                 | 2172.48 m            | 1.32858e-08 m        | 64.3387 cm/s          | 46.3145 cm/s             | 171.857 cm/s         | 1.72498e-08 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07A/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07A/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07A/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07A/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07A/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07A/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07A/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07A/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07A/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07A/Checkcase 2/orbital_elements_comparison.png)


## Orbit_07B

### Test Notes

This test validates 8x8 oblateness and n-body effects simultaneously.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 4 | Cowells_Method  | 875.12 m              | 637.357 m                | 2062.27 m            | 2.23937e-09 m        | 99.8757 cm/s          | 71.6533 cm/s             | 214.282 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 875.12 m              | 637.357 m                | 2062.27 m            | 2.23937e-09 m        | 99.8757 cm/s          | 71.6533 cm/s             | 214.282 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 906.628 m             | 885.698 m                | 3297.03 m            | 2.82392e-09 m        | 100.745 cm/s          | 78.0401 cm/s             | 279.397 cm/s         | 2.47508e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 876.091 m             | 637.891 m                | 2063.92 m            | 2.23937e-09 m        | 99.9856 cm/s          | 71.7148 cm/s             | 214.469 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 876.091 m             | 637.891 m                | 2063.92 m            | 2.23937e-09 m        | 99.9856 cm/s          | 71.7148 cm/s             | 214.469 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 907.256 m             | 886.235 m                | 3298.67 m            | 2.82392e-09 m        | 100.844 cm/s          | 78.0926 cm/s             | 279.582 cm/s         | 2.47508e-10 cm/s     |
| Checkcase 2 | Cowells_Method  | 875.124 m             | 637.36 m                 | 2062.28 m            | 2.16005e-09 m        | 99.8761 cm/s          | 71.6536 cm/s             | 214.283 cm/s         | 3.58907e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 875.124 m             | 637.36 m                 | 2062.28 m            | 2.16005e-09 m        | 99.8761 cm/s          | 71.6536 cm/s             | 214.283 cm/s         | 3.58907e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 906.631 m             | 885.7 m                  | 3297.04 m            | 2.44889e-09 m        | 100.745 cm/s          | 78.0404 cm/s             | 279.398 cm/s         | 3.39663e-10 cm/s     |
| Checkcase 1 | Cowells_Method  | 874.603 m             | 636.815 m                | 2060.76 m            | 1.38399e-08 m        | 99.8179 cm/s          | 71.5935 cm/s             | 214.133 cm/s         | 1.72605e-08 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 874.603 m             | 636.815 m                | 2060.76 m            | 1.38399e-08 m        | 99.8179 cm/s          | 71.5935 cm/s             | 214.133 cm/s         | 1.72605e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 906.21 m              | 885.228 m                | 3295.55 m            | 1.32858e-08 m        | 100.689 cm/s          | 77.9885 cm/s             | 279.252 cm/s         | 1.72498e-08 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07B/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07B/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07B/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07B/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07B/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07B/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07B/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07B/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07B/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07B/Checkcase 2/orbital_elements_comparison.png)


## Orbit_07C

### Test Notes

This test validates 4x4 oblateness, n-body effects, and drag simultaneously.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 4 | Cowells_Method  | 748.086 m             | 787.17 m                 | 2772.28 m            | 2.23937e-09 m        | 84.548 cm/s           | 89.0019 cm/s             | 307.374 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 748.086 m             | 787.17 m                 | 2772.28 m            | 2.23937e-09 m        | 84.548 cm/s           | 89.0019 cm/s             | 307.374 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 1017.38 m             | 1064.14 m                | 4138.07 m            | 2.82392e-09 m        | 103.64 cm/s           | 103.288 cm/s             | 378.561 cm/s         | 2.47508e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 747.289 m             | 786.534 m                | 2770.56 m            | 2.23937e-09 m        | 84.4564 cm/s          | 88.9302 cm/s             | 307.175 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 747.289 m             | 786.534 m                | 2770.56 m            | 2.23937e-09 m        | 84.4564 cm/s          | 88.9302 cm/s             | 307.175 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 1016.8 m              | 1063.53 m                | 4136.34 m            | 2.82392e-09 m        | 103.56 cm/s           | 103.219 cm/s             | 378.366 cm/s         | 2.47508e-10 cm/s     |
| Checkcase 1 | Cowells_Method  | 748.637 m             | 787.575 m                | 2772.88 m            | 1.38399e-08 m        | 84.6115 cm/s          | 89.0487 cm/s             | 307.471 cm/s         | 1.72605e-08 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 748.637 m             | 787.575 m                | 2772.88 m            | 1.38399e-08 m        | 84.6115 cm/s          | 89.0487 cm/s             | 307.471 cm/s         | 1.72605e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 1017.73 m             | 1064.49 m                | 4138.83 m            | 1.32858e-08 m        | 103.692 cm/s          | 103.331 cm/s             | 378.655 cm/s         | 1.72498e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 748.082 m             | 787.167 m                | 2772.27 m            | 2.16005e-09 m        | 84.5475 cm/s          | 89.0015 cm/s             | 307.373 cm/s         | 3.58907e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 748.082 m             | 787.167 m                | 2772.27 m            | 2.16005e-09 m        | 84.5475 cm/s          | 89.0015 cm/s             | 307.373 cm/s         | 3.58907e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 1017.37 m             | 1064.14 m                | 4138.06 m            | 2.44889e-09 m        | 103.639 cm/s          | 103.288 cm/s             | 378.559 cm/s         | 3.39663e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07C/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07C/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07C/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07C/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07C/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07C/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07C/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07C/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07C/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07C/Checkcase 2/orbital_elements_comparison.png)


## Orbit_07D

### Test Notes

This test validates 8x8 oblateness, n-body effects, and drag simultaneously.

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 1 | Cowells_Method  | 438.62 m              | 548.992 m                | 2095.43 m            | 1.38399e-08 m        | 47.6253 cm/s          | 58.1249 cm/s             | 219.827 cm/s         | 1.72605e-08 cm/s     |
| Checkcase 1 | Keplerian_VOP   | 438.62 m              | 548.992 m                | 2095.43 m            | 1.38399e-08 m        | 47.6253 cm/s          | 58.1249 cm/s             | 219.827 cm/s         | 1.72605e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 883.754 m             | 872.47 m                 | 3667.51 m            | 1.32858e-08 m        | 76.0514 cm/s          | 77.3318 cm/s             | 304.13 cm/s          | 1.72498e-08 cm/s     |
| Checkcase 3 | Cowells_Method  | 437.666 m             | 547.996 m                | 2093.08 m            | 2.23937e-09 m        | 47.5003 cm/s          | 58.0103 cm/s             | 219.531 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 3 | Keplerian_VOP   | 437.666 m             | 547.996 m                | 2093.08 m            | 2.23937e-09 m        | 47.5003 cm/s          | 58.0103 cm/s             | 219.531 cm/s         | 2.62154e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 883.438 m             | 871.518 m                | 3665.01 m            | 2.82392e-09 m        | 75.9748 cm/s          | 77.2236 cm/s             | 303.838 cm/s         | 2.47508e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 438.302 m             | 548.59 m                 | 2094.79 m            | 2.23937e-09 m        | 47.5824 cm/s          | 58.0753 cm/s             | 219.73 cm/s          | 2.62154e-10 cm/s     |
| Checkcase 4 | Keplerian_VOP   | 438.302 m             | 548.59 m                 | 2094.79 m            | 2.23937e-09 m        | 47.5824 cm/s          | 58.0753 cm/s             | 219.73 cm/s          | 2.62154e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 883.69 m              | 872.12 m                 | 3666.73 m            | 2.82392e-09 m        | 76.0246 cm/s          | 77.29 cm/s               | 304.032 cm/s         | 2.47508e-10 cm/s     |
| Checkcase 2 | Cowells_Method  | 438.299 m             | 548.586 m                | 2094.78 m            | 2.16005e-09 m        | 47.582 cm/s           | 58.0749 cm/s             | 219.728 cm/s         | 3.58907e-10 cm/s     |
| Checkcase 2 | Keplerian_VOP   | 438.299 m             | 548.586 m                | 2094.78 m            | 2.16005e-09 m        | 47.582 cm/s           | 58.0749 cm/s             | 219.728 cm/s         | 3.58907e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 883.689 m             | 872.117 m                | 3666.72 m            | 2.44889e-09 m        | 76.0244 cm/s          | 77.2896 cm/s             | 304.031 cm/s         | 3.39663e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/Checkcase 2/orbital_elements_comparison.png)

