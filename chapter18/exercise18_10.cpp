#include <iostream>

using namespace std;

int string_length(const char* s) {
    int count = 0;
    while (*s) {
        ++count;
        ++s;
    }
    return count;
}

// compares two strings case-sensitively in lexicographical order
int strcmp(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (*s1 < *s2) {  // s1 is lexicographically before s2
            return -1;
        } else if (*s1 > *s2) {  // s1 is lexicographically after s2
            return 1;
        } else {
            ++s1;
            ++s2;
        }
    }

    return 0;  // s1 equals s2
}

// 18.7.2 Palindromes using arrays
bool is_palindrome(const char s[], int n) {  // s points to the first character of an array of n characters
    int first = 0;                           // index of first letter
    int last = n - 1;                        // index of last letter
    while (first < last) {                   // we haven't reached the middle
        if (s[first] != s[last]) return false;
        ++first;  // move forward
        --last;   // move backward
    }
    return true;
}

// read at most max-1 characters from is into buffer
istream& read_word(istream& is, char* buffer, int max) {
    is.width(max);  // read at most max-1 characters in the next >>
    is >> buffer;   // read whitespace-terminated word, add zero after the last character read into buffer

    if (string_length(buffer) == max - 1) {
        cout << "read_word() error: Input string is too long!\n";
        is.clear(ios_base::failbit);  // set the state to fail()
    }
    return is;
}

// read arbitrarily long characters from is into buffer
istream& read_any_word(istream& is, string& buffer) {
    getline(is, buffer);
    return is;
}

int main() {
    try {
        cout << "Enter a word to check whether it is a palindrome.\n"
             << "(Enter 'exit' to break the loop)\n\n";

        cout << "(a) reporting if an input string is too long\n";
        constexpr int max = 12;
        for (char s[max]; read_word(cin, s, max);) {
            if (strcmp(s, "exit") == 0) break;
            cout << s << " is";
            if (!is_palindrome(s, string_length(s))) cout << " NOT";
            cout << " a palindrome\n";
        }

        cout << "\n(b) allowing arbitrarily long string\n";
        for (string s; read_any_word(cin, s);) {
            if (s == "exit")
                break;
            else if (s != "") {
                cout << s << " is";
                if (!is_palindrome(s.c_str(), s.size())) cout << " NOT";
                cout << " a palindrome\n";
            }
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