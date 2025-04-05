/**
 * @file Exam.cpp
 * @brief Definition of the Exam class.
 *
 * This file defines the Exam class, which contains all the attributes and methods of the
 * exam including examRm, courseNum, examReport, Students, Proctors, etc.
 *
 * @author Minh Pham
 * @author Allen Pan
 * @author Kohei Kubota
 * @version 1.4
 * @date 2025-03-24
 */


#ifndef EXAM_H
#define EXAM_H

#include "Student.h"
#include "Proctor.h"
#include <string>
#include <vector>
#include <chrono>

class Exam {
private:
    std::string examData_URL;
    int termNum;
    std::string termName;
    std::string courseNum;
    std::string rmNum;
    int capacity;
    std::vector<std::vector<bool> > seatMap;
    int maxRow;
    int maxCol;
    int numVersions;
    std::vector<int> versionsCode;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
    std::string examReport_URL;
    std::vector<Student> students;
    std::vector<Proctor> proctors;
    std::vector<std::string> incidentReport;
    std::vector<int> studentsInBreak;
    int totalPresent;

public:
    /**
     * @brief Constructs a new Exam object with default values.
     */
    Exam();

    /**
     * @brief Loads exam data from the specified file path.
     * @author Allen Pan
     *
     * @param path The file path to load the exam data from.
     * @return true if loading is successful, false otherwise.
     */
    bool loadFromFile(const std::string &path);

    /**
     * @brief Adds a proctor to the exam session.
     * @author Allen Pan
     *
     * @param p The Proctor object to be added.
     */
    void addProctor(const Proctor &p);

    /**
     * @brief Adds a student to the exam session.
     *
     * @param s The Student object to be added.
     */
    void addStudent(const Student &s);

    /**
     * @brief Sets the URL for exam data resources.
     *
     * @param url The string representing the URL.
     */
    void setExamDataURL(const std::string &url);

    /**
     * @brief Initializes the seat map for student seating assignments.
     *
     * This function sets up the seating layout according to the exam configuration.
     */
    void initializeSeatMap();

    /**
     * @brief Checks if a student with the specified ID exists in the exam session.
     * @author Allen Pan
     *
     * @param id The student ID to look for.
     * @return true if the student is found, false otherwise.
     */
    bool hasStudent(int id);

    /**
     * @brief Checks if a proctor with the specified ID exists in the exam session.
     * @author Allen Pan
     *
     * @param id The proctor ID to look for.
     * @return true if the proctor is found, false otherwise.
     */
    bool hasProctor(int id);

    /**
     * @brief load an Exam object and read from the input file.
     *
     * The loader reads from examData.txt for term number, term name, course number,
     * lists of Students and Instructors, etc.
     */
    bool loadData(const std::string &dataPath);

    /**
     * @brief Retrieves the term number of the exam
     *
     * @return The term number as an int.
     */
    int getTermNum() const;

    /**
     * @brief Sets the term number of the exam.
     *
     * @param termNum The term number to assign to the exam.
     */
    void setTermNum(int termNum);

    /**
     * @brief Retrieves the term name of the exam
     *
     * @return The term name as a string.
     */
    std::string getTermName() const;

    /**
     * @brief Sets the term name of the exam.
     *
     * @param termName The term name to assign to the exam.
     */
    void setTermName(const std::string &termName);

    /**
     * @brief Retrieves the course number of the exam
     *
     * @return The course number as an int.
     */
    std::string getCourseNum() const;

    /**
     * @brief Sets the course number of the exam.
     *
     * @param courseNum The course number to assign to the exam.
     */
    void setCourseNum(std::string courseNum);

    /**
     * @brief Retrieves the room number of the exam
     *
     * @return The room number as a string.
     */
    std::string getRmNum() const;

    /**
     * @brief Sets the room number of the exam.
     *
     * @param rmNum The room number to assign to the exam.
     */
    void setRmNum(const std::string &rmNum);

    /**
     * @brief Retrieves the exam room's capacity
     *
     * @return The capacity as an int.
     */
    int getCapacity() const;

    /**
     * @brief Sets the exam room's capacity.
     *
     * @param capacity The room's capacity to assign to the exam.
     */
    void setCapacity(int capacity);

