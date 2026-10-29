---
title: "Comparison to NASA 6DoF Checkcases"
description: "Validation report comparing ASTREA orbital propagation results against NASA 6DoF reference checkcases"
---

# Comparison to NASA 6DoF Checkcases

This report presents a comprehensive comparison of ASTREA's orbital propagation capabilities against NASA's 6 Degree of Freedom (6DoF) reference checkcases. The validation demonstrates ASTREA's accuracy and reliability for astrodynamics computations by comparing trajectory propagation results across multiple orbital scenarios and numerical integration methods.

*Report generated on October 29, 2026 at 20:56:02*



This report gives a simple overview of comparisons between NASA's published 6DoF propagation checkcases and the propagators available in Astrea.
The calculations, methodology, and process are currently undocumented as they are not yet complete, but much of it is easy enough to figure out
by examining the source files for the tests and the associated documentation (astrea/astro/tests/nasa_6dof_checkcases). By default, the tests that
produce these outputs are not run with standard tests as acceptance is complex and simply associating raw numerical precision with agreement is
generally a mistake. 

While looking through this report, keep in mind that, while some parts are written by hand, like this introduction, the majority of the content is
generated automatically and thus, may contain context errors, weird phrasing, or simply incorrect wording. This report is meant to be a way of coherently
tracking the accuracy of Astrea's numerical propagators without requiring dozens of man hours every time something is updated. As such, it will be a living
document that receives regular updates, at least for now, hopefully including improvements to the visuals, tables, and qualitative analysis.


## Executive Summary

This validation study encompasses **13 orbital test cases** with **52 total checkcases**, evaluating **7 distinct propagation methods**. The tests validate ASTREA's orbital mechanics implementation against established NASA reference solutions.

!!! info "Test Coverage"
    - **13** Orbit Tests
    - **52** Total Checkcases  
    - **7** Propagation Methods

### Tested Propagation Methods

The following numerical integration methods were evaluated:

