// Write a program that produces the sum of all the numbers
// in a file of whitespace-separated integers.

#include "std_lib_facilities.h"

int main() {
    fstream fs;
    fs.open("numbers.txt", ios_base::in);
    if (!fs) error("impossible!");

    int sum{0};
    int tmp{0};
    while (fs >> tmp) {
        sum += tmp;
    }
    fs.close();
    cout << sum << '\n';
}
