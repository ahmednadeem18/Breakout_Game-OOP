#pragma warning (disable :4996)
#ifndef LOGGER_H
#define LOGGER_H

#include "MyStr.h"
#include <fstream>

class Logger {
public:
    static Logger& getInstance();
    void initialize(const MyStr& filename);
    void cleanup();
    void writeError(const MyStr& error_message);

private:
    Logger() {};
    ~Logger() {};
    std::ofstream file;
};

#endif 