

# File Sensor.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**sensors**](dir_4c34a36d272c54a3547c6d2c18e9dea2.md) **>** [**Sensor.hpp**](Sensor_8hpp.md)

[Go to the documentation of this file](Sensor_8hpp.md)


```C++

#pragma once

#include <memory>

#include <astro/astro.fwd.hpp>
#include <astro/platforms/Payload.hpp>
#include <astro/types/typedefs.hpp>

#include <trace/platforms/AccessObject.hpp>
#include <trace/platforms/sensors/fov/FieldOfView.hpp>
#include <trace/risesets/AccessArray.hpp>
#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

class SensorParameters : public astro::PayloadParameters {
  public:
    SensorParameters(
        const FieldOfView* fov                                                               = nullptr,
        const astro::CartesianVector<Distance, astro::frames::dynamic::ric>& boresight       = astro::NADIR_RIC,
        const astro::CartesianVector<Distance, astro::frames::dynamic::ric>& attachmentPoint = astro::CENTER
    ) :
        astro::PayloadParameters(boresight, attachmentPoint),
        _fov(fov)
    {
    }

    virtual ~SensorParameters() = default;

    const FieldOfView* get_fov() const { return _fov; }

    void set_fov(FieldOfView* fov) { _fov = fov; }

  protected:
    const FieldOfView* _fov; 
};

class Sensor : public AccessObject, public astro::Payload<Sensor, SensorParameters> {

    friend Payload<Sensor, SensorParameters>;

  public:
    template <typename Parent_T>
    Sensor(const Parent_T& parent, const SensorParameters& parameters) :
        AccessObject(),
        Payload<Sensor, SensorParameters>(parent, parameters)
    {
    }

    virtual ~Sensor() = default;

    std::size_t get_id() const { return _id; }

    bool contains(const astro::RadiusVector<astro::frames::earth::icrf>& sensor2target, const astro::Date& date) const;

  private:
};

using SensorPlatform = astro::PayloadPlatform<Sensor>;

} // namespace trace
} // namespace astrea
```


