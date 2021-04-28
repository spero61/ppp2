// a program that writes out the first so many values of the Fibonacci series.
// Q. Find the largest Fibonacci number that fits in an int.
// A. 1836311903

// range of int : –2,147,483,648 ~ 2,147,483,647
// range of double : 1.7E +/- 308 (15 digits)
// check : https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-160

#include "std_lib_facilities.h"

// stores fibonacci values
vector<int> fibonacci;
int fibonacci_number = 0;
int fibonacci_max_int = 0;

void fibonacci_init();     // initialize first two Fibonacci values of the series
void fibonacci_set(int n); // find fibonacci values then push_back to the vector<int> fibonacci
void print_result();

int main()
{

    fibonacci_init();

    try
    {
        int n = 0;
        while (true)
        {
            cout << "how many fibonacci numbers do you want?\n";
            cin >> n;
            if (n > 0)
                break;
        }

        fibonacci_set(n);
        print_result();
    }
    catch (runtime_error e)
    {
        cerr << "error : reached to int upper bound\n";
        cout << "the largest Fibonacci number that fits in an int is " << e.what() << '\n';
        return 1;
    }
}

void fibonacci_init()
{

    int f1 = 1;
    int f2 = 1;

    // initialize first two fibonacci numbers of the series
    fibonacci.push_back(f1);
    fibonacci.push_back(f2);
}

void fibonacci_set(int n)
{
    // since the next number of the series is the sum of the two previous ones, index starts from 2
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
}

void print_result()
{
    cout << "\n~~ Fibonacci series ~~\n";
    for (int x : fibonacci)
        cout << x << '\n';
}