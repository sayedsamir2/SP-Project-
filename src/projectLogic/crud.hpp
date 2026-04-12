#pragma once
#include "../config/config.hpp"
#include <string>
using std::string;

void registerNewTeam(const string& team_name, const string& university_name, unsigned short int number_of_members, const string& project_title);
Response getTeamById(const string& id);
Response modifyTeamById(const string& id ,const string& team_name, const string& university_name, unsigned short int number_of_members, const string& project_title);
Response submitProjectByTeamId(const string& id , const string& project_title);
Response AddEvaluation(const string& team_id, const string& judge_id, unsigned short innovation_score, unsigned short technical_score, unsigned short presentation_score);