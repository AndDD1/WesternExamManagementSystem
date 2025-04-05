/**
 * @file Student.cpp
 * @brief Implementation of the Student class.
 *
 * This file implements the Student class, which extends the User class and
 * includes attributes and methods related to attendance, exam submission, seating,
 * and break management.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */

#include "Student.h"
#include <sstream>
#include <iomanip>
#include <ctime>

// Constructor
Student::Student(int ID, const std::string &name, const std::string &DOB, const std::string &pic_URL, bool isAttend, bool isSubmit)
    : User(ID, name, DOB, pic_URL), isAttend(isAttend), isSubmit(isSubmit), examVersion(0) {}

// Getter for Seat Number
std::string Student::getSeatNum() const {
    return seatNum;
}

// Setter for Seat Number
void Student::setSeatNum(const std::string &seat) {
    seatNum = seat;
}

// Getter for Exam Version
int Student::getExamVersion() const {
    return examVersion;
}

// Setter for Exam Version
void Student::setExamVersion(int version) {
    examVersion = version;
}

// Getter for Attendance
bool Student::getAttendance() const {
    return isAttend;
}

// Setter for Attendance
void Student::setAttendance(bool status) {
    isAttend = status;
}

// Start a new break (automatically records start time)
void Student::leaveForBreak() {
    Break newBreak;                 // Break Class will automatically record the current system time
    breaks.push_back(newBreak);
}

// End the last recorded break
void Student::returnFromBreak() {
    if (!breaks.empty()) {
        breaks.back().endBreak();  // Set end time for the last break
    }
}

// Get a reference to break records
std::vector<Break>* Student::getBreaksList() {
    return &breaks;
}

// Submit the exam
void Student::submitExam() {
    if (!isSubmit) {
        isSubmit = true;
        submissionTime = std::chrono::system_clock::now();
    }
}
// Getter for Submission
bool Student::getSubmissionStatus() const {
    return isSubmit;
}

// Getter for Submission Time
std::string Student::getSubmissionTime() const {
    // No End Time if still in a break
    if (!isSubmit) return "Exam in progress";
    std::time_t submissionT = std::chrono::system_clock::to_time_t(submissionTime);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&submissionT), "%H:%M:%S");
    return oss.str();
}
