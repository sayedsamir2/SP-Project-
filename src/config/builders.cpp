#include "builders.hpp"
#include "config.hpp"
#include "../utils/otherUtils.hpp"
#include <string>
using std::string;

string generateTeamId(){
    static int team_id_counter = 1;
    return "team_" + std::to_string(team_id_counter++);
}
string generateJudgeId(){
    static int judge_id_counter = 1;
    return "judge_" + std::to_string(judge_id_counter++);
}
string generateEvalId(){
    static int eval_id_counter = 1;
    return "eval_" + std::to_string(eval_id_counter++);
}
string generateAdminId(){
    static int admin_id_counter = 1;
    return "admin_" + std::to_string(admin_id_counter++);
}
Team createTeam(const string& team_name, const string& university_name, unsigned short number_of_members, const string& project_title)
{
    Team team;
    team.team_id_ = generateTeamId();
    team.team_name_ = team_name;
    team.project_title_ = project_title;
    team.university_name_ = university_name;
    team.number_of_members_ = number_of_members;
    team.final_score_ = 0.0f;
    team.rank_ = 0;
    return team;
}
Team updateTeam(Team team_to_update,const string& team_name, const string& university_name, unsigned short number_of_members, const string& project_title)
{
    Team team;
    team.team_id_ = team_to_update.team_id_;
    team.team_name_ = team_name;
    team.project_title_ = project_title;
    team.university_name_ = university_name;
    team.number_of_members_ = number_of_members;
    team.final_score_ = team_to_update.final_score_;
    team.rank_ = team_to_update.rank_;
    return team;
}

Judge createJudge(const string& name, const string& specialty, const string& username, const string& password)
{
    Judge judge;
    judge.judge_id_ = generateJudgeId();
    judge.name_ = name;
    judge.specialty_ = specialty;
    judge.username_ = username;
    judge.password_ = hashPassword(password);
    return judge;
}

Evaluation createEvaluation(const string& team_id, const string& judge_id, unsigned short innovation_score, unsigned short technical_score, unsigned short presentation_score)
{
    Evaluation evaluation;
    evaluation.evaluation_id_ = generateEvalId();
    evaluation.team_id_ = team_id;
    evaluation.judge_id_ = judge_id;
    evaluation.innovation_score_ = innovation_score;
    evaluation.technical_score_ = technical_score;
    evaluation.presentation_score_ = presentation_score;
    evaluation.total_score_ = innovation_score + technical_score + presentation_score;
    return evaluation;
}

Admin createAdmin(const string& name, const string& username, const string& password)
{
    Admin admin;
    admin.admin_id_ = generateAdminId();
    admin.username_ = username;
    admin.password_ = hashPassword(password);
    return admin;
}