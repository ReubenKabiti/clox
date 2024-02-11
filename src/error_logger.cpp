#include "error_logger.h"
#include <iostream>
#include <string>

void ErrorLogger::error(size_t line, std::string msg)
{
    report(line, "", msg);
}

void ErrorLogger::report(size_t line, std::string where, std::string msg)
{
    std::cerr << "Error: [" << msg << "]" << where << " >> line: " << line << '\n';
    mHadError = true;
}
