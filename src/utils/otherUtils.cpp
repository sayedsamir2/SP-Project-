#include "otherUtils.hpp"
#include <bcrypt/bcrypt.h>
#include <stdexcept>
#include <string>
#include <random>
using std::string;

string generateID(unsigned short length)
{
    const std::string chars =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, chars.size() - 1);

    std::string id;

    for (int i = 0; i < length; ++i) {
        id += chars[dist(gen)];
    }

    return id;
}


string hashPassword(const string& password)
{
    char hash[BCRYPT_HASHSIZE];
    char salt[BCRYPT_HASHSIZE];

    // e3mel salt (cost = 12)
    if (bcrypt_gensalt(12, salt) != 0) {
        throw std::runtime_error("bcrypt gensalt failed");
    }

    // Hash password using that salt
    if (bcrypt_hashpw(password.c_str(), salt, hash) != 0) {
        throw std::runtime_error("bcrypt hashing failed");
    }

    return string(hash);
}