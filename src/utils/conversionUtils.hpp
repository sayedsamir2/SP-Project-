#pragma once
#include <string>
#include "../config/config.hpp"
using std::string;

// A Function to convert a char to a number form, if the char is not a number it returns -1
// @param c The character to convert.
// @return The integer representation of the character, or -1 if it's not a valid digit
int charToNum(const char& c);

// A Function to convert a number to its character form, if the number is not a valid digit it returns ' '
// @param num The integer to convert.
// @return The character representation of the integer, or ' ' if it's not a valid digit
char numToChar(const int& num);

// A Function to convert a string of numbers to an integer
// @param str The string to convert.
// @return The integer representation of the string, or -1 if the string is not a
int numAstr(const string& str);

// A Function to convert an integer to a string format
// @param num The integer to convert.
// @return The string representation of the integer.
string stringfyNum(int num);

// A Function to convert a float to a string with a specific percision
// @param num The float to convert.
// @param percision The number of decimal places to include in the string representation.
// @return The string representation of the float with the specified percision.
string stringfyFloat(float num , int percision = Precision::kFLOAT_PRECISION);

// A Function to convert a double to a string with a specific percision
// @param num The double to convert.
// @param percision The number of decimal places to include in the string representation.
// @return The string representation of the double with the specified percision.
string stringfyDouble(double num , int percision = Precision::kDOUBLE_PRECISION );

// A Function to convert a string to a float with a specific percision
// @param num_str The string to convert.
// @param percision The number of decimal places to consider in the conversion.
// @return The float representation of the string
float floatStr(const string& num_str , int percision = Precision::kFLOAT_PRECISION );

// A Function to convert a string to a double with a specific percision
// @param num_str The string to convert.
// @param percision The number of decimal places to consider in the conversion.
// @return The double representation of the string
double doubleStr(const string& num_str , int percision  = Precision::kDOUBLE_PRECISION);
