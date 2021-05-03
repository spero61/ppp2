// Q. Improve print_until_s() from §8.5.2.
// A. Changed an argument 'vector<string> v' to 'const vector<string> &v'

// Q. Test it. What makes a good set of test cases? Give reasons.
// A. To see the improvement, vector<string> v should constain a number of string elements.

// Then, write a print_until_ss() that prints until it sees a second occurrence of its quit argument.

#include "std_lib_facilities.h"

void print_until_s(const vector<string> &v, string quit); // pass-by-const-reference
void print_until_ss(const vector<string> &v, string quit);

int main()
{
    try
    {
        vector<string> words{"awesome", "superb", "outstanding", "saraba", "excellent", "brilliant", "marvelous", "saraba", "gorgeous", "magnificent"};
        cout << "~ print_until_s ~\n";
        print_until_s(words, "saraba");

        cout << '\n';

        cout << "~ print_until_ss ~\n";
        print_until_ss(words, "saraba");

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

void print_until_s(const vector<string> &v, string quit)
{
    for (string s : v)
    {
        if (s == quit)
            return;
        cout << s << '\n';
    }
}

void print_until_ss(const vector<string> &v, string quit)
{
    int count{0};

    for (string s : v)
    {
        if (s == quit)
            ++count;
        if (count == 2)
            return;
        cout << s << '\n';
    }
}