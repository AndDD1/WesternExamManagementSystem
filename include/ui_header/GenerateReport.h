/**
 * @file GenerateReport.h
 * @brief Definition of the GenerateReport class.
 *
 * Create a report of the exam details, lists of students and proctors,
 * exam summary, and incident report
 *
 * @author Minh Pham
 * @author Andy Dai
 * @author Allen Pan
 * @version 2.1
 * @date 2025-03-29
 */
#ifndef GENERATEREPORT_H
#define GENERATEREPORT_H

#include "Exam.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
    class generatereport;
}
QT_END_NAMESPACE

class GenerateReport : public QDialog {
    Q_OBJECT

public:
    explicit GenerateReport(Exam* exam, QWidget *parent = nullptr);
    ~GenerateReport();

private slots:
    void onGenerateReport();
    void on_GenerateReportButton_clicked();
    void on_pushButton_clicked();

private:
    Ui::generatereport *ui;  // use the generated type name
    Exam* examPtr;

    /**
     * @brief A helper function to retrieve the Proctor’s data.
     */
    void populateProctors();

    /**
     * @brief A helper function to summarize the Exam.
     */
    void populateSummary();

    /**
     * @brief A helper function to display all incident reports.
     */
    void populateIncidentReport();

};

#endif // GENERATEREPORT_H

