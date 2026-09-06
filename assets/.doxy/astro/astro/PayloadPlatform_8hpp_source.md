

# File PayloadPlatform.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**PayloadPlatform.hpp**](PayloadPlatform_8hpp.md)

[Go to the documentation of this file](PayloadPlatform_8hpp.md)


```C++

#pragma once

#include <vector>

#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>


namespace astrea {
namespace astro {

template <class Payload_T>
class PayloadPlatform {

    // This is cursed
    using PayloadParameters_T = remove_cv_ref<decltype(std::declval<Payload_T>().get_parameters())>;

  protected:
    PayloadPlatform() = default;

    virtual ~PayloadPlatform() = default;

    PayloadPlatform(const PayloadPlatform& other)
    {
        _payloads = other._payloads;
        reset_payload_parentage();
    }

    PayloadPlatform(PayloadPlatform&& other) noexcept
    {
        _payloads = std::move(other._payloads);
        reset_payload_parentage();
    }

    PayloadPlatform& operator=(const PayloadPlatform& other)
    {
        if (this != &other) {
            _payloads = other._payloads;
            reset_payload_parentage();
        }
        return *this;
    }

    PayloadPlatform& operator=(PayloadPlatform&& other) noexcept
    {
        if (this != &other) {
            _payloads = std::move(other._payloads);
            reset_payload_parentage();
        }
        return *this;
    }

  public:
    virtual std::size_t get_id() const = 0;

    virtual RadiusVector<frames::primary> get_position(const Date& date) const = 0;

    virtual VelocityVector<frames::primary> get_velocity(const Date& date) const = 0;

    virtual Mass get_mass(const State& state) const { return 0.0 * mp_units::si::unit_symbols::kg; }

    void attach_payload(const PayloadParameters_T& parameters) { _payloads.emplace_back(Payload_T(*this, parameters)); }

    void attach_payloads(const std::vector<PayloadParameters_T>& parameterPack)
    {
        for (const auto& parameters : parameterPack) {
            attach_payload(parameters);
        }
    }

    std::vector<Payload_T>& get_payloads() { return _payloads; }

    const std::vector<Payload_T>& get_payloads() const { return _payloads; }

  protected:
    std::vector<Payload_T> _payloads; // List of payloads attached to the platform

    void reset_payload_parentage()
    {
        for (auto& payload : _payloads) {
            payload.set_parent(*this);
        }
    }
};


} // namespace astro
} // namespace astrea
```


