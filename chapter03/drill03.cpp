#include "std_lib_facilities.h"

int main()
{
    string first_name;
    string friend_name;
    char friend_gender = 0;
    int age;

    cout << "Please enter your first name (followed by 'enter'): \n";
    cin >> first_name;
    cout << "Dear " << first_name << ",\n";
    cout << "\nMoi, mita kuuluu?\nOlen ihan hyvaa.\n";

    cout << "Please enter your friend's name (followed by 'enter'): \n";
    cin >> friend_name;
    cout << "Have you seen " << friend_name << " lately?\n";

    cout << "Please enter your friend's gender in one character\n(e.g. f for female, m for male, n for non-binary): \n";
    cin >> friend_gender;

    if (friend_gender == 'm')
        cout << "If you see " << friend_name << " please ask him to call me.\n";
    else if (friend_gender == 'f')
        cout << "If you see " << friend_name << " please ask her to call me.\n";
    else
        cout << "If you see " << friend_name << " please ask " << friend_name << " to call me.\n";

    cout << "Please enter your recipient's age (followed by 'enter'): \n";
    cin >> age;
    if (age <= 0 || age >= 110)
        simple_error("you're kidding!");
    else
    {
        cout << "I hear you just had a birthday and you are " << age << " years old.\n";
        if (age < 12)
            cout << "Next year you will be " << age + 1 << '\n';
        else if (age == 17)
            cout << "Next year you will be able to vote.\n";
        else if (age > 70)
            cout << "I hope you are enjoying retirement.\n";
    }
    cout << "\n\nYours sincerely, " << first_name << '\n';
}