#include "conversionUtils.hpp"
#include "stringUtils.hpp"
#include "serializationUtils.hpp"
using std::string;

/* serialize Entity functions */


string serializeEntity(const Team& team)
{
    string serialized_str = team.team_id_ + "|" 
                            + team.team_name_ + "|" 
                            + team.university_name_ + "|"
                            + stringfyNum(team.number_of_members_) + "|"
                            + team.project_title_ + "|"
                            + stringfyFloat(team.final_score_) + "|"
                            + stringfyNum(team.rank_) + "|";
    return serialized_str;
};

string serializeEntity(const Judge& judge)
{
    string serialized_str = judge.judge_id_ + "|" 
                            + judge.name_ + "|" 
                            + judge.specialty_ + "|"
                            + judge.username_ + "|"
                            + judge.password_ + "|";
    return serialized_str;
};

string serializeEntity(const Evaluation& evaluation)
{
    string serialized_str = evaluation.evaluation_id_ + "|"
                            + evaluation.team_id_ + "|"
                            + evaluation.judge_id_ + "|"
                            + stringfyNum(evaluation.innovation_score_) + "|"
                            + stringfyNum(evaluation.technical_score_) + "|"
                            + stringfyNum(evaluation.presentation_score_) + "|"
                            + stringfyNum(evaluation.total_score_) + "|";
    return serialized_str;
};

string serializeEntity(const Admin& admin)
{
    string serialized_str = admin.admin_id_ + "|"
                            + admin.username_ + "|"
                            + admin.password_ + "|";
    return serialized_str;
};


/*********************************************************/
// Converts an array of Team structs into a single string.
// @param team_struct_arr Array of Team structs.
// @return The serialized string representation.
string serializeEntityArr(const Team* const team_struct_arr , int size)
{
    string serialized_str = "";
    for (int i = 0; i < size; i++)
    {
        serialized_str += serializeEntity(team_struct_arr[i]) + ';';
    }
    return serialized_str;
}


// Converts an array of Judge structs into a single string.
// @param judge_struct_arr Array of Judge structs.
// @return The serialized string representation.
string serializeEntityArr(const Judge* const judge_struct_arr , int size)
{
    string serialized_str = "";
    for (int i = 0; i < size; i++)
    {
        serialized_str += serializeEntity(judge_struct_arr[i]) + ';';
    }
    return serialized_str;
}


// Converts an array of Evaluation structs into a single string.
// @param evaluation_struct_arr Array of Evaluation structs.
// @return The serialized string representation.
string serializeEntityArr(const Evaluation* const evaluation_struct_arr, int size)
{
    string serialized_str = "";
    for (int i = 0; i < size; i++)
    {
        serialized_str += serializeEntity(evaluation_struct_arr[i]) + ';';
    }
    return serialized_str;
}


// Converts an array of Admin structs into a single string.
// @param admin_struct_arr Array of Admin structs.
// @return The serialized string representation.
string serializeEntityArr(const Admin* const admin_struct_arr, int size)
{
    string serialized_str = "";
    for (int i = 0; i < size; i++)
    {
        serialized_str += serializeEntity(admin_struct_arr[i]) + ';';
    }
    return serialized_str;
}