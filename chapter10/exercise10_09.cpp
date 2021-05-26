// Write a program that takes two files
// containing sorted whitespace-separated words
// and merges them, preserving order.

// Comment:
// This program is case-sensitive. (cf. ASCII order)
// Uppercase words come first followed by lowercase words.

#include "std_lib_facilities.h"

void fill_from_file(vector<string>& words, const string& iname);
void text_file_concatenation(const string& iname_1, const string& iname_2, const string& oname);

int main() {
    try {
        string iname_1{""};
        string iname_2{""};
        string oname{""};

        cout << "Input filename 1 of 2: ";
        cin >> iname_1;
        cout << "Input filename 2 of 2: ";
        cin >> iname_2;
        cout << "Output filename: ";
        cin >> oname;

        text_file_concatenation(iname_1, iname_2, oname);

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}

// pass-by-reference: direct modification of vector<string> words
void fill_from_file(vector<string>& words, const string& iname) {
    ifstream ist{iname};
    if (!ist) error("can't open input file: ", iname);
    ist.exceptions(ist.exceptions() | ios_base::badbit);  // throw for bad()

    for (string str; ist >> str;) {
        words.push_back(str);
    }

    if (ist.eof()) ist.clear();
    if (ist.fail()) error("get_words() failed: ", iname);
}

void text_file_concatenation(const string& iname_1, const string& iname_2, const string& oname) {
    ofstream ost{oname};
    if (!ost) error("can't open output file: ", oname);

    vector<string> words;
    fill_from_file(words, iname_1);
    fill_from_file(words, iname_2);

    sort(words);  // to preserve lexicographical order, sort vector<string> words

    for (string word : words) {
        ost << word << ' ';  // whitespace-separated words
    }
}
