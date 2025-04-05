# University Examination Identity Verification Management System (Group 66)

This project is a C++/Qt-based university examination management and identity verification system. It ensures exam integrity by combining student ONECard check-ins, facial recognition, attendance tracking, and real-time monitoring. The system is designed to be used on Raspberry Pi with database integration, a webcam, and card reader hardware.

This project was created as part of **CS3307B (Winter 2025)** at **Western University**.

**For login, username == "Administrator" and password == "cs3307"**

This readme file is prepared by Allen Pan & Andy Dai. 

---

<!-- TOC -->
* [University Examination Identity Verification System (Group 66)](#university-examination-identity-verification-system-group-66)
  * [Features](#features)
  * [Prerequisites](#prerequisites)
    * [Installing Dependencies](#installing-dependencies)
      * [Qt6 Modules](#qt6-modules)
      * [libharu](#libharu)
  * [**Building the Project (CMake ONLY)**](#building-the-project-cmake-only)
  * [Project Structure](#project-structure)
    * [include/](#include)
      * [Core Classes](#core-classes)
      * [Utility](#utility)
      * [UI Header Dialogs](#ui-header-dialogs)
    * [src/](#src)
      * [Core Logic](#core-logic)
    * [src/ui_src/](#srcui_src)
  * [Acknowledgments](#acknowledgments)
  * [Contributors](#contributors)
<!-- TOC -->

---

## Features

- **Student Identity Verification** via Student Number
- **Attendance Logging** with timestamps
- **Seating Assignment** and seat map display
- **Washroom Break Tracking**
- **Early/Automatic Exam Submission** with time logging
- **Exam Report Generation** summarizing attendance, seating, and submissions
- **Real-time Monitoring** dashboard for proctors
- **Incident Reporting** and attendance summaries

---

## Prerequisites
Before you can build and run the `ExamIdenVerif` project, you need to ensure the following dependencies are installed on your system:

- **Qt6 Libraries**: Ensure you have the Qt6 Core, Widgets, Multimedia, MultimediaWidgets, and Network modules installed.
                                                                              
- **libharu**: A library for generating PDF files (`hpdf`).

### Installing Dependencies
#### Qt6 Modules
You can install the necessary Qt6 modules using the Qt Online Installer available from the [Qt website](https://www.qt.io/download). 

#### libharu
For libharu, you can typically install it via your package manager. For example, on Ubuntu, you can use:
```bash
sudo apt-get install libhpdf-2.3.0
```

---

## **Building the Project (CMake ONLY)**

1. **Create a build directory**
    ```bash
    mkdir build && cd build
    ```
2. **Set the Qt installation path (if necessary)**

   If CMake cannot find your Qt installation, specify the `CMAKE_PREFIX_PATH` manually:
    ```bash
    cmake .. -DCMAKE_PREFIX_PATH="/path/to/Qt/6.x.x/gcc_64/lib/cmake/Qt6"
    ```
   Replace `/path/to/Qt/6.x.x/gcc_64/lib/cmake/Qt6` with your actual Qt installation path.


3. **Run CMake**
    ```bash
    cmake ..
    ```

4. **Compile the project**
    ```bash
    make
    ```

5. **Run the App**
    ```bash
    ./ExamIdenVerif
    ```

---

## Project Structure


### include/

Contains all header files used throughout the project.

#### Core Classes

- **User.h** — Base class for users (students, proctors).
- **Student.h** — Represents a student, extends `User`.
- **Proctor.h** — Represents a proctor, extends `User`.
- **Break.h** — Tracks student washroom breaks.
- **Exam.h** — Manages overall exam data, seating, and event handling.
- **ExamDataLoader.h** — Parses configuration data and initializes an `Exam`.

#### Utility

- **PDFReportGenerator.h** — Generates the PDF report using libharu.
- **Utils.h** — Miscellaneous helper functions.

#### UI Header Dialogs

- **CheckInDialog.h** — UI for handling student check-ins.
- **GenerateReport.h** — UI component for generating exam reports.
- **IncidentDialog.h** — UI for logging exam incidents.
- **SeatMapDialog.h** — UI for displaying seating arrangements.
- **SubmissionDialog.h** — UI for early or final submissions.
- **mainwindow.h** — Main window of the application.

---

### src/

Contains the implementation (.cpp) files for backend logic.

#### Core Logic

- **User.cpp**, **Student.cpp**, **Proctor.cpp** — Class implementations.
- **Break.cpp** — Implements break-tracking logic.
- **Exam.cpp** — Exam flow control, attendance, seating, and event logging.
- **ExamDataLoader.cpp** — Parses and loads exam settings from input files.
- **PDFReportGenerator.cpp** — Generates a formatted PDF report with libharu.
- **main.cpp** — Entry point of the application.


### src/ui_src/

Holds the implementations for all Qt-based UI dialogs and interactions.

- **CheckInDialog.cpp** — UI for student check-in using ONECard.
- **GenerateReport.cpp** — Handles PDF report UI interactions.
- **IncidentDialog.cpp** — UI for proctors to log incidents.
- **SeatMapDialog.cpp** — Displays dynamic seat status.
- **SubmissionDialog.cpp** — UI for early exam submissions.
- **mainwindow.cpp** — Central UI for navigation and monitoring.

---

## Acknowledgments

We would like to express our gratitude to:
- **Ubuntu**: For providing a stable development OS
- **VMware Workstation**: For allowing VM-based testing
- **Qt Framework**: For building our user interface
- **Google Test**: For unit testing

---

## Contributors (in no particular order)

- **Allen Pan**
- **Andy Dai**
- **Minh Duc Pham**
- **Kohei Kubota**

