/**
 * @file SubmissionDialog.cpp
 * @brief Implements the SubmissionDialog class.
 *
 * This file defines the SubmissionDialog class which provides a popup dialog for exam submission.
 * It prompts the user to enter their student number, and logs the exam submission if the current 
 * time is within the exam period. If the current time is outside the exam period, the submit button
 * is disabled.
 *
 * @author Andy Dai
 * @author Allen Pan
 * @version 1.2
 * @date 2025-03-29
 */

#include "../../include/ui_header/SubmissionDialog.h"
#include "../../include/Exam.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDateTime>
#include <chrono>

/**
 * @brief Constructs the SubmissionDialog.
 * @param exam Pointer to the Exam object.
 * @param parent Pointer to the parent widget.
 *
 * Sets up the UI and disables the "Submit Exam" button if the current time is outside
 * of the exam's scheduled start and end times.
 */
SubmissionDialog::SubmissionDialog(Exam* exam, QWidget* parent)
    : QDialog(parent), examPtr(exam)
{
    setWindowTitle("Exam Submission");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* promptLabel = new QLabel("Enter Student Number:", this);
    mainLayout->addWidget(promptLabel);

    studentNumberLineEdit = new QLineEdit(this);
    mainLayout->addWidget(studentNumberLineEdit);

    submitButton = new QPushButton("Submit Exam", this);
    mainLayout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &SubmissionDialog::onSubmitExam);
}


/**
 * @brief Handles the student's exam submission.
 *
 * Validates the input student number, checks if the student exists and has not already submitted,
 * and records the submission via the Student object. Displays appropriate messages based on the result.
 */
void SubmissionDialog::onSubmitExam() {
    // Get the current time and validate it's within the exam period
    auto now = std::chrono::system_clock::now();
    if (now < examPtr->getStartTime()) {
        QMessageBox::warning(this, "Time Error", "Submissions are not allowed outside the exam period.");
        submitButton->setEnabled(false);
        return;
    }

    if (now > examPtr->getEndTime()) {
        QMessageBox::warning(this, "Exam has Ended", "All exams has been marked as submitted. ");
        examPtr->endOfTimeSubmission();
        return;
    }

    // Read and validate student number input
    QString studentNumberStr = studentNumberLineEdit->text().trimmed();
    if (studentNumberStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a student number.");
        return;
    }

    bool ok;
    int studentNumber = studentNumberStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Invalid student number format.");
        return;
    }

    // Look up student using Exam::getStudentByID
    Student* student = examPtr->getStudentByID(studentNumber);

    if (!student) {
        QMessageBox::information(this, "Submission Failed",
            QString("Student %1 does not exist.").arg(studentNumber));
        return;
    }

    if (student->getAttendance() && !student->getSubmissionStatus()) {
        student->submitExam();

        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QMessageBox::information(this, "Submission Confirmed",
            QString("Exam submission logged for student %1 at %2.")
                .arg(studentNumber)
                .arg(timestamp));
    } else if (student->getSubmissionStatus()) {
        QMessageBox::information(this, "Submission Failed",
            QString("Exam has already been submitted for student %1.").arg(studentNumber));
    } else {
        QMessageBox::information(this, "Submission Failed",
            QString("Student %1 has not checked in.").arg(studentNumber));
    }

    accept(); // Close the dialog
}

