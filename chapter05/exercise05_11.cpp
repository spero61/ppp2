// a program that writes out the first so many values of the Fibonacci series.
// Q. Find the largest Fibonacci number that fits in an int.
// A. 1836311903
#include "std_lib_facilities.h"

int main()
{

    vector<int> fibonacci;

    int n = 0;
    cout << "how many fibonacci numbers do you want?\n";
    cin >> n;

    int f1 = 1;
    int f2 = 1;

    // initialize first two fibonacci numbers of the series
    fibonacci.push_back(f1);
    fibonacci.push_back(f2);

    try
    {
        // the next number of the series is the sum of the two previous ones
        // thus, index starts from 2
        int fibonacci_number = 0;
        int fibonacci_max_int = 0;
        for (int i = 2; i < n; ++i)
        {
            fibonacci_number = fibonacci[i - 2] + fibonacci[i - 1];
            if (fibonacci_number < 0)
            {
                string s = to_string(fibonacci_max_int);
                throw runtime_error(s);
            }
            fibonacci_max_int = fibonacci_number;
            fibonacci.push_back(fibonacci_number);
        }

        cout << "\n~~ Fibonacci series ~~\n";
        for (int x : fibonacci)
            cout << x << '\n';
    }
    catch (runtime_error e)
    {
        cerr << "error : reached to int upper bound\n";
        cout << "the largest Fibonacci number that fits in an int is " << e.what() << '\n';
        return 1;
    }
}