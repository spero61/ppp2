// The version from 9.4.1 struct and functions

// Feel free to ignore leap years.
// However, don’t accept a month that is not in the [1,12] range
// or day of the month that is not in the [1,31] range.
// Test each version with at least one invalid date (e.g., 2004, 13, –5).
#include "std_lib_facilities.h"

// simple Date
// guarantee initialization with constructor
// provide some notational convenience
struct Date {
    int y, m, d;                   // year, month, day
    Date(int yy, int mm, int dd);  // check for valid date and initialize
    void add_day(int n);           // increase the Date by n days
};

Date::Date(int yy, int mm, int dd) {
    if (mm < 1 || 12 < mm) error("init_day: Invalid month");
    if (dd < 1 || 31 < dd) error("init_day: Invalid day");

    y = yy;  // no restriction on a year yet
    m = mm;
    d = dd;
}

void Date::add_day(int n) {
    d += n;

    if (d > 31) {
        while (true) {
            ++m;
            d -= 31;
            if (d <= 31) break;
        }
    } else if (d < 1) {
        while (true) {
            --m;
            d += 31;
            if (d >= 1) break;
        }
    }

    // month should be handled later than day
    if (m > 12) {
        while (true) {
            ++y;
            m -= 12;
            if (m <= 12) break;
        }

    } else if (m < 1) {
        while (true) {
            --y;
            m += 12;
            if (m >= 1) break;
        }
    }
}

ostream& operator<<(ostream& os, const Date& d) {
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

int main() {
    try {
        Date today{1978, 6, 25};
        // Date today{2004, 13, -5};  // invalid date

        Date tomorrow{today};
        tomorrow.add_day(1);

        cout << "today: " << today << '\n';
        cout << "tomorrow: " << tomorrow << '\n';

        Date test_forward{2021, 12, 31};
        test_forward.add_day(22);
        cout << "test_forward from 2021, 12, 31: " << test_forward << '\n';

        Date test_backward{2021, 1, 7};
        test_backward.add_day(-33);
        cout << "test_backward from 2021, 1, 7: " << test_backward << '\n';

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception\n";
        return 2;
    }
}