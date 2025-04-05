//
// Created by panyilun on 3/28/25.
//


#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

class timeFormator {
protected:
    std::string formatTime(std::chrono::system_clock::time_point tp) {
        std::time_t time = std::chrono::system_clock::to_time_t(tp);
        std::tm *timeInfo = std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(timeInfo, "%H:%M:%S");
        return oss.str();
    }
};

