/**
 * @file Student.cpp
 * @brief Definition of the Student class.
 *
 * This file defines the Student class, which extends the User class and
 * includes attributes and methods related to attendance, exam submission, seating,
 * and break management.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */

#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Break.h"
#include <vector>

class Student : public User {
private:
    std::string seatNum;          // Assigned seat number
    int examVersion;              // Exam booklet version
    bool isAttend;                // Attendance status
    bool isSubmit;                // Exam submission status
    std::vector<Break> breaks;    // Record of student's breaks
    std::chrono::system_clock::time_point submissionTime;  // Student's submission time

public:
    /**
     * @brief Constructs a Student object with the specified attributes.
     *
     * This constructor initializes a Student object by calling the base class User constructor
     * and setting the student's attendance status, submission status, and initializing exam version.
     *
     * @param ID The unique identifier of the student.
     * @param name The name of the student.
     * @param DOB The date of birth of the student.
     * @param pic_URL The URL of the student's profile picture.
     * @param isAttend A boolean indicating whether the student is present.
     * @param isSubmit A boolean indicating whether the student has submitted the exam.
     */
    Student(int ID, const std::string &name, const std::string &DOB, const std::string &pic_URL, bool isAttend = false, bool isSubmit = false);

    /**
     * @brief Retrieves the student's seat number.
     *
     * @return A string representing the seat number of the student.
     */
    std::string getSeatNum() const;

    /**
     * @brief Sets the seat number for the student.
     *
     * @param seat The seat number to assign to the student.
     */
    void setSeatNum(const std::string &seat);


    /**
     * @brief Retrieves the student's assigned exam version.
     *
     * @return An integer representing the exam version assigned to the student.
     */
    int getExamVersion() const;

    /**
     * @brief Sets the exam version for the student.
     *
     * @param version The exam version number to assign.
     */
    void setExamVersion(int version);

    /**
     * @brief Retrieves the student's attendance status.
     *
     * @return A boolean indicating whether the student is present.
     */
    bool getAttendance() const;

    /**
     * @brief Sets the student's attendance status.
     *
     * @param status A boolean indicating the attendance status of the student.
     */
    void setAttendance(bool status);

    /**
     * @brief Records the start of a washroom break.
     *
     * This function creates a new Break object and adds it to the student's break records.
     * The Break object automatically records the current system time as the start time.
     */
    void leaveForBreak();

    /**
     * @brief Ends the last recorded break.
     *
     * This function sets the end time of the last recorded break.
     * If there are no recorded breaks, this function does nothing.
     */
    void returnFromBreak();


    /**
     * @brief Retrieves the list of breaks taken by the student.
     *
     * @return A pointer to a vector containing the student's break records.
     */
    std::vector<Break>* getBreaksList();


    /**
     * @brief Submits the exam for the student.
     *
     * This function marks the student's exam as submitted if it has not already been submitted.
     */
    void submitExam();

    /**
     * @brief Retrieves the student's exam submission status.
     *
     * @return A boolean indicating whether the student has submitted the exam.
     */
    bool getSubmissionStatus() const;

    /**
     * @brief Retrieves the student's exam submission time.
     *
     * @return A string representing the submission time.
     */
    std::string getSubmissionTime() const;
};

#endif // STUDENT_H
