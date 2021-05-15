// Design and implement a Money class for calculations involving dollars and cents
// where arithmetic has to be accurate to the last cent using the 4/5 rounding rule
// (.5 of a cent rounds up; anything less than .5 rounds down).
// Represent a monetary amount as a number of cents in a long int,
// but input and output as dollars and cents, e.g., $123.45.
// Do not worry about amounts that don’t fit into a long int.

#include "std_lib_facilities.h"

class Money {
   public:
    Money(double dollars_arg, double cents_arg);
    Money() : dollars{0}, cents{0}, amount{0} {}
    double get_dollars() const { return dollars; }
    double get_cents() const { return cents; }
    long int get_amount() const { return amount; }

   private:
    long int amount;
    double dollars;
    double cents;
};

Money::Money(double dollars_arg, double cents_arg) : dollars{round(dollars_arg)}, cents{round(cents_arg)} {
    amount = dollars * 100 + cents;
}

ostream& operator<<(ostream& os, const Money& m) {
    os << '$' << m.get_dollars() << '.' << m.get_cents();
    return os;
}

int main() {
    try {
        // input as dollars and cents
        Money kozeni{123.45, 45.67};

        cout << "kozeni dollars: " << kozeni.get_dollars() << " dollars\n";
        cout << "kozeni cents: " << kozeni.get_cents() << " cents\n";
        cout << "kozeni amount: " << kozeni.get_amount() << " cents\n";

        cout << kozeni << '\n';
        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}