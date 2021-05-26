// exercise10_07.h is equivalent to exercise10_06.cpp
// this is used for '#include' to solve exercise 10_07.cpp

#include "std_lib_facilities.h"

constexpr int not_a_roman_numeral = -1;
constexpr char done{'#'};  // used for int roman_to_int(string str)

constexpr int i_M = 1000;
constexpr int i_C = 100;
constexpr int i_X = 10;
constexpr int i_I = 1;

constexpr int i_D = 500;
constexpr int i_L = 50;
constexpr int i_V = 5;

constexpr int max_roman{3999};
constexpr int min_roman{1};

string int_to_roman(int n);
int roman_to_int(string str);

class Roman_int {
   public:
    int as_int() const { return decimal_val; }

    Roman_int(){};  // default constructor for input operator >>
    Roman_int(string str) : decimal_val{roman_to_int(str)} {}
    Roman_int(int n) : decimal_val{n} {  // holding Roman numerals as int
        if (n < min_roman || max_roman < n) error("In this program, Roman numeral is valid between 1 and 3999\nPlease enter valid Roman numerals.");
    }

   private:
    int decimal_val{not_a_roman_numeral};
    string roman_val{""};
};
bool is_valid_char(char ch);
ostream& operator<<(ostream& os, const Roman_int& r);  // print Roman_int object as Roman numerals
istream& operator>>(istream& is, Roman_int& r);        // take roman numeral as string then initialize the Roman_int

Roman_int operator+(const Roman_int& a, const Roman_int& b);
Roman_int operator-(const Roman_int& a, const Roman_int& b);
Roman_int operator-(const Roman_int& r);
Roman_int operator*(const Roman_int& a, const Roman_int& b);
Roman_int operator/(const Roman_int& a, const Roman_int& b);
Roman_int operator%(const Roman_int& a, const Roman_int& b);

Roman_int operator+=(const Roman_int& a, const Roman_int& b);
Roman_int operator-=(const Roman_int& a, const Roman_int& b);
Roman_int operator*=(const Roman_int& a, const Roman_int& b);
Roman_int operator/=(const Roman_int& a, const Roman_int& b);
Roman_int operator%=(const Roman_int& a, const Roman_int& b);

bool operator==(const Roman_int& a, const Roman_int& b);
bool operator!=(const Roman_int& a, const Roman_int& b);
bool operator<(const Roman_int& a, const Roman_int& b);
bool operator>(const Roman_int& a, const Roman_int& b);
bool operator<=(const Roman_int& a, const Roman_int& b);
bool operator>=(const Roman_int& a, const Roman_int& b);
