// a program that reads and stores a series of integers
// and then computes the sum of the first N integers.
#include "std_lib_facilities.h"

int main()
{
    vector<int> numbers;
    int n = 0;
    cout << "Please enter the number of values you want to sum: \n";
    cin >> n;

    int sum = 0;
    int number = 0;

    // error : n must be greater than 0
    if (n <= 0)
    {
        error("number of values you want to sum should be greater than or equal to 0\n");
    }

    // take user input and stores integer numbers to vector<int> numbers
    cout << "Please enter some integers (press '|' to stop): \n";
    while (cin >> number)
    {
        numbers.push_back(number);
    }

    // error : user asks for a sum of more numbers than there are in the vector<int> numbers
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
}