    /**
     * @brief Retrieves the max number of row of the exam room
     *
     * @return The max number of row as an int.
     */
    int getMaxRow() const;

    /**
     * @brief Sets the max number of row of the exam room
     *
     * @param row The number of row the exam room.
     */
    void setMaxRow(int row);

    /**
     * @brief Retrieves the max number of column of the exam room
     *
     * @return The max number of column as an int.
     */
    int getMaxCol() const;

    /**
     * @brief Sets the max number of column of the exam room
     *
     * @param col The number of column the exam room.
     */
    void setMaxCol(int col);

    /**
     * @brief Retrieves the number of exam versions
     *
     * @return The number of exam versions as an int.
     */
    int getNumVersions() const;

    /**
     * @brief Sets the number of exam versions
     *
     * @param num Number of exam versions.
     */
    void setNumVersions(int num);

    /**
     * @brief Retrieves all the exam version codes
     *
     * @return All the exam version as a vector of int.
     */
    std::vector<int> getVersionsCode() const;

    /**
     * @brief Sets the exam version codes
     *
     * @param codes The code to assign to an exam version.
     */
    void setVersionsCode(std::vector<int> codes);

    /**
     * @brief Retrieves the formatted start time of the exam.
     *
     * @return The start time as a system_clock::timepoint.
     */
    std::chrono::system_clock::time_point getStartTime() const;

    /**
     * @brief Sets the formatted start time of the exam.
     *
     * @param startTime The start time of the exam.
     */
    void setStartTime(const std::chrono::system_clock::time_point &startTime);

    /**
     * @brief Retrieves the formatted end time of the exam.
     *
     * @return The end time as a system_clock::timepoint.
     */
    std::chrono::system_clock::time_point getEndTime() const;

    /**
     * @brief Sets the formatted end time of the exam.
     *
     * @param endTime The end time of the exam.
     */
    void setEndTime(const std::chrono::system_clock::time_point &endTime);

    /**
     * @brief Retrieves all the students attending the exam.
     *
     * @return All the students as a vector of Students.
     */
    std::vector<Student> &getStudents();

    /**
     * @brief Retrieves all the proctors of the exam.
     *
     * @return All the proctors as a vector of Proctors.
     */
    std::vector<Proctor> &getProctors();

    /**
     * @brief Retrieves the real number of students showed up.
     *
     * @return The number of attended students as an int.
     */
    int getTotalPresent() const;

    /**
     * @brief Sets the real number of students showed up.
     *
     * @param totalPresent The number of attended students.
     */
    void setTotalPresent(int totalPresent);

    /**
     * @brief Retrieves every incident report during the exam.
     *
     * @return The incident report as a vector of string.
     */
    std::vector<std::string> getIncidentReport() const;

    /**
     * @brief Gets the URL of the exam report.
     * @author Allen Pan
     *
     * @return A string containing the URL where the exam report is stored.
     */
    std::string getReportURL() const;

    /**
     * @brief Retrieves a pointer to a student by their ID.
     * @author Allen Pan
     *
     * @param studentID The ID of the student to retrieve.
     * @return A pointer to the Student object if found, otherwise nullptr.
     */
    Student *getStudentByID(int studentID);


    /**
     * @brief Checking in Students.
     *
     * @param studentID The student to check in.
     */
    Student *checkIn(int studentID);

    /**
     * @brief Adding washroom break to student.
     *
     * @param studentID The student having a break.
     */
    std::string washroomBreak(int studentID);

    /**
     * @brief Submit a student's exam early
     *
     * @param studentID The student submitting their exam early.
     * @return True if submission is recorded.
     */
    bool earlySubmission(int studentID);

    /**
     * @brief Submit all remaining students' exam when the time ends.
     *
     */
    void endOfTimeSubmission();

    void generateReport(const std::string &fileName);

    /**
     * @brief Log in an academic incident that happens during the exam
     *
     * @param studentID The student that is involved in the incident
     * @param proctorID The proctor that reports the incident
     * @param incidentMsg Report of the incident
     */
    void writeIncident(int studentID, int proctorID, const std::string &incidentMsg);
    bool isOnBreak(int studentID) const;


};


#endif //EXAM_H
