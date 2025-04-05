/**
 * @file PDFReportGenerator.h
 * @brief This class uses the libharu library to generate a well-formatted PDF file.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-04-01
 */
#ifndef PDFREPORTGENERATOR_H
#define PDFREPORTGENERATOR_H

#include <string>
#include <vector>
#include "Student.h"
#include "Proctor.h"

/**
 * @class PDFReportGenerator
 * @brief Utility class for generating a PDF report of an exam session.
 *
 * This class uses the libharu library to generate a well-formatted PDF file containing
 * information about students, proctors, exam timing, seating, attendance, and incidents.
 */
class PDFReportGenerator {
public:
    /**
     * @brief Generates a PDF report for the exam session.
     *
     * This static method writes a structured PDF report summarizing exam details including
     * student attendance, seating assignments, version distribution, submission statuses,
     * and any reported incidents.
     *
     * @param fileName The name (with path) of the output PDF file.
     * @param courseNum The course number (e.g., "3307").
     * @param termNum The term number or identifier (e.g., "1229").
     * @param termName The name of the academic term (e.g., "Winter 25").
     * @param room The exam room identifier (e.g., "AH-STAGE").
     * @param examDate
     * @param startTimeStr The start time of the exam in string format (e.g., "13:30").
     * @param endTimeStr The end time of the exam in string format (e.g., "16:30").
     * @param students A list of Student objects participating in the exam.
     * @param proctors A list of Proctor objects managing the exam session.
     * @param incidentReport A list of incident descriptions recorded during the exam.
     */
    static void generate(const std::string &fileName,
                         const std::string &courseNum,
                         const std::string &termNum,
                         const std::string &termName,
                         const std::string &room,
                         const std::string &examDate,
                         const std::string &startTimeStr,
                         const std::string &endTimeStr,
                         const std::vector<Student> &students,
                         const std::vector<Proctor> &proctors, const std::vector<std::string> &incidentReport);
};

#endif
