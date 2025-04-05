/**
 * @file ExamDataLoader.h
 * @brief Declares the ExamDataLoader class used to load exam configuration data from a file into an Exam object.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-30
 */
#ifndef EXAMDATALOADER_H
#define EXAMDATALOADER_H

#include <string>
#include "Exam.h"

/**
 * @class ExamDataLoader
 * @brief Utility class for loading exam data from a structured text file into an Exam instance.
 *
 * This class provides a static method that parses exam details, proctor info, and student info from
 * a given file and populates the corresponding fields in the Exam object.
 */
class ExamDataLoader {
public:
    /**
     * @brief Loads exam data from a file and populates an Exam object.
     *
     * @param path The file path to the exam data file.
     * @param exam The Exam object to populate with the loaded data.
     * @return true if the data was loaded successfully, false otherwise.
     */
    static bool loadExamData(const std::string& path, Exam& exam);
};

#endif
