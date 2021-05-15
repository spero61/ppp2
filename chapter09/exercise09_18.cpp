// Give an example of a calculation where a Rational gives a mathematically better result than double.
// See also 11.2.4 Precision Bjarne, Stroustrup. Programming (p. 385). Pearson Education

#include "Money.h"
#include "Rational.h"

int main() {
    try {
        Rational rational{456, 100};
        Rational r{100, 1};
        double d = 4.56;
        cout << fixed << setprecision(33) << to_double(rational * r) << '\n';
        cout << fixed << setprecision(33) << d * 100 << '\n';

        // result
        // 456.000000000000000000000000000000000
        // 455.999999999999943156581139191985130

        return 0;

    } catch (exception &e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred" << '\n';
        return 2;
    }
}