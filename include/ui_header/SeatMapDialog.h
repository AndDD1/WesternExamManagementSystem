/**
 * @file SeatMapDialog.h
 * @brief Definition of the SeatMapDialog class.
 *
 * Each button represents a seat in the room. When clicked, the system shows
 * the student assigned to that seat and their details.
 *
 * @author Allen Pan
 * @author  Kohei Kubota
 * @version 1.1
 * @date 2025-03-29
 */
#include <QDialog>
#include "Exam.h"
#include <vector>      
#include <QPushButton>

class QLineEdit;   
class QPushButton; 
class QHBoxLayout; 
class QVBoxLayout; 
class QLabel; 
class SeatMapDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructs the SeatMapDialog.
     *
     * @param exam Pointer to the current Exam object containing students, seating, and metadata.
     * @param parent Optional parent widget.
     */
    SeatMapDialog(Exam* exam, QWidget* parent = nullptr);

private slots:
    /**
     * @brief Handles the click event when a seat button is clicked.
     *
     * It checks the clicked seat, looks up the assigned student, and shows their info in a popup.
     */
    void handleSeatClick();
    void onSearchClicked();

private:
    Exam* exam;

    QLineEdit* searchLineEdit;  
    QPushButton* searchButton;

    std::vector<QPushButton*> seatButtons;
};

