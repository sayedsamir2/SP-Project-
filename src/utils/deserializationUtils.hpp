#pragma once
#include <string>
#include "../config/config.hpp"
using std::string;

// deserialization utility functions

// Converts a team string into a Team struct.
// @param team_string The string to deserialize.
// @return The deserialized Team struct.
Team deserializeTeam(const string& serialized_team);

// Converts a judge string into a Judge struct.
// @param judge_string The string to deserialize.
// @return The deserialized Judge struct.
Judge deserializeJudge(const string& serialized_judge);

// Converts an evaluation string into an Evaluation struct.
// @param evaluation_string The string to deserialize.
// @return The deserialized Evaluation struct.
Evaluation deserializeEvaluation(const string& serialized_evaluation);

// Converts an admin string into an Admin struct.
// @param admin_string The string to deserialize.
// @return The deserialized Admin struct.
Admin deserializeAdmin(const string& admin_string);

/*****************************************************************/

// A function 
void deserializeTeamArrStr(const string& team_arr_str , Team* team_arr);