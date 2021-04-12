// converts spelled-out numbers into digits
#include "std_lib_facilities.h"

int main()
{
    string number = "";
    cout << "Please enter a number in English and in lower case letters.\n";
    cin >> number;
    if (number == "zero")
        cout << 0 << '\n';
    else if (number == "one")
        cout << 1 << '\n';
    else if (number == "two")
        cout << 2 << '\n';
    else if (number == "three")
        cout << 3 << '\n';
    else if (number == "four")
        cout << 4 << '\n';
    else if (number == "five")
        cout << 5 << '\n';
    else if (number == "six")
        cout << 6 << '\n';
    else if (number == "seven")
        cout << 7 << '\n';
    else if (number == "eight")
        cout << 8 << '\n';
    else if (number == "nine")
        cout << 9 << '\n';
    else
        cout << "not a number I know\n";
}