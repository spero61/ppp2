// Write a program that reads strings and for each string outputs the character classification of each character,
// as defined by the character classification functions presented in §11.6.

// Note that a character can have several classifications (e.g., x is both a letter and an alphanumeric).

#include "std_lib_facilities.h"

vector<string> char_classification(const string& str) {
    vector<string> v;
    for (char ch : str) {
        string tmp{ch};
        tmp += ": ";
        if (isspace(ch)) tmp += "whitespace, ";
        if (isalpha(ch)) tmp += "a letter, ";
        if (isdigit(ch)) tmp += "a decimal digit, ";
        if (isxdigit(ch)) tmp += "a hexadecimal digit, ";
        if (isupper(ch)) tmp += "an uppercase, ";
        if (islower(ch)) tmp += "a lowercase, ";
        if (isalnum(ch)) tmp += "isalnum, ";
        if (iscntrl(ch)) tmp += "a control character, ";
        if (ispunct(ch)) tmp += "ispunct, ";
        if (isprint(ch)) tmp += "printable, ";
        if (isgraph(ch)) tmp += "not space";
        v.push_back(tmp);
    }
    return v;
}

int main() {
    try {
        string str{""};
        // str = "Today is my birthday! June 1st, 2021 :)";
        cout << "Please type a sentence then press enter.\n> ";
        getline(cin, str);

        vector<string>
            vs{char_classification(str)};
        for (string tmp : vs) {
            cout << tmp << '\n';
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