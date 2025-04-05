/**
 * @file ExamDataLoader.cpp
 * @brief This file loads and sets all the attributes and methods to Exam.
 *
 * Provides functionality to load exam data
 * from a structured file and populate the corresponding Exam object.
 *
 * @author Allen Pan
 * @version 1.0
 * @date 2025-03-30
 */

#include "../include/ExamDataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "../include/Utils.h"

bool ExamDataLoader::loadExamData(const std::string &dataPath, Exam &exam) {
    try {
        std::ifstream infile(dataPath);
        if (!infile) {
            std::cerr << "Error: Cannot open file " << dataPath << std::endl;
            return false;
        }

        std::string line;

        exam.setExamDataURL(dataPath);

        if (std::getline(infile, line)) exam.setTermNum(std::stoi(trim(getValue(line))));
        if (std::getline(infile, line)) exam.setTermName(trim(getValue(line)));
        if (std::getline(infile, line)) exam.setCourseNum(trim(getValue(line)));
        if (std::getline(infile, line)) exam.setRmNum(trim(getValue(line)));
        if (std::getline(infile, line)) exam.setCapacity(std::stoi(trim(getValue(line))));
        if (std::getline(infile, line)) exam.setMaxRow(std::stoi(trim(getValue(line))));
        if (std::getline(infile, line)) exam.setMaxCol(std::stoi(trim(getValue(line))));
        if (std::getline(infile, line)) exam.setNumVersions(std::stoi(trim(getValue(line))));

        if (std::getline(infile, line)) {
            std::stringstream ss(trim(getValue(line)));
            std::string token;
            std::vector<int> versions;
            while (std::getline(ss, token, ',')) {
                token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
                if (!token.empty()) versions.push_back(std::stoi(token));
            }
            exam.setVersionsCode(versions);
        }

        if (std::getline(infile, line)) exam.setStartTime(stringToTimePoint(trim(getValue(line))));
        if (std::getline(infile, line)) exam.setEndTime(stringToTimePoint(trim(getValue(line))));

        // Expect "Proctor"
        if (!std::getline(infile, line) || trim(getValue(line)) != "Proctor") {
            std::cerr << "Error: Expected 'Proctor' section" << std::endl;
            return false;
        }

        // Load Proctors until "Student"
        while (std::getline(infile, line)) {
            std::string value = trim(getValue(line));
            if (value == "Student") break;

            std::vector<std::string> tokens;
            std::stringstream ss(value);
            std::string token;
            while (std::getline(ss, token, ',')) tokens.push_back(trim(token));

            if (tokens.size() == 5) {
                Proctor p(std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4]);
                exam.addProctor(p);
            } else {
                std::cerr << "Warning: Skipping malformed proctor line: " << line << std::endl;
            }
        }

        // Load Students
        while (std::getline(infile, line)) {
            if (line.empty()) continue;

            std::vector<std::string> tokens;
            std::stringstream ss(trim(line));
            std::string token;
            while (std::getline(ss, token, ',')) tokens.push_back(trim(token));

            if (tokens.size() == 4) {
                Student s(std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3], false, false);
                exam.addStudent(s);
            } else {
                std::cerr << "Warning: Skipping malformed student line: " << line << std::endl;
            }
        }

        exam.initializeSeatMap(); // If you have a method to set up the seatMap
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Exception while loading exam data: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Unknown exception during exam data load." << std::endl;
        return false;
    }
}
