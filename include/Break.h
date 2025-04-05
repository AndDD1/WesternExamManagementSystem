/**
 * @file Break.h
 * @brief Definition of the Break class.
 *
 * This file defines the Break class, which manages the break periods taken
 * by students during an exam. The class automatically records the start and end times
 * of a break and provides utility functions for retrieving and formatting these times.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-19
 */

#ifndef BREAK_H
#define BREAK_H

#include <chrono>
#include <string>

class Break {
private:
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
    bool isEnded;

public:
    /**
     * @brief Constructs a Break object and records the current system time as the start time.
     *
     * The constructor initializes a break session for a student and automatically
     * timestamps the start of the break using system time.
     */
    Break();

    /**
     * @brief Retrieves the formatted start time of the break.
     *
     * @return A string representing the break start time in HH:MM:SS format.
     */
    std::string getStartTime() const;

    /**
     * @brief Retrieves the formatted end time of the break.
     *
     * If the break has not yet ended, the function returns "Break in progress".
     *
     * @return A string representing the break end time in HH:MM:SS format,
     *         or "Break in progress" if the break has not ended.
     */
    std::string getEndTime() const;

    /**
     * @brief Ends the break and records the current system time as the end time.
     *
     * This function should be called when a student returns from a break.
     */
    void endBreak();

    /**
     * @brief Calculates and retrieves the duration of the break in HH:MM:SS format.
     *
     * If the break has not yet ended, the function returns "Break in progress".
     *
     * @return A string representing the duration of the break.
     */
    std::string getDuration() const;
};

#endif // BREAK_H

