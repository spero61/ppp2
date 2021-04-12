// ch4 drill from number 1 to 5
#include "std_lib_facilities.h"

int main()
{
    double val1 = 0;
    double val2 = 0;

    while (cin >> val1 >> val2)
    {
        if (val1 < val2)
        {
            cout << "the smaller value is: " << val1 << '\n';
            cout << "the larger value is: " << val2 << '\n';
            if (val2 - val1 < 1.0 / 100)
            {
                cout << "the numbers are almost equal.\n";
            }
        }
        else if (val1 > val2)
        {
            cout << "the smaller value is: " << val2 << '\n';
            cout << "the larger value is: " << val1 << '\n';
            if (val1 - val2 < 1.0 / 100)
            {
                cout << "the numbers are almost equal.\n";
            }
        }
        else
        {
            cout << "the numbers provided are equal.\n";
        }
    }
}