// once upon a time, story-telling exercise
// range of int : –2,147,483,648 ~ 2,147,483,647
// range of double : 1.7E +/- 308 (15 digits)
// check : https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-160
#include "std_lib_facilities.h"

int main()
{

    vector<int> grains_of_rice_int(64);
    int max_square_int = 0;

    for (int i = 0; i < grains_of_rice_int.size(); ++i)
    {
        grains_of_rice_int[i] = pow(2, i);
        if (grains_of_rice_int[i] > 0)
        {
            max_square_int = i;
        }
    }

    vector<double> grains_of_rice_double(64);
    int max_square_double = 0;

    for (int i = 0; i < grains_of_rice_double.size(); ++i)
    {
        grains_of_rice_double[i] = pow(2, i);
        if (grains_of_rice_double[i] > 0)
        {
            max_square_double = i;
        }
    }

    cout << "The largest number of squares for 'int' is " << max_square_int + 1 << " square\n";
    cout << "The largest number of squares for 'double' is " << max_square_double + 1 << " square\n";

    // for (int i = 0; i < grains_of_rice_int.size(); ++i)
    // {
    //     cout << i << '\t' << grains_of_rice_int[i] << '\n';
    // }

    // cout << "\n\n\n";

    // for (int i = 0; i < grains_of_rice_double.size(); ++i)
    // {
    //     cout << i << '\t' << grains_of_rice_double[i] << '\n';
    // }
}