/**
 * @file BreakTest.cpp
 * @brief Unit tests for the Break class.
 *
 * This file contains Google Test cases for the Break class, verifying
 * the correctness of break time initialization, end time setting, and
 * duration calculation.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */


#include <gtest/gtest.h>
#include "Break.h"
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include "timeFormator.h"

// Test fixture for Break class
class BreakTest : public ::testing::Test, public timeFormator {
protected:
    Break breakInstance;
};

// Test case: Constructor initializes start time correctly
TEST_F(BreakTest, ConstructorInitialization) {
    auto now = std::chrono::system_clock::now();
    std::string expectedStartTime = formatTime(now);
    std::string actualStartTime = breakInstance.getStartTime();

    EXPECT_EQ(actualStartTime, expectedStartTime) << "Start time should match system time at initialization";
}

// Test case: EndBreak sets endTime correctly
TEST_F(BreakTest, EndBreakSetsEndTime) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate 1 second delay
    breakInstance.endBreak();

    auto now = std::chrono::system_clock::now();
    std::string expectedEndTime = formatTime(now);
    std::string actualEndTime = breakInstance.getEndTime();

    EXPECT_EQ(actualEndTime, expectedEndTime) << "End time should match system time at termination";
}

// Test case: Duration Calculation
TEST_F(BreakTest, GetDurationAfterEnding) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate 2 seconds of break time
    breakInstance.endBreak();

    std::string duration = breakInstance.getDuration();

    EXPECT_EQ(duration, "00:00:02") << "Duration should be exactly 2 seconds";
}





