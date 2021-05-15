// 15. Refine the Money class by adding a currency (given as a constructor argument).
// Accept a floating-point initializer as long as it can be exactly represented as a long int.
// Don’t accept illegal operations.

// For example, Money*Money doesn’t make sense,
// and USD1.23+DKK5.00 makes sense only if you provide a conversion table
// defining the conversion factor between U.S. dollars (USD) and Danish kroner (DKK).

#include "std_lib_facilities.h"

constexpr double eur_to_usd = 1.21;
constexpr double jpy_to_usd = 0.0091;
constexpr double krw_to_usd = 0.00089;

enum class Currency {
    usd,  // 0
    eur,  // 1
    jpy,  // 2
    krw   // 3
};

// Exchange Rate (May 15, 2021)
// 1 EUR = 1.21 USD
// 1 JPY = 0.0091 USD
// 1 KRW = 0.00089 USB

class Money {
   public:
    Money(double dollars_arg, double cents_arg, Currency crc);
    Money() : dollars{0}, cents{0}, amount{0} {}
    double get_dollars() const { return dollars; }
    double get_cents() const { return cents; }
    long int get_amount() const { return amount; }
    Currency get_Currency() const { return crc; }

   private:
    long int amount;
    double dollars;
    double cents;
    Currency crc;
};

Money::Money(double dollars_arg, double cents_arg, Currency crc_arg) : dollars{round(dollars_arg)}, cents{round(cents_arg)}, crc{crc_arg} {
    if (cents_arg >= 100) {
        cents = (int)cents_arg % 100;
        double tmp = ((int)cents_arg / 100);
        dollars += tmp;
    }
    amount = dollars * 100 + cents;
}

long int amount_in_usd(const Money& m) {
    switch ((int)m.get_Currency()) {
        case 0:  // usd
            return m.get_amount();
        case 1:  // eur
            return m.get_amount() * eur_to_usd;
        case 2:  // jpy
            return m.get_amount() * jpy_to_usd;
        case 3:  // krw
            return m.get_amount() * krw_to_usd;
    }

    cerr << "This should not be reached\n";
    return 0;
}

// addition based on usd currency
Money operator+(const Money& a, const Money& b) {
    long int amount_in_usd_a = amount_in_usd(a);
    long int amount_in_usd_b = amount_in_usd(b);

    long int amount = amount_in_usd_a + amount_in_usd_b;
    Money tmp{narrow_cast<double>(amount / 100), narrow_cast<double>(amount % 100), Currency::usd};
    return tmp;
}

// subtraction based on usd currency
Money operator-(const Money& a, const Money& b) {
    long int amount_in_usd_a = amount_in_usd(a);
    long int amount_in_usd_b = amount_in_usd(b);

    long int amount = amount_in_usd_a - amount_in_usd_b;
    Money tmp{narrow_cast<double>(amount / 100), narrow_cast<double>(amount % 100), Currency::usd};
    return tmp;
}

int main() {
    try {
        // input as dollars and cents
        Money nordea{350.33, 522.87, Currency::eur};
        Money citi{140.61, 553.18, Currency::usd};

        cout << "nordea dollars: " << nordea.get_dollars() << " dollars\n";
        cout << "nordea cents: " << nordea.get_cents() << " cents\n";
        cout << "nordea amount: " << nordea.get_amount() << " cents\n";

        cout << '\n';

        cout << "citi dollars: " << citi.get_dollars() << " dollars\n";
        cout << "citi cents: " << citi.get_cents() << " cents\n";
        cout << "citi amount: " << citi.get_amount() << " cents\n";

        cout << '\n';

        // addition based on usd
        Money result_plus = nordea + citi;
        cout << "nordea + citi (in USD amount): " << result_plus.get_amount() << " cents\n";

        // subtraction based on usd
        Money result_minus = nordea - citi;
        cout << "nordea - citi (in USD amount): " << result_minus.get_amount() << " cents\n";

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}