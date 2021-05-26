// Write a program that accepts two file names and produces a new file
// that is the contents of the first file followed by the contents of the second;
// that is, the program concatenates the two files.

// cf. std::istream::getline() vs. std::getline() (string)
// http://www.cplusplus.com/reference/istream/istream/getline/
// https://www.cplusplus.com/reference/string/string/getline/

// Comment: I use the latter (string) to implement this exercise.

#include "std_lib_facilities.h"

int main() {
    try {
        // string iname_1{"reading_input.txt"};
        // string iname_2{"reading_output.txt"};
        // string oname{"reading_combined.txt"};

        string iname_1{""};  // input filename_1;
        string iname_2{""};  // input filename_2;
        string oname{""};    // output filename;

        cout << "Input filename 1 of 2: ";
        cin >> iname_1;
        cout << "Input filename 2 of 2: ";
        cin >> iname_2;
        cout << "Output filename: ";
        cin >> oname;

        // output file stream
        ofstream ost{oname};
        if (!ost) error("can't open output file: ", oname);

        // input file stream 1
        ifstream ist_1{iname_1};
        if (!ist_1) error("can't open input file: ", iname_1);
        ist_1.exceptions(ist_1.exceptions() | ios_base::badbit);

        string str_1{""};
        while (ist_1) {  // DO NOT use ist_1.eof()
            getline(ist_1, str_1);
            // cout << str_1 << '\n'; // console log for debugging
            ost << str_1 << '\n';
        }
        if (ist_1.eof()) ist_1.clear();
        ist_1.close();

        // input file stream 2
        ifstream ist_2{iname_2};
        if (!ist_2) error("can't open input file: ", iname_2);
        ist_2.exceptions(ist_2.exceptions() | ios_base::badbit);

        string str_2{""};
        while (ist_2) {
            getline(ist_2, str_2);
            // cout << str_2 << '\n'; // console log for debugging
            ost << str_2 << '\n';
        }
        if (ist_2.eof()) ist_2.clear();
        ist_2.close();

        // output file stream close
        ost.close();

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception occurred\n";
        return 2;
    }
}