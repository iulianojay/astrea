/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <sstream>

#include <astro/state/UserDefinedStatePartial.hpp>

using namespace astrea;
using namespace astro;

namespace {

struct MockUserDefinedStateForTime;

struct MockUserDefinedStatePartial {
    std::vector<double> values{ 1.0, 2.0, 3.0 };

    std::vector<double> force_to_double_vector() const { return values; }

    static MockUserDefinedStatePartial from_double_vector(const std::vector<double>& vec)
    {
        MockUserDefinedStatePartial state;
        state.values = vec;
        return state;
    }

    MockUserDefinedStatePartial operator+(const MockUserDefinedStatePartial& other) const
    {
        MockUserDefinedStatePartial out = *this;
        for (std::size_t ii = 0; ii < out.values.size(); ++ii) {
            out.values[ii] += other.values[ii];
        }
        return out;
    }

    MockUserDefinedStatePartial& operator+=(const MockUserDefinedStatePartial& other)
    {
        for (std::size_t ii = 0; ii < values.size(); ++ii) {
            values[ii] += other.values[ii];
        }
        return *this;
    }

    MockUserDefinedStatePartial operator-(const MockUserDefinedStatePartial& other) const
    {
        MockUserDefinedStatePartial out = *this;
        for (std::size_t ii = 0; ii < out.values.size(); ++ii) {
            out.values[ii] -= other.values[ii];
        }
        return out;
    }

    MockUserDefinedStatePartial& operator-=(const MockUserDefinedStatePartial& other)
    {
        for (std::size_t ii = 0; ii < values.size(); ++ii) {
            values[ii] -= other.values[ii];
        }
        return *this;
    }

    MockUserDefinedStatePartial operator*(const Unitless&) const { return *this; }
    MockUserDefinedStatePartial& operator*=(const Unitless&) { return *this; }
    MockUserDefinedStatePartial operator/(const Unitless&) const { return *this; }
    MockUserDefinedStatePartial& operator/=(const Unitless&) { return *this; }

    bool operator==(const MockUserDefinedStatePartial& other) const { return values == other.values; }

    std::string get_name() const { return "MockUserDefinedStatePartial"; }

    MockUserDefinedStateForTime operator*(const Time&) const;

    friend std::ostream& operator<<(std::ostream& os, const MockUserDefinedStatePartial& value)
    {
        os << "MockUserDefinedStatePartial(";
        for (std::size_t ii = 0; ii < value.values.size(); ++ii) {
            os << value.values[ii];
            if (ii + 1 < value.values.size()) { os << ", "; }
        }
        os << ')';
        return os;
    }
};

struct MockUserDefinedStateForTime {
    std::vector<double> values{ 1.0, 2.0, 3.0 };

    std::vector<double> force_to_double_vector() const { return values; }

    static MockUserDefinedStateForTime from_double_vector(const std::vector<double>& vec)
    {
        MockUserDefinedStateForTime state;
        state.values = vec;
        return state;
    }

    MockUserDefinedStateForTime operator+(const MockUserDefinedStateForTime& other) const
    {
        MockUserDefinedStateForTime out = *this;
        for (std::size_t ii = 0; ii < out.values.size(); ++ii) {
            out.values[ii] += other.values[ii];
        }
        return out;
    }

    MockUserDefinedStateForTime& operator+=(const MockUserDefinedStateForTime& other)
    {
        for (std::size_t ii = 0; ii < values.size(); ++ii) {
            values[ii] += other.values[ii];
        }
        return *this;
    }

    MockUserDefinedStateForTime operator-(const MockUserDefinedStateForTime& other) const
    {
        MockUserDefinedStateForTime out = *this;
        for (std::size_t ii = 0; ii < out.values.size(); ++ii) {
            out.values[ii] -= other.values[ii];
        }
        return out;
    }

    MockUserDefinedStateForTime& operator-=(const MockUserDefinedStateForTime& other)
    {
        for (std::size_t ii = 0; ii < values.size(); ++ii) {
            values[ii] -= other.values[ii];
        }
        return *this;
    }

    MockUserDefinedStateForTime operator*(const Unitless&) const { return *this; }
    MockUserDefinedStateForTime& operator*=(const Unitless&) { return *this; }
    MockUserDefinedStateForTime operator/(const Unitless&) const { return *this; }
    MockUserDefinedStateForTime& operator/=(const Unitless&) { return *this; }

    MockUserDefinedStatePartial operator/(const Time&) const { return MockUserDefinedStatePartial{ .values = values }; }

    bool operator==(const MockUserDefinedStateForTime& other) const { return values == other.values; }

    std::string get_name() const { return "MockUserDefinedStateForTime"; }

    friend std::ostream& operator<<(std::ostream& os, const MockUserDefinedStateForTime& value)
    {
        os << "MockUserDefinedStateForTime(";
        for (std::size_t ii = 0; ii < value.values.size(); ++ii) {
            os << value.values[ii];
            if (ii + 1 < value.values.size()) { os << ", "; }
        }
        os << ')';
        return os;
    }
};

inline MockUserDefinedStateForTime MockUserDefinedStatePartial::operator*(const Time&) const
{
    return MockUserDefinedStateForTime{ .values = values };
}

struct OtherUserDefinedStatePartial {
    std::vector<double> values{ 10.0, 20.0, 30.0 };

