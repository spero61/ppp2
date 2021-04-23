// redo the "Bulls and Cows" game from exercise 12 in Chapter 5
// to use four letters rather than four digits.

#include "std_lib_facilities.h"

int main()
{
    vector<char> letters = {'s', 'w', 'i', 'm'};

    int count_bull = 0;
    int count_cow = 0;
    while (count_bull != 4)
    {
        string guess;
        cout << "guess the sequence of four different letters\n";
        cin >> guess;

        string result;

        int first_letter = guess[0];
        int second_letter = guess[1];
        int third_letter = guess[2];
        int fourth_letter = guess[3];

        count_bull = 0;
        if (first_letter == letters[0])
        {
            ++count_bull;
        }
        if (second_letter == letters[1])
        {
            ++count_bull;
        }
        if (third_letter == letters[2])
        {
            ++count_bull;
        }
        if (fourth_letter == letters[3])
        {
            ++count_bull;
        }

        count_cow = 0;
        for (int i = 0; i < letters.size(); ++i)
        {
            if (first_letter == letters[i] || second_letter == letters[i] || third_letter == letters[i] || fourth_letter == letters[i])
            {
                ++count_cow;
            }
        }

        // adjusting a value by subtracting duplicated one(count_bull) from count_cow
        count_cow -= count_bull;

        cout << "result : " << count_bull << " bull(s) " << count_cow << " cow(s)\n";
    }
}