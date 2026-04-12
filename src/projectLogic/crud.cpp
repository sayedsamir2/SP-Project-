#include "crud.hpp"
#include "../config/config.hpp"
#include "../config/builders.hpp"
#include "../dataStore/dataStore.hpp"
#include "validations.hpp"
#include <string>
using std::string;

void registerNewTeam(const string& team_name, const string& university_name, unsigned short int number_of_members, const string& project_title)
{
    Team current_team = createTeam(team_name,university_name,number_of_members,project_title);
    setTeamAt(current_team , getNumberOfTeams());
}

Response getTeamById(const string& id)
{
    Response response = {};
    for (int i = 0; i < getNumberOfTeams(); i++)
    {
        if(getTeamAt(i).team_id_ == id)
        { 
            response.content_ptr_ = &getTeamAt(i);
            response.content_type_ = ProgramTypes::TEAM;
            response.status_ = Status::STATUS_200_OK;
        }
        else{
            response.content_ptr_ = nullptr;
            response.content_type_ = ProgramTypes::NONE;
            response.status_ = Status::STATUS_404_NOT_FOUND;
        }
    }
    return response;
}

Response modifyTeamById(const string& id ,const string& team_name, const string& university_name, unsigned short number_of_members, const string& project_title)
{
    Response response = {nullptr,ProgramTypes::NONE,Status::STATUS_404_NOT_FOUND};
    Response check_response = isTeamPresentById(id);

    Team current_team = *(Team*)check_response.content_ptr_;

    Team modified_team;
    
    switch (check_response.status_)
    {
    case Status::STATUS_200_OK :
    {
        short int team_idx = getTeamIdxById(id);
        modified_team = updateTeam(current_team,team_name,university_name,number_of_members,project_title);
        setTeamAt(modified_team,team_idx);
        
        response.content_ptr_ = &getTeamAt(team_idx);
        response.content_type_ = ProgramTypes::TEAM;
        response.status_ = Status::STATUS_200_OK;
        break;
    }
    default:
        break;
    }
    return response;
}
Response submitProjectByTeamId(const string& id , const string& project_title)
{
    Response response = {nullptr,ProgramTypes::NONE,Status::STATUS_404_NOT_FOUND};
    Response check_response = isTeamPresentById(id);

    Team current_team = *(Team*)check_response.content_ptr_;

    Team modified_team;
    
    switch (check_response.status_)
    {
    case Status::STATUS_200_OK :
    {
        short int team_idx = getTeamIdxById(id);
        modified_team = updateTeam(current_team,current_team.team_name_,current_team.university_name_,current_team.number_of_members_,project_title);
        setTeamAt(modified_team,team_idx);
        
        response.content_ptr_ = &getTeamAt(team_idx);
        response.content_type_ = ProgramTypes::TEAM;
        response.status_ = Status::STATUS_200_OK;
    }
        break;
    
    default:
        break;
    }
    return response;
}
Response AddEvaluation(const string& team_id, const string& judge_id, unsigned short innovation_score, unsigned short technical_score, unsigned short presentation_score)
{
    Evaluation current_eval = createEvaluation(team_id,judge_id, innovation_score, technical_score, presentation_score);
    setEvalAt(current_eval,getNumberOfEvaluations());
    short eval_idx = getEvalIdxById(current_eval.evaluation_id_);
    Response response = {&getEvalAt(eval_idx),ProgramTypes::EVALUATION,Status::STATUS_201_CREATED};
    return response;
}

