# Testing

Astrea's testing strategy ensures reliability, accuracy, and performance through comprehensive validation against established benchmarks, real-world data, and theoretical expectations. 

Astrea uses Google Test as its testing framework and currently hosts ~1000 unit tests, and a host of integration tests. For V&V, Astrea has been validated against the NASA 6DOF test cases, and a set of benchmarks for propagation and orbit determination. These tests are _not_ run as part of the CI/CD pipeline since they take quite a long time to run, but they are run on a regular basis to ensure that the library is performing as expected.

### NASA 6DOF Check Cases

Currently, Astrea validates it's equations and propagation directly against the published NASA 6DOF test cases. The test cases and documentation are available in the repo ([link](https://github.com/iulianojay/astrea/tree/main/astrea/astro/tests/nasa_6dof_checkcases)). The test cases include a set of 6DOF propagation scenarios with known solutions, which are used to validate the accuracy of Astrea's propagation algorithms. This repo also hosts the entirely of the unit tests as a SQL database, to make storage and comparison easier than the csv files provided by NASA.

Currently, only 3DoF propagation is well validated, while 6DoF propagation is available but hasn't been validated. It's currently being worked on. The atmospheric models are also yet to be validated since Astrea only currently supports the simpler Jacchia-Roberts and Harris-Priester models. When more sophisticated atmospheric models are implemented, the tests will be updated to compare against those test cases as well.

A great degree of effort was put into ensuring just the 3DoF propagation was accurate. Some of the main pitfalls hit included:
- The integrator silently hitting invalid stopping conditions
- The integrator taking one too many or too few steps in certain cases
- The error model in the integrator using a lower-accuracy estimation than needed
- Matching planetary ephemeris data, physical constants, and other parameters exactly to the NASA test cases.
- Floating point issues in the otherwise correct oblateness calculations
- Floating point issues in n-body perturbations due to large range discrepancies   

At this point, the 3DoF propagation is considered accurate to any reasonable degree of precision. Any further improvement on the models would require a much more sophisticated analysis of the floating-point rounding errors in the simulation which is largely impossible without access to the source code used to produce the original data. 

An automatically generated report in the NASA 6DOF check cases can be found [here](nasa_6dof_report/nasa_6dof_report.md)

### Benchmarks

Benchmarks for the Astrea propagator are run using Google Benchmark. The benchmarks are a simple measure of performance meant to give a qualitative idea of the speed resulting from many of the techniques this library employs. The benchmarks can be found [here](https://github.com/iulianojay/astrea/tree/main/astrea/astro/benchmarks/propagation). Similar to the NASA 6DOF test cases, the benchmarks are not run as part of the CI/CD pipeline since they take quite a long time to run, but they are run on a regular basis to ensure that the library is performing as expected.

While many of the standard easy optimizations were taken as a matter of habit while developing this library (passing const references, avoid unnecessary unit conversions, etc.), the largest improvements in performance came from the development of the frame system. Combined with modern C++ compile-time optimizations, the type-based frame system showed speedups of nearly 2 orders of magnitude in propagation. Runs that would take many minutes, could be reduced to a few seconds. It's difficult by the nature of the thing to pinpoint exactly where the speedup came from, but it is this authors belief that the majority of the speedup comes from pre-computing most of the calculations, lookup, and frame transformation logic at compile-time. 

An automatically generated report on the benchmarks can be found [here](benchmarks/propagation.md)