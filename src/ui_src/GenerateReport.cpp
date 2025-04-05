/**
 * @file GenerateReport.cpp
 * @brief Implementation of the GenerateReport class.
 *
 * Create a report of the exam details, lists of students and proctors,
 * exam summary, and incident report
 *
 * @author Minh Pham
 * @author Andy Dai
 * @author Allen Pan
 * @version 1.2
 * @date 2025-03-29
 */

 #include "ui_header/GenerateReport.h"
 #include "ui_generatereport.h"
 #include "Exam.h"
 #include <QLabel>
 #include <QFileDialog>
 #include <QMessageBox>
 #include "Utils.h"
 #include <iostream>
 
 /**
  * @brief Constructor for GenerateReport dialog
  * 
  * @param exam Pointer to the Exam object
  * @param parent Pointer to parent widget
  */
 GenerateReport::GenerateReport(Exam* exam, QWidget *parent)
     : QDialog(parent)
     , ui(new Ui::generatereport)
     , examPtr(exam)
 {
     ui->setupUi(this);
 
     // Display Exam Details
     std::ostringstream examName;
     examName << examPtr->getCourseNum() << " - " << examPtr->getCourseNum() << " " << examPtr->getTermName();
     ui->examValueLabel->setText(QString::fromStdString(examName.str()));
     ui->roomValueLabel->setText(QString::fromStdString(examPtr->getRmNum()));
 
     std::string date = timePointToString(examPtr->getStartTime()).substr(0, 10);
     ui->dateValueLabel->setText(QString::fromStdString(date));
 
     std::string startTime = timePointToString(examPtr->getStartTime()).substr(11);
     std::string endTime = timePointToString(examPtr->getEndTime()).substr(11);
 
     ui->startTimeValueLabel->setText(QString::fromStdString(startTime));
     ui->endTimeValueLabel->setText(QString::fromStdString(endTime));
 
     populateProctors();
     populateSummary();
     populateIncidentReport();
 }
 
 /**
  * @brief Destructor for GenerateReport dialog
  */
 GenerateReport::~GenerateReport()
 {
     delete ui;
 }
 
 /**
  * @brief Populates the list of proctors in the UI
  */
 void GenerateReport::populateProctors() {
     for (Proctor &p : examPtr->getProctors()) {
         QString name = QString::fromStdString(p.getName());
         QString role = QString::fromStdString(p.getRole());
 
         QLabel *label = new QLabel(QString("- %1 (%2)").arg(name, role));
         QFont font = label->font();
         font.setPointSize(12);
         label->setFont(font);
 
         ui->ProctorsLayout->addWidget(label);
     }
 }
 
 /**
  * @brief Handles Generate Report button click (unused in this version)
  * 
  */
 void GenerateReport::onGenerateReport() {
     QMessageBox::information(this, "Generate Report", "Generating report...");
 }
 
 /**
  * @brief Populates the exam summary section in the UI
  * 
  */
 void GenerateReport::populateSummary() {
     std::vector<Student>& students = examPtr->getStudents();
     QString examEndTimeStr = timePointToQString(examPtr->getEndTime());
     QDateTime examEndDT = QDateTime::fromString(examEndTimeStr, "yyyy-MM-dd hh:mm:ss");
 
     int totalPresent = 0;
     int earlySubmission = 0;
     int totalBreaks = 0;
 
     for (Student &s : students) {
         if (s.getAttendance()) {
             totalPresent++;
         }
 
         QString submissionTimeStr = QString::fromStdString(s.getSubmissionTime());
         QDateTime submissionDT = QDateTime::fromString(submissionTimeStr, "yyyy-MM-dd hh:mm:ss");
 
         if (s.getSubmissionStatus() && submissionDT < examEndDT) {
             earlySubmission++;
         }
 
         std::vector<Break> *breaksList = s.getBreaksList();
         totalBreaks += breaksList->size();
     }
 
     ui->totalPresentValueLabel->setText(QString::number(totalPresent));
     ui->earlySubmissionsValueLabel->setText(QString::number(earlySubmission));
     ui->breaksValueLabel->setText(QString::number(totalBreaks));
 }
 
 /**
  * @brief Populates the incident report section in the UI
  * 
  */
 void GenerateReport::populateIncidentReport() {
     std::vector<std::string> incidents = examPtr->getIncidentReport();
 
     if (incidents.empty()) {
         std::cout << "None\n";
         QLabel *label = new QLabel(QString("None"));
         QFont font = label->font();
         font.setPointSize(12);
         label->setFont(font);
         ui->IncidentReport->addWidget(label);
     }
     else {
         for (std::string &s : incidents) {
             QLabel *label = new QLabel(QString::fromStdString(s));
             QFont font = label->font();
             font.setPointSize(12);
             label->setFont(font);
             ui->IncidentReport->addWidget(label);
         }
     }
 }
 
 /**
  * @brief Handles the actual report file generation and saving
  * 
  */
 void GenerateReport::on_GenerateReportButton_clicked()
 {
     std::string date = timePointToString(examPtr->getStartTime()).substr(0, 10);
 
     std::string sanitizedTermName = examPtr->getTermName();
     sanitizedTermName.erase(std::remove(sanitizedTermName.begin(), sanitizedTermName.end(), ' '), sanitizedTermName.end());
 
     std::string sanitizedCourseNum = examPtr->getCourseNum();
     sanitizedCourseNum.erase(std::remove(sanitizedCourseNum.begin(), sanitizedCourseNum.end(), ' '), sanitizedCourseNum.end());
 
     std::string fileName = "ExamReport_" + sanitizedTermName + "_" + sanitizedCourseNum + "_" + date + ".pdf";
 
     QString filePath = QFileDialog::getSaveFileName(this, "Save Report", QString::fromStdString(fileName), "PDF Files (*.pdf)");
     if (filePath.isEmpty())
         return;
 
     examPtr->generateReport(filePath.toStdString());
 
     QMessageBox::information(this, "Report Generated", "The exam report has been generated successfully!");
 }
 
 /**
  * @brief Handles close button click
  * 
  */
 void GenerateReport::on_pushButton_clicked()
 {
     this->close();
 }
 