// modified version of the "mini calculator from exercise 04_05"
#include "std_lib_facilities.h"

int word_to_digit(string word);

int main()
{
    double val1 = -1;
    double val2 = -1;
    string str1 = " ";
    string str2 = " ";
    int selection = 0;
    char op = ' ';

    while (selection != 1 && selection != 2)
    {
        cout << "If you would like to calulate in digit number press 1 followed by enter.\n"
             << "Alternatively if you prefer type the number in spelled word, press 2 instead.\n";
        cin >> selection;
    }

    // calculate in digit number
    if (selection == 1)
    {
        while ((val1 < 0 || val1 > 9) || (val2 < 0 || val2 > 9))
        {
            cout << "Enter two single digit operands followed by an operator (e.g. +, -, *, /)\n";
            cin >> val1 >> val2 >> op;
        }
    }

    //calculate in spelled-out number
    else
    {

        while ((val1 < 0 || val1 > 9) || (val2 < 0 || val2 > 9))
        {
            cout << "Enter two operands in English followed by an operator (e.g. +, -, *, /)\n";
            cin >> str1 >> str2 >> op;
            val1 = word_to_digit(str1);
            val2 = word_to_digit(str2);
        }
    }

    switch (op)
    {
    case '+':
        cout << "The sum of " << val1 << " and " << val2 << " is " << val1 + val2 << '\n';
        break;
    case '-':
        cout << val1 << " minus " << val2 << " is " << val1 - val2 << '\n';
        break;
    case '*':
        cout << "The product of " << val1 << " and " << val2 << " is " << val1 * val2 << '\n';
        break;
    case '/':
        cout << val1 << " divided by " << val2 << " is " << val1 / val2 << '\n';
        break;
    default:
        cout << "You should provide a valid operator. ( +, -, *, or / )\n";
    }
}

int word_to_digit(string word)
{
    int digit = -1;
    vector<string> digit_words = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (int i = 0; i < digit_words.size(); ++i)
    {
        if (digit_words[i] == word)
            digit = i;
    }
    return digit;
}
