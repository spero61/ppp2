// find all the prime numbers between 1 and 100
#include "std_lib_facilities.h"

bool is_prime_number(int n);
vector<int> primes;

int main()
{
    for (int i = 2; i <= 100; ++i)
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