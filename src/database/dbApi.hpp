#pragma once
#include <string>
#include "../config/config.hpp"

using std::string;

// A Function that returns database file of a given (enum)Entity as a string
// @param entity the type of entity to get its databse file as a string
// @return the content of the database file of the given entity as a string
string getShard(EntityType::EntityType entity);

// A Function that saves the serialized data of a given (enum)Entity to its database file
// @param entity the type of entity to save its data
// @param serialized_entity_arr the serialized data of the entity to be saved
void SaveShard(EntityType::EntityType entity , const string& serialized_entity_arr);