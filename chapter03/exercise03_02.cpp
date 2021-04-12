// converts from miles to kilometers
#include "std_lib_facilities.h"

int main()
{
    double miles_to_kilometers = 1.609;
    double miles = 0;

    cout << "Please enter a distance in miles. (numeric only)\n";
    cin >> miles;
    cout << miles << " miles is equivalent to " << miles_to_kilometers * miles << " kilometers\n";
}