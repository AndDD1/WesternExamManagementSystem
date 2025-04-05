/**
 * @file mainwindow.cpp
 * @brief Implementation of MainWindow class for the University Exam Identity Verification System.
 *
 * This file defines the main window of the application. It includes user login,
 * displays exam metadata, opens dialogs for check-in, attendance, washroom breaks,
 * and seat map visualization.
 *
 * @author Andy Dai
 * @author Allen Pan
 * @version 1.6
 * @date 2025-04-2
 */


#include "ui_header/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_header/CheckInDialog.h"
#include "Exam.h"
#include <QLabel>
#include <QMainWindow>
#include <QInputDialog>
#include "Utils.h"
#include <QFileDialog>
#include <QMessageBox>
#include "ui_header/SeatMapDialog.h"
#include "ui_header/IncidentDialog.h"
#include "ui_header/SubmissionDialog.h"
#include "ui_header/GenerateReport.h"


/**
 * @brief Constructor for MainWindow.
 *
 * Initializes the UI and sets the initial view.
 *
 * @param exam Pointer to the active Exam object containing exam session data.
 * @param parent Parent widget, default is nullptr.
 */
MainWindow::MainWindow(Exam *exam, QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
      , examPtr(exam) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}


/**
 * @brief Destructor for MainWindow.
 */
MainWindow::~MainWindow() {
    delete ui;
}


/**
 * @brief Populates the exam detail labels with values from the Exam object.
 */
void MainWindow::populateExamDetails() {
    ui->termNumberValueLabel->setText(QString::number(examPtr->getTermNum()));
    ui->termNameValueLabel->setText(QString::fromStdString(examPtr->getTermName()));
    ui->courseNumberValueLabel->setText(QString::fromStdString(examPtr->getCourseNum()));
    ui->examRoomValueLabel->setText(QString::fromStdString(examPtr->getRmNum()));
    ui->numSeatsValueLabel->setText(QString::number(examPtr->getCapacity()));
    ui->numVersionsValueLabel->setText(QString::number(examPtr->getNumVersions()));

    QString versions;
    for (int code: examPtr->getVersionsCode()) {
        versions += QString::number(code) + " ";
    }
    ui->examVersionsValueLabel->setText(versions.trimmed());

    ui->startTimeValueLabel->setText(timePointToQString(examPtr->getStartTime()));
    ui->endTimeValueLabel->setText(timePointToQString(examPtr->getEndTime()));
}


/**
 * @brief Slot triggered when the Check-In dialog button is clicked.
 */
void MainWindow::on_openCheckInDialog_clicked() {
    CheckInDialog dialog(examPtr, this);
    dialog.exec();
}


/**
 * @brief Slot triggered when the Login button is clicked.
 *
 * Validates a basic username and password, and switches to the main exam interface if valid.
 */


// Update your MainWindow class to store a pointer to the Exam instance
// Constructor should look like: MainWindow(Exam* exam, QWidget *parent = nullptr);

void MainWindow::on_loginButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username == "Administrator" && password == "cs3307") {
        QString fileName = QFileDialog::getOpenFileName(this, "Select Exam Data File", "", "Text Files (*.txt)");

        if (fileName.isEmpty()) {
            QMessageBox::warning(this, "No File Selected", "Please select a valid exam data file.");
            return;
        }

        // Load new data into the Exam object
        if (!examPtr->loadFromFile(fileName.toStdString())) {
            QMessageBox::critical(this, "Load Failed", "Failed to load the exam data file.");
            return;
        }

        ui->stackedWidget->setCurrentIndex(1);
        populateExamDetails(); // Cleanly sets all labels
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}


/**
 * @brief Slot triggered when the Washroom Break button is clicked.
 *
 * Prompts for a student ID and logs a washroom break using Exam::washroomBreak().
 */
void MainWindow::on_openBreakDialog_clicked() {
    // Step 1: Prompt for student ID
    bool ok;
    QString idStr = QInputDialog::getText(this, tr("Washroom Break"),
                                          tr("Please swipe your ONECard or enter Student ID:"), QLineEdit::Normal,
                                          "", &ok);

    if (!ok || idStr.isEmpty()) {
        QMessageBox::warning(this, "Break Cancelled", "No ID entered.");
        return;
    }

    int studentID = idStr.toInt();

    // Step 2: Call Exam::washroomBreak
    std::string resultMsg = examPtr->washroomBreak(studentID);

    // Step 3: Display the result
    QMessageBox::information(this, "Break Status", QString::fromStdString(resultMsg));
}


/**
 * @brief Slot triggered when the Seat Map button is clicked.
 *
 * Opens the SeatMapDialog, which displays all seats and allows lookup of student info.
 */
void MainWindow::on_openMapDialog_clicked() {
    SeatMapDialog *mapDialog = new SeatMapDialog(examPtr, this);
    mapDialog->exec();
}


/**
 * @brief Opens a window to log a new incident involving a student and proctor.
 *
 * All fields are input in the same dialog. If validation fails, the user can retry.
 */
void MainWindow::on_openIncidentDialog_clicked() {
    while (true) {
        IncidentDialog dialog(this);
        if (dialog.exec() == QDialog::Rejected)
            return; // User cancelled

        int studentID = dialog.getStudentID();
        int proctorID = dialog.getProctorID();
        QString message = dialog.getMessage();

        bool validStudent = examPtr->hasStudent(studentID);
        bool validProctor = examPtr->hasProctor(proctorID);

        if (!validStudent) {
            QMessageBox::warning(this, "Invalid Student", "Student ID not found. Please try again.");
            continue;
        }
        if (!validProctor) {
            QMessageBox::warning(this, "Invalid Proctor", "Proctor ID not found. Please try again.");
            continue;
        }

        examPtr->writeIncident(studentID, proctorID, message.toStdString());
        QMessageBox::information(this, "Incident Logged", "Incident recorded successfully.");
        break;
    }
}


void MainWindow::on_openSubmissionDialog_clicked() {
    SubmissionDialog dialog(examPtr, this);
    dialog.exec();
}


void MainWindow::on_logOutButton_clicked() {
    // Get the current time from the system clock
    auto currentTime = std::chrono::system_clock::now();
    auto examStart = examPtr->getStartTime();
    auto examEnd = examPtr->getEndTime();

    // Determine if the exam is currently running
    bool examRunning = (currentTime >= examStart) && (currentTime <= examEnd);

    // If the exam is still running, ask the user to confirm logout
    if (examRunning) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirm Logout"),
                                      tr("The exam is still running. Are you sure you want to logout?"),
                                      QMessageBox::Yes | QMessageBox::No,
                                      QMessageBox::No);
        if (reply == QMessageBox::No) {
            return; // Abort logout if user cancels.
        }
    }
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_generateReport_clicked() {
    GenerateReport dialog(examPtr, this);
    dialog.exec();
}
