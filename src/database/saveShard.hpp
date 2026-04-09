#pragma once
#include <string>
using std::string;

// A function that saves the teams stringfied arr to the teams file.
// @param  serialized_teams_arr
// @throws runtime_error If the file cannot be opened for writing
void saveTeams(const string& serialized_teams_arr);

// A function that saves the judges stringfied arr to the judges file.
// @param  serialized_judges_arr
// @throws runtime_error If the file cannot be opened for writing
void saveJudges(const string& serialized_judges_arr);

// A function that saves the evaluations stringfied arr  to the evaluations file.
// @param  serialized_evals_arr
// @throws runtime_error If the file cannot be opened for writing
void saveEvals(const string& serialized_evals_arr);

// A function that saves the evaluations stringfied arr  to the evaluations file.
// @param  serialized_evaluations_arr
// @throws runtime_error If the file cannot be opened for writing
void saveAdmins(const string& serialized_admins_arr);