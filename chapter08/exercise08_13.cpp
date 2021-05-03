// Write a function that takes a vector<string> argument and
// returns a vector<int>containing the number of characters in each string.
// Also find the longest and the shortest string and the lexicographically first and last string.

// Q. How many separate functions would you use for these tasks? Why?
// three functions, as below.
// A number_of_chars() function is necessary as it is required in the exercise.
// The other two functions are needed to separate the chunk of logic.
// Finding the shortest and longest string shares the code,
// as finding lexicographically first and last string does.

#include "std_lib_facilities.h"

vector<int> number_of_chars(const vector<string> &v);
string find_by_length(const vector<string> &v, char operation);         // operation : 's' for shortest, 'l' for longest
string find_lexicographically(const vector<string> &v, char operation); // operation : 'f' for first, 'l' for last

int main()
{
    try
    {
        vector<string> words{"awesome", "nice", "superb", "outstanding", "excellent", "brilliant", "marvelous", "gorgeous", "magnificent"};
        cout << "~ number of characters ~\n";

        vector<int> nums;
        nums = number_of_chars(words);

        for (int x : nums)
            cout << x << ' ';
        cout << "\n\n";

        cout << "shortest string: " << find_by_length(words, 's') << '\n'; // find the shortest string
        cout << "longest string: " << find_by_length(words, 'l') << '\n';  // find the longest string

        cout << "first string: " << find_lexicographically(words, 'f') << '\n'; // find the lexicographically first
        cout << "last string: " << find_lexicographically(words, 'l') << '\n';  // find the lexicographically last

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

vector<int> number_of_chars(const vector<string> &v)
{
    vector<int> tmp;
    for (int i = 0; i < v.size(); ++i)
    {
        tmp.push_back(v[i].size());
    }

    return tmp;
}

string find_by_length(const vector<string> &v, char operation)
{

    vector<int> tmp = number_of_chars(v);
    int shortest_index = tmp[0];
    int longest_index = tmp[tmp.size() - 1];

    switch (operation)
    {
    case 's':
        for (string x : v)
        {
            if (x.size() == shortest_index)
            {
                return x;
            }
        }

    case 'l':
        for (string x : v)
        {
            if (x.size() == longest_index)
            {
                return x;
            }
        }

    default:
        error("provide valid operation: 's' for shortest, 'l' for longest");
        return "3";
    }
}

string find_lexicographically(const vector<string> &v, char operation)
{
    // take a copy of v
    vector<string> tmp = v;

    sort(tmp);

    switch (operation)
    {
    case 'f':
        return tmp[0];

    case 'l':
        return tmp[tmp.size() - 1];

    default:
        error("provide valid operation: 'f' for first, 'l' for last");
        return "4";
    }
}