- ** Cowells Method**
- ** Cowells_Method**
- ** Equinoctial VoP**
- ** Equinoctial_VoP**
- ** Keplerian VoP**
- ** Keplerian_VoP**
- ** Two Body**

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
| Checkcase 0 | Two Body        | 0.000439135 m         | 0.000155074 m            | 0.000840954 m        | 6.35935e-09 m        | 4.49611e-05 cm/s      | 1.46616e-05 cm/s         | 7.85494e-05 cm/s     | 6.74318e-10 cm/s     |
| Checkcase 0 | Cowells Method  | 0.000439158 m         | 0.000155092 m            | 0.000840808 m        | 6.35935e-09 m        | 4.49597e-05 cm/s      | 1.46631e-05 cm/s         | 7.85488e-05 cm/s     | 6.74318e-10 cm/s     |
| Checkcase 0 | Keplerian VoP   | 0.000439418 m         | 0.000155348 m            | 0.000838346 m        | 6.35935e-09 m        | 4.49561e-05 cm/s      | 1.46747e-05 cm/s         | 7.82554e-05 cm/s     | 6.74318e-10 cm/s     |
| Checkcase 0 | Equinoctial VoP | 0.000439416 m         | 0.000155343 m            | 0.000838379 m        | 4.16783e-09 m        | 4.4956e-05 cm/s       | 1.46743e-05 cm/s         | 7.8266e-05 cm/s      | 5.01756e-10 cm/s     |
| Checkcase 1 | Two Body        | 1.17734e-05 m         | 9.31201e-06 m            | 3.05877e-05 m        | 1.3219e-08 m         | 1.33658e-06 cm/s      | 1.05718e-06 cm/s         | 3.44234e-06 cm/s     | 9.14857e-10 cm/s     |
| Checkcase 1 | Cowells Method  | 1.12856e-05 m         | 8.69406e-06 m            | 2.80093e-05 m        | 1.3219e-08 m         | 1.28067e-06 cm/s      | 9.86533e-07 cm/s         | 3.16857e-06 cm/s     | 9.30487e-10 cm/s     |
| Checkcase 1 | Keplerian VoP   | 1.95813e-06 m         | 2.18169e-06 m            | 8.25293e-06 m        | 1.10635e-08 m        | 2.20944e-07 cm/s      | 2.48472e-07 cm/s         | 9.23844e-07 cm/s     | 9.77517e-10 cm/s     |
| Checkcase 1 | Equinoctial VoP | 2.09121e-06 m         | 2.33281e-06 m            | 8.62914e-06 m        | 5.2444e-09 m         | 2.35579e-07 cm/s      | 2.66145e-07 cm/s         | 9.66565e-07 cm/s     | 2.98937e-10 cm/s     |
| Checkcase 2 | Two Body        | 0.000464618 m         | 0.000267873 m            | 0.000894882 m        | 6.79178e-09 m        | 5.25888e-05 cm/s      | 3.04086e-05 cm/s         | 0.000102056 cm/s     | 6.60472e-10 cm/s     |
| Checkcase 2 | Cowells Method  | 0.000465108 m         | 0.000268436 m            | 0.000896552 m        | 6.79178e-09 m        | 5.2645e-05 cm/s       | 3.04745e-05 cm/s         | 0.000102332 cm/s     | 6.60472e-10 cm/s     |
| Checkcase 2 | Keplerian VoP   | 0.000474725 m         | 0.000274915 m            | 0.000915704 m        | 6.79178e-09 m        | 5.37373e-05 cm/s      | 3.12116e-05 cm/s         | 0.000104822 cm/s     | 6.60472e-10 cm/s     |
| Checkcase 2 | Equinoctial VoP | 0.000474502 m         | 0.00027481 m             | 0.000915325 m        | 4.91884e-09 m        | 5.37101e-05 cm/s      | 3.12028e-05 cm/s         | 0.000104779 cm/s     | 6.29741e-10 cm/s     |
| Checkcase 3 | Two Body        | 2.74614e-06 m         | 3.19345e-06 m            | 1.09652e-05 m        | 3.47071e-09 m        | 3.1115e-07 cm/s       | 3.6179e-07 cm/s          | 1.21173e-06 cm/s     | 4.46304e-10 cm/s     |
| Checkcase 3 | Cowells Method  | 2.25207e-06 m         | 2.49913e-06 m            | 8.36362e-06 m        | 3.47071e-09 m        | 2.54697e-07 cm/s      | 2.83275e-07 cm/s         | 9.35592e-07 cm/s     | 4.46304e-10 cm/s     |
| Checkcase 3 | Keplerian VoP   | 7.4306e-06 m          | 4.44741e-06 m            | 1.34917e-05 m        | 6.35935e-09 m        | 8.42751e-07 cm/s      | 5.04408e-07 cm/s         | 1.55507e-06 cm/s     | 6.74318e-10 cm/s     |
| Checkcase 3 | Equinoctial VoP | 7.20431e-06 m         | 4.35341e-06 m            | 1.31141e-05 m        | 4.16783e-09 m        | 8.16002e-07 cm/s      | 4.95351e-07 cm/s         | 1.51221e-06 cm/s     | 5.01756e-10 cm/s     |
| Checkcase 4 | Two Body        | 1.67108e-05 m         | 1.08592e-05 m            | 4.32068e-05 m        | 6.35935e-09 m        | 1.87705e-06 cm/s      | 1.24016e-06 cm/s         | 4.71969e-06 cm/s     | 6.74318e-10 cm/s     |
| Checkcase 4 | Cowells Method  | 1.62266e-05 m         | 1.02486e-05 m            | 4.06886e-05 m        | 6.35935e-09 m        | 1.82134e-06 cm/s      | 1.16988e-06 cm/s         | 4.44839e-06 cm/s     | 6.74318e-10 cm/s     |
| Checkcase 4 | Keplerian VoP   | 7.47671e-06 m         | 4.00437e-06 m            | 2.08927e-05 m        | 6.35935e-09 m        | 8.17009e-07 cm/s      | 4.5057e-07 cm/s          | 2.18537e-06 cm/s     | 6.74318e-10 cm/s     |
| Checkcase 4 | Equinoctial VoP | 7.64357e-06 m         | 4.10926e-06 m            | 2.12666e-05 m        | 4.16783e-09 m        | 8.35905e-07 cm/s      | 4.63615e-07 cm/s         | 2.22754e-06 cm/s     | 5.01756e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Two Body, Cowells Method, Equinoctial VoP, Two_Body, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Two Body, Cowells Method, Equinoctial VoP, Two_Body, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Two Body, Cowells Method, Equinoctial VoP, Two_Body, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Two Body, Cowells Method, Equinoctial VoP, Two_Body, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_02/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_02/Checkcase 2/orbital_elements_comparison.png)

#### Checkcase 0