    std::vector<double> force_to_double_vector() const { return values; }

    static OtherUserDefinedStatePartial from_double_vector(const std::vector<double>& vec)
    {
        OtherUserDefinedStatePartial state;
        state.values = vec;
        return state;
    }

    OtherUserDefinedStatePartial operator+(const OtherUserDefinedStatePartial&) const { return *this; }
    OtherUserDefinedStatePartial& operator+=(const OtherUserDefinedStatePartial&) { return *this; }
    OtherUserDefinedStatePartial operator-(const OtherUserDefinedStatePartial&) const { return *this; }
    OtherUserDefinedStatePartial& operator-=(const OtherUserDefinedStatePartial&) { return *this; }
    OtherUserDefinedStatePartial operator*(const Unitless&) const { return *this; }
    OtherUserDefinedStatePartial& operator*=(const Unitless&) { return *this; }
    OtherUserDefinedStatePartial operator/(const Unitless&) const { return *this; }
    OtherUserDefinedStatePartial& operator/=(const Unitless&) { return *this; }

    bool operator==(const OtherUserDefinedStatePartial& other) const { return values == other.values; }

    friend std::ostream& operator<<(std::ostream& os, const OtherUserDefinedStatePartial& value)
    {
        os << "OtherUserDefinedStatePartial(";
        for (std::size_t ii = 0; ii < value.values.size(); ++ii) {
            os << value.values[ii];
            if (ii + 1 < value.values.size()) { os << ", "; }
        }
        os << ')';
        return os;
    }
};

} // namespace

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(UserDefinedStatePartialTest, VectorConversionRoundTrip)
{
    UserDefinedStatePartial state(MockUserDefinedStatePartial{});
    EXPECT_EQ(state.get_name(), "MockUserDefinedStatePartial");
    EXPECT_EQ(state.force_to_double_vector(), (std::vector<double>{ 1.0, 2.0, 3.0 }));

    auto& newState = state.from_double_vector({ 4.0, 5.0, 6.0 });
    EXPECT_EQ(newState.force_to_double_vector(), (std::vector<double>{ 4.0, 5.0, 6.0 }));
}

TEST(UserDefinedStatePartialTest, SupportsMathOperations)
{
    UserDefinedStatePartial first(MockUserDefinedStatePartial{ .values = { 1.0, 2.0, 3.0 } });
    UserDefinedStatePartial second(MockUserDefinedStatePartial{ .values = { 10.0, 20.0, 30.0 } });

    auto sum = first + second;
    EXPECT_EQ(sum.force_to_double_vector(), (std::vector<double>{ 11.0, 22.0, 33.0 }));

    first += second;
    EXPECT_EQ(first.force_to_double_vector(), (std::vector<double>{ 11.0, 22.0, 33.0 }));

    auto diff = first - second;
    EXPECT_EQ(diff.force_to_double_vector(), (std::vector<double>{ 1.0, 2.0, 3.0 }));
}

TEST(UserDefinedStatePartialTest, RejectsTypeMismatchesForMath)
{
    UserDefinedStatePartial first(MockUserDefinedStatePartial{});
    UserDefinedStatePartial second(OtherUserDefinedStatePartial{});

    EXPECT_THROW((void)(first + second), std::runtime_error);
    EXPECT_THROW(first += second, std::runtime_error);
}

TEST(UserDefinedStatePartialTest, EqualityComparison)
{
    UserDefinedStatePartial first(MockUserDefinedStatePartial{ .values = { 1.0, 2.0, 3.0 } });
    UserDefinedStatePartial second(MockUserDefinedStatePartial{ .values = { 1.0, 2.0, 3.0 } });
    UserDefinedStatePartial third(MockUserDefinedStatePartial{ .values = { 4.0, 5.0, 6.0 } });

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first == third);
}

TEST(UserDefinedStatePartialTest, StreamOutput)
{
    UserDefinedStatePartial state(MockUserDefinedStatePartial{ .values = { 1.0, 2.0, 3.0 } });
    std::ostringstream oss;
    oss << state;
    EXPECT_EQ(oss.str(), "MockUserDefinedStatePartial(1, 2, 3)");
}

TEST(UserDefinedStatePartialTest, TimeConversionRoundTrip)
{
    UserDefinedState state(MockUserDefinedStateForTime{ .values = { 7.0, 8.0, 9.0 } });
    const Time dt{};

    auto partial = state / dt;
    EXPECT_EQ(partial.force_to_double_vector(), (std::vector<double>{ 7.0, 8.0, 9.0 }));

    auto recovered = partial * dt;
    EXPECT_EQ(recovered.force_to_double_vector(), (std::vector<double>{ 7.0, 8.0, 9.0 }));
}
