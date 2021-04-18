// a program that converts from Celsius to Fahrenheit and from Fahrenheit to Celsius
// Use estimation to see if your results are plausible.

// Results are plausible as long as inputs are "plausible".
// But it is hard to say that I can recognize a plausible result.
// It is known that below the Kelvin 0 is hard to achieve, which is not plausible.
// However, recent research suggests that a temperature below absolute zero
// is also plausible by using quantum gas for instance.
// I do not know to what extent it is achievable below absolute zero,
// nor how much it is plausible upper bound in temperature.
// Thus, I cannot guarantee that this program is bug-free.
// I only can make this program work correctly to a certain extent,
// by setting lower- and upper-bound of the inputs for both converts.

#include "std_lib_facilities.h"

double ctof(double c)
// converts Celsius to Fahrenheit
// pre-conditions: double c, Celsius
// post-condition: returns a double that is Fahrenheit
{
    if (c < -273.15)
        error("ctof() pre-condition");
    double f = 9.0 / 5 * c + 32;
    if (f < 0)
        error("ctof() post-condition");
    return f;
}

double ftoc(double f)
// converts Fahrenheit to Celsius
// pre-conditions: double f, Fahrenheit
// post-condition: returns a double that is Celsius
{
    double c = (f - 32) / (9.0 / 5);
    return c;
}

int main()
{
    double c = 0; // declare input variable
    cout << "Enter a temperature in Celsius\n";
    cin >> c;                     // retrieve temperature to input variable
    double f = ctof(c);           // convert temperature
    cout << f << " Fahrenheit\n"; // print out temperature

    cout << "Enter a temperature in Fahrenheit\n";
    cin >> f;                  // retrieve temperature to input variable
    c = ftoc(f);               // convert temperature
    cout << c << " Celsius\n"; // print out temperature
}
