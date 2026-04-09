#pragma once
#include <string>
#include "../config/config.hpp"
using std::string;

/* database serialization utility functions */

// Converts a team struct into a string.
// @param team The Team struct to serialize.
// @return The serialized string representation of the Team struct.
string serializeEntity(const Team& team);

// Converts a judge struct into a string.
// @param judge The Judge struct to serialize.
// @return The serialized string representation of the Judge struct.
string serializeEntity(const Judge& judge);

// Converts an evaluation struct into a string.
// @param evaluation The Evaluation struct to serialize.
// @return The serialized string representation of the Evaluation struct.
string serializeEntity(const Evaluation& evaluation);

// Converts an admin struct into a string.
// @param admin The Admin struct to serialize.
// @return The serialized string representation of the Admin struct.
string serializeEntity(const Admin& admin);


// Converts an array of Team structs into a single string.
// @param team_struct_arr Array of Team structs.
// @return The serialized string representation.
string serializeEntityArr(const Team* const team_struct_arr , int size = Size::kMIN_SIZE_OF_TEAMS);


// Converts an array of Judge structs into a single string.
// @param judge_struct_arr Array of Judge structs.
// @return The serialized string representation.
string serializeEntityArr(const Judge* const judge_struct_arr , int size = Size::kMIN_SIZE_OF_JUDGES);


// Converts an array of Evaluation structs into a single string.
// @param evaluation_struct_arr Array of Evaluation structs.
// @return The serialized string representation.
string serializeEntityArr(const Evaluation* const evaluation_struct_arr, int size = Size::kMIN_SIZE_OF_EVALUATIONS);


// Converts an array of Admin structs into a single string.
// @param admin_struct_arr Array of Admin structs.
// @return The serialized string representation.
string serializeEntityArr(const Admin* const admin_struct_arr, int size = Size::kMIN_SIZE_OF_ADMINS);