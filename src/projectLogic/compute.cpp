#include "compute.hpp"
#include "../config/config.hpp"
#include "../dataStore/dataStore.hpp"
#include <string>
using std::string;

float calculateFinalScore(const string& team_id)
{
    int sum = 0;
    int count = 0;

    for (int j = 0; j < getNumberOfEvaluations(); j++)
    {
        if (getEvalAt(j).team_id_ == team_id)
        {
            sum += getEvalAt(j).total_score_;
            count++;
        }
    }



    if (count > 0)
    {
        Team current_team = getTeamAt(getTeamIdxById(team_id));
        current_team.final_score_ = (count > 0) ? ((float)sum / count) : 0;
        setTeamAt(current_team, getTeamIdxById(team_id));
        return (float)sum / count;
    }
    else
        return 0;
}

// A function that assigns final scores to all teams in the teams array based on their evaluations.
void assignFinalScores()
{
    for (unsigned int i = 0; i < getNumberOfTeams(); i++)
    {
        Team current_team = getTeamAt(i);
        current_team.final_score_ = calculateFinalScore(current_team.team_id_);
        setTeamAt(current_team, i);
    }
    
}

//Function swap is used in teams sorting
void swapTwoTeams( unsigned short idx_1 , unsigned short idx_2 )
{
    Team temp = getTeamAt(idx_1);
    setTeamAt(getTeamAt(idx_2), idx_1);
    setTeamAt(temp, idx_2);
}

//Sort teams by their score in descending order
void sortTeams ()
{
    for (int i = 0; i < getNumberOfTeams() ; ++i)
        {
        //Distributing each team according to its ranking  
        for (int j = 0; j < getNumberOfTeams()-i-1 ; ++j)
        {
            if ( getTeamAt(j).final_score_ < getTeamAt(j+1).final_score_ )
                swapTwoTeams( j , j+1 );
        }
    }
}
//Gives each team its ranking 
void rankAllTeams () 
{
    assignFinalScores();
    sortTeams();
    for (int i = 0; i < getNumberOfTeams() ; ++i) 
    {
        setTeamRank(i,i+1);
    }
}