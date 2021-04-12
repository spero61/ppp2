// a program that takes an operation followed by two operands
// and outputs the result. (e.g. + 100 3.14  or  * 4 5)
#include "std_lib_facilities.h"

int main()
{
    int pennies, nickels, dimes, quarters, half_dollars, dollars;
    int sum = 0;

    cout << "Please type the number of pennies you have.\n";
    cin >> pennies;
    cout << "Please type the number of nickels you have.\n";
    cin >> nickels;
    cout << "Please type the number of dimes you have.\n";
    cin >> dimes;
    cout << "Please type the number of quarters you have.\n";
    cin >> quarters;
    cout << "Please type the number of half-dollars you have.\n";
    cin >> half_dollars;
    cout << "Please type the number of dollars you have.\n";
    cin >> dollars;

    if (pennies > 0)
    {
        sum += pennies;
        if (pennies == 1)
        {
            cout << "You have 1 penny.\n";
        }
        else
        {
            cout << "You have " << pennies << " pennies.\n";
        }
    }
    if (nickels > 0)
    {
        sum += 5 * nickels;
        if (nickels == 1)
        {
            cout << "You have 1 nickel.\n";
        }
        else
        {
            cout << "You have " << nickels << " nickels.\n";
        }
    }
    if (dimes > 0)
    {
        sum += 10 * dimes;
        if (dimes == 1)
        {
            cout << "You have 1 dime.\n";
        }
        else
        {
            cout << "You have " << dimes << " dimes.\n";
        }
    }
    if (quarters > 0)
    {
        sum += 25 * quarters;
        if (quarters == 1)
        {
            cout << "You have 1 quarter.\n";
        }
        else
        {
            cout << "You have " << quarters << " quarters.\n";
        }
    }
    if (half_dollars > 0)
    {
        sum += 50 * half_dollars;
        if (half_dollars == 1)
        {
            cout << "You have 1 half_dollar.\n";
        }
        else
        {
            cout << "You have " << half_dollars << " half_dollars.\n";
        }
    }
    if (dollars > 0)
    {
        sum += 100 * dollars;
        if (dollars == 1)
        {
            cout << "You have 1 dollar.\n";
        }
        else
        {
            cout << "You have " << dollars << " dollars.\n";
        }
    }

    cout << "The value of all of your coins is " << sum / 100 << " dollars and " << sum % 100 << " cents.\n";
}