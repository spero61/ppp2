// Write a program that produces the sum of all the whitespace-separated integers in a text file.
// For example, bears: 17 elephants 9 end should output 26.

// Note that 12.7 contains no whitespace-separated integeres, nor does 12f.
// Had we considered those 12s numbers to be added the exercise would have been simpler.
// According to the problem statement, -10000 is not a whitespace-separated integer.

#include "std_lib_facilities.h"

bool is_space(char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\n')
        return true;

    return false;
}

int main() {
    try {
        // string iname{""};
        // cout << "Input filename : ";
        // cin >> iname;

        string iname{"exercise10_11_input.txt"};  // sum: 2758
        ifstream ist{iname};
        if (!ist) error("can't open input file: ", iname);
        ist.exceptions(ist.exceptions() | ios_base::badbit);

        // parsing whitespac-separated words
        vector<string> words;
        for (string str; ist >> str;) {
            words.push_back(str);
        }
        ist.close();

        int sum{0};
        for (string word : words) {
            bool is_integer{true};
            for (int i = 0; i < word.size(); ++i) {
                if (isdigit(word[i]) == 0) {  // if word contains non decimal digit
                    is_integer = false;
                }
            }
            if (is_integer == true)
                sum += stoi(word);  // https://www.cplusplus.com/reference/string/stoi/
        }

        cout << "sum: " << sum << '\n';

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}