// create vector of Fibonacci numbers
// and print them using the function from exercise 2

#include "std_lib_facilities.h"

vector<int> fibonacci(int x, int y, vector<int> v, int n);
void print(string label, vector<int> numbers);

int main()
{
    int num{0};

    // fibonacci series requires at least 2 numbers
    while (num < 2)
    {
        cout << "how many fibonacci numbers do you want?: ";
        cin >> num;
        if (num < 2)
            cout << "try again with a number greater than or equal to 2\n";
    }
    vector<int> fibo;
    fibo = fibonacci(1, 2, fibo, num);

    string label = "fibonacci";
    print(label, fibo);
}

vector<int> fibonacci(int x, int y, vector<int> v, int n)
{
    v.push_back(x);
    v.push_back(y);
    for (int i = 2; i < n; ++i)
    {
        int current_val = v[i - 2] + v[i - 1];
        if (current_val > 0)
            v.push_back(current_val);
        else
        {
            string error_message = "fibonacci number has reached to the upper-range of the int.";
            error_message += "\n\t  at " + to_string(i) + "th number of the fibonacci series. Try with lower number than that.";
            error(error_message);
        }
    }

    return v;
}

void print(string label, vector<int> numbers)
{
    for (int i = 0; i < numbers.size(); ++i)
    {
        cout << label << '[' << i << "]:\t" << numbers[i] << '\n';
    }
}
