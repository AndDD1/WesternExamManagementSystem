# University Examination Identity Verification System - Unit Tests

## Overview

This folder contains unit tests for the core components of the University Examination Identity Verification System, as outlined in our project proposal and UML design. The tests are designed to ensure correct functionality, reliability, and edge case handling for the main logic classes, such as `Student`, `Proctor` and `Exam`.

This readme file is prepared by Allen Pan. 

## Framework

All tests are implemented using the **Google Test** framework.

To install and run tests:

```bash
mkdir build
cd build
cmake ..
make
./UnitTests
```

## Tested Components

### 1. `Student` Authored by Allen

- Check-in logic (`checkIn`)
- Attendance flag update (`setAttendence`)
- Break tracking (`leaveForBreak`, `returnFromBreak`)
- Early and on-time submission (`submitExam`)
- Seat and exam version assignment

### 2. `Proctor` Authored by Allen

- Role getter and setter
- Inherited attributes from `User`: ID, name, DOB, pic URL

### 3. `Break` Authored by Allen

- Start and end time initialization
- Break duration calculation

### 4. `User` Authored by Allen

- Initialization and getter/setter methods
- Name, DOB, picture URL, and ID operations

### 5. `Test Initialization` Authored by Allen

- Runs all Google Test cases in the project

Note: `Exam` and `FacialRecognitor` classes are not yet covered in current test files.

## Test Structure

Tests are organized in folders by class:

```
tests/
├── test_Student.cpp
├── test_Proctor.cpp
├── test_Break.cpp
├── test_User.cpp
├── test_Initiator.cpp
```
