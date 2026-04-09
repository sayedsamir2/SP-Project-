#include "../config/config.hpp"
#include "numericUtils.hpp"
#include "stringUtils.hpp"
#include "conversionUtils.hpp"
#include <cmath>

// A Function to convert a char to a number form, if the char is not a number it returns -1
int charToNum(const char& c)
{
    return inRange( (int)c , 48 , 57 ) ? c - 48 : -1;
}

// A Function to convert a number to its character form, if the number is not a valid digit it returns ' '
char numToChar(const int& num)
{
    return inRange(num,0,9) ? (char)(num + 48) : ' ';
}

// A Function to convert a string of numbers to an integer
int numAstr(const string& str)
{
    int result = 0;
    for(char c : str)
    {
        if (c == '-') continue;
        result += charToNum(c);
        result *= 10;
    }
    return str[0] == '-' ? -result / 10 : result / 10;
}

// A Function to convert an integer to a string
string stringfyNum(int num)
{
    bool is_negative = num < 0;
    num = abs(num);
    int limit = lengthOfNum(num);
    string result = "";
    for (int i = 0; i < limit; i++)
    {
        int last_num = num % 10;
        result = concatString(numToChar(last_num),result);
        num/=10;
    }
    return is_negative ? '-' + result : result;
}
/********************************************************** */
// A Function to convert a float to a string with a specific percision
string stringfyFloat(float num , int percision)
{
    float decimal_part = roundDecTo( ( num - (int)num ) , percision );
    int decimal_as_int = abs((decimal_part * (int)pow(10,percision)));
    return stringfyNum((int)num) + '.' + stringfyNum(decimal_as_int);
}
// A Function to convert a double to a string with a specific percision
string stringfyDouble(double num , int percision)
{
    double decimal_part = roundDecTo( ( num - (int)num ) , percision );
    int decimal_as_int = abs((decimal_part * (int)pow(10,percision)));
    return stringfyNum((int)num) + '.' + stringfyNum(decimal_as_int);
}
/*-----------------------------------------------------------*/

// A Function to convert a string to a float with a specific percision
float floatStr(const string& num_str , int percision)
{
    bool is_negative = num_str[0] == '-';

    int whole_part = is_negative 
                    ? numAstr(substr( num_str , 1 , indexOfChar('.',num_str)-1 )) 
                    : numAstr(substr( num_str , 0 , indexOfChar('.',num_str)-1 ));

    float decimal_part = numAstr(substr( num_str , indexOfChar('.',num_str)+1 ));
    return is_negative ? negative( whole_part + decimal_part* pow(10,-1*lengthOfNum(decimal_part)) ) : whole_part + decimal_part* pow(10,-1*lengthOfNum(decimal_part));
}

// A Function to convert a string to a double with a specific percision
double doubleStr(const string& num_str , int percision)
{
    bool is_negative = num_str[0] == '-';
    int whole_part = is_negative ? numAstr(substr( num_str , 1 , indexOfChar('.',num_str)-1 )) : numAstr(substr( num_str , 0 , indexOfChar('.',num_str)-1 ));
    double decimal_part = numAstr(substr( num_str , indexOfChar('.',num_str)+1 ));
    return is_negative ? -1*( whole_part + decimal_part* pow(10,-1*lengthOfNum(decimal_part)) ) : whole_part + decimal_part* pow(10,-1*lengthOfNum(decimal_part));
}