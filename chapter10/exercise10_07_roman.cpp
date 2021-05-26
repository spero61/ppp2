#include "exercise10_07_roman.h"

#include "std_lib_facilities.h"

// exception handling: 4, 9, 40, 90, 400, 900
string int_to_roman(int n) {
    string str{""};

    // thousands (until 3999)
    // i_M: 1000
    if (n / i_M != 0) {
        int count{n / i_M};
        for (int i = 0; i < count; ++i) {
            str += 'M';
            n -= i_M;
        }
    }

    // hundreds

    // exception: CM(900)
    if (n / 900 != 0) {
        str += "CM";
        n -= 900;
    }

    else if (n / i_D != 0) {
        str += 'D';
        n -= i_D;
    }

    // exception: CD(400)
    else if (n / 400 != 0) {
        str += "CD";
        n -= 400;
    }

    // i_C: 100
    if (n / i_C != 0) {
        int count{n / i_C};
        for (int i = 0; i < count; ++i) {
            str += 'C';
            n -= i_C;
        }
    }

    // tenth
    // exception: XC(90)
    if (n / 90 != 0) {
        str += "XC";
        n -= 90;
    }

    else if (n / i_L != 0) {
        str += 'L';
        n -= i_L;
    }

    // exception: XL(40)
    else if (n / 40 != 0) {
        str += "XL";
        n -= 40;
    }

    // i_X: 10
    if (n / i_X != 0) {
        int count{n / i_X};
        for (int i = 0; i < count; ++i) {
            str += 'X';
            n -= i_X;
        }
    }

    // digits
    // exception: IX(9)
    if (n / 9 != 0) {
        str += "IX";
        n -= 9;
    }

    else if (n / i_V != 0) {
        str += 'V';
        n -= i_V;
    }

    // exception: IV(4)
    else if (n / 4 != 0) {
        str += "IV";
        n -= 4;
    }

    // i_I: 1
    if (n / i_I != 0) {
        int count{n / i_I};
        for (int i = 0; i < count; ++i) {
            str += 'I';
            n -= i_I;
        }
    }

    if (n != 0)
        error("something's wrong!");

    return str;
}

// exception handling: 4, 9, 40, 90, 400, 900
int roman_to_int(string str) {
    int n{0};

    // exceptions
    // str.size() - 1 because it searches i and i+1 pair
    for (int i = 0; i < str.size() - 1; ++i) {
        if (str[i] == 'C' && str[i + 1] == 'M') {
            n += 900;
            str[i] = done;
            str[i + 1] = done;
        }

        if (str[i] == 'C' && str[i + 1] == 'D') {
            n += 400;
            str[i] = done;
            str[i + 1] = done;
        }
        if (str[i] == 'X' && str[i + 1] == 'C') {
            n += 90;
            str[i] = done;
            str[i + 1] = done;
        }
        if (str[i] == 'X' && str[i + 1] == 'L') {
            n += 40;
            str[i] = done;
            str[i + 1] = done;
        }
        if (str[i] == 'I' && str[i + 1] == 'X') {
            n += 9;
            str[i] = done;
            str[i + 1] = done;
        }
        if (str[i] == 'I' && str[i + 1] == 'V') {
            n += 4;
            str[i] = done;
            str[i + 1] = done;
        }
    }

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == 'M')
            n += i_M;
        else if (str[i] == 'D')
            n += i_D;
        else if (str[i] == 'C')
            n += i_C;
        else if (str[i] == 'L')
            n += i_L;
        else if (str[i] == 'X')
            n += i_X;
        else if (str[i] == 'V')
            n += i_V;
        else if (str[i] == 'I')
            n += i_I;
    }

    return n;
}

// print Roman_int object as Roman numerals
ostream& operator<<(ostream& os, const Roman_int& r) {
    int tmp = r.as_int();

    return os << int_to_roman(tmp);
}

// determines if a character can be part of a roman numeral
bool is_valid_char(char ch) {
    return ch == 'M' || ch == 'C' || ch == 'X' || ch == 'I' || ch == 'D' || ch == 'L' || ch == 'V';
}

// take roman numeral as string then initialize the Roman_int
istream& operator>>(istream& is, Roman_int& r) {
    is.exceptions(is.exceptions() | ios_base::badbit);

    char c;
    string str;
    while (is.get(c)) {
        if (is_valid_char(c))
            str += c;
        else {
            is.putback(c);
            break;
        }
    }
    int tmp = roman_to_int(str);
    r = Roman_int{tmp};
    return is;
}

Roman_int operator+(const Roman_int& a, const Roman_int& b) {
    return Roman_int(a.as_int() + b.as_int());
}

Roman_int operator-(const Roman_int& a, const Roman_int& b) {
    return Roman_int(a.as_int() - b.as_int());
}

Roman_int operator-(const Roman_int& r) {
    return Roman_int(-r.as_int());
}

Roman_int operator*(const Roman_int& a, const Roman_int& b) {
    return Roman_int(a.as_int() * b.as_int());
}

Roman_int operator/(const Roman_int& a, const Roman_int& b) {
    if (b.as_int() == 0) error("division by zero");
    double d = double(a.as_int()) / b.as_int();
    int res = int(d);
    if (res != d) error("division leads to non-integer result");
    return Roman_int(res);
}

Roman_int operator%(const Roman_int& a, const Roman_int& b) {
    return Roman_int(a.as_int() % b.as_int());
}

Roman_int& operator+=(Roman_int& a, const Roman_int& b) {
    a = a + b;
    return a;
}

Roman_int& operator-=(Roman_int& a, const Roman_int& b) {
    a = a - b;
    return a;
}

Roman_int& operator*=(Roman_int& a, const Roman_int& b) {
    a = a * b;
    return a;
}

Roman_int& operator/=(Roman_int& a, const Roman_int& b) {
    a = a / b;
    return a;
}

Roman_int& operator%=(Roman_int& a, const Roman_int& b) {
    a = a % b;
    return a;
}

bool operator==(const Roman_int& a, const Roman_int& b) {
    return a.as_int() == b.as_int();
}
bool operator!=(const Roman_int& a, const Roman_int& b) {
    return !(a == b);
}
bool operator<(const Roman_int& a, const Roman_int& b) {
    return a.as_int() < b.as_int();
}
bool operator>(const Roman_int& a, const Roman_int& b) {
    return a.as_int() > b.as_int();
}
bool operator<=(const Roman_int& a, const Roman_int& b) {
    return a.as_int() <= b.as_int();
}
bool operator>=(const Roman_int& a, const Roman_int& b) {
    return a.as_int() >= b.as_int();
}
