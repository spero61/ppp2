// Implement leapyear() from §9.8.

// Leap year creteria
// The year must be evenly divisible by 4
// If the year can also be evenly divided by 100, it is not a leap year;
// unless...
// The year is also evenly divisible by 400. Then it is a leap year.

#include "std_lib_facilities.h"

bool leapyear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                return true;
            else
                return false;
        } else
            return true;
    } else
        return false;
}

int main() {
    int y1 = 1987;
    int y2 = 1994;
    int y3 = 2002;
    int y4 = 1900;
    int y5 = 2100;
    int y6 = 2300;
    int y7 = 2021;
    int y8 = 2015;
    int y9 = 2007;
    int y10 = 1600;
    int y11 = 2000;
    int y12 = 2400;
    int y13 = 2008;
    int y14 = 2020;
    int y15 = 4;

    cout << y1 << " : " << leapyear(y1) << '\n';
    cout << y2 << " : " << leapyear(y2) << '\n';
    cout << y3 << " : " << leapyear(y3) << '\n';
    cout << y4 << " : " << leapyear(y4) << '\n';
    cout << y5 << " : " << leapyear(y5) << '\n';
    cout << y6 << " : " << leapyear(y6) << '\n';
    cout << y7 << " : " << leapyear(y7) << '\n';
    cout << y8 << " : " << leapyear(y8) << '\n';
    cout << y9 << " : " << leapyear(y9) << '\n';
    cout << y10 << " : " << leapyear(y10) << '\n';
    cout << y11 << " : " << leapyear(y11) << '\n';
    cout << y12 << " : " << leapyear(y12) << '\n';
    cout << y13 << " : " << leapyear(y13) << '\n';
    cout << y14 << " : " << leapyear(y14) << '\n';
    cout << y15 << " : " << leapyear(y15) << '\n';
}