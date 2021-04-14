// a program to play a numbers guessing game
#include "std_lib_facilities.h"

int main()
{
    int answer = 0;
    int guess = 0;
    int count = 0;
    int number_of_trial = 7;
    bool is_correct = false;

    while (answer < 1 || answer > 100)
    {
        cout << "Please enter a number between 1 and 100\n";
        cin >> answer;
    }

    cout << "Guess what number I have in my mind.\n";
    while (count != number_of_trial)
    {
        ++count;
        cin >> guess;

        if (guess < answer)
        {
            cout << "your assumption is lower than the answer. try again!\n";
            cout << "You have " << number_of_trial - count << " trial(s) left\n";
        }
        else if (guess > answer)
        {
            cout << "number you entered is higher than the answer. try again!\n";
            cout << "You have " << number_of_trial - count << " trial(s) left\n";
        }
        else
        {
            is_correct = true;
            count = number_of_trial;
        }
    }

    if (is_correct)
    {
        cout << "You got it!  answer : " << answer << '\n';
    }
    else
    {
        cout << "~~ game over ~~\n";
    }
}