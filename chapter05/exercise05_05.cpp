// a program takes in a temperature value in Celsius and converts it to Kelvin.
// add to the program so that it can also convert from Kelvin to Celsius.
#include "std_lib_facilities.h"

double ctok(double c)
// converts Celsius to Kelvin
// pre-conditions: double c, Celsius, should not be given below -273.15
// post-condition: returns a positive value that is the Kelvin
{
    if (c < -273.15)
        error("ctok() pre-condition");
    double k = c + 273.15;
    if (k < 0)
        error("ctok() post-condition");
    return k;
}

double ktoc(double k)
// converts Kelvin to Celsius
// pre-conditions: double k, Kelvin, should not be given below 0
// post-condition: returns a temperature value in Celsius that is greater than or equal to -273.15
{
    if (k < 0)
        error("ktoc() pre-condition");
    double c = k - 273.15;
    if (c < -273.15)
        error("ktoc() post-condition");
    return c;
}

int main()
{
    double c = 0;       // declare input variable
    cin >> c;           // retrieve temperature to input variable
    double k = ctok(c); // convert temperature
    cout << k << '\n';  // print out temperature

    cin >> k;          // retrieve temperature to input variable
    c = ktoc(k);       // convert temperature
    cout << c << '\n'; // print out temperature
}
