// Rational.h

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
