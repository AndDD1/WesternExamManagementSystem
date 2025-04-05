/**
 * @file SubmissionDialog.h
 * @brief Definition of the SubmissionDialog class.
 *
 * This file contains the declaration of the SubmissionDialog class.
 * It allows the user to enter a student number to mark their exam as completed.
 *
 * @author Andy Dai
 * @author Allen Pan
 * @version 1.2
 * @date 2025-03-29
 */
#ifndef SUBMISSIONDIALOG_H
#define SUBMISSIONDIALOG_H

#include <QDialog>

class Exam;
class QLineEdit;   ///< Forward declaration for QLineEdit
class QPushButton; ///< Forward declaration for QPushButton


/**
 * @brief Dialog for exam submission.
 *
 * This dialog allows a student to submit their exam by entering their student number.
 */
class SubmissionDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Constructs a SubmissionDialog.
     * @param exam Pointer to the Exam object.
     * @param parent Pointer to the parent widget.
     */
    explicit SubmissionDialog(class Exam* exam, QWidget* parent = nullptr);

private slots:
    /**
     * @brief Slot called when the "Submit Exam" button is clicked.
     *
     * Validates input, logs submission, and displays confirmation with a timestamp.
     */
    void onSubmitExam();

private:
    class Exam* examPtr;               ///< Pointer to the Exam object.
    QLineEdit* studentNumberLineEdit;  ///< Line edit for entering the student number.
    QPushButton* submitButton;         ///< Button to submit the exam.
};

#endif // SUBMISSIONDIALOG_H
