/**
 * @file main.cpp
 * @brief Entry point for the University Examination Identity Verification System. Initializes the application, creates an exam instance, and launches the MainWindow for user authentication and exam management.
 * @author Andy Dai
 * @version 1.0
 * @date 2025-03-30
 */
#include "../include/ui_header/mainwindow.h"
#include "Exam.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Exam exam;
    MainWindow w(&exam);
    w.show();
    return a.exec();
}


