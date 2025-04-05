/**
 * @file Utils.h
 * @brief Utility functions for the Project.
 *
 * @author Allen Pan
 * @version 1.1
 * @date 2025-03-29
 */
#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <chrono>
#include <QDateTime>
#include <iomanip>
#include <sstream>

/**
 * @brief Converts a std::chrono::system_clock::time_point to a formatted std::string.
 *
 * The format used is "YYYY-MM-DD HH:MM:SS".
 *
 * @param tp The time point to convert.
 * @return A formatted string representing the time point.
 */
inline std::string timePointToString(const std::chrono::system_clock::time_point& tp) {
    std::time_t timeT = std::chrono::system_clock::to_time_t(tp);
    std::tm tm = *std::localtime(&timeT);  // or std::gmtime for UTC

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");  // Format: YYYY-MM-DD HH:MM:SS
    return oss.str();
}

/**
 * @brief Converts a std::chrono::system_clock::time_point to a formatted QString.
 *
 * The format used is "yyyy-MM-dd hh:mm:ss".
 *
 * @param tp The time point to convert.
 * @return A QString representing the time point.
 */
inline QString timePointToQString(const std::chrono::system_clock::time_point& tp) {
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(static_cast<qint64>(time));
    return dateTime.toString("yyyy-MM-dd hh:mm:ss");
}



/**
 * @brief Converts a ISO 8601 formatted string ti std::chrono::system_clock::time_point.
 *
 * The format used is "yyyy-MM-dd hh:mm:ss".
 *
 * @param isoString String address to be converted.
 * @return A std::chrono::system_clock::time_point.
 */
inline std::chrono::system_clock::time_point stringToTimePoint(const std::string &isoString) {
    std::tm t = {};
    std::istringstream ss(isoString);
    ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse time: " + isoString);
    }
    std::time_t time_c = std::mktime(&t);
    return std::chrono::system_clock::from_time_t(time_c);
}


inline std::string trim(const std::string &s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start))
        start++;
    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    return std::string(start, end + 1);
}

// Helper function to extract the substring before ";;", if present.
inline std::string getValue(const std::string &line) {
    size_t pos = line.find(";;");
    std::string value = (pos != std::string::npos) ? line.substr(0, pos) : line;
    return trim(value);
}

#endif // UTILS_H

