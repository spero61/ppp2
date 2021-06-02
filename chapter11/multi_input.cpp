// see exercise11_04.md

#include "std_lib_facilities.h"

int main() {
    try {
        int a, b, c;
        cin.unsetf(ios::dec);  // don’t assume decimal (so that 0x can mean hex)
        cin.unsetf(ios::oct);  // don’t assume octal (so that 12 can mean twelve)
        cin.unsetf(ios::hex);  // don’t assume hexadecimal (so that 12 can mean twelve)

        cin >> a >> b >> c;
        cout << showbase;  // show bases
        cout << hex << setw(8) << a << " hexadecimal\tconverts to " << dec << setw(10) << a << " decimal\n";
        cout << oct << setw(8) << b << " octal\t\tconverts to " << dec << setw(10) << b << " decimal\n";
        cout << dec << setw(8) << c << " decimal\tconverts to " << dec << setw(10) << c << " decimal\n";

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}