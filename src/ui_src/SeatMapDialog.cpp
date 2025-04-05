/**
 * @file SeatMapDialog.cpp
 * @brief Implementation of the SeatMapDialog class.
 *
 * Dynamically creates a grid of buttons for each seat in the exam room using the
 * maxRow and maxCol from the Exam object.
 * Each button represents a seat in the room. When clicked, the system shows
 * the student assigned to that seat and their details.
 *
 * @author Allen Pan
 * @author Kohei Kubota
 * @author Andy Dai
 * @version 1.1
 * @date 2025-03-29
 */
#include "ui_header/SeatMapDialog.h"
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox> 
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>

/**
 * @brief Constructor for SeatMapDialog
 * 
 * @param exam Pointer to the Exam object
 * @param parent Pointer to the parent widget
 */
SeatMapDialog::SeatMapDialog(Exam* exam, QWidget* parent)
    : QDialog(parent), exam(exam)
{
    setWindowTitle("Exam Seating Map");

    
    QHBoxLayout* searchLayout = new QHBoxLayout;  
    searchLineEdit = new QLineEdit(this);         
    searchButton = new QPushButton("Find Student", this); 

    searchLayout->addWidget(new QLabel("Student ID:", this)); 
    searchLayout->addWidget(searchLineEdit);                  
    searchLayout->addWidget(searchButton);                    

    connect(searchButton, &QPushButton::clicked,
            this, &SeatMapDialog::onSearchClicked);           

    
    QGridLayout* gridLayout = new QGridLayout;
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    
    for (int row = 0; row < exam->getMaxRow(); ++row) {
        for (int col = 0; col < exam->getMaxCol(); ++col) {

            QString seatLabel = QString("Row: %1\nColum: %2")
                                    .arg(row + 1)
                                    .arg(col + 1);

            QPushButton* seatBtn = new QPushButton(
                QString::number(row + 1) + "-" + QString::number(col + 1)
            );
            seatBtn->setProperty("seatString", seatLabel);

            bool seatIsFree = true;
            bool seatOnBreak = false;

            
            for (Student &s : exam->getStudents()) {
                if (QString::fromStdString(s.getSeatNum()) == seatLabel) {
                    seatIsFree = false;
                    if (exam->isOnBreak(s.getID())) {
                        seatOnBreak = true;
                    }
                    break;
                }
            }

            if (seatOnBreak) {
                seatBtn->setStyleSheet("background-color: yellow;");
            } 
            else if (seatIsFree) {
                seatBtn->setStyleSheet("background-color: green;");
            } 
            else {
                seatBtn->setStyleSheet("background-color: red;");
            }

            
            seatButtons.push_back(seatBtn); 

            connect(seatBtn, &QPushButton::clicked,
                    this, &SeatMapDialog::handleSeatClick);

            gridLayout->addWidget(seatBtn, row, col);
        }
    }

    
    QHBoxLayout* legendLayout = new QHBoxLayout;

    QLabel* freeLabel = new QLabel("  Free  ");
    freeLabel->setStyleSheet("background-color: green; color: white;");
    legendLayout->addWidget(freeLabel);

    QLabel* takenLabel = new QLabel("  Taken  ");
    takenLabel->setStyleSheet("background-color: red; color: white;");
    legendLayout->addWidget(takenLabel);

    QLabel* breakLabel = new QLabel("  On Break  ");
    breakLabel->setStyleSheet("background-color: yellow; color: black;");
    legendLayout->addWidget(breakLabel);

    legendLayout->addStretch();

   
    mainLayout->addLayout(searchLayout);  
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(legendLayout);
}
/**
 * @brief Handles seat button click event
 *
 */
void SeatMapDialog::handleSeatClick() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString seatStr = btn->property("seatString").toString();

    for (Student& s : exam->getStudents()) {
        if (QString::fromStdString(s.getSeatNum()) == seatStr) {
            QString info = QString("Student ID: %1\nName: %2\nDOB: %3\nAttended: %4\nSubmitted: %5")
                           .arg(s.getID())
                           .arg(QString::fromStdString(s.getName()))
                           .arg(QString::fromStdString(s.getDOB()))
                           .arg(s.getAttendance() ? "Yes" : "No")
                           .arg(s.getSubmissionStatus() ? "Yes" : "No");

            QMessageBox::information(this, "Student Info", info);
            return;
        }
    }

    QMessageBox::warning(this, "No Student", "No student assigned to this seat.");
}

void SeatMapDialog::onSearchClicked() {
    bool ok = false;
    int studentID = searchLineEdit->text().toInt(&ok);
    if (!ok || studentID <= 0) {
        QMessageBox::warning(this, "Search Error", "Please enter a valid student ID.");
        return;
    }

    
    Student* foundStudent = exam->getStudentByID(studentID);
    if (!foundStudent) {
        QMessageBox::information(this, "Not Found", "No such student ID in the exam.");
        return;
    }

    
    QString seatLabel = QString::fromStdString(foundStudent->getSeatNum());
    if (seatLabel.isEmpty()) {
        QMessageBox::information(this, "No Seat", "This student has no seat assigned yet.");
        return;
    }

    
    QPushButton* targetBtn = nullptr;
    for (auto btn : seatButtons) {
        QString btnSeatStr = btn->property("seatString").toString();
        if (btnSeatStr == seatLabel) {
            targetBtn = btn;
            break;
        }
    }

    if (!targetBtn) {
        QMessageBox::warning(this, "Not Found", "Couldn't find a seat button for this student.");
        return;
    }

    
    QString originalStyle = targetBtn->styleSheet();
    targetBtn->setStyleSheet("background-color: orange;");

    
    QTimer::singleShot(1000, this, [=]() {
        
        targetBtn->setStyleSheet(originalStyle);
    });

    QMessageBox::information(this, "Seat Found",
        QString("Student %1 is at seat:\n%2").arg(studentID).arg(targetBtn->text()));
}