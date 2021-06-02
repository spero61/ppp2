// Write a function vector<string> split(const string& s, const string& w)
// that returns a vector of whitespace-separated substrings from the argument s,
// where whitespace is defined as “ordinary whitespace” plus the characters in w.

#include "std_lib_facilities.h"

constexpr int not_a_index{-1};

// returns a vector of whitespace-separated substrings from the argument s
vector<string> split(const string& s) {
    vector<string> vs;
    istringstream is{s};
    for (string word; is >> word;) {
        vs.push_back(word);
    }
    return vs;
}

// whitespace is defined as “ordinary whitespace” plus the characters in w
vector<string> split(const string& s, const string& w) {
    string tmp{s};
    while (tmp.find(w) != string::npos) {  // http://www.cplusplus.com/reference/string/string/find/
        int index = tmp.find(w);           // find index
        // substitute string w with ' ' + '\0'*w.size()-1  <- pseudocode
        for (int i = 0; i < w.size(); ++i) {
            tmp[index++] = ' ';
        }
    }

    return split(tmp);
}

int main() {
    try {
        string text{"IDUHsimplyDUHlikeDUHC++DUHasDUHaDUHlanguageDUHforDUHwritingDUHelegantDUHandDUHefficientDUHcode. Bjarne, Stroustrup. Programming (p. xxvi). Pearson Education. Kindle Edition."};

        vector<string> words;
        words = split(text, "DUH");

        for (string word : words) {
            cout << word << '\n';
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