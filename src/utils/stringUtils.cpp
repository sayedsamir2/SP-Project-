#include "stringUtils.hpp"


string concatString(const string& str1 , const string& str2)
{
    return str1 + str2;
}

string concatString(const string& str1 , const char& str2  )
{
    return str1 + str2;
}

string concatString(const char& str1 , const string& str2  ) 
{
    return str1 + str2;
}

/************************************************/

int indexOfChar(const char& letter , const string& word)
{

    for(int i = 0; i < word.size();i++)
    {
        if(word[i] == letter)
        {
            return i;
        }
    }
    return -1;
}

/*******************************************************/

string substr(const string& str, const int& start, int end)
{
    string result = "";
    if (end < 0)
    {
        end = str.size();
    }
    
    for(int i = start ; i <= end && i < str.size() ; i++)
    {
        result += str[i];
    }
    return result;
}

/********************************************************/
string cutSubString(const string& str , const int& start , const int& end)
{
    return substr(str , 0 , start-1) + substr( str , end+1);
}
string f_cutSubString(string& str , const int& start , const int& end)
{
    if (start < 0 || end >= str.size() || start > end) return "";
    string cutted_str = substr(str,start,end);
    str = start!= 0 ? substr(str , 0 , start-1) + substr( str , end+1) : substr( str , end+1);
    return cutted_str;
}

int countChar(const char& target , const string& str)
{
    int counter = 0;
    for (char c : str)
    {
        if (c==target) counter++;
    }
    return counter;
}