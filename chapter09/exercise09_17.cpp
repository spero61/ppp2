// Give an example of a calculation where a Rational gives a mathematically better result than Money.

#include "Money.h"
#include "Rational.h"

int main() {
    try {
        Rational rational{10045, 100};
        Money money{100.45, 0, Currency::usd};

        cout << to_double(rational) << '\n';  // 100.45
        cout << money << '\n';                // USD100.0

        return 0;

    } catch (exception &e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred" << '\n';
        return 2;
    }
}