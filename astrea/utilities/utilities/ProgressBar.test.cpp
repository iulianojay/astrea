/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <utilities/utilities.hpp>

using namespace astrea;
using namespace utilities;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(ProgressBarTest, Build) { ASSERT_NO_THROW(ProgressBar bar(100, "Test Progress Bar", 10, 50)); }

TEST(ProgressBarTest, IncrementAndReset)
{
    const std::size_t maxRecords = 100;
    const std::size_t frequency  = 10;

    ProgressBar bar(maxRecords, "Test Progress Bar", frequency);
    ASSERT_EQ(bar.get_progress(), 0);
    for (std::size_t ii = 0; ii < maxRecords; ++ii) {
        bar();
        ASSERT_EQ(bar.get_progress(), ii + 1);
    }

    bar.reset();
    ASSERT_EQ(bar.get_progress(), 0);
}
