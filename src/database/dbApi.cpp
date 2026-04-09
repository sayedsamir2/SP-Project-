#include "dbApi.hpp"
#include "getShard.hpp"
#include "saveShard.hpp"
#include "../config/config.hpp"
#include <string>

using std::string;

string getShard(EntityType::EntityType entity)
{
    switch (entity)
    {
        case EntityType::TEAM :
            return getTeams();
            break;
        case EntityType::JUDGE :
            return getJudges();
            break;
        case EntityType::EVALUATION :
            return getEvals();
            break;
        case EntityType::ADMIN :
            return getAdmins();
            break;
        default:
            break;
    }
    return "";
}

void SaveShard(EntityType::EntityType entity , const string& serialized_entity_arr)
{
    switch (entity)
    {
        case EntityType::TEAM :
            // return STeams();
            saveTeams(serialized_entity_arr);
            break;
        case EntityType::JUDGE :
            saveJudges(serialized_entity_arr);
            break;
        case EntityType::EVALUATION :
            saveEvals(serialized_entity_arr);
            break;
        case EntityType::ADMIN :
            saveAdmins(serialized_entity_arr);
            break;
        default:
            break;
    }
}