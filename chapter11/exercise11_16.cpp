// Write a program to read a file of whitespace-separated numbers
// and output them in order (lowest value first), one value per line.

// Write a value only once, and if it occurs more than once
// write the count of its occurrences on its line.
// For example, 7 5 5 7 3 117 5 should give
/*
3
5    3
7    2
117
*/

#include "std_lib_facilities.h"

double to_number(const string& str) {
    istringstream is{str};
    double num{0.0};
    is >> num;
    return num;
}

int main() {
    try {
        string iname{"integers.txt"};
        ifstream ifs{iname};
        if (!ifs) error("can't open input file: ", iname);
        ifs.exceptions(ifs.exceptions() | ios_base::badbit);

        string numbers_str{""};
        getline(ifs, numbers_str);

        istringstream is{numbers_str};
        vector<double> numbers;
        for (string num_str; is >> num_str;) {
            numbers.push_back(to_number(num_str));
        }

        ifs.close();

        sort(numbers.begin(), numbers.end());  // sort the numbers in ascending order
        for (int i = 0; i < numbers.size(); ++i) {
            if (i == 0 || numbers[i] != numbers[i - 1]) {
                int count{0};
                for (double num : numbers) {
                    if (num == numbers[i]) {
                        count++;
                    }
                }

                if (count == 1) {
                    cout << numbers[i] << '\n';
                } else {
                    cout << numbers[i] << '\t' << count << '\n';
                }
            }
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