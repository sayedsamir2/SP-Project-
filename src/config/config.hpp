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

/* precision for floating-point conversions */
namespace Precision
{
    inline constexpr int kFLOAT_PRECISION = 5;
    inline constexpr int kDOUBLE_PRECISION = 5;  
} 

/*absolute paths for codebase resources*/
namespace Paths 
{
    constexpr char kTEAMS_FILE[] = "/home/ezat/Desktop/workspace/spProject/dataFiles/teams.txt";
    constexpr char kEVALUATION_FILE[] = "/home/ezat/Desktop/workspace/spProject/dataFiles/evaluations.txt";
    constexpr char kJUDGES_FILE[] = "/home/ezat/Desktop/workspace/spProject/dataFiles/judges.txt";
    constexpr char kADMINS_FILE[] = "/home/ezat/Desktop/workspace/spProject/dataFiles/admins.txt";
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


/* struct schemas for project entities */

// struct of a ( Team )
struct Team 
{
    std::string team_id_;
    std::string team_name_;
    std::string university_name_;
    unsigned short int number_of_members_;
    std::string project_title_;
    float final_score_;
    unsigned short int rank_;
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
    unsigned short int innovation_score_; // 0 to 10
    unsigned short int technical_score_; // 0 to 10
    unsigned short int presentation_score_; // 0 to 10
    unsigned short int total_score_; // 0 to 30
};

// struct of ( Admin )
struct Admin
{
    std::string admin_id_;
    std::string username_;
    std::string password_; // hashed
};


