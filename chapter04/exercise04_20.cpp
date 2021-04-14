// Modify the program from exercise 04_19 so that when you enter a name,
// the program will output the corresponding score or name not found.

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

    string user_input = " ";
    // when a user enter a name, print the corresponding score or name not found.
    // Terminate the search by enter NoName

    while (user_input != "NoName")
    {

        cout << "Please enter a name that you wish to check the corresponding score\n"
             << "( you can terminate input with NoName )\n";
        cin >> user_input;

        bool is_found = false;

        for (int i = 0; i < names.size(); ++i)
        {
            if (user_input == names[i])
            {
                cout << names[i] << " : " << scores[i] << '\n';
                is_found = true;
            }
        }

        if (!is_found && name != "NoName")
        {
            cout << "name not found\n";
        }
        cout << '\n';
    }
}
