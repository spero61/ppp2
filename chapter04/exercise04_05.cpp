// a very simple calculator
#include "std_lib_facilities.h"

int main()
{
    double val1 = 0;
    double val2 = 0;
    char op = ' ';

    cout << "Enter two operands followed by an operator (e.g. +, -, *, /)\n";
    cin >> val1 >> val2 >> op;

    switch (op)
    {
    case '+':
        cout << "The sum of " << val1 << " and " << val2 << " is " << val1 + val2 << '\n';
        break;
    case '-':
        cout << val1 << " minus " << val2 << " is " << val1 - val2 << '\n';
        break;
    case '*':
        cout << "The product of " << val1 << " and " << val2 << " is " << val1 * val2 << '\n';
        break;
    case '/':
        cout << val1 << " divided by " << val2 << " is " << val1 / val2 << '\n';
        break;
    default:
        cout << "You should provide a valid operator. ( +, -, *, or / )\n";
    }
}