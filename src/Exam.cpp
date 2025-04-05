/**
 * @file Exam.cpp
 * @brief Implementation of the Student class.
 *
 * This file implements the Exam class, which contains all the attributes and methods of the
 * exam including examRm, courseNum, examReport, Students, Proctors, etc.
 *
 * @author Minh Pham
 * @author Allen Pan
 * @author Kohei Kubota
 * @author Andy Dai
 * @version 1.6
 * @date 2025-03-24
 */

#include "../include/Exam.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <iomanip>    // for std::get_time and std::put_time
#include <sstream>
#include "Utils.h"
#include "../include/ExamDataLoader.h"
#include "PDFReportGenerator.h"

// Constructor
Exam::Exam() {
}

bool Exam::loadFromFile(const std::string &path) {
    return ExamDataLoader::loadExamData(path, *this);
}

bool Exam::isOnBreak(int studentID) const { // NEW
    auto it = std::find(studentsInBreak.begin(), studentsInBreak.end(), studentID);
    return (it != studentsInBreak.end());
}

void Exam::addProctor(const Proctor &p) {
    for (const auto &existing: proctors) {
        if (existing.getID() == p.getID()) return; // skip if already added
    }
    proctors.push_back(p);
}


void Exam::addStudent(const Student &s) {
    for (const auto &existing: students) {
        if (existing.getID() == s.getID()) return;
    }
    students.push_back(s);
}

void Exam::setExamDataURL(const std::string &url) {
    examData_URL = url;
}

void Exam::initializeSeatMap() {
    seatMap = std::vector<std::vector<bool> >(maxRow, std::vector<bool>(maxCol, false));
}


/**
 * @brief Retrieves a pointer to a student by their ID.
 * 
 * Iterates through the list of students and returns a pointer to the student 
 * whose ID matches the given studentID.
 * 
 * @param studentID The unique identifier of the student.
 * @return Pointer to the matching Student object, or nullptr if not found.
 */
 Student *Exam::getStudentByID(int studentID) {
    for (Student &s : students) {
        if (s.getID() == studentID) {
            return &s;
        }
    }
    return nullptr;
}

/**
 * @brief Checks in a student by their ID.
 * 
 * Searches for the student using the provided studentID. If the student exists
 * and hasn't already checked in, assigns an available seat and exam version, marks 
 * attendance, and returns a pointer to the student. Otherwise, logs an error message.
 * 
 * @param studentID The unique identifier of the student to check in.
 * @return Pointer to the Student object after successful check-in, or nullptr on failure.
 */
Student *Exam::checkIn(int studentID) {
    Student *s = getStudentByID(studentID);
    if (!s) {
        std::cerr << "Student ID not found: " << studentID << std::endl;
        return nullptr;
    }

    if (s->getAttendance()) {
        std::cout << "Student already checked in.\n";
        return nullptr;
    }

    // Assign first available seat
    bool seatAssigned = false;
    for (int row = 0; row < maxRow && !seatAssigned; ++row) {
        for (int col = 0; col < maxCol; ++col) {
            if (!seatMap[row][col]) {
                std::string seatLabel = "Row: " + std::to_string(row + 1) +
                                        "\nColum: " + std::to_string(col + 1);
                s->setSeatNum(seatLabel);
                seatMap[row][col] = true;
                seatAssigned = true;
                break;
            }
        }
    }

    if (!seatAssigned) {
        std::cerr << "No available seat for student.\n";
        return nullptr;
    }

    // Assign version
    totalPresent++;
    int versionIndex = studentID % numVersions;
    s->setExamVersion(versionsCode.at(versionIndex));

    // Mark attendance
    s->setAttendance(true);

    std::cout << "Student " << studentID << " checked in successfully.\n";
    return s;
}

/**
 * @brief Processes a washroom break request for a student.
 * 
 * Determines if the current time is within the allowed break window. If the 
 * student is eligible for a break, toggles the break status (entering or returning 
 * from break) and returns a message indicating the action and timestamps. Otherwise, 
 * returns an error message.
 * 
 * @param studentID The unique identifier of the student requesting a break.
 * @return A message string describing the result of the break request.
 */
