/**
 * @file IncidentDialog.cpp
 * @brief Constructs the IncidentDialog.
 *
 * Initializes a dialog for logging exam-related incidents.
 * Allows the TA or instructor to enter a student ID, proctor ID, and a description of the incident.
 * Includes OK and Cancel buttons to confirm or discard the entry.
 *
 * @author Allen Pan
 * @author Andy Dai
 * @version 1.0
 * @date 2025-03-30
 */
#include "../include/ui_header/IncidentDialog.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QTextEdit>

/**
 * @brief Constructor for IncidentDialog
 * 
 * @param parent Pointer to parent widget
 */
IncidentDialog::IncidentDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Log Exam Incident");

    studentIDEdit = new QLineEdit(this);
    proctorIDEdit = new QLineEdit(this);
    messageEdit = new QTextEdit(this);

    QFormLayout* layout = new QFormLayout;
    layout->addRow("Student ID:", studentIDEdit);
    layout->addRow("Proctor ID:", proctorIDEdit);
    layout->addRow("Incident Message:", messageEdit);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    setLayout(layout);
}

/**
 * @brief Gets the entered student ID
 * 
 * @return int The student ID as integer
 */
int IncidentDialog::getStudentID() const {
    return studentIDEdit->text().toInt();
}

/**
 * @brief Gets the entered proctor ID
 * 
 * @return int The proctor ID as integer
 */
int IncidentDialog::getProctorID() const {
    return proctorIDEdit->text().toInt();
}

/**
 * @brief Gets the incident message
 * 
 * @return QString The message text
 */
QString IncidentDialog::getMessage() const {
    return messageEdit->toPlainText();
}
