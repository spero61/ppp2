// Modify the program from exercise 04_19 so that when you enter an integer,
// the program will output all the names with that score or score not found.

#include "std_lib_facilities.h"

int main()
{
    vector<string> names;
    vector<int> scores;
    string name = " ";
    int score = -1;
    bool is_unique = true;

    cout << "Please enter name, score pairs (e.g. Kris 99)\n"
         << "you can terminate input with NoName 0\n";

    while (name != "NoName" || score != 0)
    {
        is_unique = true;
        cin >> name >> score;

        // check that each name is unique
        for (int i = 0; i < names.size(); ++i)
        {
            if (names[i] == name)
                is_unique = false;
        }

        if (is_unique && name != "NoName")
        {
            names.push_back(name);
            scores.push_back(score);
        }
        // terminate with an error message if a name is entered twice
        else
        {
            cout << "Error : name already exist! or You entered NoName\n";
        }
    }

    // write out all the (name, score) pairs, one per line.
    for (int i = 0; i < names.size(); ++i)
    {
        cout << "(name : score) is (" << names[i] << " : " << scores[i] << ")\n";
    }

    cout << '\n';

    int user_input = -1;
    // when a user enter an integer, print the corresponding name or score not found.
    // Terminate the search by enter 0

    cout << "Please enter an integer number that you wish to check the corresponding name\n"
         << "( you can terminate input with a number 999 )\n";
    while (user_input != 999)
    {
        user_input = -1;
        while (user_input < 0)
        {
            cout << "Please enter a positive integer number (enter 999 to exit)\n";
            cin >> user_input;
        }

        bool is_found = false;

        for (int i = 0; i < scores.size(); ++i)
        {
            if (user_input == scores[i])
            {
                cout << names[i] << " : " << scores[i] << '\n';
                is_found = true;
            }
        }

        if (!is_found)
        {
            cout << "score not found\n";
        }
        cout << '\n';
    }
}
