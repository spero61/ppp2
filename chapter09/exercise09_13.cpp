// Design and implement a rational number class, Rational.
// A rational number has two parts: a numerator and a denominator,
// for example, 5/6 (five-sixths, also known as approximately .83333).
// Look up the definition if you need to.

// Provide assignment, addition, subtraction, multiplication, division, and equality operators.
// Also, provide a conversion to double. Why would people want to use a Rational class?

// Comment:
// I provide constructors instead of assignment operator for Rational class.
// assignment operator has to be treated differently than other operators
// and it requires knowledge from pointers. Might be REVIEW this problem later on.

// People would like to use a Rational class where the precision is important
// this stems from the fact that it is not vulnerable to Floating-point error.

#include "std_lib_facilities.h"

class Rational {
   public:
    Rational(int n_arg, int d_arg);
    Rational() : numerator{0}, denominator{1} {}
    int get_numerator() const { return numerator; }
    int get_denominator() const { return denominator; }
    void set_numerator(int n_arg) { numerator = n_arg; }
    void set_denominator(int d_arg) { denominator = d_arg; }

   private:
    int numerator;
    int denominator;
};

int gcd(int a, int b) {
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

Rational::Rational(int n_arg, int d_arg) {
    int gcd_val = gcd(n_arg, d_arg);
    numerator = n_arg / gcd_val;
    denominator = d_arg / gcd_val;
}

Rational operator+(const Rational &a, const Rational &b) {
    int numerator = a.get_numerator() * b.get_denominator() + b.get_numerator() * a.get_denominator();
    int denominator = a.get_denominator() * b.get_denominator();
    Rational tmp{numerator, denominator};
    return tmp;
}
Rational operator-(const Rational &a, const Rational &b) {
    int numerator = a.get_numerator() * b.get_denominator() - b.get_numerator() * a.get_denominator();
    int denominator = a.get_denominator() * b.get_denominator();
    Rational tmp{numerator, denominator};
    return tmp;
}
Rational operator*(const Rational &a, const Rational &b) {
    int numerator = a.get_numerator() * b.get_numerator();
    int denominator = a.get_denominator() * b.get_denominator();
    Rational tmp{numerator, denominator};
    return tmp;
}
// Dividing two fractions is the same as multiplying the first fraction by the reciprocal of the second fraction
Rational operator/(const Rational &a, const Rational &b) {
    int numerator = a.get_numerator() * b.get_denominator();
    int denominator = a.get_denominator() * b.get_numerator();
    Rational tmp{numerator, denominator};
    return tmp;
}
bool operator==(const Rational &a, const Rational &b) {
    if ((a.get_numerator() == b.get_numerator()) && (a.get_numerator() == b.get_numerator())) {
        return true;
    } else
        return false;
}

double to_double(const Rational &r) {
    return (double)r.get_numerator() / r.get_denominator();
}

int main() {
    try {
        Rational left{3, 15};
        Rational right{12, 60};
        cout << "left==right(true: 1 false: 0): " << (left == right) << '\n';
        Rational up{5, 15};
        Rational down{12, 60};
        cout << "up==down(true: 1 false: 0): " << (up == down) << '\n';
        cout << '\n';

        Rational a{9, 2};
        Rational b{4, 3};
        Rational c{8, 15};
        Rational result_one{a * b * c};  // 16/5
        cout << "result_one = " << to_double(result_one) << ": \n";
        cout << result_one.get_numerator() << '\n';
        cout << result_one.get_denominator() << '\n';
        cout << '\n';

        Rational d{34, 3};
        Rational e{5, 2};
        Rational result_two{d / e};  // 68/15
        cout << "result_two = " << to_double(result_two) << ": \n";
        cout << result_two.get_numerator() << '\n';
        cout << result_two.get_denominator() << '\n';
        cout << '\n';

        Rational f{8, 7};
        Rational g{6, 1};
        Rational result_three{f + g};  // 50 / 7
        cout << "result_three = " << to_double(result_three) << ": \n";
        cout << result_three.get_numerator() << '\n';
        cout << result_three.get_denominator() << '\n';

        return 0;
    } catch (exception &e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred" << '\n';
        return 2;
    }
}