/**
 * @file main.cpp
 * @brief Entry point for Google Test execution.
 *
 * This file initializes and runs all Google Test cases in the project.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
