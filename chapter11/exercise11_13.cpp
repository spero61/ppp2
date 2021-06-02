// Reverse the order of words (defined as whitespace-separated strings) in a file.
// For example, Norwegian Blue parrot becomes parrot Blue Norwegian.
// You are allowed to assume that all the strings from the file will fit into memory at once.

#include "std_lib_facilities.h"

constexpr char new_line_separator{'|'};

string reverse_order_of_words(const string& s) {
    string tmp{""};

    istringstream is{s};
    vector<string> vs;
    for (string word; is >> word;) {
        vs.push_back(word);
    }

    for (int i = vs.size() - 1; i >= 0; --i) {
        if (vs[i][vs[i].size() - 1] == new_line_separator) {
            vs[i][vs[i].size() - 1] = '\n';  // substitute '\n' for new_line_separator
            tmp += vs[i];
        } else {
            tmp += (vs[i] + ' ');
        }
    }

    return tmp;
}

int main() {
    try {
        string iname{"little_prince.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);
        ifs.exceptions(ifs.exceptions() | ios_base::badbit);

        string oname{"exercise11_13_output.txt"};
        ofstream ofs{oname};
        if (!ofs) error("can't open output file ", oname);
        string text{""};
        for (string line; ifs;) {
            if (ifs.eof()) {
                ifs.clear();
                break;
            }
            getline(ifs, line);

            text += (line + new_line_separator + ' ');
        }

        string reversed_text{reverse_order_of_words(text)};

        ofs << reversed_text << '\n';

        ifs.close();
        ofs.close();

        cout << oname << " is created\n";

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}