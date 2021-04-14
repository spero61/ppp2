// once upon a time, story-telling exercise
// range of int : –2,147,483,648 ~ 2,147,483,647
// check : https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-160
#include "std_lib_facilities.h"

int main()
{
    vector<int> grains_of_rice(64);
    vector<int> thousand_grains;
    vector<int> million_grains;
    vector<int> billion_grains;

    for (int i = 0; i < grains_of_rice.size(); ++i)
    {
        grains_of_rice[i] = pow(2, i);
        if ((grains_of_rice[i] / 1000) > 0)
        {
            thousand_grains.push_back(i);
        }
        if ((grains_of_rice[i] / 1000000) > 0)
        {
            million_grains.push_back(i);
        }
        if ((grains_of_rice[i] / 1000000000) > 0)
        {
            billion_grains.push_back(i);
        }
    }

    cout << thousand_grains[0] << "\tthousand\n";
    cout << million_grains[0] << "\tmillion\n";
    cout << billion_grains[0] << "\tbillion\n";

    // for (int x : grains_of_rice)
    // {
    //     cout << x << '\n';
    // }
}