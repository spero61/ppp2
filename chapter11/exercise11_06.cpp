// Write a program that replaces punctuation with whitespace.
// Consider .(dot), ;(semicolon), ,(comma), ?(question mark),
// -(dash), '(single quote) punctuation characters.

// Don't modify characters within a pair of double quotes (").
// For example,
// "- don't use the as-if rule." becomes
// " don t use the as if rule ".

#include "std_lib_facilities.h"

bool is_punct(const char& ch) {
    if (ch == '.' || ch == ';' || ch == ',' || ch == '?' || ch == '-' || ch == '\'') {
        return true;
    }
    return false;
}

void punct_to_space(string& str) {
    for (char& ch : str) {
        if (is_punct(ch)) ch = ' ';
    }
}

int main() {
    try {
        string text{"- don't use the as-if rule."};
        cout << text << '\n';

        punct_to_space(text);
        cout << text << '\n';

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}
