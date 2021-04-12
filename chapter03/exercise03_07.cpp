// sort three strings in lexicographical order
#include "std_lib_facilities.h"

int main()
{
    string val1 = "";
    string val2 = "";
    string val3 = "";
    string tmp = "";
    cout << "Please enter three string values separated by space.\n";
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