std::string Exam::washroomBreak(int studentID) {
    using namespace std::chrono;

    // Get current time and define break window
    system_clock::time_point now = system_clock::now();
    system_clock::time_point earliestBreak = startTime + minutes(30);
    system_clock::time_point latestBreak = endTime - minutes(15);

    if (now < earliestBreak) {
        auto waitDuration = duration_cast<seconds>(earliestBreak - now);
        int minutesLeft = waitDuration.count() / 60;
        int secondsLeft = waitDuration.count() % 60;

        std::ostringstream oss;
        oss << "Washroom break not allowed: Exam started less than 30 minutes ago.\n"
            << "Please wait for " << std::setw(2) << std::setfill('0') << minutesLeft
            << ":" << std::setw(2) << std::setfill('0') << secondsLeft << " (MM:SS)";
        return oss.str();
    }

    if (now > latestBreak) {
        return "Washroom break not allowed: Within the last 15 minutes of the exam.";
    }

    // Lookup student
    Student* student = getStudentByID(studentID);
    if (!student || !student->getAttendance() || student->getSubmissionStatus()) {
        return "Invalid student number or student is ineligible for a break.";
    }

    auto it = std::find(studentsInBreak.begin(), studentsInBreak.end(), studentID);
    if (it != studentsInBreak.end()) {
        student->returnFromBreak();
        studentsInBreak.erase(it);
        Break* lastBreak = student->getBreaksList()->empty() ? nullptr : &student->getBreaksList()->back();

        return "Student: " + student->getName() + " (" + std::to_string(studentID) + ") Returned from break.\n\n" +
               "You left at " + lastBreak->getStartTime() +
               "\nYou returned at " + lastBreak->getEndTime() +
               "\nTotal time of " + lastBreak->getDuration();
    } else {
        student->leaveForBreak();
        studentsInBreak.push_back(studentID);
        Break* currentBreak = student->getBreaksList()->empty() ? nullptr : &student->getBreaksList()->back();

        return "Student: " + student->getName() + " (" + std::to_string(studentID) + ") Leaving for break.\n\n" +
               "You leave at " + currentBreak->getStartTime();
    }
}

/**
 * @brief Logs an incident involving a student and a proctor.
 * 
 * Formats and appends an incident report message to the internal incident log.
 * Optionally prints the incident message to the console for debugging purposes.
 * 
 * @param studentID The unique identifier of the student involved.
 * @param proctorID The unique identifier of the proctor involved.
 * @param incidentMsg A description of the incident.
 */
void Exam::writeIncident(int studentID, int proctorID, const std::string &incidentMsg) {
    // Log the incident
    std::ostringstream report;
    report << "Student: " << studentID
           << "; Proctor: " << proctorID
           << "; Message: " << incidentMsg << std::endl;

    incidentReport.push_back(report.str());
    std::cout << report.str(); // Optional: for debug logging
}

/**
 * @brief Checks if a student with the given ID exists.
 * 
 * Iterates through the students to determine if any student's ID matches the given id.
 * 
 * @param id The unique identifier of the student.
 * @return True if a student with the specified ID exists, false otherwise.
 */
bool Exam::hasStudent(int id) {
    return std::any_of(students.begin(), students.end(),
                       [id](Student &s) { return s.getID() == id; });
}

/**
 * @brief Checks if a proctor with the given ID exists.
 * 
 * Iterates through the proctors to determine if any proctor's ID matches the given id.
 * 
 * @param id The unique identifier of the proctor.
 * @return True if a proctor with the specified ID exists, false otherwise.
 */
bool Exam::hasProctor(int id) {
    return std::any_of(proctors.begin(), proctors.end(),
                       [id](Proctor &p) { return p.getID() == id; });
}

/**
 * @brief Processes an early exam submission for a student.
 * 
 * Checks if the student exists, has attended the exam, and has not already submitted.
 * If so, the student's exam is submitted.
 * 
 * @param studentID The unique identifier of the student.
 * @return True if the submission was processed successfully, false otherwise.
 */
