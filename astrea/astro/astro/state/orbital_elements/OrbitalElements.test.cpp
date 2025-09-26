#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class OrbitalElementsTest : public testing::Test {
  public:
    OrbitalElementsTest() = default;

    void SetUp() override
    {
        _mu           = _sys.get_mu();
        _cartElements = Cartesian::LEO(_mu);
        _keplElements = Keplerian::LEO();
        _equiElements = Equinoctial::LEO(_mu);
    }

    const Unitless REL_TOL = 1.0e-6;

    AstrodynamicsSystem _sys;
    GravParam _mu;
    OrbitalElements _cartElements;
    OrbitalElements _keplElements;
    OrbitalElements _equiElements;
    Unitless _scalar = 2.0 * astrea::detail::unitless;
    Time _time       = seconds(1);
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

static_assert(IsOrbitalElements<Cartesian>);
static_assert(IsOrbitalElements<Keplerian>);
static_assert(IsOrbitalElements<Equinoctial>);

TEST_F(OrbitalElementsTest, DefaultConstructor) { ASSERT_NO_THROW(OrbitalElements()); }

TEST_F(OrbitalElementsTest, CartesianConstructor) { ASSERT_NO_THROW(OrbitalElements(Cartesian())); }

TEST_F(OrbitalElementsTest, KeplerianConstructor) { ASSERT_NO_THROW(OrbitalElements(Keplerian())); }

TEST_F(OrbitalElementsTest, EquinoctialConstructor) { ASSERT_NO_THROW(OrbitalElements(Equinoctial())); }

TEST_F(OrbitalElementsTest, EqualityOperator)
{
    ASSERT_TRUE(_cartElements == _cartElements);
    ASSERT_TRUE(_keplElements == _keplElements);
    ASSERT_TRUE(_equiElements == _equiElements);

    ASSERT_FALSE(_cartElements == _keplElements);
    ASSERT_FALSE(_cartElements == _equiElements);
    ASSERT_FALSE(_keplElements == _equiElements);
}

TEST_F(OrbitalElementsTest, ConvertInPlace)
{
    OrbitalElements elements = _cartElements;
    ASSERT_EQ(elements.index(), 0);
    elements.convert_to_set<Keplerian>(_mu);
    ASSERT_EQ(elements.index(), 1);
    elements.convert_to_set<Equinoctial>(_mu);
    ASSERT_EQ(elements.index(), 2);
}

TEST_F(OrbitalElementsTest, ConvertToSetCartesian)
{
    OrbitalElements newElements = _cartElements.convert_to_set<Keplerian>(_mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Keplerian>());
    newElements = _cartElements.convert_to_set(OrbitalElements::get_set_id<Keplerian>(), _mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Keplerian>());

    newElements = _cartElements.convert_to_set<Equinoctial>(_mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Equinoctial>());
    newElements = _cartElements.convert_to_set(OrbitalElements::get_set_id<Equinoctial>(), _mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Equinoctial>());

    ASSERT_NO_THROW(OrbitalElements newElements = static_cast<const OrbitalElements&>(_cartElements).convert_to_set<Keplerian>(_mu););
    ASSERT_NO_THROW(
        newElements = static_cast<const OrbitalElements&>(_cartElements).convert_to_set(OrbitalElements::get_set_id<Keplerian>(), _mu)
    );
}

TEST_F(OrbitalElementsTest, ConvertToSetKeplerian)
{
    OrbitalElements newElements = _keplElements.convert_to_set<Cartesian>(_mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Cartesian>());
    newElements = _keplElements.convert_to_set(OrbitalElements::get_set_id<Cartesian>(), _mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Cartesian>());

    newElements = _keplElements.convert_to_set<Equinoctial>(_mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Equinoctial>());
    newElements = _keplElements.convert_to_set(OrbitalElements::get_set_id<Equinoctial>(), _mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Equinoctial>());

    ASSERT_NO_THROW(newElements = static_cast<const OrbitalElements&>(_keplElements).convert_to_set<Cartesian>(_mu));
    ASSERT_NO_THROW(
        newElements = static_cast<const OrbitalElements&>(_keplElements).convert_to_set(OrbitalElements::get_set_id<Cartesian>(), _mu)
    );
}

