// a program to solve quadratic equations
#include "std_lib_facilities.h"

int main()
{
    double a = 0;
    double b = 0;
    double c = 0;

    double x1 = 0;
    double x2 = 0;

    cout << "please enter a, b, and c respectively and orderly.\n"
         << "and they are separated by space\n"
         << "note that your quadratic equation looks like as follows: ax^2 + bx + c = 0 \n";

    cin >> a >> b >> c;

    // +
    x1 = (-b + sqrt((b * b) - (4 * a * c))) / (2 * a);

    // -
    x2 = (-b - sqrt((b * b) - (4 * a * c))) / (2 * a);

    cout << "solutions of " << a << "x^2 + " << b << "x + " << c << " = 0 are \n";
    cout << "x1 : " << x1 << '\n';
    cout << "x2 : " << x2 << '\n';
}