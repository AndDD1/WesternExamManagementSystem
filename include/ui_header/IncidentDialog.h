/**
 * @file IncidentDialog.h
 * @brief A dialog used to record an incident during an exam session.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-30
 */

#include <QDialog>

class QLineEdit;
class QTextEdit;

/**
 * @class IncidentDialog
 * @brief A dialog used to record an incident during an exam session.
 *
 * This dialog allows a TA or Course Instructor to enter and submit
 * information about an incident, including the student ID, proctor ID, and a descriptive message.
 */
class IncidentDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructor for the IncidentDialog.
     * @param parent The parent widget, default is nullptr.
     */
    IncidentDialog(QWidget* parent = nullptr);

    /**
     * @brief Retrieves the entered student ID.
     * @return The student ID as an integer.
     */
    int getStudentID() const;

    /**
     * @brief Retrieves the entered proctor ID.
     * @return The proctor ID as an integer.
     */
    int getProctorID() const;

    /**
     * @brief Retrieves the incident message.
     * @return The message as a QString.
     */
    QString getMessage() const;

private:
    QLineEdit* studentIDEdit;   ///< Line edit for entering the student ID.
    QLineEdit* proctorIDEdit;   ///< Line edit for entering the proctor ID.
    QTextEdit* messageEdit;     ///< Text edit for entering the incident message.
};
