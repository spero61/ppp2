// Make a version where the user can play repeatedly
// (without stopping and restarting the program)
// and each game has a new set of four digits.
#include "std_lib_facilities.h"

int main()
{
    vector<int> numbers;
    int n;
    cout << "Enter a number (any number) to play randomly generated game\n";
    cin >> n;
    seed_randint(n);

    // four different integers should be given to the vector
    // check dupilication needed!
    bool is_unique = true;
    int tmp = randint(9);

    for (int i = 0; i < 4; ++i)
    {
        is_unique = true;
        tmp = randint(9);

        for (int x : numbers)
        {
            if (x == tmp)
                is_unique = false;
        }

        // if there is no duplicated integer in the vector numbers
        if (is_unique)
        {
            numbers.push_back(tmp);
        }
        else
        {
            --i;
        }
    }

    // following codes are the same as the previous one
    int count_bull = 0;
    int count_cow = 0;
    while (count_bull != 4)
    {
        int guess;
        cout << "guess the sequence of numbers of four digit\n";
        cin >> guess;

        string result;

        int thousands = guess / 1000;
        int hundreds = (guess % 1000) / 100;
        int tens = (guess % 100) / 10;
        int digits = guess % 10;

        count_bull = 0;
        if (thousands == numbers[0])
        {
            ++count_bull;
        }
        if (hundreds == numbers[1])
        {
            ++count_bull;
        }
        if (tens == numbers[2])
        {
            ++count_bull;
        }
        if (digits == numbers[3])
        {
            ++count_bull;
        }

        count_cow = 0;
        for (int i = 0; i < numbers.size(); ++i)
        {
            if (thousands == numbers[i] || hundreds == numbers[i] || tens == numbers[i] || digits == numbers[i])
            {
                ++count_cow;
            }
        }
        // adjusting a value by subtracting duplicated one(count_bull) from count_cow
        count_cow -= count_bull;

        cout << "result : " << count_bull << " bull(s) " << count_cow << " cow(s)\n";
    }
}