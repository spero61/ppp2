// a program that converts a digit to its corresponding spelled-out value
#include "std_lib_facilities.h"

int main()
{
    vector<string> digit_words = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int user_input = -1;

    while (user_input < 0 || user_input > 9)
    {
        cout << "Please enter a digit number (from 0 to 9)\n";
        cin >> user_input;
    }

    cout << digit_words[user_input] << '\n';
}