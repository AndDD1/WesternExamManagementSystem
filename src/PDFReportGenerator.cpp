/**
 * @file PDFReportGenerator.cpp
 * @brief This class uses the libharu library to generate a well-formatted PDF file.
 *
 * Create a report of the exam details, lists of students and proctors,
 * exam summary, and incident report
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-04-01
 */
#include "PDFReportGenerator.h"
#include <hpdf.h>
#include <iostream>
#include <iomanip>
#include <sstream>

void PDFReportGenerator::generate(const std::string &fileName,
                                  const std::string &courseNum,
                                  const std::string &termNum,
                                  const std::string &termName,
                                  const std::string &room,
                                  const std::string &examDate,
                                  const std::string &startTimeStr,
                                  const std::string &endTimeStr,
                                  const std::vector<Student> &students,
                                  const std::vector<Proctor> &proctors,
                                  const std::vector<std::string> &incidentReport) {
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf) {
        std::cerr << "Failed to create PDF object\n";
        return;
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_LETTER, HPDF_PAGE_LANDSCAPE);
    HPDF_Page_SetFontAndSize(page, HPDF_GetFont(pdf, "Courier", NULL), 10);

    float x = 40;
    float y = HPDF_Page_GetHeight(page) - 40;
    const float lineSpacing = 14;

    auto printLine = [&](const std::string &text) {
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, x, y, text.c_str());
        HPDF_Page_EndText(page);
        y -= lineSpacing;
        if (y < 40) {
            page = HPDF_AddPage(pdf);
            HPDF_Page_SetFontAndSize(page, HPDF_GetFont(pdf, "Courier", NULL), 10);
            y = HPDF_Page_GetHeight(page) - 40;
        }
    };

    auto formatField = [](const std::string &text, size_t width) {
        std::ostringstream oss;
        if (text.length() > width)
            oss << text.substr(0, width);
        else
            oss << std::left << std::setw(width) << text;
        return oss.str();
    };

    // Header
    printLine("Exam Report: CS" + courseNum + " - " + termNum + " " + termName);
    printLine("Room: " + room);
    printLine("Date: " + examDate);
    printLine("Start: " + startTimeStr + " | End: " + endTimeStr);
    printLine("");

    // Proctor info
    printLine("Proctors:");
    for (const Proctor &p : proctors) {
        printLine("- " + p.getName() + " (" + p.getRole() + ")");
    }
    printLine("");

    // Table header
    printLine("Students:");
    printLine(formatField("ID", 11) + formatField("Name", 30) + formatField("Attend", 10) +
              formatField("Seat", 15) + formatField("Version", 10) + formatField("Submission", 18) + "Breaks");

    int totalPresent = 0;
    int totalSubmitted = 0;
    int totalBreaks = 0;

    for (Student &s : const_cast<std::vector<Student>&>(students)) {

        std::string id = std::to_string(s.getID());
        std::string name = s.getName();
        std::string attendance = s.getAttendance() ? "Present" : "Absent";
        if (s.getAttendance()) totalPresent++;

        std::string seat = s.getSeatNum();
        if (seat.empty()) {
            seat = "--";
        } else {
            size_t rowPos = seat.find("Row: ");
            if (rowPos != std::string::npos) {
                seat.replace(rowPos, 4, "R");
            }
            size_t colPos = seat.find("Colum: ");
            if (colPos != std::string::npos) {
                seat.replace(colPos, 7, "C");
            }
        }


        std::string version = (s.getExamVersion() == 0) ? "N/A" : std::to_string(s.getExamVersion());
        std::string submission = s.getSubmissionStatus() ? "Submitted" : "Not Submitted";
        if (s.getSubmissionStatus()) totalSubmitted++;

        std::string breaksStr;
        std::vector<Break> *breaks = s.getBreaksList();
        if (breaks->empty()) {
            breaksStr = "---";
        } else {
            for (const Break &br : *breaks) {
                breaksStr += "[" + br.getStartTime() + "-" + br.getEndTime() + "] ";
                totalBreaks++;
            }
        }

        printLine(formatField(id, 11) + formatField(name, 30) + formatField(attendance, 10) +
                  formatField(seat, 15) + formatField(version, 10) + formatField(submission, 18) + breaksStr);
    }

    // Summary
    printLine("");
    printLine("Summary:");
    printLine("- Total Present: " + std::to_string(totalPresent));
    printLine("- Total Submitted: " + std::to_string(totalSubmitted));
    printLine("- Total Breaks Taken: " + std::to_string(totalBreaks));

    // Incidents
    printLine("");
    printLine("Incident Report:");
    if (incidentReport.empty()) {
        printLine("None");
    } else {
        for (const std::string &r : incidentReport) {
            printLine("- " + r);
        }
    }

    HPDF_SaveToFile(pdf, fileName.c_str());
    HPDF_Free(pdf);

    std::cout << "PDF Report generated: " << fileName << std::endl;
}
