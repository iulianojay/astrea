

# File Payload.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**Payload.hpp**](Payload_8hpp.md)

[Go to the documentation of this file](Payload_8hpp.md)


```C++

#pragma once

#include <memory>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/frames/dynamic_frames.hpp>
#include <astro/frames/frames.hpp>
#include <astro/platforms/PayloadPlatform.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

static const astro::RadiusVector<astro::frames::dynamic::ric> NADIR_RIC  = { -1.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit };
static const astro::RadiusVector<astro::frames::dynamic::ric> RADIAL_RIC = { 1.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit };
static const astro::RadiusVector<astro::frames::dynamic::ric> CENTER     = { 0.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit };

class PayloadParameters {
  protected:
    PayloadParameters(
        const astro::RadiusVector<astro::frames::dynamic::ric>& boresight       = NADIR_RIC,
        const astro::RadiusVector<astro::frames::dynamic::ric>& attachmentPoint = CENTER
    ) :
        _boresight(boresight),
        _attachmentPoint(attachmentPoint)
    {
    }

    virtual ~PayloadParameters() = default;

  public:
    astro::RadiusVector<astro::frames::dynamic::ric> get_boresight() const { return _boresight; }

    astro::RadiusVector<astro::frames::dynamic::ric> get_attachment_point() const { return _attachmentPoint; }

    void set_boresight(const astro::RadiusVector<astro::frames::dynamic::ric>& boresight) { _boresight = boresight; }

    void set_attachment_point(const astro::RadiusVector<astro::frames::dynamic::ric>& attachmentPoint)
    {
        _attachmentPoint = attachmentPoint;
    }

  protected:
    astro::RadiusVector<astro::frames::dynamic::ric> _boresight; 
    astro::RadiusVector<astro::frames::dynamic::ric> _attachmentPoint; 

    // TODO: Make a fixed-offset frame for attachment point
};

template <class Payload_T, class PayloadParameters_T>
class Payload { // TODO: add -> : public FrameReference

    friend PayloadPlatform<Payload_T>;

  protected:
    template <typename Parent_T>
        requires(std::is_base_of_v<PayloadPlatform<Payload_T>, Parent_T>)
    Payload(const Parent_T& parent, const PayloadParameters_T& parameters) :
        _parent(&parent),
        _parameters(parameters),
        _id(generate_id())
    {
    }

    virtual ~Payload() = default;

  public:
    virtual std::size_t get_id() const = 0;

    std::size_t generate_id() const { return static_cast<const Payload_T*>(this)->generate_id(); }

    const PayloadPlatform<Payload_T>* const get_parent() const { return _parent; }

    PayloadParameters_T get_parameters() const { return _parameters; }

  protected:
    const PayloadPlatform<Payload_T>* _parent; 
    PayloadParameters_T _parameters;           
    std::size_t _id;                           

    template <typename Parent_T>
        requires(std::is_base_of_v<PayloadPlatform<Payload_T>, Parent_T>)
    void set_parent(const Parent_T& parent)
    {
        _parent = &parent;
    }
};

} // namespace astro
} // namespace astrea
```


