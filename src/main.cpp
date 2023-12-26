#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "scanner.h"

#define MAX_LINE_LEN 2048 // the maximum line length of a prompt
 
void runFile(char* path);
void runPrompt();
void run(std::string& source, ErrorLogger& logger);

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::cerr << "Usage:\nlox <FILE>\n";
        return 64;
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else 
    {
        runPrompt();
    }
}

void runFile(char* path)
{
    std::ifstream stream;
    try 
    {
        stream.open(path, std::ios::in);
        std::stringstream sstream;
        sstream << stream.rdbuf();

        std::string source = sstream.str();

        ErrorLogger errorLogger;
        run(source, errorLogger);
        if (errorLogger.hadError())
            exit(64);
    }
    catch (std::exception& e)
    {
        std::cout << "Error reading file\n";
    }
}

void runPrompt()
{
    while(true)
    {
        std::cout << "> ";
        char buff[MAX_LINE_LEN];
        fgets(buff, MAX_LINE_LEN, stdin);
        std::string source(buff);
        source.pop_back();
        ErrorLogger errorLogger;
        run(source, errorLogger);
    }
}

void run(std::string& source, ErrorLogger& logger)
{
    Scanner scanner(source, logger);
    auto tokens = scanner.scanTokens();
    for (auto& token : tokens)
    {
        std::cout << token << '\n';
    }
}
