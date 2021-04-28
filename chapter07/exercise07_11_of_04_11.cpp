// a program to find all the prime numbers between 1 and max
// modified version of exercise04_11.cpp

#include "std_lib_facilities.h"

bool is_prime_number(int n);      // if n is prime number return true;
void find_prime_numbers(int max); // find all the prime numbers between 1 and max
void print_result();              // print result
vector<int> primes;

int main()
{
    try
    {
        find_prime_numbers(100);
        print_result();
    }
    catch (exception &e)
    {
        cerr << "exception: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "exception\n";
        return 2;
    }
}

bool is_prime_number(int n)
{
    // index i starts from 2
    for (int i = 2; i < n; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

void find_prime_numbers(int max)
{
    for (int i = 2; i <= max; ++i)
    {
        if (is_prime_number(i))
        {
            primes.push_back(i);
        }
    }
}

void print_result()
{
    for (int x : primes)
    {
        cout << x << "\t is prime number\n";
    }
}
