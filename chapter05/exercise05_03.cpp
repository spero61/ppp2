// a program takes in a temperature value in Celsius and converts it to Kelvin.
#include "std_lib_facilities.h"

double ctok(double c)
// converts Celsius to Kelvin
// pre-conditions: double c, Celsius, should not be given below -273.15
// post-condition: returns a positive value that is the Kelvin
{
    double k = c + 273.15;
    return k;
}
int main()
{
    double c = 0; // declare input variable
    cin >> c;     // retrieve temperature to input variable
    if (c < -273.15)
        error("c, Celsius, should not be below -273.15");
    double k = ctok(c); // convert temperature
    cout << k << '\n';  // print out temperature
}
