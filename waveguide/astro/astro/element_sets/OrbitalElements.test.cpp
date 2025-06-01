#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using namespace astro;

class OrbitalElementsTest : public testing::Test {
  public:
    OrbitalElementsTest() = default;

    void SetUp() override
    {
        _cartElements = Cartesian();
        _keplElements = Keplerian();
        _equiElements = Equinoctial();
    }

    AstrodynamicsSystem _sys;
    OrbitalElements _cartElements;
    OrbitalElements _keplElements;
    OrbitalElements _equiElements;
    Unitless _scalar = 2 * detail::unitless;
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

TEST_F(OrbitalElementsTest, ConvertInPlace)
{
    OrbitalElements elements = _cartElements;
    ASSERT_EQ(elements.index(), 0);
    elements.convert<Keplerian>(_sys);
    ASSERT_EQ(elements.index(), 1);
    elements.convert<Equinoctial>(_sys);
    ASSERT_EQ(elements.index(), 2);
}

TEST_F(OrbitalElementsTest, Convert)
{
    OrbitalElements newElements = _cartElements.convert<Keplerian>(_sys);
    ASSERT_EQ(newElements.index(), 1);
    newElements = _cartElements.convert<Equinoctial>(_sys);
    ASSERT_EQ(newElements.index(), 2);
}

TEST_F(OrbitalElementsTest, In)
{
    ASSERT_NO_THROW(Keplerian keplerian = _cartElements.in<Keplerian>(_sys));
    ASSERT_NO_THROW(Equinoctial equinoctial = _cartElements.in<Equinoctial>(_sys));
}

TEST_F(OrbitalElementsTest, Addition)
{
    ASSERT_NO_THROW(_cartElements + _cartElements);
    ASSERT_NO_THROW(_keplElements + _keplElements);
    ASSERT_NO_THROW(_equiElements + _equiElements);
}

TEST_F(OrbitalElementsTest, InPlaceAddition)
{
    ASSERT_NO_THROW(_cartElements += _cartElements);
    ASSERT_NO_THROW(_keplElements += _keplElements);
    ASSERT_NO_THROW(_equiElements += _equiElements);
}

TEST_F(OrbitalElementsTest, Subtraction)
{
    ASSERT_NO_THROW(_cartElements - _cartElements);
    ASSERT_NO_THROW(_keplElements - _keplElements);
    ASSERT_NO_THROW(_equiElements - _equiElements);
}

TEST_F(OrbitalElementsTest, InPlaceSubtraction)
{
    ASSERT_NO_THROW(_cartElements -= _cartElements);
    ASSERT_NO_THROW(_keplElements -= _keplElements);
    ASSERT_NO_THROW(_equiElements -= _equiElements);
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

TEST_F(OrbitalElementsTest, _scalarDivision)
{
    ASSERT_NO_THROW(_cartElements / _scalar);
    ASSERT_NO_THROW(_keplElements / _scalar);
    ASSERT_NO_THROW(_equiElements / _scalar);
}

TEST_F(OrbitalElementsTest, InPlace_scalarDivision)
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

TEST_F(OrbitalElementsTest, Interpolate) {}

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
