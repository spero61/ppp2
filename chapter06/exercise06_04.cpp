// Rework exercise 19 in Chapter 4
// to use a vector<Name_value> instead of two vectors

#include "std_lib_facilities.h"

class Name_value
{
public:
    string name;
    int score;

private:
    bool is_unique(string name);
};

bool Name_value::is_unique(string name)
{

    return false;
}

int main()
{
    string name = " ";
    int score = -1;
    Name_value nv;

    cout << "Please enter name, score pairs (e.g. Kris 99)\n"
         << "you can terminate input with NoName 0\n";
}