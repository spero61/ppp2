// Reverse the order of characters in a text file.
// For example, asdfghjkl becomes lkjhgfdsa.

// Warning: There is no really good, portable, and efficient way of reading a file backward.

#include "std_lib_facilities.h"

string reverse_string(const string& s) {
    string tmp{""};
    for (int i = s.size() - 1; i >= 0; --i) {
        tmp += s[i];
    }
    return tmp;
}

int main() {
    try {
        string iname{"little_prince.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);
        ifs.exceptions(ifs.exceptions() | ios_base::badbit);

        string oname{"exercise11_12.txt"};
        ofstream ofs{oname};
        if (!ofs) error("can't open output file ", oname);

        for (string line; ifs;) {
            if (ifs.eof()) {
                ifs.clear();
                break;
            }
            getline(ifs, line);

            line = reverse_string(line);

            ofs << line << '\n';
        }

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