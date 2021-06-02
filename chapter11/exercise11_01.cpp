// Write a program that reads a text file
// and converts its input to all lower case, producing a new file.

#include "std_lib_facilities.h"

void tolower(string& line) {
    for (char& ch : line) {
        ch = tolower(ch);
    }
}

int main() {
    try {
        // output file stream: ofs
        string oname{"exercise11_01_output.txt"};
        ofstream ofs{oname};
        if (!ofs) error("can't open output file: ", oname);

        // input file stream: ifs
        string iname{"little_prince.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);

        string line{""};
        while (ifs) {
            if (ifs.eof()) {
                ifs.clear();
                break;
            }
            getline(ifs, line);
            tolower(line);
            ofs << line << '\n';
        }

        ifs.close();

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
