// a program that reads and stores a series of integers
// and then computes the sum of the first N integers.

// modify the program to use double instead of int
#include "std_lib_facilities.h"

int main()
{
    vector<double> numbers;

    double n = 0;
    cout << "Please enter the number of values you want to sum: \n";
    cin >> n;

    double sum = 0;
    int number = 0;

    // error : n must be greater than 0
    if (n <= 0)
    {
        error("number of values you want to sum should be greater than or equal to 0\n");
    }

    // take user input and stores numbers to vector<double> numbers
    cout << "Please enter some numbers (press '|' to stop): \n";
    while (cin >> number)
    {
        numbers.push_back(number);
    }

    // error : user asks for a sum of more numbers than there are in the vector<double> numbers
    if (n > numbers.size())
    {
        error("range error: n\n");
    }

    // calculate a sum of first n integers user asked
    for (int i = 0; i < n; ++i)
    {
        sum += numbers[i];
    }
    // prints results
    cout << "sum: " << sum << '\n';

    // a vectoc of doubles containing the n-1 differences between adjacent values
    vector<double> differences;

    // index starts from 1 to calculate differences
    for (int i = 1; i < n; ++i)
    {
        differences.push_back(numbers[i] - numbers[i - 1]);
    }

    // prints differences up to n-1
    for (int i = 1; i < n - 1; ++i)
    {
        cout << "differences: numbers[" << i << "] - numbers[" << i - 1 << "] = " << differences[i] << '\n';
    }
}