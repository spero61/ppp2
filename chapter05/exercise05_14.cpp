// Read (day-of-the-week, value) pairs from standard input.
// e.g., Tuesday 23 Friday 56 Tuesday -3 Thursday 99
#include "std_lib_facilities.h"

int main()
{

    vector<string> week_days;
    vector<int> week_values;

    vector<string> day_of_the_week = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    vector<string> day_of_the_week_lower = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};
    vector<string> day_of_the_week_short = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    string day_name = "";
    int day_value = 0;
    int sum = 0;
    bool is_correct_name = false;
    int rejected_count = 0;

    cout << "Collect all the values for each day of the week \n"
         << "e.g., Tuesday 23 Friday 56 Tuesday -3 Thursday 99\n\n";

    cout << "Please enter day of the week and its value separated by space\n"
         << "you can terminate the loop by giving NoName and its value to 0\n\n";

    while (day_name != "NoName" || day_value != 0)
    {
        is_correct_name = false;
        // loop if the name of the day is not acceptable
        while (!is_correct_name)
        {
            cout << "Please next values : (to exit, type : NoName 0 )\n";
            cin >> day_name >> day_value;
            // Ignore illegal days of the week, such as Funday,
            // but accept common synonyms such as Mon and monday.
            for (string s : day_of_the_week)
            {
                if (s == day_name)
                    is_correct_name = true;
            }
            for (string s : day_of_the_week_lower)
            {
                if (s == day_name)
                    is_correct_name = true;
            }
            for (string s : day_of_the_week_short)
            {
                if (s == day_name)
                    is_correct_name = true;
            }

            if (day_name == "NoName" && day_value == 0)
            {
                is_correct_name = true;
            }
            if (!is_correct_name)
            {
                cerr << "error : name of the day is invalid."
                     << "Please provide acceptable name e.g., Sunday, Sun, or sunday\n\n";
                ++rejected_count;
            }
        }

        // if the name is acceptable put name and its value to the respective vector
        if (day_name != "NoName")
        {
            week_days.push_back(day_name);
            week_values.push_back(day_value);
            sum += day_value;
        }
    }

    cout << "\n~~ Result ~~\n";
    // write out the values of the seven day-of-the-week vectors
    for (int i = 0; i < week_days.size(); ++i)
    {
        cout << week_days[i] << " : " << week_values[i] << '\n';
    }
    cout << '\n';
    // print out the sum of the values in each vector
    cout
        << "sum : " << sum << '\n';
    // write out the number of rejected values.
    cout << "rejected count : " << rejected_count << '\n';
}