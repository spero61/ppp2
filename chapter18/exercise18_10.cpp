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

istream& read_word(istream& is, char* buffer, int max) {  // read at most max-1 characters from is into buffer
    is.width(max);                                        // read at most max-1 characters in the next >>
    is >> buffer;                                         // read whitespace-terminated word, add zero after the last character read into buffer

    return is;
}

int main() {
    try {
        cout << "Enter a word to check whether it is a palindrome.\n";
        
        constexpr int max = 128;
        for (char s[max]; read_word(cin, s, max);) {
            cout << s << " is";
            if (!is_palindrome(s, string_length(s))) cout << " NOT";
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