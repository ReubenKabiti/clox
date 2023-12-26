#pragma once
#include <string>

class ErrorLogger
{
public:

    void error(size_t line, std::string msg);
    void report(size_t line, std::string where, std::string msg);
    bool hadError() { return mHadError; }

private:
    bool mHadError = false;
};
