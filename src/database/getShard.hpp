#pragma once
#include <string>
using std::string;

// A function that reads the teams file and returns its content as a string.
// @return The content of the teams file as a string. [The deserialized teams array string]
// @throws runtime_error If the file cannot be opened for reading
string getTeams();

// A function that reads the judges file and returns its content as a string.
// @return The content of the judges file as a string. [The deserialized judges array string]
// @throws runtime_error If the file cannot be opened for reading
string getJudges();

// A function that reads the evaluations file and returns its content as a string.
// @return The content of the evaluations file as a string. [The deserialized evaluations array string]
// @throws runtime_error If the file cannot be opened for reading
string getEvals();

// A function that reads the admins file and returns its content as a string.
// @return The content of the admins file as a string. [The deserialized admins array string]
// @throws runtime_error If the file cannot be opened for reading
string getAdmins();
