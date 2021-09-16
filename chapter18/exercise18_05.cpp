#include <iostream>

using namespace std;

// concatenates two strings with a dot in between
string cat_dot(const string& s1, const string& s2) {
    return s1 + '.' + s2;
}

int main() {
    try {
        cout << cat_dot("Niels", "Bohr") << '\n';
        return 0;
    } catch (std::exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}