bool Exam::earlySubmission(int studentID) {
    // Submit the exam
    for (Student &s : students) {
        if (s.getID() == studentID && s.getAttendance() && !s.getSubmissionStatus()) {
            s.submitExam();
            return true;
        }
    }
    return false;
}

/**
 * @brief Processes exam submissions when time expires.
 * 
 * Iterates through all students and submits the exam for those who have attended but have not yet submitted.
 */
void Exam::endOfTimeSubmission() {
    for (Student &s : students) {
        // Only set final submission time for students who attended and haven't submitted
        if (s.getAttendance() && !s.getSubmissionStatus()) {
            s.submitExam();
        }
    }
}

/**
 * @brief Generates a report for the exam session.
 * 
 * Converts the exam start and end times to string format, extracts relevant date and time information, 
 * and invokes the PDFReportGenerator to create a report including course details, student and proctor lists,
 * and incident reports.
 * 
 * @param fileName The name (or path) of the file to generate the report.
 */
void Exam::generateReport(const std::string &fileName) {
    std::string startTimeStr = timePointToString(startTime);
    std::string endTimeStr = timePointToString(endTime);
    std::string examDate = startTimeStr.substr(0, 10);
    std::string examStart = startTimeStr.substr(11, 5);
    std::string examEnd = endTimeStr.substr(11, 5);

    PDFReportGenerator::generate(
        fileName,
        courseNum,
        std::to_string(termNum),
        termName,
        rmNum,
        examDate,
        examStart,
        examEnd,
        students,
        proctors,
        incidentReport
    );
}


// Getter and Setter for termNum
int Exam::getTermNum() const {
    return termNum;
}

void Exam::setTermNum(int termNum) {
    this->termNum = termNum;
}

// Getter and Setter for termName
std::string Exam::getTermName() const {
    return termName;
}

void Exam::setTermName(const std::string &termName) {
    this->termName = termName;
}

// Getter and Setter for courseNum
std::string Exam::getCourseNum() const {
    return courseNum;
}

void Exam::setCourseNum(std::string courseNum) {
    this->courseNum = courseNum;
}

// Getter and Setter for rmNum
std::string Exam::getRmNum() const {
    return rmNum;
}

void Exam::setRmNum(const std::string &rmNum) {
    this->rmNum = rmNum;
}

// Getter and Setter for capacity
int Exam::getCapacity() const {
    return capacity;
}

void Exam::setCapacity(int capacity) {
    this->capacity = capacity;
}

// Getter and Setter for maxRow
int Exam::getMaxRow() const {
    return maxRow;
}

void Exam::setMaxRow(int row) {
    maxRow = row;
}

// Getter and Setter for maxCol
int Exam::getMaxCol() const {
    return maxCol;
}

void Exam::setMaxCol(int col) {
    maxCol = col;
}

// Getter and Setter for numVersions
int Exam::getNumVersions() const {
    return numVersions;
}

void Exam::setNumVersions(int numVersions) {
    this->numVersions = numVersions;
}

// Getter and Setter for versionsCode
std::vector<int> Exam::getVersionsCode() const {
    return versionsCode;
}

void Exam::setVersionsCode(std::vector<int> codes) {
    this->versionsCode = codes;
}

// Getter and Setter for startTime
std::chrono::system_clock::time_point Exam::getStartTime() const {
    return startTime;
}

void Exam::setStartTime(const std::chrono::system_clock::time_point &startTime) {
    this->startTime = startTime;
}

// Getter and Setter for endTime
std::chrono::system_clock::time_point Exam::getEndTime() const {
    return endTime;
}

void Exam::setEndTime(const std::chrono::system_clock::time_point &endTime) {
    this->endTime = endTime;
}

// Getter for examReport_URL
std::string Exam::getReportURL() const {
    return examReport_URL;
}

std::vector<Student> &Exam::getStudents() {
    return students;
}

std::vector<Proctor> &Exam::getProctors() {
    return proctors;
}

int Exam::getTotalPresent() const {
    return totalPresent;
}

void Exam::setTotalPresent(int totalPresent) {
    this->totalPresent = totalPresent;
}

std::vector<std::string> Exam::getIncidentReport() const {
    return incidentReport;
}
