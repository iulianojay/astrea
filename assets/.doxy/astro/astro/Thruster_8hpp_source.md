

# File Thruster.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**thrusters**](dir_c4651317ac77989e0950f932d02daf86.md) **>** [**Thruster.hpp**](Thruster_8hpp.md)

[Go to the documentation of this file](Thruster_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <astro/platforms/Payload.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class ThrusterParameters : public PayloadParameters {
  public:
    ThrusterParameters(
        const Force& thrust,
        const CartesianVector<Distance, frames::dynamic::ric>& boresight       = NADIR_RIC,
        const CartesianVector<Distance, frames::dynamic::ric>& attachmentPoint = CENTER
    ) :
        PayloadParameters(boresight, attachmentPoint),
        _thrust(thrust)
    {
    }

    virtual ~ThrusterParameters() = default;

    Force get_thrust() const { return _thrust; }

    bool is_on() const { return _isOn; }

    void switch_on() { _isOn = true; }

    void switch_off() { _isOn = false; }

  protected:
    Force _thrust;      
    bool _isOn = false; 
};

class Thruster : public Payload<Thruster, ThrusterParameters> {

    friend Payload<Thruster, ThrusterParameters>;

  public:
    template <typename Parent_T>
    Thruster(const Parent_T& parent, const ThrusterParameters& parameters) :
        Payload<Thruster, ThrusterParameters>(parent, parameters)
    {
    }

    virtual ~Thruster() = default;

    std::size_t get_id() const;

    Velocity get_impulsive_delta_v() const;

    Force get_thrust() const;

    void switch_on();

    void switch_off();

    bool is_on() const;
};

using ThrusterPlatform = PayloadPlatform<Thruster>;

} // namespace astro
} // namespace astrea
```


