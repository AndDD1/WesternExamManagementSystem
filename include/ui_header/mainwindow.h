/**
 * @file MainWindow.h
 * @brief The main window of the System.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-30
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Exam.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The main window of the University Examination Identity Verification System.
 *
 * This class represents the initial page of the application, including:
 * - A login screen for TAs or instructors to authenticate using credentials.
 * - A dashboard that displays exam details and offers access to various exam-related operations.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a MainWindow object.
     * @param exam Pointer to the Exam object containing current exam session data.
     * @param parent Optional parent widget.
     */
    explicit MainWindow(Exam* exam, QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

    /**
     * @brief Populates the UI with current exam details (e.g., course, time, room).
     */
    void populateExamDetails();

private:
    Ui::MainWindow *ui;   ///< Pointer to the auto-generated UI class.
    Exam* examPtr;        ///< Pointer to the current Exam object.

private slots:
    /**
     * @brief Triggered when the login button is clicked.
     *        Validates user credentials and proceeds to the dashboard.
     */
    void on_loginButton_clicked();

    /**
     * @brief Opens the Washroom Break Dialog.
     */
    void on_openBreakDialog_clicked();

    /**
     * @brief Opens the Exam Room Map Dialog.
     */
    void on_openMapDialog_clicked();

    /**
     * @brief Opens the Incident Report Dialog.
     */
    void on_openIncidentDialog_clicked();

    /**
     * @brief Opens the Check-In Dialog for student attendance.
     */
    void on_openCheckInDialog_clicked();

    /**
     * @brief Opens the Exam Submission Dialog.
     */
    void on_openSubmissionDialog_clicked();

    /**
     * @brief Logs out the current user and returns to the login screen.
     */
    void on_logOutButton_clicked();

    void on_generateReport_clicked();
};

#endif // MAINWINDOW_H
