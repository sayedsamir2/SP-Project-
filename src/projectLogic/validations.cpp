#include "validations.hpp"
#include "../dataStore/dataStore.hpp"
#include "../config/config.hpp"
#include "../utils/otherUtils.hpp"
#include <string>
using std::string;


bool verifyPassword(const string& entered_password , const string& real_password)
{
    return hashPassword(entered_password) == real_password;
}

Response isAdminPresentById(const string& id)
{
    Response response = {nullptr, ProgramTypes::NONE, Status::STATUS_404_NOT_FOUND};
    for(int i = 0; i < getNumberOfAdmins();i++)
    {
        Admin current_user = getAdminAt(i);
        if (current_user.admin_id_ == id)
        {
            response.content_ptr_ = &getAdminAt(i);
            response.content_type_ = ProgramTypes::ADMIN;
            response.status_ = Status::STATUS_200_OK;
            return response;
        }
        
    }
    return response;
}
Response isTeamPresentById(const string& id)
{
    Response response = {nullptr, ProgramTypes::NONE, Status::STATUS_404_NOT_FOUND};
    for(int i = 0; i < getNumberOfTeams();i++)
    {
        Team current_user = getTeamAt(i);
        if (current_user.team_id_ == id)
        {
            response.content_ptr_ = &getTeamAt(i);
            response.content_type_ = ProgramTypes::TEAM;
            response.status_ = Status::STATUS_200_OK;
            return response;
        }
        
    }
    return response;
}

Response checkAdminByPassword(const string& user_name , const string& password)
{
    Response response = {};
    for(int i = 0; i < getNumberOfAdmins();i++)
    {
        Admin currentAdmin = getAdminAt(i);
        if (currentAdmin.username_ == user_name)
        {
            if (verifyPassword(password , currentAdmin.password_))
            {
                response.content_ptr_ = &getAdminAt(i);
                response.content_type_ = ProgramTypes::ADMIN;
                response.status_ = Status::STATUS_200_OK;
                return response;
            }
            else
            {
                response.content_ptr_ = nullptr;
                response.content_type_ = ProgramTypes::NONE;
                response.status_ = Status::STATUS_401_UNAUTHORIZED;
                return response;
            }
        }
        else
        {
            response.content_ptr_ = nullptr;
            response.content_type_ = ProgramTypes::NONE;
            response.status_ = Status::STATUS_404_NOT_FOUND;
            return response;
        }
    }
    response.status_ = Status::STATUS_401_UNAUTHORIZED;
    return response;
}