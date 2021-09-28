// backward copy of the string then check whether it is a palindrome
#include <iostream>

using namespace std;

bool is_palindrome(const string& s) {
    int first = 0;              // index of first letter
    int last = s.length() - 1;  // index of last letter
    while (first < last) {
        if (s[first] != s[last]) return false;
        ++first;
        --last;
    }
    return true;  // reached the middle without violating the palidrome's rule
}

int main() {
    try {
        cout << "Enter a word to check whether it is a palindrome.\n"
             << "(Enter 'exit' to break the loop)\n";

        for (string s; cin >> s;) {
            if (s == "exit") break;
            cout << s << " is";
            if (!is_palindrome(s)) cout << " NOT";
            cout << " a palindrome\n";
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