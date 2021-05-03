// Then, do that exercise08_07 again but allowing an arbitrary number of names.

#include "std_lib_facilities.h"

void sort(vector<string> &name, vector<double> &age);
void print(const vector<string> &name, const vector<double> &age);

int main()
{
    try
    {
        int number_of_people{0};
        cout << "how many people do you want to handle? \n> ";
        while (number_of_people < 1)
        {
            cin >> number_of_people;
            if (number_of_people < 1)
                cout << "Dude, Be Serious. Try again.\n> ";
        }

        vector<string> name;
        for (int i = 0; i < number_of_people; ++i)
        {
            string name_val;
            cout << "name[" + to_string(i) + "]: ";
            cin >> name_val;
            name.push_back(name_val);
        }

        vector<double> age;
        for (int i = 0; i < number_of_people; ++i)
        {
            double age_val;
            cout << "age[" + to_string(i) + "]: ";
            cin >> age_val;
            age.push_back(age_val);
        }

        cout << '\n';
        print(name, age);

        sort(name, age);

        cout << '\n';
        print(name, age);
        return 0;
    }
    catch (exception &e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cerr << "...Exception\n";
        return 2;
    }

}

void sort(vector<string> &name, vector<double> &age)
{
    // take a copy of name for adding an index number to its end of the string
    vector<string> name_copy = name;
    for (int i = 0; i < name_copy.size(); ++i)
        name_copy[i] += to_string(i);

    // perform sort name as well as name_copy
    sort(name.begin(), name.end());
    sort(name_copy.begin(), name_copy.end());

    // create and set sorted_index to figure out sorted order of the index
    vector<int> sorted_index;
    for (int i = 0; i < name_copy.size(); ++i)
    {
        // last_index to get an index from last char of name_copy[i]
        int last_index = name_copy[i].size() - 1;

        // subtract '0' to convert char to int
        int index = name_copy[i][last_index] - '0';

        sorted_index.push_back(index);
    }

    // make a copy of age using sorted_index to match in correct order
    vector<double> age_copy;
    for (int i = 0; i < sorted_index.size(); ++i)
    {
        int index = sorted_index[i];
        age_copy.push_back(age[index]);
    }
    // substitute age_copy for age
    age = age_copy;
}

void print(const vector<string> &name, const vector<double> &age)
{
    for (int i = 0; i < name.size(); ++i)
        cout << name[i] << ": " << age[i] << '\n';
}
