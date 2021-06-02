// Write a program that removes all vowels from a file ("disemvowels").
// For example, "Once upon a time!" becomes "nc pn tm!".
// Surprisingly often, the result is still readable;
// try it on your friends.

// Comment:
// REVIEW is needed
// If a word consists of vowels only (like an article 'a')
// disemvowels() creates unnecessary extra space.

// I somehow get managed to print as it is intended, but there must be a better way to do it.

#include "std_lib_facilities.h"

bool is_vowel(char ch) {
    ch = tolower(ch);
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        return true;

    return false;
}

void disemvowels(string& line) {
    for (char& ch : line) {
        if (is_vowel(ch)) ch = '\0';
    }
}

int main() {
    try {
        string iname{"exercise11_03_input.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);
        ifs.exceptions(ifs.exceptions() | ios_base::badbit);

        int index{0};
        for (string line; ifs;) {
            if (ifs.eof()) {
                ifs.clear();
                break;
            }
            ++index;
            getline(ifs, line);
            disemvowels(line);
            istringstream ss{line};
            string result{""};                              // create an istringstream from str
            for (string word; ss >> word;) {                // extract a word
                if (word.size() == 1 && word[0] == '\0') {  // if it is a empty string
                    continue;
                }
                result += (word + ' ');
            }
            cout << result << '\n';
            // cout << line << '\n'; // this contains extra space in a certain case. see comments above
        }

        ifs.close();

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}
