// Modify the program described in the previous exercise
// to take an input value max and then find all prime numbers from 1 to max.

// find all the prime numbers between 1 and 100
// by using “Sieve of Eratosthenes” method
#include "std_lib_facilities.h"

int find_smallest_index(vector<int> numbers);

int main()
{
    vector<int> primes;

    int max = 2;
    cout << "find prime numbers between 1 and max\n";

    while (max <= 2)
    {
        cout << "please enter the number 'max'\n";
        cin >> max;
    }

    vector<int> numbers(max);

    // set vector numbers from 1 to 100;
    for (int i = 0; i < max; ++i)
    {
        numbers[i] = i + 1;
    }

    // initially, mark the number 1 as not prime number
    // then replace its value to 0
    // note that index of the numbers starts from 0 NOT 1
    numbers[0] = 0;
    int index;
    int p;

    while (p * p < max)
    {

        // find the smallest numbers[index] in numbers that is not 0
        index = find_smallest_index(numbers);

        // p is prime number
        p = numbers[index];

        // put p into primes vector
        primes.push_back(p);

        // Enumerate the multiples of p by counting in increments of p from 2p to n,
        // and mark them in the list (these will be 2p, 3p, 4p, ...;
        // the p itself should not be marked)
        // source : https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
        for (int i = index; i < max; ++i)
        {
            if (numbers[i] % p == 0)
            {
                numbers[i] = 0;
            }
        }
    }

    // put remained unmarked numbers to numbers as they are prime numbers
    for (int x : numbers)
    {
        if (x != 0)
        {
            primes.push_back(x);
        }
    }

    cout << "\n\n\n";

    // print prime numbers found
    for (int p : primes)
    {
        cout << p << "  is prime\n";
    }

    // print the number of prime numbers found
    cout << "\nthe number of prime numbers between 1 and " << max << " is " << primes.size() << '\n';
}

int find_smallest_index(vector<int> numbers)
{
    bool tmp = false;
    int smallest = -1;

    for (int i = 0; i < numbers.size(); ++i)
    {
        if (!tmp)
        {
            if (numbers[i] != 0)
            {
                tmp = true;
                smallest = i;
            }
        }
    }

    if (smallest != -1)
    {
        return smallest;
    }
    else
    {
        return -1;
        cout << "something went wrong\n";
    }
}