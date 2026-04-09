#pragma once

// A function that returns the length of a given number (number of digits)
// @param num The number to evaluate.
// @return The number of digits in the given number.
int lengthOfNum(int num);

// A function that checks if a number is in a given range (inclusive)
// @param num The number to check.
// @param start The start of the range.
// @param end The end of the range.
// @return True if the number is in the range, false otherwise.
bool inRange(int num,int start,int end);

// A function that rounds a float to the nearest integer
// @param num The float to round.
// @return The rounded integer.
int roundFirst(float num);

// A function that rounds a double to the nearest integer
// @param num The double to round.
// @return The rounded integer.
int roundFirst(double num);

// A function that rounds a float to a specified number of decimal places
// @param num The float to round.
// @param place The number of decimal places to round to.
// @return The rounded float.
float roundDecTo(float num,int place = 1);

// A function that rounds a double to a specified number of decimal places
// @param num The double to round.
// @param place The number of decimal places to round to.
// @return The rounded double.
double roundDecTo(double num,int place = 1);

// A function that ensures the return of the negative of a given number
// @param num The number to negate.
// @return The negative of the given number.
int negative(int num);
float negative(float num);
double negative(double num);

// A function that reverses the sign of a number
// @param num The number to reverse the sign of.
// @return The number with its sign reversed.
int reverseSign(int num);
float reverseSign(float num);
double reverseSign(double num);