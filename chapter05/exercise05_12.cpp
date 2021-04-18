// implement a little guessing game called "Bulls and Cows."
// 1 bull : user got one digit right in the right position
// 1 cow : user got one digit right but in the wrong position
// the guessing continues until the user gets four bulls
#include "std_lib_facilities.h"

int main()
{
    vector<int> numbers = {8, 7, 6, 1};

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