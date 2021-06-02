// Write a program that reads a text file and writes out
// how many characters of each character classification (§11.6) are in the file.

#include "std_lib_facilities.h"

struct Char_Stats {
    int isspace{0};
    int isalpha{0};
    int isdigit{0};
    int isxdigit{0};
    int isupper{0};
    int islower{0};
    int isalnum{0};
    int iscntrl{0};
    int ispunct{0};
    int isprint{0};
    int isgraph{0};
};

Char_Stats count_char_classification(const string& str) {
    Char_Stats cs;
    for (char ch : str) {
        string tmp{ch};
        tmp += ": ";
        if (isspace(ch)) cs.isspace++;
        if (isalpha(ch)) cs.isalpha++;
        if (isdigit(ch)) cs.isdigit++;
        if (isxdigit(ch)) cs.isxdigit++;
        if (isupper(ch)) cs.isupper++;
        if (islower(ch)) cs.islower++;
        if (isalnum(ch)) cs.isalnum++;
        if (iscntrl(ch)) cs.iscntrl++;
        if (ispunct(ch)) cs.ispunct++;
        if (isprint(ch)) cs.isprint++;
        if (isgraph(ch)) cs.isgraph++;
    }
    return cs;
}
// setw(8)
ostream& operator<<(ostream& os, const Char_Stats& cs) {
    return os << "~ Character Classification Stats ~\n\n"
              << "isspace: " << setw(7) << cs.isspace << "\twhitespace\n"
              << "isalpha: " << setw(7) << cs.isalpha << "\ta letter\n"
              << "isdigit: " << setw(7) << cs.isdigit << "\ta decimal digit\n"
              << "isxdigit:" << setw(7) << cs.isxdigit << "\ta hexadecimal digit\n"
              << "isupper: " << setw(7) << cs.isupper << "\tan uppercase\n"
              << "islower: " << setw(7) << cs.islower << "\ta lowercase\n"
              << "isalnum: " << setw(7) << cs.isalnum << "\tisalnum\n"
              << "iscntrl: " << setw(7) << cs.iscntrl << "\ta control character\n"
              << "ispunct: " << setw(7) << cs.ispunct << "\tispunct\n"
              << "isprint: " << setw(7) << cs.isprint << "\tprintable\n"
              << "isgraph: " << setw(7) << cs.isgraph << "\tnot space\n";
}

int main() {
    try {
        string iname{"little_prince.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);
        ifs.exceptions(ifs.exceptions() | ios_base::badbit);

        string oname{"exercise11_14_output.txt"};
        ofstream ofs{oname};
        if (!ofs) error("can't open output file ", oname);

        string text{""};
        for (string line; ifs;) {
            if (ifs.eof()) {
                ifs.clear();
                break;
            }
            getline(ifs, line);

            text += (line + '\n');
        }

        ifs.close();

        Char_Stats stats;
        stats = count_char_classification(text);

        ofs << stats;

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