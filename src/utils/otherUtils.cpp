#include "otherUtils.hpp"
#include <string>
using std::string;

string hashPassword(const string& password)
{
    string hashed_password = "hashed_" + password;
    return hashed_password;
}