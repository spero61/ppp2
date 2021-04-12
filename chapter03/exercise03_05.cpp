#include "std_lib_facilities.h"

int main()
{
    double val1 = 0;
    double val2 = 0;
    cout << "Please enter two floating-point values separated by space.\n";
    cin >> val1 >> val2;

    if (val1 < val2)
    {
        cout << "smaller : " << val1 << '\n';
        cout << "larger : " << val2 << '\n';
        cout << "difference : " << val2 - val1 << '\n';
    }
    else if (val1 > val2)
    {
        cout << "smaller : " << val2 << '\n';
        cout << "larger : " << val1 << '\n';
        cout << "difference : " << val1 - val2 << '\n';
    }
    else
    {
        cout << "two values are the same.\n";
        cout << "difference : " << 0 << '\n';
    }
    cout << "sum : " << val1 + val2 << '\n';
    cout << "product : " << val1 * val2 << '\n';
    cout << "ratio : " << val1 / val2 << '\n';
}