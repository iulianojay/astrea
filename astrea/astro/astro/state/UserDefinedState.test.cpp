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

#include <astro/state/UserDefinedState.hpp>

using namespace astrea;
using namespace astro;

namespace {

struct MockUserDefinedState {
    std::vector<double> values{ 1.0, 2.0, 3.0 };

    std::vector<double> force_to_double_vector() const { return values; }

    static MockUserDefinedState from_double_vector(const std::vector<double>& vec)
    {
        MockUserDefinedState state;
        state.values = vec;
        return state;
    }

    MockUserDefinedState operator+(const MockUserDefinedState& other) const
    {
        MockUserDefinedState out = *this;
        for (std::size_t i = 0; i < out.values.size(); ++i) {
            out.values[i] += other.values[i];
        }
        return out;
    }

    MockUserDefinedState& operator+=(const MockUserDefinedState& other)
    {
        for (std::size_t i = 0; i < values.size(); ++i) {
            values[i] += other.values[i];
        }
        return *this;
    }

    MockUserDefinedState operator-(const MockUserDefinedState& other) const
    {
        MockUserDefinedState out = *this;
        for (std::size_t i = 0; i < out.values.size(); ++i) {
            out.values[i] -= other.values[i];
        }
        return out;
    }

    MockUserDefinedState& operator-=(const MockUserDefinedState& other)
    {
        for (std::size_t i = 0; i < values.size(); ++i) {
            values[i] -= other.values[i];
        }
        return *this;
    }

    MockUserDefinedState operator*(const Unitless&) const { return *this; }
    MockUserDefinedState& operator*=(const Unitless&) { return *this; }
    MockUserDefinedState operator/(const Unitless&) const { return *this; }
    MockUserDefinedState& operator/=(const Unitless&) { return *this; }

    bool operator==(const MockUserDefinedState& other) const { return values == other.values; }

    std::string get_name() const { return "MockUserDefinedState"; }

    friend std::ostream& operator<<(std::ostream& os, const MockUserDefinedState& value)
    {
        os << "MockUserDefinedState(";
        for (std::size_t ii = 0; ii < value.values.size(); ++ii) {
            os << value.values[ii];
            if (ii + 1 < value.values.size()) { os << ", "; }
        }
        os << ')';
        return os;
    }
};

struct OtherUserDefinedState {
    std::vector<double> values{ 10.0, 20.0, 30.0 };

    std::vector<double> force_to_double_vector() const { return values; }

    static OtherUserDefinedState from_double_vector(const std::vector<double>& vec)
    {
        OtherUserDefinedState state;
        state.values = vec;
        return state;
    }

    OtherUserDefinedState operator+(const OtherUserDefinedState&) const { return *this; }
    OtherUserDefinedState& operator+=(const OtherUserDefinedState&) { return *this; }
    OtherUserDefinedState operator-(const OtherUserDefinedState&) const { return *this; }
    OtherUserDefinedState& operator-=(const OtherUserDefinedState&) { return *this; }
    OtherUserDefinedState operator*(const Unitless&) const { return *this; }
    OtherUserDefinedState& operator*=(const Unitless&) { return *this; }
    OtherUserDefinedState operator/(const Unitless&) const { return *this; }
    OtherUserDefinedState& operator/=(const Unitless&) { return *this; }

    bool operator==(const OtherUserDefinedState& other) const { return values == other.values; }

    friend std::ostream& operator<<(std::ostream& os, const OtherUserDefinedState& value)
    {
        os << "OtherUserDefinedState(";
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

TEST(UserDefinedStateTest, VectorConversionRoundTrip)
{
    UserDefinedState state(MockUserDefinedState{});
    EXPECT_EQ(state.get_name(), "MockUserDefinedState");
    EXPECT_EQ(state.force_to_double_vector(), (std::vector<double>{ 1.0, 2.0, 3.0 }));

    auto& newState = state.from_double_vector({ 4.0, 5.0, 6.0 });
    EXPECT_EQ(newState.force_to_double_vector(), (std::vector<double>{ 4.0, 5.0, 6.0 }));
}

TEST(UserDefinedStateTest, SupportsMathOperations)
{
    UserDefinedState first(MockUserDefinedState{ .values = { 1.0, 2.0, 3.0 } });
    UserDefinedState second(MockUserDefinedState{ .values = { 10.0, 20.0, 30.0 } });

    auto sum = first + second;
    EXPECT_EQ(sum.force_to_double_vector(), (std::vector<double>{ 11.0, 22.0, 33.0 }));

    first += second;
    EXPECT_EQ(first.force_to_double_vector(), (std::vector<double>{ 11.0, 22.0, 33.0 }));

    auto diff = first - second;
    EXPECT_EQ(diff.force_to_double_vector(), (std::vector<double>{ 1.0, 2.0, 3.0 }));
}

TEST(UserDefinedStateTest, RejectsTypeMismatchesForMath)
{
    UserDefinedState first(MockUserDefinedState{});
    UserDefinedState second(OtherUserDefinedState{});

    EXPECT_THROW((void)(first + second), std::runtime_error);
    EXPECT_THROW(first += second, std::runtime_error);
}

TEST(UserDefinedStateTest, EqualityComparison)
{
    UserDefinedState first(MockUserDefinedState{ .values = { 1.0, 2.0, 3.0 } });
    UserDefinedState second(MockUserDefinedState{ .values = { 1.0, 2.0, 3.0 } });
    UserDefinedState third(MockUserDefinedState{ .values = { 4.0, 5.0, 6.0 } });

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first == third);
}

TEST(UserDefinedStateTest, StreamOutput)
{
    UserDefinedState state(MockUserDefinedState{ .values = { 1.0, 2.0, 3.0 } });
    std::ostringstream oss;
    oss << state;
    EXPECT_EQ(oss.str(), "MockUserDefinedState(1, 2, 3)");
}
