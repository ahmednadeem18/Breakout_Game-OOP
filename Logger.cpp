#pragma warning (disable :4996)
#include "Logger.h"
#include <ctime>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::initialize(const char* arr) {
    file.open(arr);
}

void Logger::cleanup() {
    if (file.is_open()) {
        file.close();
    }
}

void Logger::writeError(const MyStr& error_message) {
    if (file.is_open()) {
        time_t timestamp;
        time(&timestamp);
        file << error_message.ToCharArray() << "\t" << ctime(&timestamp);
    }
}