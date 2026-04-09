#include "saveShard.hpp"
#include <fstream>
#include <stdexcept>
#include "../config/config.hpp"

using std::string;

void saveTeams(const string& serialized_teams_arr)
{
    const string file_name = Paths::kTEAMS_FILE;

    std::ofstream outFile(file_name, std::ios::out);
    if (outFile.is_open())
    {
        outFile << serialized_teams_arr;
        outFile.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file: " + file_name);
    }
}

void saveJudges(const string& serialized_judges_arr)
{
    const string file_name = Paths::kJUDGES_FILE;

    std::ofstream outFile(file_name, std::ios::out);
    if (outFile.is_open())
    {
        outFile << serialized_judges_arr;
        outFile.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file: " + file_name);
    }
}

void saveEvals(const string& serialized_evals_arr)
{
    const string file_name = Paths::kEVALUATION_FILE;

    std::ofstream outFile(file_name, std::ios::out);
    if (outFile.is_open())
    {
        outFile << serialized_evals_arr;
        outFile.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file: " + file_name);
    }
}

void saveAdmins(const string& serialized_admins_arr)
{
    const string file_name = Paths::kADMINS_FILE;

    std::ofstream outFile(file_name, std::ios::out);
    if (outFile.is_open())
    {
        outFile << serialized_admins_arr;
        outFile.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file: " + file_name);
    }
}
