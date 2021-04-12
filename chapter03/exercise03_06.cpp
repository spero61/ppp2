// sort three integers using the knowledge explained in chapter3 only
#include "std_lib_facilities.h"

int main()
{
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
    int tmp = 0;
    cout << "Please enter three integer values separated by space.\n";
    cin >> val1 >> val2 >> val3;
    if (val2 > val3)
    {
        tmp = val2;
        val2 = val3;
        val3 = tmp;
    }
    if (val1 > val2)
    {
        tmp = val1;
        val1 = val2;
        val2 = tmp;
    }
    if (val2 > val3)
    {
        tmp = val2;
        val2 = val3;
        val3 = tmp;
    }
    cout << val1 << ", " << val2 << ", " << val3;
}