// Write a program that given a file name
// and a word outputs each line that contains that word together with the line number.
// Hint: getline()

#include "std_lib_facilities.h"

int main() {
    try {
        string iname{"exercise11_02_input.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);
        ifs.exceptions(ifs.exceptions() | ios_base::badbit);

        string line{""};
        int index{0};
        while (ifs) {
            if (ifs.eof()) {
                ifs.clear();
                break;
            }
            ++index;
            getline(ifs, line);
            for (char& ch : line) {  // replace each punctuation character by a space
                switch (ch) {
                    case ';':
                    case '.':
                    case ',':
                    case '?':
                    case '!':
                        ch = '\0';  // or (char) 0
                }
            }
            stringstream ss{line};
            vector<string> vs;
            for (string word; ss >> word;)
                vs.push_back(word);
            sort(vs.begin(), vs.end());          // sort in lexicographical order
            for (int i = 0; i < vs.size(); ++i)  // write dictionary
                if (i == 0 || vs[i] != vs[i - 1])
                    cout << index << ": " << vs[i] << '\n';
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
