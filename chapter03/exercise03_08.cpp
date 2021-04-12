// determine whether an integer is odd or even
#include "std_lib_facilities.h"

int main()
{
    int val = 0;
    string result = "";
    cout << "Please enter an integer value followed by enter.\n";
    cin >> val;
    if (val % 2 == 0)
        result = "even";
    else
        result = "odd";
    cout << "The value " << val << " is an " << result << " number.\n";
}