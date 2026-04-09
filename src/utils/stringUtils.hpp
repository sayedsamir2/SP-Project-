#pragma once
#include <string>
using std::string;

// functions that concatenates two strings or a string and a character and returns the result

// A function that concatenates two strings and returns the result
// @param str1 The first string to concatenate.
// @param str2 The second string to concatenate.
// @return The concatenated string.
string concatString(const string& str1 , const string& str2);
string concatString(const string& str1 , const char& str2);
string concatString(const char& str1 , const string& str2);

// A function that returns the index of a character in a string, or -1 if not found
// @param letter The character to find.
// @param word The string to search in.
// @return The index of the character in the string, or -1 if not found.
int indexOfChar(const char& letter , const string& word);

// A function that returns a substring of a string given a start index
// @param str The string to extract the substring from.
// @param start The start index of the substring.
// @param end The end index of the substring.
// @return The extracted substring.
string substr(const string& str, const int& start, int end = -1);

// A function that counts the occurrences of a character in a string
// @param target The character to count.
// @param str The string to search in.
// @return The number of occurrences of the character in the string.
int countChar(const char& target , const string& str);

// A function that removes a substring from a string given a start index
// @param str The string to remove the substring from.
// @param start The start index of the substring.
// @param end The end index of the substring.
// @return The string with the substring removed.
string cutSubString(const string& str , const int& start , const int& end);

// A function that removes a substring from a string given a start index
// @param str The string to remove the substring from.
// @param start The start index of the substring.
// @param end The end index of the substring.
// @return The string with the substring removed.
string f_cutSubString(string& str , const int& start , const int& end);
