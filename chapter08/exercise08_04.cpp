// An int can hold integers only up to a maximum number.
// Find an approximation of that maximum number by using fibonacci().

#include "std_lib_facilities.h"

vector<int> fibonacci(int x, int y, vector<int> v, int n);
void print(string label, vector<int> numbers);

int main()
{

    int num{0};

    vector<int> fibo;
    fibo = fibonacci(1, 2, fibo, 100);

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
            error_message += "\n maximum number of the fibonacci series using int is " + to_string(v[i - 1]);
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
