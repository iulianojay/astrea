---
title: "Comparison to NASA 6DoF Checkcases"
description: "Validation report comparing ASTREA orbital propagation results against NASA 6DoF reference checkcases"
---

# Comparison to NASA 6DoF Checkcases

This report presents a comprehensive comparison of ASTREA's orbital propagation capabilities against NASA's 6 Degree of Freedom (6DoF) reference checkcases. The validation demonstrates ASTREA's accuracy and reliability for astrodynamics computations by comparing trajectory propagation results across multiple orbital scenarios and numerical integration methods.

*Report generated on June 03, 2026 at 19:41:22*



This report gives a simple overview of comaprisons between NASA's published 6DoF propagation checkcases and the propagators available in Astrea.
The calculations, methodology, and process are currently undocumented as they are not yet complete, but much of it is easy enough to figure out
by examining the source files for the tests and the associated documentation (astrea/astro/tests/nasa_6dof_checkcases). By default, the tests that
produce these outputs are not run with standard tests as acceptance is complex and simply associating raw numerical precision with agreement is
generally a mistake. 

While looking through this report, keep in mind that, while some parts are written by hand, like this introduction, the majority of the content is
generated automatically and thus, may contain context errors, weird phrasing, or simply incorrect wording. This report is meant to be a way of coherently
tracking the accuracy of Astrea's numerical propagators without requiring dozens of man hours every time something is updated. As such, it will be a living
document that receives regular updates, at least for now, hopefully including improvements to the visuals, tables, and qualitative analysis.


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
| Checkcase 0 | Two_Body        | 0.817011 m            | 0.473155 m               | 1.6353 m             | 5.86011e-09 m        | 0.0932402 cm/s        | 0.0533367 cm/s           | 0.185911 cm/s        | 0.00564167 cm/s      |
| Checkcase 0 | Cowells_Method  | 0.817012 m            | 0.473155 m               | 1.6353 m             | 5.86011e-09 m        | 0.0932402 cm/s        | 0.0533367 cm/s           | 0.185911 cm/s        | 0.00564167 cm/s      |
| Checkcase 0 | Keplerian_VOP   | 0.81701 m             | 0.473155 m               | 1.6353 m             | 6.26929e-09 m        | 0.0928293 cm/s        | 0.0537505 cm/s           | 0.18582 cm/s         | 7.1409e-10 cm/s      |
| Checkcase 0 | Equinoctial_VOP | 0.81701 m             | 0.473155 m               | 1.6353 m             | 4.57015e-09 m        | 0.0928293 cm/s        | 0.0537505 cm/s           | 0.18582 cm/s         | 5.01969e-10 cm/s     |
| Checkcase 1 | Two_Body        | 0.815305 m            | 0.472136 m               | 1.63121 m            | 1.37029e-08 m        | 0.0930466 cm/s        | 0.0532231 cm/s           | 0.185499 cm/s        | 0.00566945 cm/s      |
| Checkcase 1 | Cowells_Method  | 0.815305 m            | 0.472136 m               | 1.63121 m            | 1.37029e-08 m        | 0.0930466 cm/s        | 0.0532231 cm/s           | 0.185499 cm/s        | 0.00566945 cm/s      |
| Checkcase 1 | Keplerian_VOP   | 0.815303 m            | 0.472135 m               | 1.63121 m            | 1.25035e-08 m        | 0.0926346 cm/s        | 0.0536379 cm/s           | 0.185406 cm/s        | 1.1036e-09 cm/s      |
| Checkcase 1 | Equinoctial_VOP | 0.815303 m            | 0.472135 m               | 1.63121 m            | 1.39835e-08 m        | 0.0926346 cm/s        | 0.0536379 cm/s           | 0.185406 cm/s        | 1.0778e-09 cm/s      |
| Checkcase 2 | Two_Body        | 0.817481 m            | 0.4734 m                 | 1.63562 m            | 6.16116e-09 m        | 0.0932934 cm/s        | 0.0533675 cm/s           | 0.186015 cm/s        | 0.00566945 cm/s      |
| Checkcase 2 | Cowells_Method  | 0.817481 m            | 0.4734 m                 | 1.63562 m            | 6.16116e-09 m        | 0.0932934 cm/s        | 0.0533675 cm/s           | 0.186015 cm/s        | 0.00566945 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 0.81748 m             | 0.4734 m                 | 1.63562 m            | 6.55156e-09 m        | 0.0928821 cm/s        | 0.0537817 cm/s           | 0.185922 cm/s        | 7.21479e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 0.81748 m             | 0.4734 m                 | 1.63562 m            | 4.63753e-09 m        | 0.0928821 cm/s        | 0.0537817 cm/s           | 0.185922 cm/s        | 5.10589e-10 cm/s     |
| Checkcase 3 | Two_Body        | 0.817018 m            | 0.473128 m               | 1.63474 m            | 5.86011e-09 m        | 0.0932407 cm/s        | 0.0533366 cm/s           | 0.185911 cm/s        | 0.00566945 cm/s      |
| Checkcase 3 | Cowells_Method  | 0.817018 m            | 0.473128 m               | 1.63474 m            | 5.86011e-09 m        | 0.0932407 cm/s        | 0.0533367 cm/s           | 0.185911 cm/s        | 0.00566945 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 0.817016 m            | 0.473127 m               | 1.63474 m            | 6.26929e-09 m        | 0.0928294 cm/s        | 0.0537509 cm/s           | 0.185819 cm/s        | 7.1409e-10 cm/s      |
| Checkcase 3 | Equinoctial_VOP | 0.817016 m            | 0.473127 m               | 1.63474 m            | 4.57015e-09 m        | 0.0928294 cm/s        | 0.0537509 cm/s           | 0.185819 cm/s        | 5.01969e-10 cm/s     |
| Checkcase 4 | Two_Body        | 0.817005 m            | 0.473119 m               | 1.63471 m            | 5.86011e-09 m        | 0.0932392 cm/s        | 0.0533357 cm/s           | 0.185908 cm/s        | 0.00566945 cm/s      |
| Checkcase 4 | Cowells_Method  | 0.817005 m            | 0.473119 m               | 1.63471 m            | 5.86011e-09 m        | 0.0932392 cm/s        | 0.0533357 cm/s           | 0.185908 cm/s        | 0.00566945 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 0.817003 m            | 0.473119 m               | 1.63471 m            | 6.26929e-09 m        | 0.0928279 cm/s        | 0.0537499 cm/s           | 0.185816 cm/s        | 7.1409e-10 cm/s      |
| Checkcase 4 | Equinoctial_VOP | 0.817003 m            | 0.473119 m               | 1.63471 m            | 4.57015e-09 m        | 0.0928279 cm/s        | 0.0537499 cm/s           | 0.185816 cm/s        | 5.01969e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 360.279 m             | 209.438 m                | 734.034 m            | 1.37029e-08 m        | 40.3779 cm/s          | 20.7011 cm/s             | 77.9393 cm/s         | 0.00566945 cm/s      |
| Checkcase 1 | Keplerian_VOP   | 360.279 m             | 209.438 m                | 734.034 m            | 1.25035e-08 m        | 40.378 cm/s           | 20.7011 cm/s             | 77.9378 cm/s         | 1.1036e-09 cm/s      |
| Checkcase 1 | Equinoctial_VOP | 340.969 m             | 195.935 m                | 715.283 m            | 1.39835e-08 m        | 38.694 cm/s           | 19.755 cm/s              | 77.8744 cm/s         | 1.0778e-09 cm/s      |
| Checkcase 2 | Cowells_Method  | 359.738 m             | 209.075 m                | 705.385 m            | 6.16116e-09 m        | 40.3308 cm/s          | 20.609 cm/s              | 69.6184 cm/s         | 0.00566945 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 359.738 m             | 209.075 m                | 705.385 m            | 6.55156e-09 m        | 40.3308 cm/s          | 20.609 cm/s              | 69.6185 cm/s         | 7.21479e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 340.377 m             | 195.069 m                | 658.34 m             | 4.63753e-09 m        | 38.6367 cm/s          | 19.625 cm/s              | 68.1738 cm/s         | 5.10589e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 359.028 m             | 208.622 m                | 704.029 m            | 5.86011e-09 m        | 40.2378 cm/s          | 20.5674 cm/s             | 69.4919 cm/s         | 0.00566945 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 359.028 m             | 208.622 m                | 704.029 m            | 6.26929e-09 m        | 40.2378 cm/s          | 20.5674 cm/s             | 69.4921 cm/s         | 7.1409e-10 cm/s      |
| Checkcase 3 | Equinoctial_VOP | 339.631 m             | 194.64 m                 | 657.178 m            | 4.57015e-09 m        | 38.5428 cm/s          | 19.5851 cm/s             | 68.0469 cm/s         | 5.01969e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 359.809 m             | 209.102 m                | 705.464 m            | 5.86011e-09 m        | 40.3389 cm/s          | 20.6122 cm/s             | 69.6319 cm/s         | 0.00566945 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 359.809 m             | 209.102 m                | 705.464 m            | 6.26929e-09 m        | 40.339 cm/s           | 20.6122 cm/s             | 69.6321 cm/s         | 7.1409e-10 cm/s      |
| Checkcase 4 | Equinoctial_VOP | 340.447 m             | 195.102 m                | 658.463 m            | 4.57015e-09 m        | 38.6448 cm/s          | 19.6288 cm/s             | 68.1874 cm/s         | 5.01969e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 500.018 m             | 284.673 m                | 1697.51 m            | 1.37029e-08 m        | 56.7394 cm/s          | 32.064 cm/s              | 195.311 cm/s         | 0.00566945 cm/s      |
| Checkcase 1 | Keplerian_VOP   | 500.018 m             | 284.673 m                | 1697.51 m            | 1.25035e-08 m        | 56.7397 cm/s          | 32.0637 cm/s             | 195.311 cm/s         | 1.1036e-09 cm/s      |
| Checkcase 1 | Equinoctial_VOP | 512.049 m             | 289.489 m                | 1691 m               | 1.39835e-08 m        | 58.283 cm/s           | 32.6472 cm/s             | 196.776 cm/s         | 1.0778e-09 cm/s      |
| Checkcase 2 | Cowells_Method  | 497.715 m             | 279.01 m                 | 936.248 m            | 6.16116e-09 m        | 56.4763 cm/s          | 31.3944 cm/s             | 108.083 cm/s         | 0.00566945 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 497.715 m             | 279.01 m                 | 936.248 m            | 6.55156e-09 m        | 56.4766 cm/s          | 31.3941 cm/s             | 108.083 cm/s         | 7.21479e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 509.718 m             | 283.711 m                | 972.339 m            | 4.63753e-09 m        | 58.0168 cm/s          | 31.9774 cm/s             | 109.62 cm/s          | 5.10589e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 498.743 m             | 279.493 m                | 938.01 m             | 5.86011e-09 m        | 56.5928 cm/s          | 31.4492 cm/s             | 108.282 cm/s         | 0.00566945 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 498.743 m             | 279.493 m                | 938.01 m             | 6.26929e-09 m        | 56.5931 cm/s          | 31.4489 cm/s             | 108.282 cm/s         | 7.1409e-10 cm/s      |
| Checkcase 3 | Equinoctial_VOP | 510.708 m             | 284.246 m                | 974.062 m            | 4.57015e-09 m        | 58.1291 cm/s          | 32.0382 cm/s             | 109.818 cm/s         | 5.01969e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 497.637 m             | 279.024 m                | 936.227 m            | 5.86011e-09 m        | 56.4675 cm/s          | 31.3961 cm/s             | 108.084 cm/s         | 0.00566945 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 497.637 m             | 279.024 m                | 936.227 m            | 6.26929e-09 m        | 56.4678 cm/s          | 31.3958 cm/s             | 108.084 cm/s         | 7.1409e-10 cm/s      |
| Checkcase 4 | Equinoctial_VOP | 509.641 m             | 283.725 m                | 972.334 m            | 4.57015e-09 m        | 58.0081 cm/s          | 31.9791 cm/s             | 109.621 cm/s         | 5.01969e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 0.813441 m            | 0.470899 m               | 1.62697 m            | 1.37029e-08 m        | 0.0928347 cm/s        | 0.0530843 cm/s           | 0.185043 cm/s        | 0.00566945 cm/s      |
| Checkcase 1 | Keplerian_VOP   | 0.813435 m            | 0.470894 m               | 1.62696 m            | 1.25035e-08 m        | 0.0924228 cm/s        | 0.0534982 cm/s           | 0.184949 cm/s        | 1.1036e-09 cm/s      |
| Checkcase 1 | Equinoctial_VOP | 0.813859 m            | 0.471993 m               | 1.63341 m            | 1.39835e-08 m        | 0.092443 cm/s         | 0.0535679 cm/s           | 0.185289 cm/s        | 1.0778e-09 cm/s      |
| Checkcase 2 | Cowells_Method  | 0.815658 m            | 0.472196 m               | 1.63152 m            | 6.16116e-09 m        | 0.0930862 cm/s        | 0.0532324 cm/s           | 0.185575 cm/s        | 0.00566945 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 0.815652 m            | 0.472191 m               | 1.63151 m            | 6.55156e-09 m        | 0.092675 cm/s         | 0.0536457 cm/s           | 0.185481 cm/s        | 7.21479e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 0.816086 m            | 0.473303 m               | 1.63686 m            | 4.63753e-09 m        | 0.0926957 cm/s        | 0.0537161 cm/s           | 0.185758 cm/s        | 5.10589e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 0.814772 m            | 0.471665 m               | 1.62978 m            | 5.86011e-09 m        | 0.0929855 cm/s        | 0.0531725 cm/s           | 0.185373 cm/s        | 0.00566945 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 0.814766 m            | 0.471661 m               | 1.62977 m            | 6.26929e-09 m        | 0.0925742 cm/s        | 0.0535858 cm/s           | 0.185279 cm/s        | 7.1409e-10 cm/s      |
| Checkcase 3 | Equinoctial_VOP | 0.8152 m              | 0.472773 m               | 1.63512 m            | 4.57015e-09 m        | 0.092595 cm/s         | 0.0536562 cm/s           | 0.185556 cm/s        | 5.01969e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 0.824049 m            | 0.47992 m                | 1.65848 m            | 5.86011e-09 m        | 0.0940442 cm/s        | 0.0541123 cm/s           | 0.188639 cm/s        | 0.00566945 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 0.824043 m            | 0.479916 m               | 1.65847 m            | 6.26929e-09 m        | 0.0936325 cm/s        | 0.0545238 cm/s           | 0.188545 cm/s        | 7.1409e-10 cm/s      |
| Checkcase 4 | Equinoctial_VOP | 0.824477 m            | 0.481033 m               | 1.66381 m            | 4.57015e-09 m        | 0.0936532 cm/s        | 0.0545945 cm/s           | 0.188821 cm/s        | 5.01969e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 6.75947e+06 m         | 36741.7 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 1 | Keplerian_VOP   | 6.75947e+06 m         | 36741.7 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 1 | Equinoctial_VOP | 6.75947e+06 m         | 36741.6 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 2 | Cowells_Method  | 14.152 m              | 8.26679 m                | 29.2817 m            | 2.6148e-09 m         | 1.60906 cm/s          | 0.933105 cm/s            | 3.2253 cm/s          | 0.00563888 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 14.152 m              | 8.26679 m                | 29.2817 m            | 2.34371e-09 m        | 1.60879 cm/s          | 0.933336 cm/s            | 3.22541 cm/s         | 4.10567e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 14.1607 m             | 8.2786 m                 | 29.3322 m            | 2.55479e-09 m        | 1.60951 cm/s          | 0.934307 cm/s            | 3.23334 cm/s         | 4.09439e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 14.1516 m             | 8.26651 m                | 29.2808 m            | 2.66134e-09 m        | 1.60901 cm/s          | 0.933074 cm/s            | 3.2252 cm/s          | 0.00563888 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 14.1516 m             | 8.26652 m                | 29.2808 m            | 2.41702e-09 m        | 1.60874 cm/s          | 0.933305 cm/s            | 3.22531 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 14.1603 m             | 8.27832 m                | 29.3313 m            | 2.61232e-09 m        | 1.60946 cm/s          | 0.934276 cm/s            | 3.23324 cm/s         | 2.41601e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 14.1516 m             | 8.26651 m                | 29.2808 m            | 2.66134e-09 m        | 1.60901 cm/s          | 0.933073 cm/s            | 3.2252 cm/s          | 0.00563888 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 14.1516 m             | 8.26651 m                | 29.2808 m            | 2.41702e-09 m        | 1.60874 cm/s          | 0.933305 cm/s            | 3.22531 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 14.1603 m             | 8.27832 m                | 29.3313 m            | 2.61232e-09 m        | 1.60946 cm/s          | 0.934276 cm/s            | 3.23324 cm/s         | 2.41601e-10 cm/s     |

