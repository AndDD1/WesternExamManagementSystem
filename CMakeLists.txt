# ====================================================================
# @file CMakeLists.txt
# @brief CMake configuration for building the project. Including
# google unit test.
#
# @author Allen Pan
# @version 4.1
# @date 2025-03-10
# ====================================================================

cmake_minimum_required(VERSION 3.19)
project(ExamIdenVerif LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_PREFIX_PATH "/home/panyilun/Qt/6.8.1/gcc_64/lib/cmake/Qt6")

# Find Qt
find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        MultimediaWidgets
        Network
)



# Enable Qt-specific automatic handling
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect source files
set(SRC_FILES
        src/main.cpp
        src/ui_src/mainwindow.cpp
        src/User.cpp
        src/Proctor.cpp
        src/Break.cpp
        src/Student.cpp
        src/Exam.cpp
        src/ui_src/CheckInDialog.cpp
        src/ui_src/SeatMapDialog.cpp
        src/ui_src/IncidentDialog.cpp
        src/ExamDataLoader.cpp
        src/ui_src/SubmissionDialog.cpp
        src/ui_src/GenerateReport.cpp
        src/PDFReportGenerator.cpp
)

# Collect header files
set(HEADER_FILES
        include/ui_header/mainwindow.h
        include/User.h
        include/Proctor.h
        include/Break.h
        include/Student.h
        include/Exam.h
        include/ui_header/CheckInDialog.h
        include/Utils.h
        include/ui_header/SeatMapDialog.h
        include/ui_header/IncidentDialog.h
        include/ExamDataLoader.h
        include/ui_header/SubmissionDialog.h
        include/ui_header/GenerateReport.h
        include/PDFReportGenerator.h
)

# Collect UI files
set(UI_FILES
        ui/mainwindow.ui
        ui/generatereport.ui
)

# Collect media files
file(GLOB_RECURSE MEDIA_FILES "media/*")

# Ensure media files are copied to the build directory
foreach(file ${MEDIA_FILES})
    configure_file(${file} ${CMAKE_BINARY_DIR}/${file} COPYONLY)
endforeach()

# Add the executable
qt_add_executable(ExamIdenVerif
        WIN32 MACOSX_BUNDLE
        resources.qrc
        ${SRC_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
)

# Ensure AutoUic processes UI files properly
set_target_properties(ExamIdenVerif PROPERTIES
        AUTOUIC ON
        AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui
)

# Link Libraries
target_link_libraries(ExamIdenVerif
        PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::Network
        hpdf
)

# Installation settings
include(GNUInstallDirs)

install(TARGETS ExamIdenVerif
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Ensure media files are installed with the application
install(DIRECTORY ${CMAKE_SOURCE_DIR}/media DESTINATION ${CMAKE_INSTALL_PREFIX})

# Deploy Qt dependencies (Windows/macOS)
qt_generate_deploy_app_script(
        TARGET ExamIdenVerif
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})



# =============== UNIT TEST =============== #

# Enable Testing
enable_testing()

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Set test source files
set(TEST_FILES
        tests/test_Initiator.cpp
        tests/test_User.cpp
        tests/test_Student.cpp
        tests/test_Proctor.cpp
        tests/test_Break.cpp
        tests/timeFormator.h
)


# Add Unit Test Executable
add_executable(UnitTests
        ${TEST_FILES}
        src/User.cpp
        src/Proctor.cpp
        src/Break.cpp
        src/Student.cpp
)

# Include Directories for Tests
target_include_directories(UnitTests PRIVATE include)

# Link Google Test to UnitTests
target_link_libraries(UnitTests
        gtest
        gtest_main
        pthread
)

# Register Unit Tests
add_test(NAME UnitTests COMMAND UnitTests)

# Run Unit Tests Before Executing Main Program
add_custom_target(run_tests
        COMMAND ctest --output-on-failure
        DEPENDS UnitTests
)
add_dependencies(ExamIdenVerif run_tests)
