// Use the program from the previous exercise to make a dictionary
// (as an alternative to the approach in §11.7)
// Run the result on a multi-page text file, look at the result,
// and see if you can improve the program to make a better dictionary.

#include "std_lib_facilities.h"

bool is_punct(const char& ch) {
    if (ch == '.' || ch == ';' || ch == ',' || ch == '?' || ch == '!' || ch == '(' || ch == ')' || ch == ':' || ch == '$') {
        return true;
    }
    return false;
}

bool is_word(const string& str) {
    for (char ch : str) {
        if (!isalpha(ch)) return false;
    }
    return true;
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

void tolower(string& line) {
    for (char& ch : line) {
        ch = tolower(ch);
    }
}

int main() {
    try {
        // input file stream: ifs
        string iname{"little_prince.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);

        string text{""};
        for (string line; ifs;) {
            if (ifs.eof()) {
                ifs.clear();
                break;
            }
            getline(ifs, line);
            tolower(line);

            text += (line + '\n');
        }

        ifs.close();
        // cout << text << '\n';

        punct_to_space(text);

        istringstream is{text};

        vector<string> vs;
        for (string word; is >> word;) {
            if (is_word(word))
                vs.push_back(word);
        };

        sort(vs.begin(), vs.end());  // sort in lexicographical order

        // output file stream: ofs
        string oname{"exercise11_08_output.txt"};
        ofstream ofs{oname};

        for (int i = 0; i < vs.size(); ++i)    // write dictionary
            if (i == 0 || vs[i] != vs[i - 1])  // remove duplicates
                ofs << vs[i] << '\n';

        ofs.close();

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}