**Propagation Methods:** Two Body, Cowells Method, Equinoctial VoP, Two_Body, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

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
| Checkcase 1 | Cowells Method  | 1566.38 m             | 718.037 m                | 2450.29 m            | 1.3219e-08 m         | 177.679 cm/s          | 80.9785 cm/s             | 279.434 cm/s         | 1.06991e-09 cm/s     |
| Checkcase 1 | Keplerian VoP   | 1566.38 m             | 718.037 m                | 2450.29 m            | 1.3219e-08 m         | 177.679 cm/s          | 80.9785 cm/s             | 279.434 cm/s         | 1.06991e-09 cm/s     |
| Checkcase 1 | Equinoctial VoP | 1566.38 m             | 718.037 m                | 2450.29 m            | 1.25123e-08 m        | 177.679 cm/s          | 80.9785 cm/s             | 279.434 cm/s         | 7.98203e-10 cm/s     |
| Checkcase 2 | Cowells Method  | 1564.41 m             | 716.817 m                | 2443.22 m            | 6.79178e-09 m        | 177.455 cm/s          | 80.8592 cm/s             | 279.189 cm/s         | 6.60472e-10 cm/s     |
| Checkcase 2 | Keplerian VoP   | 1564.41 m             | 716.817 m                | 2443.22 m            | 6.79178e-09 m        | 177.455 cm/s          | 80.8592 cm/s             | 279.189 cm/s         | 6.60472e-10 cm/s     |
| Checkcase 2 | Equinoctial VoP | 1564.41 m             | 716.817 m                | 2443.22 m            | 4.91884e-09 m        | 177.455 cm/s          | 80.8592 cm/s             | 279.189 cm/s         | 6.29741e-10 cm/s     |
| Checkcase 3 | Cowells Method  | 1563.42 m             | 716.289 m                | 2441.45 m            | 6.35935e-09 m        | 177.342 cm/s          | 80.7995 cm/s             | 278.99 cm/s          | 6.74318e-10 cm/s     |
| Checkcase 3 | Keplerian VoP   | 1563.42 m             | 716.289 m                | 2441.45 m            | 6.35935e-09 m        | 177.342 cm/s          | 80.7995 cm/s             | 278.99 cm/s          | 6.74318e-10 cm/s     |
| Checkcase 3 | Equinoctial VoP | 1563.42 m             | 716.289 m                | 2441.45 m            | 4.16783e-09 m        | 177.342 cm/s          | 80.7995 cm/s             | 278.99 cm/s          | 5.01756e-10 cm/s     |
| Checkcase 4 | Cowells Method  | 1564.38 m             | 716.759 m                | 2443.05 m            | 6.35935e-09 m        | 177.451 cm/s          | 80.8524 cm/s             | 279.165 cm/s         | 6.74318e-10 cm/s     |
| Checkcase 4 | Keplerian VoP   | 1564.38 m             | 716.759 m                | 2443.05 m            | 6.35935e-09 m        | 177.451 cm/s          | 80.8524 cm/s             | 279.165 cm/s         | 6.74318e-10 cm/s     |
| Checkcase 4 | Equinoctial VoP | 1564.38 m             | 716.759 m                | 2443.05 m            | 4.16783e-09 m        | 177.451 cm/s          | 80.8524 cm/s             | 279.165 cm/s         | 5.01756e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03A/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03A/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03A/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03A/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03A/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03A/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03A/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03A/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

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
| Checkcase 1 | Cowells Method  | 1094.68 m             | 680.827 m                | 2147.34 m            | 1.3219e-08 m         | 124.156 cm/s          | 77.0313 cm/s             | 245.932 cm/s         | 1.06991e-09 cm/s     |
| Checkcase 1 | Keplerian VoP   | 1094.68 m             | 680.827 m                | 2147.34 m            | 1.3219e-08 m         | 124.156 cm/s          | 77.0313 cm/s             | 245.932 cm/s         | 1.06991e-09 cm/s     |
| Checkcase 1 | Equinoctial VoP | 1094.68 m             | 680.827 m                | 2147.34 m            | 1.25123e-08 m        | 124.156 cm/s          | 77.0313 cm/s             | 245.932 cm/s         | 7.98203e-10 cm/s     |
| Checkcase 2 | Cowells Method  | 1096.93 m             | 683.525 m                | 2149 m               | 6.79178e-09 m        | 124.411 cm/s          | 77.3487 cm/s             | 246.337 cm/s         | 6.60472e-10 cm/s     |
| Checkcase 2 | Keplerian VoP   | 1096.93 m             | 683.525 m                | 2149 m               | 6.79178e-09 m        | 124.411 cm/s          | 77.3487 cm/s             | 246.337 cm/s         | 6.60472e-10 cm/s     |
| Checkcase 2 | Equinoctial VoP | 1096.93 m             | 683.525 m                | 2149 m               | 4.91884e-09 m        | 124.411 cm/s          | 77.3487 cm/s             | 246.337 cm/s         | 6.29741e-10 cm/s     |
| Checkcase 3 | Cowells Method  | 1095.94 m             | 682.983 m                | 2147.28 m            | 6.35935e-09 m        | 124.299 cm/s          | 77.2873 cm/s             | 246.138 cm/s         | 6.74318e-10 cm/s     |
| Checkcase 3 | Keplerian VoP   | 1095.94 m             | 682.983 m                | 2147.28 m            | 6.35935e-09 m        | 124.299 cm/s          | 77.2873 cm/s             | 246.138 cm/s         | 6.74318e-10 cm/s     |
| Checkcase 3 | Equinoctial VoP | 1095.94 m             | 682.983 m                | 2147.28 m            | 4.16783e-09 m        | 124.299 cm/s          | 77.2873 cm/s             | 246.138 cm/s         | 5.01756e-10 cm/s     |
| Checkcase 4 | Cowells Method  | 1097.01 m             | 683.51 m                 | 2149 m               | 6.35935e-09 m        | 124.42 cm/s           | 77.347 cm/s              | 246.336 cm/s         | 6.74318e-10 cm/s     |
| Checkcase 4 | Keplerian VoP   | 1097.01 m             | 683.51 m                 | 2149 m               | 6.35935e-09 m        | 124.42 cm/s           | 77.347 cm/s              | 246.336 cm/s         | 6.74318e-10 cm/s     |
| Checkcase 4 | Equinoctial VoP | 1097.01 m             | 683.51 m                 | 2149 m               | 4.16783e-09 m        | 124.42 cm/s           | 77.347 cm/s              | 246.336 cm/s         | 5.01756e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03B/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03B/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03B/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03B/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03B/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03B/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_03B/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_03B/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

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
| Checkcase 1 | Cowells Method  | 0.00211954 m          | 0.00131751 m             | 0.00483136 m         | 1.3219e-08 m         | 0.000237463 cm/s      | 0.000146926 cm/s         | 0.000527497 cm/s     | 1.06991e-09 cm/s     |
| Checkcase 1 | Keplerian VoP   | 0.0021235 m           | 0.00132108 m             | 0.00484171 m         | 1.3219e-08 m         | 0.000237916 cm/s      | 0.000147338 cm/s         | 0.000528695 cm/s     | 1.06991e-09 cm/s     |
| Checkcase 1 | Equinoctial VoP | 0.00212025 m          | 0.00131804 m             | 0.00483191 m         | 1.25123e-08 m        | 0.000237544 cm/s      | 0.000146988 cm/s         | 0.00052748 cm/s      | 7.98203e-10 cm/s     |
| Checkcase 2 | Cowells Method  | 0.00167634 m          | 0.00102838 m             | 0.00394602 m         | 6.79178e-09 m        | 0.000186342 cm/s      | 0.000114397 cm/s         | 0.000428578 cm/s     | 6.60472e-10 cm/s     |
| Checkcase 2 | Keplerian VoP   | 0.00168004 m          | 0.00103172 m             | 0.00395554 m         | 6.79178e-09 m        | 0.000186768 cm/s      | 0.000114781 cm/s         | 0.000429653 cm/s     | 6.60472e-10 cm/s     |
| Checkcase 2 | Equinoctial VoP | 0.001677 m            | 0.00102888 m             | 0.00394652 m         | 4.91884e-09 m        | 0.000186419 cm/s      | 0.000114453 cm/s         | 0.000428594 cm/s     | 6.29741e-10 cm/s     |
| Checkcase 3 | Cowells Method  | 0.00244125 m          | 0.00152144 m             | 0.00542038 m         | 6.35935e-09 m        | 0.000275013 cm/s      | 0.000170483 cm/s         | 0.000602593 cm/s     | 6.74318e-10 cm/s     |
| Checkcase 3 | Keplerian VoP   | 0.00244536 m          | 0.00152514 m             | 0.0054299 m          | 6.35935e-09 m        | 0.000275482 cm/s      | 0.000170905 cm/s         | 0.000603821 cm/s     | 6.74318e-10 cm/s     |
| Checkcase 3 | Equinoctial VoP | 0.00244199 m          | 0.00152199 m             | 0.00542029 m         | 4.16783e-09 m        | 0.000275096 cm/s      | 0.000170546 cm/s         | 0.000602611 cm/s     | 5.01756e-10 cm/s     |
| Checkcase 4 | Cowells Method  | 0.00725449 m          | 0.00710935 m             | 0.023814 m           | 6.35935e-09 m        | 0.000824372 cm/s      | 0.000810312 cm/s         | 0.00275471 cm/s      | 6.74318e-10 cm/s     |
| Checkcase 4 | Keplerian VoP   | 0.00725026 m          | 0.00710514 m             | 0.0238018 m          | 6.35935e-09 m        | 0.000823888 cm/s      | 0.000809838 cm/s         | 0.00275334 cm/s      | 6.74318e-10 cm/s     |
| Checkcase 4 | Equinoctial VoP | 0.00725373 m          | 0.00710873 m             | 0.0238137 m          | 4.16783e-09 m        | 0.000824287 cm/s      | 0.000810243 cm/s         | 0.00275469 cm/s      | 5.01756e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_04/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_04/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_04/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_04/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_04/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_04/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_04/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_04/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

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
| Checkcase 1 | Cowells Method  | 13.356 m              | 7.80727 m                | 27.914 m             | 1.31661e-08 m        | 1.51841 cm/s          | 0.881701 cm/s            | 3.06495 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Keplerian VoP   | 13.356 m              | 7.80727 m                | 27.914 m             | 1.31661e-08 m        | 1.51841 cm/s          | 0.881701 cm/s            | 3.06495 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Equinoctial VoP | 13.356 m              | 7.80727 m                | 27.9139 m            | 1.58592e-08 m        | 1.51841 cm/s          | 0.881701 cm/s            | 3.06495 cm/s         | 1.70892e-08 cm/s     |
| Checkcase 2 | Cowells Method  | 13.3819 m             | 7.81935 m                | 27.9148 m            | 2.49335e-09 m        | 1.52128 cm/s          | 0.882978 cm/s            | 3.06505 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Keplerian VoP   | 13.3819 m             | 7.81935 m                | 27.9148 m            | 2.49335e-09 m        | 1.52128 cm/s          | 0.882978 cm/s            | 3.06505 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Equinoctial VoP | 13.3819 m             | 7.81935 m                | 27.9148 m            | 3.18526e-09 m        | 1.52128 cm/s          | 0.882978 cm/s            | 3.06504 cm/s         | 5.55673e-10 cm/s     |
| Checkcase 3 | Cowells Method  | 13.3815 m             | 7.81907 m                | 27.914 m             | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Keplerian VoP   | 13.3815 m             | 7.81908 m                | 27.914 m             | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Equinoctial VoP | 13.3814 m             | 7.81907 m                | 27.914 m             | 2.66134e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.02536e-10 cm/s     |
| Checkcase 4 | Cowells Method  | 13.3814 m             | 7.81907 m                | 27.9139 m            | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Keplerian VoP   | 13.3814 m             | 7.81907 m                | 27.9139 m            | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Equinoctial VoP | 13.3814 m             | 7.81907 m                | 27.9139 m            | 2.66134e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.02536e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

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
| Checkcase 1 | Cowells Method  | 6.75947e+06 m         | 36741.7 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 1 | Keplerian VoP   | 6.75947e+06 m         | 36741.7 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 1 | Equinoctial VoP | 6.75947e+06 m         | 36741.7 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 2 | Cowells Method  | 13.3819 m             | 7.81935 m                | 27.9148 m            | 2.49335e-09 m        | 1.52128 cm/s          | 0.882978 cm/s            | 3.06505 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Keplerian VoP   | 13.3819 m             | 7.81935 m                | 27.9148 m            | 2.49335e-09 m        | 1.52128 cm/s          | 0.882978 cm/s            | 3.06505 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Equinoctial VoP | 13.3819 m             | 7.81935 m                | 27.9148 m            | 3.18526e-09 m        | 1.52128 cm/s          | 0.882978 cm/s            | 3.06504 cm/s         | 5.55673e-10 cm/s     |
| Checkcase 3 | Cowells Method  | 13.3815 m             | 7.81907 m                | 27.914 m             | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Keplerian VoP   | 13.3815 m             | 7.81908 m                | 27.914 m             | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Equinoctial VoP | 13.3814 m             | 7.81907 m                | 27.914 m             | 2.66134e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.02536e-10 cm/s     |
| Checkcase 4 | Cowells Method  | 13.3814 m             | 7.81907 m                | 27.9139 m            | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Keplerian VoP   | 13.3814 m             | 7.81907 m                | 27.9139 m            | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Equinoctial VoP | 13.3814 m             | 7.81907 m                | 27.9139 m            | 2.66134e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.02536e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05B/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05B/Checkcase 2/orbital_elements_comparison.png)


