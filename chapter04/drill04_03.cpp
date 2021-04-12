// ch4 drill from number 9 to the end
#include "std_lib_facilities.h"

int main()
{
    double val = 0;

    // HUOM! 1/100 is 0 not 0.01  you should put 1.0 / 100 or 1 / 100.0
    constexpr double cm_per_m = 0.01;
    constexpr double in_per_m = 2.54 * cm_per_m;
    constexpr double ft_per_m = 12 * in_per_m;
    string unit = " ";
    double sum = 0;
    int count = 0;

    vector<double> vals;
    cout << cm_per_m << '\t' << in_per_m << '\t' << ft_per_m << '\n';
    cout << "Please enter a number and a unit(cm, m, in, or ft).\n";

    while (cin >> val >> unit)
    {
        // if the unit indicator is properly provided
        if (unit == "cm" || unit == "m" || unit == "in" || unit == "ft")
        {
            // convert values in meter using constant expressions
            if (unit == "cm")
            {
                val *= cm_per_m;
                // cout << val << '\n'; // 왜 이거 0이 나옴??
            }
            else if (unit == "in")
            {
                val *= in_per_m;
                // cout << val << '\n';
            }
            else if (unit == "ft")
            {
                val *= ft_per_m;
                // cout << val << '\n';
            }

            vals.push_back(val);

            sum += val;
            ++count;
            // keep track of the sum of values entered
        }

        // exclude illegal unit input
        else
        {
            cout << "illegal unit indicator. Try again.\n";
        }
    }

    // sorting elements of vector vals in ascending order by harnessing the standard library
    sort(vals);

    // values from the user in provided order
    cout << "all the values entered in meter: \n";
    for (double val : vals)
    {
        cout << val << " m\n";
    }

    // print the results
    cout << "In total " << count << " values have been entered.\n"
         << "the smallest so far in meter: " << vals[0] << " m\n"
         << "the largest so far in meter: " << vals[vals.size() - 1] << " m\n"
         << "sum of values entered : " << sum << " m\n";
}