#include <astro/element_sets/OrbitalElements.hpp>

#include <stdexcept>

#include <mp-units/math.h>

using namespace mp_units;

namespace astro {

std::ostream& operator<<(std::ostream& os, const OrbitalElements& elements)
{
    std::visit([&os](const auto& x) { os << x; }, elements._elements);
    return os;
}

OrbitalElements OrbitalElements::operator+(const OrbitalElements& other) const
{
    return std::visit(
        [&](const auto& x) -> OrbitalElements {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            return x + y;
        },
        _elements
    );
}
OrbitalElements& OrbitalElements::operator+=(const OrbitalElements& other)
{
    std::visit(
        [&](auto& x) {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            x += y;
        },
        _elements
    );
    return *this;
}

OrbitalElements OrbitalElements::operator-(const OrbitalElements& other) const
{
    return std::visit(
        [&](const auto& x) -> OrbitalElements {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            return x - y;
        },
        _elements
    );
}
OrbitalElements& OrbitalElements::operator-=(const OrbitalElements& other)
{
    std::visit(
        [&](auto& x) {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            x -= y;
        },
        _elements
    );
    return *this;
}

OrbitalElements OrbitalElements::operator*(const Unitless& multiplier) const
{
    return std::visit([&](const auto& x) -> OrbitalElements { return x * multiplier; }, _elements);
}
OrbitalElements& OrbitalElements::operator*=(const Unitless& multiplier)
{
    std::visit([&](auto& x) { x *= multiplier; }, _elements);
    return *this;
}

OrbitalElementPartials OrbitalElements::operator/(const Time& divisor) const
{
    return std::visit([&](const auto& x) -> OrbitalElementPartials { return x / divisor; }, _elements);
}
OrbitalElements OrbitalElements::operator/(const Unitless& divisor) const
{
    return std::visit([&](const auto& x) -> OrbitalElements { return x / divisor; }, _elements);
}
OrbitalElements& OrbitalElements::operator/=(const Unitless& divisor)
{
    std::visit([&](auto& x) { x /= divisor; }, _elements);
    return *this;
}

std::vector<Unitless> OrbitalElements::to_vector() const
{
    return std::visit([&](const auto& x) { return x.to_vector(); }, _elements);
}

OrbitalElements
    OrbitalElements::interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const
{
    return std::visit(
        [&](const auto& x) -> OrbitalElements {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            return x.interpolate(thisTime, otherTime, y, sys, targetTime);
        },
        _elements
    );
}

const OrbitalElements::ElementVariant& OrbitalElements::extract() const { return _elements; }
OrbitalElements::ElementVariant& OrbitalElements::extract() { return _elements; }

constexpr std::size_t OrbitalElements::index() const { return _elements.index(); }


void OrbitalElements::same_underlying_type(const OrbitalElements& other) const
{
    if (_elements.index() != other.extract().index()) [[unlikely]] { throw_mismatched_types(); }
}


OrbitalElements OrbitalElementPartials::operator*(const Time& time) const
{
    return std::visit([&](const auto& x) -> OrbitalElements { return x * time; }, _elements);
}

const OrbitalElementPartials::PartialVariant& OrbitalElementPartials::extract() const { return _elements; }
OrbitalElementPartials::PartialVariant& OrbitalElementPartials::extract() { return _elements; }

constexpr std::size_t OrbitalElementPartials::index() const { return _elements.index(); }


void OrbitalElementPartials::same_underlying_type(const OrbitalElementPartials& other) const
{
    if (_elements.index() != other.extract().index()) [[unlikely]] { throw_mismatched_types(); }
}

void throw_mismatched_types()
{
    throw std::runtime_error("Cannot perform operations on orbital elements from different "
                             "element sets.");
}


bool nearly_equal(const OrbitalElements& first, const OrbitalElements& second, bool ignoreFastVariable, Unitless relTol)
{
    if (first.index() != second.index()) {
        throw std::runtime_error("Cannot compare elements sets of different types.");
    }
    const auto firstScaled  = first.to_vector();
    const auto secondScaled = second.to_vector();
    for (int ii = 0; ii < 6; ii++) {
        if (abs((firstScaled[ii] - secondScaled[ii]) / firstScaled[ii]) > relTol) { return false; }
    }
    return true;
}

} // namespace astro