#pragma once
#include <string>
#include <cstdint> 


/* minSizeOf role arrays */
namespace Size
{
    inline constexpr int kMIN_SIZE_OF_TEAMS = 10;
    inline constexpr int kMIN_SIZE_OF_JUDGES = 5;
    inline constexpr int kMIN_SIZE_OF_EVALUATIONS = 30;
    inline constexpr int kMIN_SIZE_OF_ADMINS = 2;
}
namespace NumOfMembers
{
    inline constexpr int kNUM_OF_TEAM_MEMBERS = 7;
    inline constexpr int kNUM_OF_JUDGE_MEMBERS = 5;
    inline constexpr int kNUM_OF_EVALUATION_MEMBERS = 7;
    inline constexpr int kNUM_OF_ADMIN_MEMBERS = 3;
}

/* precision for floating-point conversions */
namespace Precision
{
    inline constexpr int kFLOAT_PRECISION = 5;
    inline constexpr int kDOUBLE_PRECISION = 5;
    inline constexpr unsigned short kID_DEFAULT_LENGTH = 6;
} 

/*absolute paths for codebase resources*/
namespace Paths
{
    const std::string kDATA_FOLDER_PATH = "C:/Users/ateee/Desktop/0000000000000000/SP-Project--main/dataFiles";
    const std::string kTEAMS_FILE = kDATA_FOLDER_PATH + "/teams.txt";
    const std::string kEVALUATION_FILE = kDATA_FOLDER_PATH + "/evaluations.txt";
    const std::string kJUDGES_FILE = kDATA_FOLDER_PATH + "/judges.txt";
    const std::string kADMINS_FILE = kDATA_FOLDER_PATH + "/admins.txt";
}

namespace EntityType
{
    enum EntityType
    {
        TEAM,
        JUDGE,
        EVALUATION,
        ADMIN
    };
}

namespace ProgramTypes
{
    enum ProgramTypes
    {
        TEAM,
        JUDGE,
        EVALUATION,
        ADMIN,
        STRING,
        INT,
        FLOAT,
        DOUBLE,
        NONE
    };
}

namespace RoleType
{
    enum RoleType
    {
        TEAM,
        JUDGE,
        ADMIN,
        ANONYMOUS
    };
}
namespace Status
{
    enum StatusType
    {
        STATUS_200_OK,
        STATUS_201_CREATED,
        STATUS_202_ACCEPTED,
        STATUS_204_NO_CONTENT,
        STATUS_401_UNAUTHORIZED,
        STATUS_404_NOT_FOUND,
    };
}


/* struct schemas for project entities */

// struct of a ( Team )
struct Team 
{
    std::string team_id_;
    std::string team_name_;
    std::string university_name_;
    unsigned short number_of_members_;
    std::string project_title_;
    float final_score_;
    unsigned short rank_;
};

// struct of a ( Judge )
struct Judge 
{
    std::string judge_id_;
    std::string name_;
    std::string specialty_;
    std::string username_;
    std::string password_; // hashed
};

// struct of ( Evaluation )
struct Evaluation
{
    std::string evaluation_id_;
    std::string team_id_;
    std::string judge_id_;
    unsigned short innovation_score_; // 0 to 10
    unsigned short technical_score_; // 0 to 10
    unsigned short presentation_score_; // 0 to 10
    unsigned short total_score_; // 0 to 30
};

// struct of ( Admin )
struct Admin
{
    std::string admin_id_;
    std::string username_;
    std::string password_; // hashed
};

// struct of current logged in user ( can be either a judge or an admin )
struct CurrentUser
{
    const void *user_ptr_;
    RoleType::RoleType user_type_;
};

struct Response
{
    const void *content_ptr_;
    ProgramTypes::ProgramTypes content_type_;
    Status::StatusType status_;
};