#include "../config/config.hpp"
#include "../database/dbApi.hpp"
#include "../utils/numericUtils.hpp"
#include "../utils/serializationUtils.hpp"
#include "../utils/deserializationUtils.hpp"

#include <stdexcept>
#include <string>
using std::string;

static Team teams[Size::kMIN_SIZE_OF_TEAMS];
static unsigned int number_of_teams = 0;

static Judge judges[Size::kMIN_SIZE_OF_JUDGES];
static unsigned int number_of_judges = 0;

static Evaluation evaluations[Size::kMIN_SIZE_OF_EVALUATIONS];
static unsigned int number_of_evaluations = 0;

static Admin admins[Size::kMIN_SIZE_OF_ADMINS];
static unsigned int number_of_admins = 0;

static CurrentUser current_user = {nullptr, RoleType::ANONYMOUS};


/******************************************************************** */
void loadData()
{
    string team_arr_str = getShard(EntityType::TEAM);
    number_of_teams = deserializeTeamArrStr(team_arr_str, teams);

    string judge_arr_str = getShard(EntityType::JUDGE);
    number_of_judges = deserializeJudgeArrStr(judge_arr_str, judges);

    string evaluation_arr_str = getShard(EntityType::EVALUATION);
    number_of_evaluations = deserializeEvalArrStr(evaluation_arr_str, evaluations);

    string admin_arr_str = getShard(EntityType::ADMIN);
    number_of_admins = deserializeAdminArrStr(admin_arr_str, admins);
}

void saveData()
{
    string team_arr_str = serializeEntityArr(teams, number_of_teams);
    SaveShard(EntityType::TEAM, team_arr_str);

    string judge_arr_str = serializeEntityArr(judges, number_of_judges);
    SaveShard(EntityType::JUDGE, judge_arr_str);

    string evaluation_arr_str = serializeEntityArr(evaluations, number_of_evaluations);
    SaveShard(EntityType::EVALUATION, evaluation_arr_str);

    string admin_arr_str = serializeEntityArr(admins, number_of_admins);
    SaveShard(EntityType::ADMIN, admin_arr_str);
}
/***************************************************************************/
void setCurrentUsr(Team& team)
{
    current_user.user_ptr_ = &team;
    current_user.user_type_ = RoleType::TEAM;
}
void setCurrentUsr(Judge& judge)
{
    current_user.user_ptr_ = &judge;
    current_user.user_type_ = RoleType::JUDGE;
}
void setCurrentUsr(Admin& admin)
{
    current_user.user_ptr_ = &admin;
    current_user.user_type_ = RoleType::ADMIN;
}

CurrentUser getCurrentUsr(){
    return current_user;
}


/*************************************************************************/
unsigned int getNumberOfTeams()
{
    return number_of_teams;
}

unsigned int getNumberOfJudges()
{
    return number_of_judges;
}

unsigned int getNumberOfEvaluations()
{
    return number_of_evaluations;
}

unsigned int getNumberOfAdmins()
{
    return number_of_admins;
}
/****************************************************************************/
const Team& getTeamAt(unsigned int index)
{
    static const Team emptyTeam{};
    if (inRange(index,0,number_of_teams))
    {
        return teams[index];
    }
    else if (inRange(index,0,Size::kMIN_SIZE_OF_TEAMS))
    {
        return emptyTeam;
    }
    throw std::runtime_error("Index out of range");
    // return {};
}

const Judge& getJudgeAt(unsigned int index)
{
    static const Judge emptyJudge{};
    if (inRange(index,0,number_of_judges))
    {
        return judges[index];
    }
    else if (inRange(index,0,Size::kMIN_SIZE_OF_JUDGES))
    {
        return emptyJudge;
    }
    throw std::runtime_error("Index out of range");
    // return {};
}

const Evaluation& getEvalAt(unsigned int index)
{
    static const Evaluation emptyEvaluation{};
    if (inRange(index,0,number_of_evaluations))
    {
        return evaluations[index];
    }
    else if (inRange(index,0,Size::kMIN_SIZE_OF_EVALUATIONS))
    {
        return emptyEvaluation;
    }
    throw std::runtime_error("Index out of range");
    // return {};
}

const Admin& getAdminAt(unsigned int index)
{
    static const Admin emptyAdmin{};
    if (inRange(index,0,number_of_admins))
    {
        return admins[index];
    }
    else if (inRange(index,0,Size::kMIN_SIZE_OF_ADMINS))
    {
        return emptyAdmin;
    }
    throw std::runtime_error("Index out of range");
    // return {};
}

/**************************************************************************/
short getTeamIdxById(const string& id)
{
    for (int i = 0; i < number_of_teams; i++)
    {
        if (teams[i].team_id_ == id)
            return i;
        
    }
    return -1;
}
short getEvalIdxById(const string& id)
{
    for (int i = 0; i < number_of_evaluations; i++)
    {
        if (evaluations[i].evaluation_id_ == id)
            return i;
        
    }
    return -1;
}
/*************************************************************************/
void setTeamAt(const Team& team , unsigned int index)
{
    if (inRange(index,0,number_of_teams))
    {
        teams[index] = team;
    }
    else if (inRange(index,0,Size::kMIN_SIZE_OF_TEAMS))
    {
        teams[index] = team;
        number_of_teams++;
    }
    else
    {
        throw std::runtime_error("Index out of range");
    }
}

void setJudgeAt(const Judge& judge , unsigned int index)
{
    if (inRange(index,0,number_of_judges))
    {
        judges[index] = judge;
    }
    else if (inRange(index,0,Size::kMIN_SIZE_OF_JUDGES))
    {
        judges[index] = judge;
        number_of_judges++;
    }
    else
    {
        throw std::runtime_error("Index out of range");
    }
}

void setEvalAt(const Evaluation& evaluation , unsigned int index)
{
    if (inRange(index,0,number_of_evaluations))
    {
        evaluations[index] = evaluation;
    }
    else if (inRange(index,0,Size::kMIN_SIZE_OF_EVALUATIONS))
    {
        evaluations[index] = evaluation;
        number_of_evaluations++;
    }
    else
    {
        throw std::runtime_error("Index out of range");
    }
}

void setAdminAt(const Admin& admin , unsigned int index)
{
    if (inRange(index,0,number_of_admins))
    {
        admins[index] = admin;
    }
    else if (inRange(index,0,Size::kMIN_SIZE_OF_ADMINS))
    {
        admins[index] = admin;
        number_of_admins++;
    }
    else
    {
        throw std::runtime_error("Index out of range");
    }
}
//
void setTeamRank(unsigned short idx,unsigned short rank)
{
    teams[idx].rank_ = rank;
}