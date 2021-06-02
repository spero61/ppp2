// Test_output.cpp

#include "std_lib_facilities.h"

struct Table {
    Table(string lastname, string firstname, string telephonenumber, string emailaddress) : ln{lastname}, fn{firstname}, tn{telephonenumber}, ea{emailaddress} {}
    string ln{""};  // last name
    string fn{""};  // first name
    string tn{""};  // telephone number
    string ea{""};  // email address
};

int main() {
    try {
        int birth_year{2017};
        cout << showbase << dec;  // show bases

        cout /*<< dec*/ << birth_year << "\t(decimal)\n";
        cout << hex << birth_year << "\t(hexadecimal)\n";
        cout << oct << birth_year << "\t(octal)\n";

        int age{99};
        cout << "age: " << dec << age << "\t(decimal)\n";  // hex, oct, and dec manipulators are sticky

        // int a, b, c, d;
        // cin >> a >> oct >> b >> hex >> c >> d;
        // cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';
        // a takes input as decimal value by default,
        // then b takes input then convert it to octal value then assinged to b
        // c takes input then convert it to hexadecimal value then assigned to c
        // d is the same as c because oct, hex, and dec are sticky.

        // so if you run this code with the input
        // 1234 1234 1234 1234
        // then it prints
        // 1234    668    4660    4660

        cout /*<< defaultfloat*/ << 1234567.89 << '\n';
        cout << fixed << 1234567.89 << '\n';
        cout << scientific << 1234567.89 << '\n';
        // fixed format is the most accurate representation in the case above
        // because the others perform round up to fulfil the default precision which is 6.
        cout << '\n';

        // Make a simple table including last name, first name, telephone number,
        // and email address for yourself and at least five of your friends.
        // Experiment with different field widths until you are satisfied
        // that the table is well presented.
        vector<Table> tables;

        tables.push_back(Table("Yoru", "Narita", "080-1234-5678", "spiro_spero61@gmail.com"));
        tables.push_back(Table("Kamata", "Rinko", "358-1988-0722", "yuriko_hayase@email.com"));
        tables.push_back(Table("Kurosawa", "Kokoro", "358-1990-0314", "haru_kuroki@email.com"));
        tables.push_back(Table("Yoshida", "Rei", "358-1987-0603", "masami_nagasawa@email.com"));
        tables.push_back(Table("Konno", "Akari", "358-1982-1015", "maki_yoko@email.com"));
        tables.push_back(Table("Akana", "Rika", "358-1994-0708", "shizuka_ishibashi@email.com"));
        // last name, first name, telephone number, email address

        for (Table tb : tables) {
            cout << setw(8) << tb.ln << setw(8) << tb.fn << setw(15) << tb.tn << setw(29) << tb.ea << '\n';
        }

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}