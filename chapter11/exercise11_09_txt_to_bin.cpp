// see exercise11_09.md
// output file: exercise11_09.bin

#include "std_lib_facilities.h"

int main() {
    try {
        // input file stream: ifs
        string iname{"little_prince.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);

        string oname{"exercise11_09.bin"};
        ofstream ofs{oname, ios_base::binary};

        vector<char> vc;
        for (char ch; ifs.read(as_bytes(ch), sizeof(char));) {
            vc.push_back(ch);
        }

        for (char x : vc) {
            ofs.write(as_bytes(x), sizeof(int));
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
