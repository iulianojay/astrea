

# File propagation.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation.hpp**](propagation_8hpp.md)

[Go to the documentation of this file](propagation_8hpp.md)


```C++

#pragma once

#include <astro/propagation/analytic/LambertSolver.hpp>

#include <astro/propagation/force_models/AtmosphericForce.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/force_models/NBodyForce.hpp>
#include <astro/propagation/force_models/OblatenessForce.hpp>
#include <astro/propagation/force_models/Perturbation.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>
#include <astro/propagation/force_models/SolarRadiationPressure.hpp>

#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>
#include <astro/propagation/equations_of_motion/J2MeanVop.hpp>
#include <astro/propagation/equations_of_motion/KeplerianVop.hpp>
#include <astro/propagation/equations_of_motion/TwoBody.hpp>

#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/event_detection/events/ImpulsiveBurn.hpp>

#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/propagation/numerical/StepWatcher.hpp>
#include <astro/propagation/numerical/butcher_tableau.hpp>
```


