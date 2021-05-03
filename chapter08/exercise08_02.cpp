// Write a function print() that prints a vector of ints to cout.
// Give it two arguments: a string for "labeling" the output and a vector.

#include "std_lib_facilities.h"

void print(string label, vector<int> numbers)
{
    for (int i = 0; i < numbers.size(); ++i)
    {
        cout << label << '[' << i << "]: " << numbers[i] << '\n';
    }
}

int main()
{
    vector<int> odds{1, 3, 5, 7, 9};
    vector<int> evens = {0, 2, 4, 6, 8};
    string label1 = "odd digits";
    string label2 = "even digits";
    print(label1, odds);
    print(label2, evens);
}