### Main Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/orbital_elements_comparison.png)

### Checkcase Details

#### Checkcase 3

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 3 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/Checkcase 3/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/Checkcase 3/orbital_elements_comparison.png)

#### Checkcase 1

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 1 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/Checkcase 1/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/Checkcase 1/orbital_elements_comparison.png)

#### Checkcase 4

**Propagation Methods:** Equinoctial_VOP, Cowells_Method, Keplerian_VOP

### Checkcase 4 Comparisons

#### Trajectory Comparison

![Trajectory Comparison](results/Orbit_05A/Checkcase 4/trajectory_comparison.png)

#### Orbital Elements Comparison

![Orbital Elements Comparison](results/Orbit_05A/Checkcase 4/orbital_elements_comparison.png)

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
| Checkcase 1 | Cowells_Method  | 6.75947e+06 m         | 36741.7 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 1 | Keplerian_VOP   | 6.75947e+06 m         | 36741.7 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 1 | Equinoctial_VOP | 6.75947e+06 m         | 36741.6 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 2 | Cowells_Method  | 14.152 m              | 8.26679 m                | 29.2817 m            | 2.6148e-09 m         | 1.60906 cm/s          | 0.933105 cm/s            | 3.2253 cm/s          | 0.00563888 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 14.152 m              | 8.26679 m                | 29.2817 m            | 2.34371e-09 m        | 1.60879 cm/s          | 0.933336 cm/s            | 3.22541 cm/s         | 4.10567e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 14.1607 m             | 8.2786 m                 | 29.3322 m            | 2.55479e-09 m        | 1.60951 cm/s          | 0.934307 cm/s            | 3.23334 cm/s         | 4.09439e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 14.1516 m             | 8.26651 m                | 29.2808 m            | 2.66134e-09 m        | 1.60901 cm/s          | 0.933074 cm/s            | 3.2252 cm/s          | 0.00563888 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 14.1516 m             | 8.26652 m                | 29.2808 m            | 2.41702e-09 m        | 1.60874 cm/s          | 0.933305 cm/s            | 3.22531 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 14.1603 m             | 8.27832 m                | 29.3313 m            | 2.61232e-09 m        | 1.60946 cm/s          | 0.934276 cm/s            | 3.23324 cm/s         | 2.41601e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 14.1516 m             | 8.26651 m                | 29.2808 m            | 2.66134e-09 m        | 1.60901 cm/s          | 0.933073 cm/s            | 3.2252 cm/s          | 0.00563888 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 14.1516 m             | 8.26651 m                | 29.2808 m            | 2.41702e-09 m        | 1.60874 cm/s          | 0.933305 cm/s            | 3.22531 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 14.1603 m             | 8.27832 m                | 29.3313 m            | 2.61232e-09 m        | 1.60946 cm/s          | 0.934276 cm/s            | 3.23324 cm/s         | 2.41601e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 6.75947e+06 m         | 36741.7 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 1 | Keplerian_VOP   | 6.75947e+06 m         | 36741.7 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 1 | Equinoctial_VOP | 6.75947e+06 m         | 36741.6 m                | 6.81166e+06 m        | 6.70644e+06 m        | 767902 cm/s           | 4174.54 cm/s             | 773939 cm/s          | 761983 cm/s          |
| Checkcase 2 | Cowells_Method  | 14.152 m              | 8.26679 m                | 29.2817 m            | 2.6148e-09 m         | 1.60906 cm/s          | 0.933105 cm/s            | 3.2253 cm/s          | 0.00563888 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 14.152 m              | 8.26679 m                | 29.2817 m            | 2.34371e-09 m        | 1.60879 cm/s          | 0.933336 cm/s            | 3.22541 cm/s         | 4.10567e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 14.1607 m             | 8.2786 m                 | 29.3322 m            | 2.55479e-09 m        | 1.60951 cm/s          | 0.934307 cm/s            | 3.23334 cm/s         | 4.09439e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 14.1516 m             | 8.26651 m                | 29.2808 m            | 2.66134e-09 m        | 1.60901 cm/s          | 0.933074 cm/s            | 3.2252 cm/s          | 0.00563888 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 14.1516 m             | 8.26652 m                | 29.2808 m            | 2.41702e-09 m        | 1.60874 cm/s          | 0.933305 cm/s            | 3.22531 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 14.1603 m             | 8.27832 m                | 29.3313 m            | 2.61232e-09 m        | 1.60946 cm/s          | 0.934276 cm/s            | 3.23324 cm/s         | 2.41601e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 14.1516 m             | 8.26651 m                | 29.2808 m            | 2.66134e-09 m        | 1.60901 cm/s          | 0.933073 cm/s            | 3.2252 cm/s          | 0.00563888 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 14.1516 m             | 8.26651 m                | 29.2808 m            | 2.41702e-09 m        | 1.60874 cm/s          | 0.933305 cm/s            | 3.22531 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 14.1603 m             | 8.27832 m                | 29.3313 m            | 2.61232e-09 m        | 1.60946 cm/s          | 0.934276 cm/s            | 3.23324 cm/s         | 2.41601e-10 cm/s     |

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
| Checkcase 2 | Cowells_Method  | 316.033 m             | 283.377 m                | 949.179 m            | 2.6148e-09 m         | 35.9402 cm/s          | 32.1473 cm/s             | 108.162 cm/s         | 0.00563888 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 316.033 m             | 283.377 m                | 949.179 m            | 2.34371e-09 m        | 35.9403 cm/s          | 32.1474 cm/s             | 108.162 cm/s         | 4.10567e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 316.033 m             | 283.377 m                | 949.179 m            | 2.55479e-09 m        | 35.9403 cm/s          | 32.1474 cm/s             | 108.162 cm/s         | 4.09439e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 316.059 m             | 283.4 m                  | 949.258 m            | 2.66134e-09 m        | 35.9432 cm/s          | 32.1499 cm/s             | 108.17 cm/s          | 0.00563888 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 316.059 m             | 283.4 m                  | 949.258 m            | 2.41702e-09 m        | 35.9433 cm/s          | 32.15 cm/s               | 108.171 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 316.059 m             | 283.4 m                  | 949.258 m            | 2.61232e-09 m        | 35.9433 cm/s          | 32.15 cm/s               | 108.171 cm/s         | 2.41601e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 0.816672 m            | 0.472599 m               | 1.63886 m            | 2.66134e-09 m        | 0.0931642 cm/s        | 0.053224 cm/s            | 0.186879 cm/s        | 0.00563888 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 0.816672 m            | 0.472599 m               | 1.63886 m            | 2.41702e-09 m        | 0.0927526 cm/s        | 0.0536377 cm/s           | 0.186751 cm/s        | 2.65309e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 0.816672 m            | 0.472599 m               | 1.63886 m            | 2.61232e-09 m        | 0.0927526 cm/s        | 0.0536377 cm/s           | 0.186751 cm/s        | 2.41601e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 1726.53 m             | 1525.75 m                | 6007.07 m            | 1.45537e-08 m        | 196.046 cm/s          | 172.237 cm/s             | 674.574 cm/s         | 0.00563888 cm/s      |
| Checkcase 1 | Keplerian_VOP   | 1726.53 m             | 1525.75 m                | 6007.07 m            | 1.38399e-08 m        | 196.045 cm/s          | 172.237 cm/s             | 674.574 cm/s         | 9.97754e-10 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 1726.53 m             | 1525.75 m                | 6007.07 m            | 1.38903e-08 m        | 196.045 cm/s          | 172.237 cm/s             | 674.574 cm/s         | 9.95064e-10 cm/s     |
| Checkcase 2 | Cowells_Method  | 316.033 m             | 283.377 m                | 949.179 m            | 2.6148e-09 m         | 35.9402 cm/s          | 32.1473 cm/s             | 108.162 cm/s         | 0.00563888 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 316.033 m             | 283.377 m                | 949.179 m            | 2.34371e-09 m        | 35.9403 cm/s          | 32.1474 cm/s             | 108.162 cm/s         | 4.10567e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 316.033 m             | 283.377 m                | 949.179 m            | 2.55479e-09 m        | 35.9403 cm/s          | 32.1474 cm/s             | 108.162 cm/s         | 4.09439e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 316.059 m             | 283.4 m                  | 949.258 m            | 2.66134e-09 m        | 35.9432 cm/s          | 32.1499 cm/s             | 108.17 cm/s          | 0.00563888 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 316.059 m             | 283.4 m                  | 949.258 m            | 2.41702e-09 m        | 35.9433 cm/s          | 32.15 cm/s               | 108.171 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 316.059 m             | 283.4 m                  | 949.258 m            | 2.61232e-09 m        | 35.9433 cm/s          | 32.15 cm/s               | 108.171 cm/s         | 2.41601e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 0.816672 m            | 0.472599 m               | 1.63886 m            | 2.66134e-09 m        | 0.0931642 cm/s        | 0.053224 cm/s            | 0.186879 cm/s        | 0.00563888 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 0.816672 m            | 0.472599 m               | 1.63886 m            | 2.41702e-09 m        | 0.0927526 cm/s        | 0.0536377 cm/s           | 0.186751 cm/s        | 2.65309e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 0.816672 m            | 0.472599 m               | 1.63886 m            | 2.61232e-09 m        | 0.0927526 cm/s        | 0.0536377 cm/s           | 0.186751 cm/s        | 2.41601e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 1600.76 m             | 1656.31 m                | 6138.36 m            | 1.45537e-08 m        | 181.361 cm/s          | 187.079 cm/s             | 688.234 cm/s         | 0.00563887 cm/s      |
| Checkcase 1 | Keplerian_VOP   | 1600.76 m             | 1656.31 m                | 6138.36 m            | 1.38399e-08 m        | 181.361 cm/s          | 187.079 cm/s             | 688.234 cm/s         | 1.71909e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 1586.34 m             | 1560.56 m                | 5530.31 m            | 1.38903e-08 m        | 179.263 cm/s          | 176.988 cm/s             | 650.371 cm/s         | 1.72033e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 1576.89 m             | 1631.98 m                | 5300.24 m            | 2.6148e-09 m         | 178.662 cm/s          | 184.335 cm/s             | 592.944 cm/s         | 0.00563888 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 1576.89 m             | 1631.98 m                | 5300.24 m            | 2.34371e-09 m        | 178.662 cm/s          | 184.335 cm/s             | 592.944 cm/s         | 4.10567e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 1564.47 m             | 1537.25 m                | 5024.76 m            | 2.55479e-09 m        | 176.665 cm/s          | 174.279 cm/s             | 556.081 cm/s         | 4.09439e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 1577.65 m             | 1632.43 m                | 5301.48 m            | 2.66134e-09 m        | 178.748 cm/s          | 184.386 cm/s             | 593.092 cm/s         | 0.00563888 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 1577.65 m             | 1632.43 m                | 5301.48 m            | 2.41702e-09 m        | 178.748 cm/s          | 184.386 cm/s             | 593.092 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 1565.13 m             | 1537.75 m                | 5026.12 m            | 2.61232e-09 m        | 176.747 cm/s          | 174.331 cm/s             | 556.227 cm/s         | 2.41601e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 1576.46 m             | 1631.58 m                | 5298.64 m            | 2.66134e-09 m        | 178.614 cm/s          | 184.289 cm/s             | 592.776 cm/s         | 0.00563888 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 1576.46 m             | 1631.58 m                | 5298.64 m            | 2.41702e-09 m        | 178.614 cm/s          | 184.289 cm/s             | 592.776 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 1564.07 m             | 1536.86 m                | 5023.81 m            | 2.61232e-09 m        | 176.618 cm/s          | 174.233 cm/s             | 555.915 cm/s         | 2.41601e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 2364.82 m             | 1926.99 m                | 7110.27 m            | 1.45537e-08 m        | 268.849 cm/s          | 219.103 cm/s             | 806.882 cm/s         | 0.00563887 cm/s      |
| Checkcase 1 | Keplerian_VOP   | 2364.82 m             | 1926.99 m                | 7110.27 m            | 1.38399e-08 m        | 268.849 cm/s          | 219.103 cm/s             | 806.883 cm/s         | 1.71909e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 2301.52 m             | 1914.19 m                | 6515.91 m            | 1.38903e-08 m        | 264.556 cm/s          | 212.635 cm/s             | 770.556 cm/s         | 1.72033e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 2340.37 m             | 1903.68 m                | 6272.44 m            | 2.6148e-09 m         | 266.074 cm/s          | 216.466 cm/s             | 711.573 cm/s         | 0.00563888 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 2340.37 m             | 1903.68 m                | 6272.44 m            | 2.34371e-09 m        | 266.075 cm/s          | 216.466 cm/s             | 711.573 cm/s         | 4.10567e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 2277.43 m             | 1893.33 m                | 6407.4 m             | 2.55479e-09 m        | 261.818 cm/s          | 210.084 cm/s             | 676.255 cm/s         | 4.09439e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 2341.22 m             | 1904.08 m                | 6273.68 m            | 2.66134e-09 m        | 266.17 cm/s           | 216.511 cm/s             | 711.721 cm/s         | 0.00563888 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 2341.22 m             | 1904.08 m                | 6273.68 m            | 2.41702e-09 m        | 266.17 cm/s           | 216.511 cm/s             | 711.721 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 2278.27 m             | 1893.71 m                | 6408.76 m            | 2.61232e-09 m        | 261.913 cm/s          | 210.129 cm/s             | 676.401 cm/s         | 2.41601e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 2339.95 m             | 1903.28 m                | 6270.84 m            | 2.66134e-09 m        | 266.026 cm/s          | 216.42 cm/s              | 711.405 cm/s         | 0.00563888 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 2339.95 m             | 1903.28 m                | 6270.84 m            | 2.41702e-09 m        | 266.026 cm/s          | 216.42 cm/s              | 711.405 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 2277.01 m             | 1892.96 m                | 6406.44 m            | 2.61232e-09 m        | 261.77 cm/s           | 210.04 cm/s              | 676.088 cm/s         | 2.41601e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 1600.76 m             | 1656.31 m                | 6138.36 m            | 1.45537e-08 m        | 181.361 cm/s          | 187.079 cm/s             | 688.234 cm/s         | 0.00563887 cm/s      |
| Checkcase 1 | Keplerian_VOP   | 1600.76 m             | 1656.31 m                | 6138.36 m            | 1.38399e-08 m        | 181.361 cm/s          | 187.079 cm/s             | 688.234 cm/s         | 1.71909e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 1586.34 m             | 1560.56 m                | 5530.31 m            | 1.38903e-08 m        | 179.263 cm/s          | 176.988 cm/s             | 650.371 cm/s         | 1.72033e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 1576.89 m             | 1631.98 m                | 5300.24 m            | 2.6148e-09 m         | 178.662 cm/s          | 184.335 cm/s             | 592.944 cm/s         | 0.00563888 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 1576.89 m             | 1631.98 m                | 5300.24 m            | 2.34371e-09 m        | 178.662 cm/s          | 184.335 cm/s             | 592.944 cm/s         | 4.10567e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 1564.47 m             | 1537.25 m                | 5024.76 m            | 2.55479e-09 m        | 176.665 cm/s          | 174.279 cm/s             | 556.081 cm/s         | 4.09439e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 1577.65 m             | 1632.43 m                | 5301.48 m            | 2.66134e-09 m        | 178.748 cm/s          | 184.386 cm/s             | 593.092 cm/s         | 0.00563888 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 1577.65 m             | 1632.43 m                | 5301.48 m            | 2.41702e-09 m        | 178.748 cm/s          | 184.386 cm/s             | 593.092 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 1565.13 m             | 1537.75 m                | 5026.12 m            | 2.61232e-09 m        | 176.747 cm/s          | 174.331 cm/s             | 556.227 cm/s         | 2.41601e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 1576.46 m             | 1631.58 m                | 5298.64 m            | 2.66134e-09 m        | 178.614 cm/s          | 184.289 cm/s             | 592.776 cm/s         | 0.00563888 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 1576.46 m             | 1631.58 m                | 5298.64 m            | 2.41702e-09 m        | 178.614 cm/s          | 184.289 cm/s             | 592.776 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 1564.07 m             | 1536.86 m                | 5023.81 m            | 2.61232e-09 m        | 176.618 cm/s          | 174.233 cm/s             | 555.915 cm/s         | 2.41601e-10 cm/s     |

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
| Checkcase 1 | Cowells_Method  | 2364.82 m             | 1926.99 m                | 7110.27 m            | 1.45537e-08 m        | 268.849 cm/s          | 219.103 cm/s             | 806.882 cm/s         | 0.00563887 cm/s      |
| Checkcase 1 | Keplerian_VOP   | 2364.82 m             | 1926.99 m                | 7110.27 m            | 1.38399e-08 m        | 268.849 cm/s          | 219.103 cm/s             | 806.883 cm/s         | 1.71909e-08 cm/s     |
| Checkcase 1 | Equinoctial_VOP | 2301.52 m             | 1914.19 m                | 6515.91 m            | 1.38903e-08 m        | 264.556 cm/s          | 212.635 cm/s             | 770.556 cm/s         | 1.72033e-08 cm/s     |
| Checkcase 2 | Cowells_Method  | 2340.37 m             | 1903.68 m                | 6272.44 m            | 2.6148e-09 m         | 266.074 cm/s          | 216.466 cm/s             | 711.573 cm/s         | 0.00563888 cm/s      |
| Checkcase 2 | Keplerian_VOP   | 2340.37 m             | 1903.68 m                | 6272.44 m            | 2.34371e-09 m        | 266.075 cm/s          | 216.466 cm/s             | 711.573 cm/s         | 4.10567e-10 cm/s     |
| Checkcase 2 | Equinoctial_VOP | 2277.43 m             | 1893.33 m                | 6407.4 m             | 2.55479e-09 m        | 261.818 cm/s          | 210.084 cm/s             | 676.255 cm/s         | 4.09439e-10 cm/s     |
| Checkcase 3 | Cowells_Method  | 2341.22 m             | 1904.08 m                | 6273.68 m            | 2.66134e-09 m        | 266.17 cm/s           | 216.511 cm/s             | 711.721 cm/s         | 0.00563888 cm/s      |
| Checkcase 3 | Keplerian_VOP   | 2341.22 m             | 1904.08 m                | 6273.68 m            | 2.41702e-09 m        | 266.17 cm/s           | 216.511 cm/s             | 711.721 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 3 | Equinoctial_VOP | 2278.27 m             | 1893.71 m                | 6408.76 m            | 2.61232e-09 m        | 261.913 cm/s          | 210.129 cm/s             | 676.401 cm/s         | 2.41601e-10 cm/s     |
| Checkcase 4 | Cowells_Method  | 2339.95 m             | 1903.28 m                | 6270.84 m            | 2.66134e-09 m        | 266.026 cm/s          | 216.42 cm/s              | 711.405 cm/s         | 0.00563888 cm/s      |
| Checkcase 4 | Keplerian_VOP   | 2339.95 m             | 1903.28 m                | 6270.84 m            | 2.41702e-09 m        | 266.026 cm/s          | 216.42 cm/s              | 711.405 cm/s         | 2.65309e-10 cm/s     |
| Checkcase 4 | Equinoctial_VOP | 2277.01 m             | 1892.96 m                | 6406.44 m            | 2.61232e-09 m        | 261.77 cm/s           | 210.04 cm/s              | 676.088 cm/s         | 2.41601e-10 cm/s     |

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

