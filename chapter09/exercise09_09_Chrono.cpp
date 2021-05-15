// The version from 9.7.1 Argument types

// Feel free to ignore leap years.
// However, don’t accept a month that is not in the [1,12] range
// or day of the month that is not in the [1,31] range.
// Test each version with at least one invalid date (e.g., 2004, 13, –5).

#include "exercise09_09_Chrono.h"

#include "std_lib_facilities.h"


enum class Month {
    jan = 1,
    feb,
    mar,
    apr,
    may,
    jun,
    jul,
    aug,
    sep,
    oct,
    nov,
    dec
};

// simple Date (use Month type)
class Date {
   public:
    class Invalid {};
    Date(int yy, Month mm, int dd);    // check for valid date and initialize
    void add_day(int n);               // increase the Date by n days
    Month month() const { return m; }  // operator overloading of << requires a const-by-reference representation.
    int day() const { return d; }      // Thus we have to explicitly use 'const' keyword for declaration
    int year() const { return y; }     // to make sure these member functions do not modify its object.

   private:
    int y;  // year
    Month m;
    int d;  // day
    bool is_valid();
};

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd} {
    if (!is_valid())
        throw Invalid{};
}

bool Date::is_valid() {
    if (d < 1 || d > 31) return false;
    if (m < Month::jan || m > Month::dec) return false;
    return true;
}

Month operator++(Month& m)  // prefix increment operator
{
    m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);  // "wrap around"
    return m;
}

Month operator--(Month& m)  // prefix decrement operator
{
    m = (m == Month::jan) ? Month::dec : Month(int(m) - 1);  // "wrap around"
    return m;
}

Month& operator+=(Month& m, int n) {
    for (int i = 0; i < n; ++i) {
        ++m;
    }
    return m;
}

Month& operator-=(Month& m, int n) {
    for (int i = 0; i < n; ++i) {
        --m;
    }
    return m;
}

bool operator<(const Month& m, int n) { return int(m) < n; }
bool operator>(const Month& m, int n) { return int(m) > n; }

void Date::add_day(int n) {
    // handle year in different way from drill 1 to 3
    // because now we handle Month type and Date::y is not accessible within Month
    // as it is private member variable

    d += n;

    int count_days{d + (int(month()) - 1) * 31};  // calculate total number of days past of that year
    const int year_in_days{12 * 31};              // we assumed that a year is consisted of 12*31 days

    int year_index{0};
    // handle increment of a year
    if (count_days >= 0) {
        year_index = count_days / year_in_days;
        y += year_index;
    }
    // handle decrement of a year
    else {
        // convert minus sign to plus sign then decrease a year by one
        count_days = -count_days;
        --y;

        // check if it needs to subtract additional years
        year_index = count_days / year_in_days;
        y -= year_index;
    }

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
}

// note: int(d.month()) as it is the Month type
ostream& operator<<(ostream& os, const Date& d) {
    return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
}
