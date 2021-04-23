// a program that reads digits and composes them into integers

#include "std_lib_facilities.h"

// to handle numbers with one, two, three, or four digits.
bool is_validate(string user_input)
{
    if (user_input.size() <= 4)
    {
        for (int i = 0; i < user_input.size(); ++i)
        {
            // ASCII code range for '0' to '9' is 48 to 57
            // when user_input contains not a number return false
            if (user_input[i] < 48 || 57 < user_input[i])
            {
                return false;
            }
        }
        // user_input is one, two, three, or four digits
        return true;
    }
    // if user_input is more than four digits (or maybe letters)
    return false;
}

int main()
{
    string user_input = "";
    int thousands;
    int hundreds;
    int tens;
    int digits;
    bool validated_input = false;

    while (true)
    {
        cout << "please enter one, two, three, or four digits.\n";
        cin >> user_input;

        if (is_validate(user_input))
            break;
    }

    switch (user_input.size())
    {
    case 1:
        digits = user_input[0] - '0';
        cout << user_input << " is " << digits << " one(s)";
        break;
    case 2:
        tens = user_input[0] - '0';
        digits = user_input[1] - '0';
        cout << user_input << " is " << tens << " ten(s) and " << digits << " one(s)";
        break;
    case 3:
        hundreds = user_input[0] - '0';
        tens = user_input[1] - '0';
        digits = user_input[2] - '0';
        cout << user_input << " is " << hundreds << " hundred(s) " << tens << " ten(s) and " << digits << " one(s)";
        break;
    case 4:
        thousands = user_input[0] - '0';
        hundreds = user_input[1] - '0';
        tens = user_input[2] - '0';
        digits = user_input[3] - '0';
        cout << user_input << " is " << thousands << " thousand " << hundreds << " hundred(s) " << tens << " ten(s) and " << digits << " one(s)";
        break;
    default:
        cerr << "this can't be possible if the input has validated properly.\n";
        break;
    }
}