## Orbit_05C

### Detailed Results

| Checkcase   | Propagation     | Mean Position Error   | Std Dev Position Error   | Max Position Error   | Min Position Error   | Mean Velocity Error   | Std Dev Velocity Error   | Max Velocity Error   | Min Velocity Error   |
|:------------|:----------------|:----------------------|:-------------------------|:---------------------|:---------------------|:----------------------|:-------------------------|:---------------------|:---------------------|
| Checkcase 1 | Cowells Method  | 13.356 m              | 7.80727 m                | 27.914 m             | 1.31661e-08 m        | 1.51841 cm/s          | 0.881701 cm/s            | 3.06495 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Keplerian VoP   | 13.356 m              | 7.80727 m                | 27.914 m             | 1.31661e-08 m        | 1.51841 cm/s          | 0.881701 cm/s            | 3.06495 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Equinoctial VoP | 13.356 m              | 7.80727 m                | 27.9139 m            | 1.58592e-08 m        | 1.51841 cm/s          | 0.881701 cm/s            | 3.06495 cm/s         | 1.70892e-08 cm/s     |
| Checkcase 2 | Cowells Method  | 13.3819 m             | 7.81935 m                | 27.9148 m            | 2.49335e-09 m        | 1.52128 cm/s          | 0.882978 cm/s            | 3.06505 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Keplerian VoP   | 13.3819 m             | 7.81935 m                | 27.9148 m            | 2.49335e-09 m        | 1.52128 cm/s          | 0.882978 cm/s            | 3.06505 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Equinoctial VoP | 13.3819 m             | 7.81935 m                | 27.9148 m            | 3.18526e-09 m        | 1.52128 cm/s          | 0.882978 cm/s            | 3.06504 cm/s         | 5.55673e-10 cm/s     |
| Checkcase 3 | Cowells Method  | 13.3815 m             | 7.81907 m                | 27.914 m             | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Keplerian VoP   | 13.3815 m             | 7.81908 m                | 27.914 m             | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Equinoctial VoP | 13.3814 m             | 7.81907 m                | 27.914 m             | 2.66134e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.02536e-10 cm/s     |
| Checkcase 4 | Cowells Method  | 13.3814 m             | 7.81907 m                | 27.9139 m            | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Keplerian VoP   | 13.3814 m             | 7.81907 m                | 27.9139 m            | 2.58247e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Equinoctial VoP | 13.3814 m             | 7.81907 m                | 27.9139 m            | 2.66134e-09 m        | 1.52123 cm/s          | 0.882947 cm/s            | 3.06495 cm/s         | 3.02536e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05C/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05C/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05C/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05C/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05C/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05C/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05C/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05C/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Cowells Method, Equinoctial VoP, Equinoctial_VOP, Keplerian VoP, Cowells_Method, Keplerian_VOP

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
| Checkcase 2 | Cowells_Method  | 236.53 m              | 206.703 m                | 734.187 m            | 2.49335e-09 m        | 26.7771 cm/s          | 23.0098 cm/s             | 79.959 cm/s          | 4.43751e-10 cm/s     |
| Checkcase 2 | Keplerian_VoP   | 236.53 m              | 206.703 m                | 734.187 m            | 2.49335e-09 m        | 26.7771 cm/s          | 23.0098 cm/s             | 79.959 cm/s          | 4.43751e-10 cm/s     |
| Checkcase 2 | Equinoctial_VoP | 236.53 m              | 206.703 m                | 734.187 m            | 3.18526e-09 m        | 26.7771 cm/s          | 23.0098 cm/s             | 79.959 cm/s          | 5.55673e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 236.504 m             | 206.68 m                 | 734.109 m            | 2.58247e-09 m        | 26.7741 cm/s          | 23.0072 cm/s             | 79.95 cm/s           | 3.70399e-10 cm/s     |
| Checkcase 3 | Keplerian_VoP   | 236.504 m             | 206.68 m                 | 734.109 m            | 2.58247e-09 m        | 26.7741 cm/s          | 23.0072 cm/s             | 79.95 cm/s           | 3.70399e-10 cm/s     |
| Checkcase 3 | Equinoctial_VoP | 236.504 m             | 206.68 m                 | 734.109 m            | 2.66134e-09 m        | 26.7741 cm/s          | 23.0072 cm/s             | 79.95 cm/s           | 3.02536e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 553.635 m             | 488.528 m                | 1684.6 m             | 2.58247e-09 m        | 62.861 cm/s           | 55.0879 cm/s             | 188.282 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Keplerian_VoP   | 553.635 m             | 488.528 m                | 1684.6 m             | 2.58247e-09 m        | 62.861 cm/s           | 55.0879 cm/s             | 188.282 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Equinoctial_VoP | 553.635 m             | 488.528 m                | 1684.6 m             | 2.66134e-09 m        | 62.861 cm/s           | 55.0879 cm/s             | 188.282 cm/s         | 3.02536e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06A/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06A/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06A/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06A/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06A/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06A/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

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
| Checkcase 1 | Cowells_Method  | 1172.83 m             | 1038.8 m                 | 4324.11 m            | 1.31661e-08 m        | 133.195 cm/s          | 117.31 cm/s              | 486.479 cm/s         | 1.1077e-09 cm/s      |
| Checkcase 1 | Keplerian_VoP   | 1172.83 m             | 1038.8 m                 | 4324.11 m            | 1.31661e-08 m        | 133.195 cm/s          | 117.31 cm/s              | 486.479 cm/s         | 1.1077e-09 cm/s      |
| Checkcase 1 | Equinoctial_VoP | 1172.83 m             | 1038.8 m                 | 4324.11 m            | 1.58592e-08 m        | 133.195 cm/s          | 117.31 cm/s              | 486.479 cm/s         | 8.25013e-10 cm/s     |
| Checkcase 2 | Cowells_Method  | 1145.24 m             | 1011.82 m                | 3476.91 m            | 2.49335e-09 m        | 130.065 cm/s          | 114.269 cm/s             | 390.036 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Keplerian_VoP   | 1145.24 m             | 1011.82 m                | 3476.91 m            | 2.49335e-09 m        | 130.065 cm/s          | 114.269 cm/s             | 390.036 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Equinoctial_VoP | 1145.24 m             | 1011.82 m                | 3476.91 m            | 3.18526e-09 m        | 130.065 cm/s          | 114.269 cm/s             | 390.036 cm/s         | 5.55673e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 1145.08 m             | 1011.67 m                | 3476.36 m            | 2.58247e-09 m        | 130.047 cm/s          | 114.252 cm/s             | 389.977 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Keplerian_VoP   | 1145.08 m             | 1011.67 m                | 3476.36 m            | 2.58247e-09 m        | 130.047 cm/s          | 114.252 cm/s             | 389.977 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Equinoctial_VoP | 1145.08 m             | 1011.67 m                | 3476.36 m            | 2.66134e-09 m        | 130.047 cm/s          | 114.252 cm/s             | 389.977 cm/s         | 3.02536e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 1144.67 m             | 1011.27 m                | 3474.84 m            | 2.58247e-09 m        | 130 cm/s              | 114.207 cm/s             | 389.815 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Keplerian_VoP   | 1144.67 m             | 1011.27 m                | 3474.84 m            | 2.58247e-09 m        | 130 cm/s              | 114.207 cm/s             | 389.815 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Equinoctial_VoP | 1144.67 m             | 1011.27 m                | 3474.84 m            | 2.66134e-09 m        | 130 cm/s              | 114.207 cm/s             | 389.815 cm/s         | 3.02536e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06B/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06B/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06B/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06B/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06B/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06B/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_06B/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_06B/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

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
| Checkcase 1 | Cowells_Method  | 1548.69 m             | 707.506 m                | 2409.63 m            | 1.31661e-08 m        | 175.547 cm/s          | 79.6546 cm/s             | 276.304 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Keplerian_VoP   | 1548.69 m             | 707.506 m                | 2409.63 m            | 1.31661e-08 m        | 175.547 cm/s          | 79.6546 cm/s             | 276.304 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Equinoctial_VoP | 1548.69 m             | 707.506 m                | 2409.63 m            | 1.58592e-08 m        | 175.547 cm/s          | 79.6546 cm/s             | 276.304 cm/s         | 1.70892e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 1549.82 m             | 707.983 m                | 2408.44 m            | 2.49335e-09 m        | 175.675 cm/s          | 79.7294 cm/s             | 276.948 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Keplerian_VoP   | 1549.82 m             | 707.983 m                | 2408.44 m            | 2.49335e-09 m        | 175.675 cm/s          | 79.7294 cm/s             | 276.948 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Equinoctial_VoP | 1549.82 m             | 707.983 m                | 2408.44 m            | 3.18526e-09 m        | 175.675 cm/s          | 79.7294 cm/s             | 276.948 cm/s         | 5.55673e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 1548.84 m             | 707.46 m                 | 2406.7 m             | 2.58247e-09 m        | 175.564 cm/s          | 79.6704 cm/s             | 276.75 cm/s          | 3.70399e-10 cm/s     |
| Checkcase 3 | Keplerian_VoP   | 1548.84 m             | 707.46 m                 | 2406.7 m             | 2.58247e-09 m        | 175.564 cm/s          | 79.6704 cm/s             | 276.75 cm/s          | 3.70399e-10 cm/s     |
| Checkcase 3 | Equinoctial_VoP | 1548.84 m             | 707.46 m                 | 2406.7 m             | 2.66134e-09 m        | 175.564 cm/s          | 79.6704 cm/s             | 276.75 cm/s          | 3.02536e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 1549.82 m             | 707.986 m                | 2408.45 m            | 2.58247e-09 m        | 175.676 cm/s          | 79.7297 cm/s             | 276.949 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Keplerian_VoP   | 1549.82 m             | 707.986 m                | 2408.45 m            | 2.58247e-09 m        | 175.676 cm/s          | 79.7297 cm/s             | 276.949 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Equinoctial_VoP | 1549.82 m             | 707.986 m                | 2408.45 m            | 2.66134e-09 m        | 175.676 cm/s          | 79.7297 cm/s             | 276.949 cm/s         | 3.02536e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07A/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07A/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07A/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07A/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07A/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07A/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07A/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07A/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

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
| Checkcase 1 | Cowells_Method  | 1082.9 m              | 673.928 m                | 2127.06 m            | 1.31661e-08 m        | 122.733 cm/s          | 76.1429 cm/s             | 244.143 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Keplerian_VoP   | 1082.9 m              | 673.928 m                | 2127.06 m            | 1.31661e-08 m        | 122.733 cm/s          | 76.1429 cm/s             | 244.143 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Equinoctial_VoP | 1082.9 m              | 673.928 m                | 2127.06 m            | 1.58592e-08 m        | 122.733 cm/s          | 76.1429 cm/s             | 244.143 cm/s         | 1.70892e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 1087.94 m             | 678.294 m                | 2134.68 m            | 2.49335e-09 m        | 123.308 cm/s          | 76.6523 cm/s             | 245.372 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Keplerian_VoP   | 1087.94 m             | 678.294 m                | 2134.68 m            | 2.49335e-09 m        | 123.308 cm/s          | 76.6523 cm/s             | 245.372 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Equinoctial_VoP | 1087.94 m             | 678.294 m                | 2134.68 m            | 3.18526e-09 m        | 123.308 cm/s          | 76.6523 cm/s             | 245.372 cm/s         | 5.55673e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 1086.96 m             | 677.758 m                | 2132.98 m            | 2.58247e-09 m        | 123.197 cm/s          | 76.5917 cm/s             | 245.175 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Keplerian_VoP   | 1086.96 m             | 677.758 m                | 2132.98 m            | 2.58247e-09 m        | 123.197 cm/s          | 76.5917 cm/s             | 245.175 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Equinoctial_VoP | 1086.96 m             | 677.758 m                | 2132.98 m            | 2.66134e-09 m        | 123.197 cm/s          | 76.5917 cm/s             | 245.175 cm/s         | 3.02536e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 1087.94 m             | 678.298 m                | 2134.7 m             | 2.58247e-09 m        | 123.308 cm/s          | 76.6526 cm/s             | 245.374 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Keplerian_VoP   | 1087.94 m             | 678.298 m                | 2134.7 m             | 2.58247e-09 m        | 123.308 cm/s          | 76.6526 cm/s             | 245.374 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Equinoctial_VoP | 1087.94 m             | 678.298 m                | 2134.7 m             | 2.66134e-09 m        | 123.308 cm/s          | 76.6526 cm/s             | 245.374 cm/s         | 3.02536e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07B/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07B/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07B/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07B/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07B/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07B/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07B/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07B/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

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
| Checkcase 1 | Cowells_Method  | 616.288 m             | 341.629 m                | 1624.64 m            | 1.31661e-08 m        | 69.1721 cm/s          | 37.122 cm/s              | 173.079 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Keplerian_VoP   | 616.288 m             | 341.629 m                | 1624.64 m            | 1.31661e-08 m        | 69.1721 cm/s          | 37.122 cm/s              | 173.079 cm/s         | 1.72894e-08 cm/s     |
| Checkcase 1 | Equinoctial_VoP | 616.288 m             | 341.629 m                | 1624.64 m            | 1.58592e-08 m        | 69.1721 cm/s          | 37.122 cm/s              | 173.079 cm/s         | 1.70892e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 617.823 m             | 347.41 m                 | 1148.77 m            | 2.49335e-09 m        | 69.4367 cm/s          | 37.7567 cm/s             | 123.626 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Keplerian_VoP   | 617.823 m             | 347.41 m                 | 1148.77 m            | 2.49335e-09 m        | 69.4367 cm/s          | 37.7567 cm/s             | 123.626 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Equinoctial_VoP | 617.823 m             | 347.41 m                 | 1148.77 m            | 3.18526e-09 m        | 69.4367 cm/s          | 37.7567 cm/s             | 123.626 cm/s         | 5.55673e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 617.403 m             | 347.038 m                | 1147.73 m            | 2.58247e-09 m        | 69.3886 cm/s          | 37.7155 cm/s             | 123.515 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Keplerian_VoP   | 617.403 m             | 347.038 m                | 1147.73 m            | 2.58247e-09 m        | 69.3886 cm/s          | 37.7155 cm/s             | 123.515 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 3 | Equinoctial_VoP | 617.403 m             | 347.038 m                | 1147.73 m            | 2.66134e-09 m        | 69.3886 cm/s          | 37.7155 cm/s             | 123.515 cm/s         | 3.02536e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 617.877 m             | 347.541 m                | 1148.96 m            | 2.58247e-09 m        | 69.4443 cm/s          | 37.7729 cm/s             | 123.655 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Keplerian_VoP   | 617.877 m             | 347.541 m                | 1148.96 m            | 2.58247e-09 m        | 69.4443 cm/s          | 37.7729 cm/s             | 123.655 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Equinoctial_VoP | 617.877 m             | 347.541 m                | 1148.96 m            | 2.66134e-09 m        | 69.4443 cm/s          | 37.7729 cm/s             | 123.655 cm/s         | 3.02536e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07C/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07C/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07C/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07C/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07C/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07C/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07C/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07C/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

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
| Checkcase 1 | Cowells_Method  | 277.329 m             | 216.531 m                | 1861.28 m            | 1.31661e-08 m        | 30.854 cm/s           | 23.7253 cm/s             | 203.92 cm/s          | 1.72894e-08 cm/s     |
| Checkcase 1 | Keplerian_VoP   | 277.329 m             | 216.531 m                | 1861.28 m            | 1.31661e-08 m        | 30.854 cm/s           | 23.7253 cm/s             | 203.92 cm/s          | 1.72894e-08 cm/s     |
| Checkcase 1 | Equinoctial_VoP | 277.329 m             | 216.531 m                | 1861.28 m            | 1.58592e-08 m        | 30.854 cm/s           | 23.7253 cm/s             | 203.92 cm/s          | 1.70892e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 270.189 m             | 188.037 m                | 1018 m               | 2.49335e-09 m        | 29.9877 cm/s          | 20.5087 cm/s             | 107.742 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Keplerian_VoP   | 270.189 m             | 188.037 m                | 1018 m               | 2.49335e-09 m        | 29.9877 cm/s          | 20.5087 cm/s             | 107.742 cm/s         | 4.43751e-10 cm/s     |
| Checkcase 2 | Equinoctial_VoP | 270.189 m             | 188.037 m                | 1018 m               | 3.18526e-09 m        | 29.9877 cm/s          | 20.5087 cm/s             | 107.742 cm/s         | 5.55673e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 270.037 m             | 188.379 m                | 1019.23 m            | 2.58247e-09 m        | 29.9726 cm/s          | 20.548 cm/s              | 107.89 cm/s          | 3.70399e-10 cm/s     |
| Checkcase 3 | Keplerian_VoP   | 270.037 m             | 188.379 m                | 1019.23 m            | 2.58247e-09 m        | 29.9726 cm/s          | 20.548 cm/s              | 107.89 cm/s          | 3.70399e-10 cm/s     |
| Checkcase 3 | Equinoctial_VoP | 270.037 m             | 188.379 m                | 1019.23 m            | 2.66134e-09 m        | 29.9726 cm/s          | 20.548 cm/s              | 107.89 cm/s          | 3.02536e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 270.072 m             | 187.717 m                | 1016.4 m             | 2.58247e-09 m        | 29.9742 cm/s          | 20.4736 cm/s             | 107.574 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Keplerian_VoP   | 270.072 m             | 187.717 m                | 1016.4 m             | 2.58247e-09 m        | 29.9742 cm/s          | 20.4736 cm/s             | 107.574 cm/s         | 3.70399e-10 cm/s     |
| Checkcase 4 | Equinoctial_VoP | 270.072 m             | 187.717 m                | 1016.4 m             | 2.66134e-09 m        | 29.9742 cm/s          | 20.4736 cm/s             | 107.574 cm/s         | 3.02536e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/Checkcase 4/orbital_elements_comparison.png)

#### Checkcase 2

**Propagation Methods:** Equinoctial_VoP, Equinoctial_VOP, Cowells_Method, Keplerian_VOP, Keplerian_VoP

### Checkcase 2 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_07D/Checkcase 2/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_07D/Checkcase 2/orbital_elements_comparison.png)

