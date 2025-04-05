/**
 * @file CheckInDialog.cpp
 * @brief Constructs the CheckInDialog.
 *
 * Initializes the dialog for looking up and checking in students by ID.
 * Displays student information and a photo upon successful lookup.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-30
 */

#include "../include/ui_header/CheckInDialog.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QPixmap>
 
 /**
  * @brief Constructor for CheckInDialog
  * 
  * @param exam Pointer to the Exam object
  * @param parent Pointer to the parent widget
  */
 CheckInDialog::CheckInDialog(Exam* exam, QWidget* parent)
     : QDialog(parent), examPtr(exam), currentStudent(nullptr)
 {
     setWindowTitle("Student Check-In");
 
     idInput = new QLineEdit;
     QPushButton* lookupButton = new QPushButton("Lookup Student");
 
     nameLabel = new QLabel("Name: ");
     dobLabel = new QLabel("DOB: ");
     seatLabel = new QLabel("Seat: ");
     versionLabel = new QLabel("Version: ");
     statusLabel = new QLabel("Status: ");
     photoLabel = new QLabel("No Photo");
     photoUrlLabel = new QLabel("Photo URL: ");
 
     photoLabel->setFixedSize(500, 200);
     photoLabel->setAlignment(Qt::AlignCenter);
 
     confirmButton = new QPushButton("Confirm Check-In");
     confirmButton->setEnabled(false);
 
     QVBoxLayout* layout = new QVBoxLayout(this);
     layout->addWidget(new QLabel("Enter Student ID:"));
     layout->addWidget(idInput);
     layout->addWidget(lookupButton);
     layout->addWidget(nameLabel);
     layout->addWidget(dobLabel);
     layout->addWidget(photoLabel);
     layout->addWidget(photoUrlLabel);
     layout->addWidget(seatLabel);
     layout->addWidget(versionLabel);
     layout->addWidget(statusLabel);
     layout->addWidget(confirmButton);
 
     connect(lookupButton, &QPushButton::clicked, this, &CheckInDialog::onLookupStudent);
     connect(confirmButton, &QPushButton::clicked, this, &CheckInDialog::onConfirmCheckIn);
 }
 
 /**
  * @brief Slot to look up a student by entered ID
  * 
  */
 void CheckInDialog::onLookupStudent() {
     bool ok;
     int studentID = idInput->text().toInt(&ok);
     if (!ok || studentID <= 0) {
         QMessageBox::warning(this, "Invalid Input", "Please enter a valid student ID.");
         return;
     }
 
     currentStudent = examPtr->getStudentByID(studentID);
     if (!currentStudent) {
         QMessageBox::critical(this, "Not Found", "Student not found.");
         confirmButton->setEnabled(false);
         return;
     }
 
     updateStudentInfo(currentStudent);
     confirmButton->setEnabled(!currentStudent->getAttendance());
 }
 
 /**
  * @brief Updates the student information on the UI
  * 
  * @param s Pointer to the Student object
  */
 void CheckInDialog::updateStudentInfo(Student* s) {
     nameLabel->setText("Name: " + QString::fromStdString(s->getName()));
     dobLabel->setText("DOB: " + QString::fromStdString(s->getDOB()));
     seatLabel->setText("Seat: " + QString::fromStdString(s->getSeatNum()));
     versionLabel->setText("Version: " + QString::number(s->getExamVersion()));
     statusLabel->setText("Status: " + QString(s->getAttendance() ? "Already Checked In" : "Not Checked In"));
 
     QString picPath = QString::fromStdString(s->getPicURL());
     photoUrlLabel->setText("Photo URL: " + picPath);
     loadLocalPhoto(picPath);
 }
 
 /**
  * @brief Loads and displays a local photo from a given path
  * 
  * @param path File path to the photo
  */
 void CheckInDialog::loadLocalPhoto(const QString& path) {
     QPixmap pix;
     if (!pix.load(path)) {
         photoLabel->setText("Photo not found");
         photoLabel->setPixmap(QPixmap());
         return;
     }
 
     pix = pix.scaled(photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
     photoLabel->setPixmap(pix);
 }
 
 /**
  * @brief Slot to confirm student check-in and update the UI
  * 
  */
 void CheckInDialog::onConfirmCheckIn() {
     if (!currentStudent) return;
 
     Student* updated = examPtr->checkIn(currentStudent->getID());
     if (!updated) {
         QMessageBox::warning(this, "Check-In Failed", "Unable to check in student.");
         return;
     }
 
     updateStudentInfo(updated);
     confirmButton->setEnabled(false);
     QMessageBox::information(this, "Success", "Student checked in.");
 }
 