#include <cmath>
#include "numericUtils.hpp"

int lengthOfNum(int num)
{
    return num > 0 ? (int)log10(num) + 1 : 1;
}


bool inRange(int num,int start,int end)
{
    return num >= start && num <= end;
}
/******************************** */

int roundFirst(float num)
{
    int result = 0;
    if (num >= 0 && (num - (int)num) >= 0.5)
    {
        result += (int)num + 1;
    }
    else if(num >= 0 && (num - (int)num) < 0.5)
    {
        result += (int)num;
    }
    else if(num <= 0 && (num - (int)num) > -0.5)
    {
        result += (int)num;
    }
    else if(num <= 0 && (num - (int)num) <= -0.5)
    {
        result += (int)num - 1;
    }
    return result;
}
int roundFirst(double num)
{
    int result = 0;
    if (num >= 0 && (num - (int)num) >= 0.5)
    {
        result += (int)num + 1;
    }
    else if(num >= 0 && (num - (int)num) < 0.5)
    {
        result += (int)num;
    }
    else if(num <= 0 && (num - (int)num) > -0.5)
    {
        result += (int)num;
    }
    else if(num <= 0 && (num - (int)num) <= -0.5)
    {
        result += (int)num - 1;
    }
    return result;
}
/************************************** */
float roundDecTo(float num,int place)
{
    return roundFirst(num*pow(10,place))/pow(10,place);
}

double roundDecTo(double num,int place)
{
    return roundFirst(num*pow(10,place))/pow(10,place);
}
/******************************************/
int negative(int num){
    return num < 0 ? num : -1*num;
}
float negative(float num){
    return num < 0 ? num : -1*num;
}
double negative(double num){
    return num < 0 ? num : -1*num;
}
/*****************************************/
int reverseSign(int num){
    return num * -1;
}
float reverseSign(float num){
    return num * -1;
}
double reverseSign(double num){
    return num * -1;
}
/****************************************/