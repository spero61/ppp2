// The version from 9.4.1 struct and functions

// Feel free to ignore leap years.
// However, don’t accept a month that is not in the [1,12] range
// or day of the month that is not in the [1,31] range.
// Test each version with at least one invalid date (e.g., 2004, 13, –5).

#include "std_lib_facilities.h"

// simple Date
struct Date {
    int y;  // year
    int m;  // month in year
    int d;  // day of month
};

// check on the validity of Date
void init_day(Date& dd, int y, int m, int d) {
    if (m < 1 || 12 < m) error("init_day: Invalid month");
    if (d < 1 || 31 < d) error("init_day: Invalid day");

    dd.y = y;  // no restriction on a year yet
    dd.m = m;
    dd.d = d;
}

void add_day(Date& dd, int n) {
    dd.d += n;

    if (dd.d > 31) {
        while (true) {
            ++dd.m;
            dd.d -= 31;
            if (dd.d <= 31) break;
        }
    } else if (dd.d < 1) {
        while (true) {
            --dd.m;
            dd.d += 31;
            if (dd.d >= 1) break;
        }
    }

    // month should be handled later than day
    if (dd.m > 12) {
        while (true) {
            ++dd.y;
            dd.m -= 12;
            if (dd.m <= 12) break;
        }

    } else if (dd.m < 1) {
        while (true) {
            --dd.y;
            dd.m += 12;
            if (dd.m >= 1) break;
        }
    }
}

ostream& operator<<(ostream& os, const Date& d) {
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

int main() {
    try {
        Date today;  // a Data variable (a named object)
        init_day(today, 1978, 6, 25);
        // init_day(today, 2004, 13, -5);  // invalid date

        Date tomorrow{today};
        add_day(tomorrow, 1);

        cout << "today: " << today << '\n';
        cout << "tomorrow: " << tomorrow << '\n';

        Date test_forward;
        init_day(test_forward, 2021, 12, 31);
        add_day(test_forward, 22);
        cout << "test_forward from 2021, 12, 31: " << test_forward << '\n';

        Date test_backward;
        init_day(test_backward, 2021, 1, 7);
        add_day(test_backward, -33);
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