TEST_F(OrbitalElementsTest, ConvertToSetEquinoctial)
{
    OrbitalElements newElements = _equiElements.convert_to_set<Keplerian>(_mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Keplerian>());
    newElements = _equiElements.convert_to_set(OrbitalElements::get_set_id<Keplerian>(), _mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Keplerian>());

    newElements = _equiElements.convert_to_set<Cartesian>(_mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Cartesian>());
    newElements = _equiElements.convert_to_set(OrbitalElements::get_set_id<Cartesian>(), _mu);
    ASSERT_EQ(newElements.index(), OrbitalElements::get_set_id<Cartesian>());

    ASSERT_NO_THROW(OrbitalElements newElements = static_cast<const OrbitalElements&>(_equiElements).convert_to_set<Cartesian>(_mu););
    ASSERT_NO_THROW(
        newElements = static_cast<const OrbitalElements&>(_equiElements).convert_to_set(OrbitalElements::get_set_id<Cartesian>(), _mu)
    );
}

TEST_F(OrbitalElementsTest, In)
{
    ASSERT_NO_THROW(Keplerian keplerian = _cartElements.in_element_set<Keplerian>(_mu));
    ASSERT_NO_THROW(Equinoctial equinoctial = _cartElements.in_element_set<Equinoctial>(_mu));
}

TEST_F(OrbitalElementsTest, Addition)
{
    ASSERT_NO_THROW(_cartElements + _cartElements);
    ASSERT_NO_THROW(_keplElements + _keplElements);
    ASSERT_NO_THROW(_equiElements + _equiElements);

    ASSERT_ANY_THROW(_cartElements + _keplElements);
    ASSERT_ANY_THROW(_cartElements + _equiElements);
    ASSERT_ANY_THROW(_keplElements + _equiElements);
}

TEST_F(OrbitalElementsTest, InPlaceAddition)
{
    ASSERT_NO_THROW(_cartElements += _cartElements);
    ASSERT_NO_THROW(_keplElements += _keplElements);
    ASSERT_NO_THROW(_equiElements += _equiElements);

    ASSERT_ANY_THROW(_cartElements += _keplElements);
    ASSERT_ANY_THROW(_cartElements += _equiElements);
    ASSERT_ANY_THROW(_keplElements += _equiElements);
}

TEST_F(OrbitalElementsTest, Subtraction)
{
    ASSERT_NO_THROW(_cartElements - _cartElements);
    ASSERT_NO_THROW(_keplElements - _keplElements);
    ASSERT_NO_THROW(_equiElements - _equiElements);

    ASSERT_ANY_THROW(_cartElements - _keplElements);
    ASSERT_ANY_THROW(_cartElements - _equiElements);
    ASSERT_ANY_THROW(_keplElements - _equiElements);
}

TEST_F(OrbitalElementsTest, InPlaceSubtraction)
{
    ASSERT_NO_THROW(_cartElements -= _cartElements);
    ASSERT_NO_THROW(_keplElements -= _keplElements);
    ASSERT_NO_THROW(_equiElements -= _equiElements);

    ASSERT_ANY_THROW(_cartElements -= _keplElements);
    ASSERT_ANY_THROW(_cartElements -= _equiElements);
    ASSERT_ANY_THROW(_keplElements -= _equiElements);
}

TEST_F(OrbitalElementsTest, Multiplication)
{
    ASSERT_NO_THROW(_cartElements * _scalar);
    ASSERT_NO_THROW(_keplElements * _scalar);
    ASSERT_NO_THROW(_equiElements * _scalar);
}

TEST_F(OrbitalElementsTest, InPlaceMultiplication)
{
    ASSERT_NO_THROW(_cartElements *= _scalar);
    ASSERT_NO_THROW(_keplElements *= _scalar);
    ASSERT_NO_THROW(_equiElements *= _scalar);
}

TEST_F(OrbitalElementsTest, ScalarDivision)
{
    ASSERT_NO_THROW(_cartElements / _scalar);
    ASSERT_NO_THROW(_keplElements / _scalar);
    ASSERT_NO_THROW(_equiElements / _scalar);
}

TEST_F(OrbitalElementsTest, InPlaceScalarDivision)
{
    ASSERT_NO_THROW(_cartElements /= _scalar);
    ASSERT_NO_THROW(_keplElements /= _scalar);
    ASSERT_NO_THROW(_equiElements /= _scalar);
}

TEST_F(OrbitalElementsTest, DivisionByTime)
{
    ASSERT_NO_THROW(_cartElements / _time);
    ASSERT_NO_THROW(_keplElements / _time);
    ASSERT_NO_THROW(_equiElements / _time);
}

