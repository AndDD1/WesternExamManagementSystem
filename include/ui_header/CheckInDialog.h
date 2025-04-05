/**
 * @file CheckInDialog.h
 * @brief Defines the CheckInDialog class used for student check-in via ONECard in the exam system.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-29
 */

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include "Exam.h"

/**
 * @class CheckInDialog
 * @brief A Qt dialog for handling student check-in during the exam session.
 *
 * This dialog allows TAs or proctors to input a student ID, view student details,
 * and confirm their attendance. It displays information such as name, date of birth,
 * seat assignment, exam version, and student photo.
 */
class CheckInDialog : public QDialog {
    Q_OBJECT

public:
    explicit CheckInDialog(Exam* exam, QWidget* parent = nullptr);

    private slots:
        void onLookupStudent();
    void onConfirmCheckIn();

private:
    Exam* examPtr;
    Student* currentStudent;

    QLineEdit* idInput;
    QLabel* nameLabel;
    QLabel* dobLabel;
    QLabel* seatLabel;
    QLabel* versionLabel;
    QLabel* photoLabel;
    QLabel* statusLabel;
    QLabel* photoUrlLabel;


    QPushButton* confirmButton;

    void updateStudentInfo(Student* student);
    void loadLocalPhoto(const QString& path);
};
