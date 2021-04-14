// find all the prime numbers
#include "std_lib_facilities.h"

bool is_prime_number(int n);
vector<int> primes;

int main()
{
    int max = 2;
    cout << "find prime numbers between 1 and max\n";

    while (max <= 2)
    {
        cout << "please enter the number 'max'\n";
        cin >> max;
    }

    for (int i = 2; i <= max; ++i)
    {
        if (is_prime_number(i))
        {
            primes.push_back(i);
        }
    }

    for (int x : primes)
    {
        cout << x << "\t is prime number\n";
    }

    // print the number of prime numbers found
    cout << "\nthe number of prime numbers between 1 and " << max << " is " << primes.size() << '\n';
}

bool is_prime_number(int n)
{
    bool tmp = true;
    for (int i = 2; i < n; ++i)
    {
        if (n % i == 0)
        {
            tmp = false;
        }
    }
    return tmp;
}