TEST_F(OrbitalElementsTest, ToVector)
{
    ASSERT_NO_THROW(_cartElements.to_vector());
    ASSERT_NO_THROW(_keplElements.to_vector());
    ASSERT_NO_THROW(_equiElements.to_vector());
}

TEST_F(OrbitalElementsTest, InterpolateCartesian)
{
    Cartesian original = Cartesian::LEO(_mu);
    Cartesian final    = Cartesian::LEO(_mu) * Unitless(1.1 * one);

    OrbitalElements result   = _cartElements.interpolate(0.0 * s, 1.0 * s, OrbitalElements(final), _mu, 0.5 * s);
    OrbitalElements expected = original.interpolate(0.0 * s, 1.0 * s, final, _mu, 0.5 * s);

    ASSERT_EQ_ORB_ELEM(result, OrbitalElements(expected), false, REL_TOL);
    ASSERT_ANY_THROW(_cartElements.interpolate(0.0 * s, 1.0 * s, _keplElements, _mu, 0.5 * s));
    ASSERT_ANY_THROW(_cartElements.interpolate(0.0 * s, 1.0 * s, _equiElements, _mu, 0.5 * s));
}

TEST_F(OrbitalElementsTest, InterpolateKeplerian)
{
    Keplerian original = Keplerian::LEO();
    Keplerian final    = Keplerian::LEO() * Unitless(1.1 * one);

    OrbitalElements result   = _keplElements.interpolate(0.0 * s, 1.0 * s, OrbitalElements(final), _mu, 0.5 * s);
    OrbitalElements expected = original.interpolate(0.0 * s, 1.0 * s, final, _mu, 0.5 * s);

    ASSERT_EQ_ORB_ELEM(result, OrbitalElements(expected), false, REL_TOL);
    ASSERT_ANY_THROW(_keplElements.interpolate(0.0 * s, 1.0 * s, _cartElements, _mu, 0.5 * s));
    ASSERT_ANY_THROW(_keplElements.interpolate(0.0 * s, 1.0 * s, _equiElements, _mu, 0.5 * s));
}

TEST_F(OrbitalElementsTest, InterpolateEquinoctial)
{
    Equinoctial original = Equinoctial::LEO(_mu);
    Equinoctial final    = Equinoctial::LEO(_mu) * Unitless(1.1 * one);

    OrbitalElements result   = _equiElements.interpolate(0.0 * s, 1.0 * s, OrbitalElements(final), _mu, 0.5 * s);
    OrbitalElements expected = original.interpolate(0.0 * s, 1.0 * s, final, _mu, 0.5 * s);

    ASSERT_EQ_ORB_ELEM(result, OrbitalElements(expected), false, REL_TOL);
    ASSERT_ANY_THROW(_equiElements.interpolate(0.0 * s, 1.0 * s, _cartElements, _mu, 0.5 * s));
    ASSERT_ANY_THROW(_equiElements.interpolate(0.0 * s, 1.0 * s, _keplElements, _mu, 0.5 * s));
}

TEST_F(OrbitalElementsTest, Extract)
{
    ASSERT_NO_THROW(_cartElements.extract());
    ASSERT_NO_THROW(_keplElements.extract());
    ASSERT_NO_THROW(_equiElements.extract());
}

TEST_F(OrbitalElementsTest, Index)
{
    ASSERT_EQ(_cartElements.index(), 0);
    ASSERT_EQ(_keplElements.index(), 1);
    ASSERT_EQ(_equiElements.index(), 2);
}

TEST_F(OrbitalElementsTest, Stream)
{
    std::stringstream ss;
    std::stringstream exp;

    ss << _cartElements;
    exp << Cartesian::LEO(_mu);
    ASSERT_EQ(ss.str(), exp.str());

    ss.str("");
    ss << _keplElements;
    exp.str("");
    exp << Keplerian::LEO();
    ASSERT_EQ(ss.str(), exp.str());

    ss.str("");
    ss << _equiElements;
    exp.str("");
    exp << Equinoctial::LEO(_mu);
    ASSERT_EQ(ss.str(), exp.str());
}

TEST_F(OrbitalElementsTest, PartialStream)
{
    std::stringstream ss;
    ss << (_cartElements / _time);
    ASSERT_FALSE(ss.str().empty());

    ss.str("");
    ss << (_keplElements / _time);
    ASSERT_FALSE(ss.str().empty());

    ss.str("");
    ss << (_equiElements / _time);
    ASSERT_FALSE(ss.str().empty());
}
