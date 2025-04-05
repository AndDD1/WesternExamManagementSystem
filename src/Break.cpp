/**
 * @file Break.cpp
 * @brief Implementation of the Break class.
 *
 * This file implements the Break class, which manages the break periods taken
 * by students during an exam. The class automatically records the start and end times
 * of a break and provides utility functions for retrieving and formatting these times.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */


#include "Break.h"
#include <sstream>
#include <iomanip>
#include <ctime>

// Constructor: Automatically sets current time as startTime
Break::Break() : isEnded(false) {
    startTime = std::chrono::system_clock::now();
}

// Convert time_point to HH:MM:SS
std::string Break::getStartTime() const {
    std::time_t startT = std::chrono::system_clock::to_time_t(startTime);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&startT), "%H:%M:%S");
    return oss.str();
}

// Convert endTime to HH:MM:SS
std::string Break::getEndTime() const {
    // No End Time if still in a break
    if (!isEnded) return "Break in progress";
    std::time_t endT = std::chrono::system_clock::to_time_t(endTime);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&endT), "%H:%M:%S");
    return oss.str();
}

// Set End Time when as student return to exam
void Break::endBreak() {
    endTime = std::chrono::system_clock::now();
    isEnded = true;
}

// Calculate duration and return formatted string
std::string Break::getDuration() const {
    // No duration if still in a break
    if (!isEnded) return "Break in progress";

    std::chrono::duration<int> duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    int hours = duration.count() / 3600;
    int minutes = (duration.count() % 3600) / 60;
    int seconds = duration.count() % 60;

    std::ostringstream durationStream;
    // Make output as consistent as getTime operation
    durationStream << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;

    return durationStream.str();
}
