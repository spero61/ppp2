// a program that takes an operation followed by two operands
// and outputs the result. (e.g. + 100 3.14  or  * 4 5)
#include "std_lib_facilities.h"

int main()
{
    char operation = ' ';
    double val1 = 0;
    double val2 = 0;
    cout << "type an operator followed by two numbers separeted by space.\n";

    cin >> operation >> val1 >> val2;
    if (operation == '+')
        cout << val1 + val2 << '\n';
    else if (operation == '-')
        cout << val1 - val2 << '\n';
    else if (operation == '*')
        cout << val1 * val2 << '\n';
    else if (operation == '/')
        cout << val1 / val2 << '\n';
    else
        cout << "please type a valid operand. (e.g. +, -, *, /)\n";
}