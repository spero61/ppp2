// implement the map  (in Python it is called dictionary)
// Terminate input with NoName 0

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
        cin >> name >> score;
        // check that each name is unique
        for (int i = 0; i < names.size(); ++i)
        {
            if (names[i] == name)
                is_unique = false;
        }

        if (is_unique && (name != "NoName" && score != 0))
        {
            names.push_back(name);
            scores.push_back(score);
        }
        // terminate with an error message if a name is entered twice
        else if (name != "NoName" && score != 0)
        {
            cout << "Error : name already exist! \n";
        }

        is_unique = true;
    }

    // write out all the (name, score) pairs, one per line.
    for (int i = 0; i < names.size(); ++i)
    {
        cout << "(name : score) is (" << names[i] << " : " << scores[i] << ")\n";
    }
}