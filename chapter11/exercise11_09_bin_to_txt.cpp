// see exercise11_09.md
// output file: exercise11_09.txt

#include "std_lib_facilities.h"

int main() {
    try {
        // open an istream for binary input from a file:
        string iname{"exercise11_09.bin"};
        ifstream ifs{iname, ios_base::binary};
        if (!ifs) error("can't open input file ", iname);

        // open an ostream for text output to a file:
        string oname{"exercise11_09.txt"};
        ofstream ofs{oname};
        if (!ofs) error("can't open output file ", oname);

        vector<int> vi;
        // read from binary file:
        for (int x; ifs.read(as_bytes(x), sizeof(int));)  // note: reading bytes
            vi.push_back(x);

        // do something with vi if necessary

        // write to a file as character representations:
        for (char x : vi)
            ofs << x;

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
