/**
 * @file StudentTest.cpp
 * @brief Unit tests for the Student class.
 *
 * This file contains Google Test cases for the Student class, verifying
 * proper initialization, seat assignment, attendance tracking, break
 * management, and exam submission functionality.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */

#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <gtest/gtest.h>
#include "Student.h"
#include "timeFormator.h"



// Test fixture for Student class
class StudentTest : public ::testing::Test, public timeFormator {
protected:
    Student student{1, "Alice", "2002-09-15", "https://example.com/alice.jpg", false, false};
};

// Test case: Constructor initializes values correctly
TEST_F(StudentTest, ConstructorInitialization) {
    EXPECT_EQ(student.getID(), 1);
    EXPECT_EQ(student.getName(), "Alice");
    EXPECT_EQ(student.getDOB(), "2002-09-15");
    EXPECT_EQ(student.getPicURL(), "https://example.com/alice.jpg");
    EXPECT_EQ(student.getAttendance(), false);
    EXPECT_EQ(student.getExamVersion(), 0); // Default value
    EXPECT_EQ(student.getBreaksList()->size(), 0);
}

// Test case: Seat Number Getter and Setter
TEST_F(StudentTest, SeatNumberGetterSetter) {
    student.setSeatNum("R12C10");
    EXPECT_EQ(student.getSeatNum(), "R12C10");
}

// Test case: Exam Version Getter and Setter
TEST_F(StudentTest, ExamVersionGetterSetter) {
    student.setExamVersion(333);
    EXPECT_EQ(student.getExamVersion(), 333);
}

// Test case: Attendance Getter and Setter
TEST_F(StudentTest, AttendanceGetterSetter) {
    student.setAttendance(true);
    EXPECT_TRUE(student.getAttendance());
}

// Test case: Leave for Break (Start a new break)
TEST_F(StudentTest, LeaveForBreak) {
    student.leaveForBreak();
    EXPECT_EQ(student.getBreaksList()->size(), 1);
}

// Test case: Return from Break (End the last break)
TEST_F(StudentTest, ReturnFromBreak) {
    student.leaveForBreak();
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate break time
    student.returnFromBreak();

    EXPECT_EQ(student.getBreaksList()->size(), 1);
    EXPECT_FALSE(student.getBreaksList()->back().getEndTime().empty());
}

// Test case: Exam Submission Time Record
TEST_F(StudentTest, ExamSubmission) {
    EXPECT_FALSE(student.getSubmissionStatus());  // Initially, should be false
    student.submitExam();

    auto now = std::chrono::system_clock::now();
    std::string expectedSubmitTime = formatTime(now);
    std::string actualSubmitTime = student.getSubmissionTime();

    EXPECT_EQ(actualSubmitTime, expectedSubmitTime) << "Submission time should match current time";
    EXPECT_TRUE(student.getSubmissionStatus());   // After submitting, should be true
}


