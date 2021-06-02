// Write a function vector<string> split(const string& s)
// that returns a vector of whitespace-separated substrings from the argument s.

#include "std_lib_facilities.h"

// returns a vector of whitespace-separated substrings from the argument s
vector<string> split(const string& s) {
    vector<string> vs;
    istringstream is{s};
    for (string word; is >> word;) {
        vs.push_back(word);
    }
    return vs;
}

int main() {
    try {
        string amendment_one{"Congress shall make no law respecting an establishment of religion, or prohibiting the free exercise thereof; or abridging the freedom of speech, or of the press; or the right of the people peaceably to assemble, and to petition the Government for a redress of grievances."};

        vector<string> words;
        words = split(amendment_one);

        // optional: lexicographical order (case-sensitive)
        // sort(words.begin(), words.end());

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