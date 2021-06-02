// Modify the program from the previous exercise so that it replaces
// don't with do not, can't with cannot, etc.; leaves hyphens within words intact
// (so that we get " do not use the as-if rule "); and converts all characters to lower case.

#include "std_lib_facilities.h"

bool is_punct(const char& ch) {
    if (ch == '.' || ch == ';' || ch == ',' || ch == '?') {
        return true;
    }
    return false;
}

void punct_to_space(string& str) {
    // deal with .(dot), ;(semicolon), ,(comma), ?(question mark)
    for (int i = 0; i < str.size(); ++i) {
        if (is_punct(str[i])) str[i] = ' ';
        // deal with -(dash)
        else if (str[i] == '-') {
            if (!isalpha(str[i - 1]) || !isalpha(str[i + 1])) str[i] = ' ';
        }
    }
}

// '(single quote)
string expand_abbr(const string& str) {
    string tmp{""};
    istringstream is{str};

    int index{0};
    if (str[0] == ' ') tmp += ' ';
    for (string word; is >> word;) {
        if (word == "can't")
            word = "cannot";
        else if (word == "don't")
            word = "do not";

        tmp += (word + ' ');
    }

    return tmp;
}

void tolower(string& line) {
    for (char& ch : line) {
        ch = tolower(ch);
    }
}

int main() {
    try {
        string text{"- Don't Use the As-If Rule. Can't take my eyes off you!"};
        cout << text << '\n';

        // text processing 3-steps
        punct_to_space(text);
        tolower(text);
        text = expand_abbr(text);

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
