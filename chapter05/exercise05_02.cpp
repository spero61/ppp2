// a program takes in a temperature value in Celsius and converts it to Kelvin.
// find the errors, list them, and correct the code

#include "std_lib_facilities.h"

/*
double ctok(double c) // converts Celsius to Kelvin
{
    int k = c + 273.15;  // truncation of double into int 
    return int    // semi-colon is missing, should return variable k
}
int main()
{
    double c = 0;         
    cin >> d;             // there is no variable declared as d, might be its typo of c
    double k = ctok("c"); // variable c should not be double quoted
    Cout << k << '/n';    // cout should be all in lower case, use backslash(\) instead of /
}
*/

double ctok(double c) // converts Celsius to Kelvin
{
    double k = c + 273.15;
    return k;
}
int main()
{
    double c = 0;       // declare input variable
    cin >> c;           // retrieve temperature to input variable
    double k = ctok(c); // convert temperature
    cout << k << '\n';  // print out temperature
}
