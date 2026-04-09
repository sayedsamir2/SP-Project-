#include "../config/config.hpp"
#include "conversionUtils.hpp"
#include "stringUtils.hpp"
#include "deserializationUtils.hpp"

/* deserialize Entity functions */

// Converts a team string into a Team struct.
Team deserializeTeam(const string& serialized_team)
{
    string entity_string = serialized_team;
    Team team = {};
    if (countChar('|' , entity_string) == 0) return team;
    for (int i = 1; i <= 7; i++)
    {
        if (i == 1)
        {
            string team_id = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            team.team_id_ = team_id;
        }
        else if(i == 2){
            string team_name = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            team.team_name_ = team_name;
        }
        else if(i == 3){
            string university_name = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            team.university_name_ = university_name;
        }
        else if(i == 4){
            string number_of_members = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            team.number_of_members_ = numAstr( number_of_members );
        }
        else if(i == 5){
            string project_title = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            team.project_title_ = project_title;
        }
        else if(i == 6){
            string final_score = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            team.final_score_ = floatStr( final_score );
        }
        else if(i == 7){
            string rank = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            team.rank_ = numAstr( rank );
        }
        
    }
    
    return team;
}


// Converts a judge string into a Judge struct.
Judge deserializeJudge(const string& serialized_judge)
{
    string entity_string = serialized_judge;
    Judge judge = {};
    if (countChar('|' , entity_string) == 0) return judge;
    for (int i = 1; i <= 5; i++)
    {
        if (i == 1)
        {
            string judge_id = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            judge.judge_id_ = judge_id;
        }
        else if(i == 2){
            string name = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            judge.name_ = name;
        }
        else if(i == 3){
            string speciality = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            judge.specialty_ = speciality;
        }
        else if(i == 4){
            string username = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            judge.username_ = username;
        }
        else if(i == 5){
            string password = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            judge.password_ = password;
        }
        
    }
    
    return judge;
}


// Converts an evaluation string into an Evaluation struct.
Evaluation deserializeEvaluation(const string& serialized_evaluation)
{
    string entity_string = serialized_evaluation;
    Evaluation evaluation = {};
    if (countChar('|' , entity_string) == 0) return evaluation;

    for (int i = 1; i <= 7; i++)
    {
        if (i == 1)
        {
            string evaluation_id = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            evaluation.evaluation_id_ = evaluation_id;
        }
        else if(i == 2){
            string team_id = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            evaluation.team_id_ = team_id;
        }
        else if(i == 3){
            string judge_id = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            evaluation.judge_id_ = judge_id;
        }
        else if(i == 4){
            string innovation_score = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            evaluation.innovation_score_ = numAstr(innovation_score);
        }
        else if(i == 5){
            string technical_score = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            evaluation.technical_score_ = numAstr(technical_score);
        }
        else if(i == 6){
            string presentation_score = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            evaluation.presentation_score_ = numAstr(presentation_score);
        }
        else if(i == 7){
            string total_score = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            evaluation.total_score_ = numAstr(total_score);
        }
    }
    return evaluation; 
}


// Converts an admin string into an Admin struct.
Admin deserializeAdmin(const string& admin_string)
{
    string entity_string = admin_string;
    Admin admin = {};
    if (countChar('|' , entity_string) == 0) return admin;
    for (int i = 1; i <= 3; i++)
    {
        if (i == 1)
        {
            string admin_id = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            admin.admin_id_ = admin_id;
        }
        else if(i == 2){
            string username = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            admin.username_ = username;
        }
        else if(i == 3){
            string password = substr( f_cutSubString(entity_string,0,indexOfChar('|' , entity_string)) , 0 , indexOfChar('|' , entity_string)-1 );
            admin.password_ = password;
        }
    }
    return admin;
}
/***************************************************************/

void deserializeTeamArrStr(const string& des_team_arr , Team* team_arr)
{
    string team_arr_str = des_team_arr;
    int number_of_teams = countChar('\n',team_arr_str);

    for (int i = 0; i < number_of_teams; i++)
    {
        string team_str = substr( f_cutSubString(team_arr_str,0,indexOfChar('\n',team_arr_str)) , 0 , indexOfChar('\n',team_arr_str)-1 );
        team_arr[i] = deserializeTeam(team_str);
    }
    
}

void deserializeJudgeArrStr(const string& des_judge_arr , Judge* judge_arr)
{
    string judge_arr_str = des_judge_arr;
    int number_of_judges = countChar('\n',judge_arr_str);

    for (int i = 0; i < number_of_judges; i++)
    {
        string judge_str = substr( f_cutSubString(judge_arr_str,0,indexOfChar('\n',judge_arr_str)) , 0 , indexOfChar('\n',judge_arr_str)-1 );
        judge_arr[i] = deserializeJudge(judge_str);
    }
    
}

void deserializeEvalArrStr(const string& des_evaluation_arr , Evaluation* evaluation_arr)
{
    string evaluation_arr_str = des_evaluation_arr;
    int number_of_evaluations = countChar('\n',evaluation_arr_str);

    for (int i = 0; i < number_of_evaluations; i++)
    {
        string evaluation_str = substr( f_cutSubString(evaluation_arr_str,0,indexOfChar('\n',evaluation_arr_str)) , 0 , indexOfChar('\n',evaluation_arr_str)-1 );
        evaluation_arr[i] = deserializeEvaluation(evaluation_str);
    }   
}

void deserializeAdminArrStr(const string& des_admin_arr , Admin* admin_arr)
{
    string admin_arr_str = des_admin_arr;
    int number_of_admins = countChar('\n',admin_arr_str);

    for (int i = 0; i < number_of_admins; i++)
    {
        string admin_str = substr( f_cutSubString(admin_arr_str,0,indexOfChar('\n',admin_arr_str)) , 0 , indexOfChar('\n',admin_arr_str)-1 );
        admin_arr[i] = deserializeAdmin(admin_str);
    }
}