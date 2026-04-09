#include <fstream>
#include <string>
#include <stdexcept>
#include "getShard.hpp"
#include "../config/config.hpp"
using std::string;

// A function that reads the teams file and returns its content as a string.
string getTeams()
{
    const string file_name = Paths::kTEAMS_FILE;

    string content;
    string line;

    std::ifstream inFile(file_name);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + file_name);
    }


    while (std::getline(inFile, line))
    {
        content += line + "\n";
    }

    return content;
}

// A function that reads the judges file and returns its content as a string.
string getJudges()
{
    const string file_name = Paths::kJUDGES_FILE;

    string content;
    string line;

    std::ifstream inFile(file_name);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + file_name);
    }


    while (std::getline(inFile, line))
    {
        content += line + "\n";
    }

    return content;
}

// A function that reads the evaluations file and returns its content as a string.
string getEvals()
{
    const string file_name = Paths::kEVALUATION_FILE;
    
    string content;
    string line;

    std::ifstream inFile(file_name);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + file_name);
    }

    while (std::getline(inFile, line))
    {
        content += line + "\n";
    }

    return content;
}

// A function that reads the admins file and returns its content as a string.
string getAdmins()
{
    const string file_name = Paths::kADMINS_FILE;
    
    string content;
    string line;

    std::ifstream inFile(file_name);
    if (!inFile)
    {
        throw std::runtime_error("Unable to open file: " + file_name);
    }

    while (std::getline(inFile, line))
    {
        content += line + "\n";
    }

    return content;
}
