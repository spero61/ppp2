// Write a program that reads a file of whitespace-separated numbers
// and outputs a file of numbers using scientific format
// and precision 8 in four fields of 20 characters per line.

#include "std_lib_facilities.h"

double to_number(const string& str) {
    istringstream is{str};
    double num{0.0};
    is >> num;
    return num;
}

int main() {
    try {
        string iname{"numbers.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);
        ifs.exceptions(ifs.exceptions() | ios_base::badbit);

        string numbers_str{""};
        getline(ifs, numbers_str);
        // cout << numbers_str;

        istringstream is{numbers_str};
        vector<double> numbers;
        for (string num_str; is >> num_str;) {
            numbers.push_back(to_number(num_str));
        }

        ifs.close();

        // scientific format, precision 8 in four fields of 20 characters per line.
        for (int i = 0; i < numbers.size(); ++i) {
            if (i != 0 && i % 4 == 0) cout << '\n';
            cout << scientific << setprecision(8) << setw(20) << numbers[i];
            if (i == numbers.size() - 1) cout << '\n';
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