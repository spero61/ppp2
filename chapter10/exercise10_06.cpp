// Define a Roman_int class for holding Roman numerals (as ints) with a << and >>.
// Provide Roman_int with an as_int() member that returns the int value,
// so that if r is a Roman_int, we can write cout << "Roman" << r << " equals " << r.as_int() << '\n';

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

class Roman_int {
   public:
    int as_int() const { return decimal_val; }

    Roman_int(){};  // default constructor for input operator >>

    Roman_int(int n) : decimal_val{n} {  // holding Roman numerals as int
        if (n < min_roman || max_roman < n) error("In this program, Roman numeral is valid between 1 and 3999\nPlease enter valid Roman numerals.");
    }

   private:
    int decimal_val{not_a_roman_numeral};
    string roman_val{""};
};

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

int main() {
    try {
        const int num1 = 1111;
        const int num2 = 2222;
        const int num3 = 3333;
        const int num4 = 3999;
        const int num5 = 2021;
        const int num6 = 1987;
        const int num7 = 555;
        const int num8 = 61;
        const int num9 = 7;

        Roman_int test1{num1};
        Roman_int test2{num2};
        Roman_int test3{num3};
        Roman_int test4{num4};
        Roman_int test5{num5};
        Roman_int test6{num6};
        Roman_int test7{num7};
        Roman_int test8{num8};
        Roman_int test9{num9};

        cout << num1 << " is " << test1 << '\n';
        cout << num2 << " is " << test2 << '\n';
        cout << num3 << " is " << test3 << '\n';
        cout << num4 << " is " << test4 << '\n';
        cout << num5 << " is " << test5 << '\n';
        cout << num6 << " is " << test6 << '\n';
        cout << num7 << " is " << test7 << '\n';
        cout << num8 << " is " << test8 << '\n';
        cout << num9 << " is " << test9 << '\n';
        cout << '\n';

        Roman_int r;
        cout << "please enter Roman numerals e.g VII\n";
        cin >> r;

        cout << "Roman " << r << " equals " << r.as_int() << '\n';

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}